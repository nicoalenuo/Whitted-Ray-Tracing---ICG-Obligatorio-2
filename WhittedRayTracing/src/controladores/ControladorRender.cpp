#include "../../lib/controladores/ControladorRender.h"

const color negro = { 0., 0., 0., 1. };
const color blanco = { 1., 1., 1., 1. };
const color gris = { 0.3, 0.3, 0.3, 1. }; //color luz ambiental?

color aux_color_x_escalar(color i, float k) {
	return { i.r * k,  i.g * k, i.g * k, i.a };
}

color aux_color_x_color(color ik, color o) {
	return { ik.r * o.r, ik.g * o.g, ik.b * o.b, ik.a * o.a };
}

color aux_color_a_color(color ik, color o) {
	return { ik.r + o.r, ik.g + o.g, ik.b + o.b, ik.a * o.a };
}


ControladorRender* ControladorRender::instancia = nullptr;

ControladorRender::ControladorRender() {

}

ControladorRender::~ControladorRender() {

}

ControladorRender* ControladorRender::getInstance() {
	if (instancia == nullptr)
		instancia = new ControladorRender();
	return instancia;
}

color get_componente_ambiente(objeto* objeto) {
	return aux_color_x_color(aux_color_x_escalar(gris, objeto->get_coeficiente_ambiente()), objeto->get_color_difuso());
}

color get_componente_difuso(objeto* objeto, vector_3 N, vector_3 L_i) {
	//k_d * O_d_alpha * (N * L_i)
	return aux_color_x_escalar(
		aux_color_x_escalar(
			objeto->get_color_difuso(),      // O_d_alpha
			objeto->get_coeficiente_difuso() // k_d
		),
		max(0.f, N.producto_interno(L_i)));
}

vector_3 direccion_reflejada(vector_3 I, vector_3 N) {
	return I - N * 2  * (I.producto_interno(N));
}

color get_componente_especular(objeto* objeto, vector_3 V, vector_3 N, vector_3 L) {
	return objeto->get_color_especular();
	return aux_color_x_escalar(
		aux_color_x_escalar(
			objeto->get_color_especular(),      //O_s_alpha
			objeto->get_coeficiente_especular() //k_s
		),
		pow(direccion_reflejada(L, N).producto_interno(V), EXPONENTE_ESPECULAR) // (R_i * V)^n
	);
}

color get_componente_luz(objeto* objeto, rayo Rayo, vector_3 punto_interseca, vector_3 normal) {
	float distancia_de_la_luz = 0;
	color color_especular = negro;
	color color_especular_aux;
	float atenuacion = 0;
	float sombra = 0;
	color componente_difuso;
	color componente_especular;

	vector<luz*> luces = ControladorEscena::getInstance()->get_luces();

	for (size_t i = 0; i < luces.size(); i++) {

		rayo rayo_sombra = rayo(punto_interseca + normal * EPSILON,
			luces[i]->get_posicion() - (punto_interseca + normal * EPSILON)); //los algoritmos que se toman como base
																		      //solo corrigen el punto de origen no la direcion
																			  //habria que revisar
		
		if (rayo_sombra.get_direccion().producto_interno(normal) > 0) {

			distancia_de_la_luz = (luces[i]->get_posicion() - punto_interseca).norma();

			//f_att_i
			atenuacion = min(1 / (distancia_de_la_luz * distancia_de_la_luz), 1.f);

			// Para calcular S_i usar
			sombra = ControladorEscena::getInstance()->obtener_cantidad_de_luz_bloqueada(rayo_sombra, luces[i]->get_posicion());

			//k_d * O_d_alpha * (N * L_i)
			componente_difuso = get_componente_difuso(objeto, normal, rayo_sombra.get_direccion());
			
			//ks * O_s_alpha * (R_i * V)^n
			componente_especular = get_componente_especular(objeto, -Rayo.get_direccion(), normal, -rayo_sombra.get_direccion());

			color_especular_aux = aux_color_x_color(
				aux_color_x_escalar(
					luces[i]->get_color(), //I_p_alpha
					sombra * atenuacion    //S_i * f_att_i
				),
				aux_color_a_color(componente_difuso, componente_especular)
			);	
		}
		color_especular = aux_color_a_color(color_especular, color_especular_aux);
	}

	return color_especular;
}

color ControladorRender::sombra_rr(objeto* objeto, rayo Rayo, vector_3 punto_interseca, vector_3 normal, int profundidad) {
	
	//color = término del ambiente;
	color color = get_componente_ambiente(objeto);

	//for (cada luz)
	color = aux_color_a_color(color, get_componente_luz(objeto, Rayo, punto_interseca, normal));

	
	if (profundidad < PROFUNDIDAD_MAXIMA) {
		//if (objeto es reflejante)
		if (objeto->get_material() == REFLECTANTE) {
			
		}
		//if (objeto es transparente)
		//if(objeto->get_material() == TRANSPARENTE){}
	}

	return color;
}

color ControladorRender::traza_rr(rayo Rayo, int profundidad) {
	objeto* objeto;
	vector_3 punto_interseca;
	
	if (ControladorEscena::getInstance()->obtener_objeto_intersecado_mas_cercano(Rayo, objeto, punto_interseca)) {
		
		vector_3 normal = objeto->normal(punto_interseca, Rayo);
		
		return sombra_rr(objeto, Rayo, punto_interseca, normal, profundidad);
	}
	else {
		return negro;
	}

}

imagen* ControladorRender::whitted_ray_tracing() {
	camara* camara = ControladorEscena::getInstance()->get_camara();
	vector_3 origen = camara->getPosicionCamara(); //ojo de la camera
	vector_3 plano = vector_3(0.f, 0.f, 0.f);

	int imagen_width = camara->get_imagen_width();
	int imagen_height = camara->get_imagen_height();

	imagen* img_resultado = new imagen(imagen_width, imagen_height);

	#pragma omp parallel for collapse(2) //para paralelizacion
	for (int i = 0; i < imagen_height; i++) {
		for (int j = 0; j < imagen_width; j++) {
			rayo Rayo = rayo(origen,
				vector_3((float)(j - imagen_width / 2), (float)(i - imagen_height / 2), plano.get_z()) - origen);

			img_resultado->set_pixel(i, j, traza_rr(Rayo, 1));
		}
	}

	return img_resultado;
}

