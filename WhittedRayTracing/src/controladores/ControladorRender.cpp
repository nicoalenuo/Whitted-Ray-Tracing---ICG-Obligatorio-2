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

color ControladorRender::sombra_rr(objeto* objeto, rayo* Rayo, vector_3 punto_interseca, vector_3 normal, int profundidad) {
	float distancia_de_la_luz = 0;
	
	color color = { 255., 255., 255., 1. }; //Blanco

	vector<luz*> luces = ControladorEscena::getInstance()->get_luces();

	for (size_t i = 0; i < luces.size(); i++) {

		rayo* rayo_sombra = new rayo(punto_interseca + normal * EPSILON,
			luces[i]->get_posicion() - (punto_interseca + normal * EPSILON)); //los algoritmos que se toman como base
																			  //solo corrigen el punto de origen no la direcion
																			  //habria que revisar

		if (rayo_sombra->get_direccion().producto_interno(normal) > 0) {

			distancia_de_la_luz = (luces[i]->get_posicion() - punto_interseca).norma();

			//color = luces[i]->get_color() * objeto->get_color();
			color = { 255.f, 0., 0., 1 };

		}

		delete rayo_sombra;
	}

	return color;
}

color ControladorRender::traza_rr(rayo* Rayo, int profundidad) {

	objeto* objeto;
	vector_3 punto_interseca;

	if (profundidad > PROFUNDIDAD_MAXIMA) {
		return {0., 0., 0., 1.}; //Negro
	}
	
	if (ControladorEscena::getInstance()->obtener_objeto_intersecado_mas_cercano(rayo(Rayo->get_origen(), Rayo->get_direccion()), objeto, punto_interseca)) {
		
		vector_3 normal = objeto->normal(punto_interseca);
		
		return sombra_rr(objeto, Rayo, punto_interseca, normal, profundidad);
	}
	else {
		return { 0., 0., 0., 1. }; //Negro
	}
	

}


imagen* ControladorRender::whitted_ray_tracing() {
	imagen* img_resultado = new imagen();

	camara* camara = ControladorEscena::getInstance()->get_camara();
	vector_3 origen = camara->getPosicionCamara(); //ojo de la camera
	//vector_3 plano = camara->getDireccionCamara(); //hay que importar ademas el plano que ya se agrego en el archivo
	vector_3 plano = vector_3(0.f, 0.f, 0.f);

	rayo* rayo1;

	/* 
	Ray tracing potente
	*/
	for (int i = 0; i < IMAGEN_HEIGHT; i++) {
		for (int j = 0; j < IMAGEN_WIDTH; j++) {

			rayo1 = new rayo(origen, 
				vector_3((float)(j - HALF_IMAGE_WIDTH), (float)(i - HALF_IMAGEN_HEIGHT), plano.get_z()) - origen);

			img_resultado->set_pixel(i, j, traza_rr(rayo1, 1));
		}
	}

	delete rayo1;

	return img_resultado;
}
