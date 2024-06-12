#include "../../lib/controladores/ControladorRender.h"

color COLOR_NEGRO( 0., 0., 0. );
color COLOR_BLANCO( 1., 1., 1. );
color COLOR_GRIS( .3, .3, .3 );
color COLOR_ESCENA_AMBIENTE = COLOR_GRIS;

ControladorRender* ControladorRender::instancia = nullptr;

ControladorRender::ControladorRender() {
	window = nullptr;
	renderer = nullptr;
	texture = nullptr;
	SDL_pixeles = nullptr;
}

ControladorRender::~ControladorRender() {
	if (SDL_pixeles != nullptr) {
		delete[] SDL_pixeles;
	}
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
	}
	if (window != nullptr) {
		SDL_DestroyWindow(window);
	}
}

ControladorRender* ControladorRender::getInstance() {
	if (instancia == nullptr)
		instancia = new ControladorRender();
	return instancia;
}

vector_3 direccion_reflejada(vector_3 L, vector_3 N) {
	return L - N * 2 * (L.producto_interno(N));
}

color get_componente_ambiente(objeto* objeto) {
	// I_a_alpha * k_a * O_d_alpha
	return
		COLOR_ESCENA_AMBIENTE * // I_a_alpha
		objeto->get_color_difuso() * //O_d_alpha
		objeto->get_coeficiente_ambiente(); //k_a
}

color get_componente_difuso(objeto* objeto, vector_3 N, vector_3 L_i) {
	//k_d * O_d_alpha * (N * L_i)
	return 
		objeto->get_color_difuso() * // O_d_alpha
		objeto->get_coeficiente_difuso() * // k_d
		N.producto_interno(L_i); // (N * L_i)
}

color get_componente_especular(objeto* objeto, vector_3 V, vector_3 N, vector_3 L) {
	// k_s * O_s_alpha * (R_i * V)^n
	return
		objeto->get_color_especular() * //O_s_alpha
		objeto->get_coeficiente_especular() * //k_s
		pow(direccion_reflejada(L, N).producto_interno(V), EXPONENTE_ESPECULAR); // (R_i * V)^n
}

color get_componente_luz(objeto* objeto_in, rayo Rayo, vector_3 punto_interseca, vector_3 normal, tipo_imagen tipo) {
	// Sumatoria de difuso y phong multiplicado por coeficientes de luz directa

	// Para calcular el color que obtiene una sombra al atravsar un objeto transparente
	// No es parte de la ecuacion original
	objeto* objeto_color_sombra;
	vector_3 punto_color_sombra;

	color color_resultado = COLOR_NEGRO;

	vector<luz*> luces = ControladorEscena::getInstance()->get_luces();

	for (size_t i = 0; i < luces.size(); i++) {

		rayo rayo_sombra = rayo(punto_interseca + (normal * EPSILON),
			luces[i]->get_posicion() - (punto_interseca + (normal * EPSILON)));
		
		if (rayo_sombra.get_direccion().producto_interno(normal) > 0) {

			float distancia_de_la_luz = (luces[i]->get_posicion() - punto_interseca).norma();

			// f_att_i
			float atenuacion = min(1 / (C1 + C2 * distancia_de_la_luz + C3 * distancia_de_la_luz * distancia_de_la_luz), 1.f);

			// S_i
			float sombra = ControladorEscena::getInstance()->obtener_cantidad_de_luz_bloqueada(rayo_sombra, luces[i]->get_posicion());

			color componente_difuso = COLOR_NEGRO;
			if (tipo == SIN_ANTIALIASING || tipo == CON_ANTIALIASING || tipo == COLOR_DIFUSO) {
				// k_d * O_d_alpha * (N * L_i)
				componente_difuso = get_componente_difuso(objeto_in, normal, rayo_sombra.get_direccion());
			}

			color componente_especular = COLOR_NEGRO;
			if (tipo == SIN_ANTIALIASING || tipo == CON_ANTIALIASING || tipo == COLOR_ESPECULAR) {
				// k_s * O_s_alpha * (R_i * V)^n
				componente_especular = get_componente_especular(objeto_in, -Rayo.get_direccion(), normal, rayo_sombra.get_direccion());
			}

			color color_sombra = COLOR_BLANCO;
			if (ControladorEscena::getInstance()->obtener_objeto_intersecado_mas_cercano(rayo_sombra, objeto_color_sombra, punto_color_sombra) &&
				(punto_color_sombra - rayo_sombra.get_origen()).norma() < distancia_de_la_luz &&
				objeto_color_sombra->get_coeficiente_transmicion() > 0) {
				color_sombra = objeto_color_sombra->get_color_difuso() * objeto_color_sombra->get_coeficiente_difuso();
			}

			color_resultado = color_resultado +
				luces[i]->get_color() * // I_p_alpha
				sombra * atenuacion *   // S_i * f_att_i
				color_sombra * // color_sombra no es parte de la ecuacion original, se agrega para dar mas fidelidad
				(componente_difuso + componente_especular);
		}
	}

	return color_resultado;
}

color ControladorRender::get_componente_reflectivo(objeto* objeto_in, rayo I, vector_3 punto_interseca, vector_3 N, int profundidad, tipo_imagen tipo) {
	rayo rayo_r = rayo(punto_interseca + (N * EPSILON),
		direccion_reflejada(I.get_direccion(), N)
	);
	return
		traza_rr(rayo_r, profundidad + 1, tipo) *
		objeto_in->get_coeficiente_especular();
}

color ControladorRender::get_componente_refractivo(objeto* objeto_in, rayo I, vector_3 punto_interseca, vector_3 N, int profundidad, tipo_imagen tipo) {
	color refractive_color = COLOR_NEGRO;
	vector_3 direccion_refract;
	bool sigue;

	float cosi = min(1.f, max(-1.f, I.get_direccion().producto_interno(N)));
	float etai = COEFICIENTE_REFRACCION_VACIO; // Medio antes de la refraccion
	float etat = COEFICIENTE_REFRACCION_VACIO; // Medio despues de la refraccion

	if (cosi <= 0) {//El rayo esta afuera
		cosi = -cosi;
		if (I.esVaciaPilaRefraccion()) {
			etai = COEFICIENTE_REFRACCION_VACIO;
		}
		else {
			etai = I.obtenerCoefPilaRefrccion();
		}
		etat = objeto_in->get_coeficiente_refraccion();
		I.apilarCoefRefraccion(etat);
	}
	else {//El rayo esta dentro
		N = -N;
		etai = objeto_in->get_coeficiente_refraccion();
		if (I.esVaciaPilaRefraccion()) {
			etat = COEFICIENTE_REFRACCION_VACIO;
		}
		else {
			I.desapilarCoefRefraccion();
			if (I.esVaciaPilaRefraccion()) {
				etat = COEFICIENTE_REFRACCION_VACIO;
			}
			else {
				etat = I.obtenerCoefPilaRefrccion();
			}
		}
	}

	float eta = etai / etat;
	float cost = 1.f - pow(eta, 2.f) * (1.f - pow(cosi, 2.f));
	if (cost >= 0.f) {
		direccion_refract = (I.get_direccion() * eta) + (N * (eta * cosi - sqrtf(cost)));
		sigue = true;
	}
	else {
		sigue = false;
	}

	if (sigue) {
		rayo rayo_aux = rayo(punto_interseca - (N * EPSILON),
			direccion_refract);
		refractive_color = traza_rr(rayo_aux, profundidad + 1, tipo) * objeto_in->get_coeficiente_transmicion();
	}

	return refractive_color;
}

color ControladorRender::sombra_rr(objeto* objeto, rayo Rayo, vector_3 punto_interseca, vector_3 normal, int profundidad, tipo_imagen tipo) {

	color color_resultado = COLOR_NEGRO;

	//color_resultado = termino del ambiente;
	if (tipo == SIN_ANTIALIASING || tipo == CON_ANTIALIASING || tipo == COLOR_AMBIENTE)
		color_resultado = get_componente_ambiente(objeto);

	//for (cada luz)
	if (tipo == SIN_ANTIALIASING || tipo == CON_ANTIALIASING || tipo == COLOR_DIFUSO || tipo == COLOR_ESPECULAR)
		color_resultado = color_resultado + get_componente_luz(objeto, Rayo, punto_interseca, normal, tipo);
	
	if ((tipo == SIN_ANTIALIASING || tipo == CON_ANTIALIASING) && profundidad < PROFUNDIDAD_MAXIMA) {
		//if (objeto es reflejante)
		if (objeto->get_es_reflectante()) {
			color_resultado = color_resultado + get_componente_reflectivo(objeto, Rayo, punto_interseca, normal, profundidad, tipo);
		}
		//if (objeto es transparente)
		if (objeto->get_coeficiente_transmicion() > 0) {
			color_resultado = color_resultado + get_componente_refractivo(objeto, Rayo, punto_interseca, normal, profundidad, tipo);
		}
	}

	return color_resultado;
}

color ControladorRender::traza_rr(rayo Rayo, int profundidad, tipo_imagen tipo) {
	objeto* objeto;
	vector_3 punto_interseca;

	if (ControladorEscena::getInstance()->obtener_objeto_intersecado_mas_cercano(Rayo, objeto, punto_interseca)) {
		vector_3 normal = objeto->normal(punto_interseca, Rayo);
		return sombra_rr(objeto, Rayo, punto_interseca, normal, profundidad, tipo);
	}
	else {
		return COLOR_NEGRO;
	}
}

color traza_rr_por_coeficiente(rayo Rayo, tipo_imagen tipo) {
	color color_resultado = COLOR_NEGRO;
	objeto* objeto;
	vector_3 punto_interseca;

	float coeficiente = 0.f;

	if (ControladorEscena::getInstance()->obtener_objeto_intersecado_mas_cercano(Rayo, objeto, punto_interseca)) {
		switch (tipo){
			case COEF_AMBIENTAL:
				coeficiente = objeto->get_coeficiente_ambiente();
				break;
			case COEF_DIFUSO:
				coeficiente = objeto->get_coeficiente_difuso();
				break;
			case COEF_ESPECULAR:
				coeficiente = objeto->get_coeficiente_especular();
				break;
			case COEF_REFLEXIVO:
				coeficiente = objeto->get_es_reflectante();
				break;
			case COEF_TRANSMISION:
				coeficiente = objeto->get_coeficiente_transmicion();
				break;
		}
		color_resultado = COLOR_BLANCO * coeficiente;
	}

	return color_resultado;
}

imagen* ControladorRender::whitted_ray_tracing(tipo_imagen tipo) {
	camara* camara = ControladorEscena::getInstance()->get_camara();
	vector_3 origen = camara->getPosicionCamara(); //ojo de la camara
	vector_3 plano = camara->getPosicionImagen(); // direccion de la camara

	int imagen_width = camara->get_imagen_width();
	int imagen_height = camara->get_imagen_height();

	// Mostrar como se genera la imagen (solo en caso de imagen principal sin antialiasing)
	if (tipo == SIN_ANTIALIASING) {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
			exit(1);
		}

		window = SDL_CreateWindow(
			"Imagen sin antialiasing",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			imagen_width,
			imagen_height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
		);

		if (!window) {
			std::cerr << "Error al crear la ventana: " << SDL_GetError() << std::endl;
			SDL_Quit();
			exit(1);
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (!renderer) {
			std::cerr << "Error al crear el renderer: " << SDL_GetError() << std::endl;
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(1);
		}

		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, imagen_width, imagen_height);
		if (!texture) {
			std::cerr << "Error al crear la textura: " << SDL_GetError() << std::endl;
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(1);
		}

		SDL_pixeles = new Uint32[imagen_width * imagen_height];
		for (int y = 0; y < imagen_height; ++y) {
			for (int x = 0; x < imagen_width; ++x) {
				SDL_pixeles[y * imagen_width + x] = 0;
			}
		}

		SDL_UpdateTexture(texture, nullptr, SDL_pixeles, imagen_width * sizeof(Uint32));
	}

	imagen* img_resultado = new imagen(imagen_width, imagen_height);

	#pragma omp parallel for
	for (int i = 0; i < imagen_height; i++) {
		for (int j = 0; j < imagen_width; j++) {
			rayo Rayo = rayo(origen,
				vector_3(float(j - imagen_width / 2), float(i - imagen_height / 2), plano.get_z()) - origen);
			
			if (tipo == COEF_AMBIENTAL || tipo == COEF_DIFUSO || tipo == COEF_ESPECULAR || tipo == COEF_REFLEXIVO || tipo == COEF_TRANSMISION) {
				img_resultado->set_pixel(i, j, traza_rr_por_coeficiente(Rayo, tipo));
			} else {
				img_resultado->set_pixel(i, j, traza_rr(Rayo, 1, tipo));

				if (tipo == CON_ANTIALIASING) {
					rayo rayo_antiasliasing_1 = rayo(origen,
						vector_3(float(j - imagen_width / 2 + DESPLAZAMIENTO_ANTIALIASING), float(i - imagen_height / 2 + DESPLAZAMIENTO_ANTIALIASING), plano.get_z()) - origen);
					rayo rayo_antiasliasing_2 = rayo(origen,
						vector_3(float(j - imagen_width / 2 + DESPLAZAMIENTO_ANTIALIASING), float(i - imagen_height / 2 - DESPLAZAMIENTO_ANTIALIASING), plano.get_z()) - origen);
					rayo rayo_antiasliasing_3 = rayo(origen,
						vector_3(float(j - imagen_width / 2 - DESPLAZAMIENTO_ANTIALIASING), float(i - imagen_height / 2 + DESPLAZAMIENTO_ANTIALIASING), plano.get_z()) - origen);
					rayo rayo_antiasliasing_4 = rayo(origen,
						vector_3(float(j - imagen_width / 2 - DESPLAZAMIENTO_ANTIALIASING), float(i - imagen_height / 2 - DESPLAZAMIENTO_ANTIALIASING), plano.get_z()) - origen);

					color AA1 = traza_rr(rayo_antiasliasing_1, 1, tipo);
					color AA2 = traza_rr(rayo_antiasliasing_2, 1, tipo);
					color AA3 = traza_rr(rayo_antiasliasing_3, 1, tipo);
					color AA4 = traza_rr(rayo_antiasliasing_4, 1, tipo);

					img_resultado->set_pixel(i, j, (img_resultado->get_pixeles()[i][j] + AA1 + AA2 + AA3 + AA4) / 5.0f);
				}
			}

		}

		// Imprime en pantalla el contenido generado linea por linea
		if (tipo == SIN_ANTIALIASING){
			for (int x = 0; x < imagen_width; ++x) {
				Uint8 r = Uint8(img_resultado->get_pixeles()[i][x].get_r() * 255);
				Uint8 g = Uint8(img_resultado->get_pixeles()[i][x].get_g() * 255);
				Uint8 b = Uint8(img_resultado->get_pixeles()[i][x].get_b() * 255);
				Uint8 a = 255;

				SDL_pixeles[(imagen_height - i - 1) * imagen_width + x] = (a << 24) | (r << 16) | (g << 8) | b;
			}
			SDL_UpdateTexture(texture, nullptr, SDL_pixeles, imagen_width * sizeof(Uint32));
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, texture, nullptr, nullptr);
			SDL_RenderPresent(renderer);
		}
	}

	if (tipo == SIN_ANTIALIASING) {
		SDL_Quit();
	}
	
	return img_resultado;
}