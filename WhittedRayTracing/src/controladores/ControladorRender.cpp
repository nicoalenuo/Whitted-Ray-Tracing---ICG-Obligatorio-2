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

color ControladorRender::traza_rr(rayo* rayo, int profundidad) {

	if (profundidad > MAX_DEPTH) {
		return {0., 0., 0., 1.};
	}
	
	return { 255., 255., 255., 1. };

}


imagen* ControladorRender::whitted_ray_tracing() {
	imagen* img_resultado = new imagen();

	camara* camara = ControladorEscena::getInstance()->getCamara();
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
