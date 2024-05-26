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

imagen* ControladorRender::whitted_ray_tracing() {
	imagen* img_resultado = new imagen();

	/* 
	Ray tracing potente
	*/

	return img_resultado;
}
