#include "../../lib/controladores/ControladorRender.h"

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

color ControladorRender::sombra_rr(objeto* objeto, rayo Rayo, vector_3 punto_interseca, vector_3 normal, int profundidad) {
	float distancia_de_la_luz = 0;
	
	color color = { 255., 255., 255., 1. }; //Blanco

	vector<luz*> luces = ControladorEscena::getInstance()->get_luces();

	for (size_t i = 0; i < luces.size(); i++) {

		rayo* rayo_sombra = new rayo(punto_interseca + normal * EPSILON,
			luces[i]->get_posicion() - (punto_interseca + normal * EPSILON)); //los algoritmos que se toman como base
																			  //solo corrigen el punto de origen no la direcion
																			  //habria que revisar

		if (rayo_sombra->get_direccion().producto_interno(normal) > 0) {

			// Para calcular S_i usar
			// ControladorEscena::obtener_cantidad_de_luz_bloqueada(rayo_sombra, luces[i]->get_posicion());  

			distancia_de_la_luz = (luces[i]->get_posicion() - punto_interseca).norma();

			color = objeto->get_color_difuso();
			//color = { 255.f, 0., 0., 1 };

		}

		delete rayo_sombra;
	}

	return color;
}

color ControladorRender::traza_rr(rayo Rayo, int profundidad) {

	objeto* objeto;
	vector_3 punto_interseca;

	//En el codigo que muestra el profe esto no se chequea aca xd tal vez se puede R E M O V E R
	if (profundidad > PROFUNDIDAD_MAXIMA) {
		return {0., 0., 0., 1.}; //Negro
	}
	
	if (ControladorEscena::getInstance()->obtener_objeto_intersecado_mas_cercano(Rayo, objeto, punto_interseca)) {
		
		vector_3 normal = objeto->normal(punto_interseca, Rayo);
		
		return sombra_rr(objeto, Rayo, punto_interseca, normal, profundidad);
	}
	else {
		return { 0., 0., 0., 1. }; //Negro
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

