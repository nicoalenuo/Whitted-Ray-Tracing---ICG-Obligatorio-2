#include "WhittedRayTracing/lib/controladores/ControladorRender.h"
#include "WhittedRayTracing/lib/controladores/ControladorArchivos.h"
#include "WhittedRayTracing/lib/controladores/ControladorEscena.h"

#include <iostream>

int main() {
	ControladorRender* controlador_render = ControladorRender::getInstance();
	ControladorArchivos* controlador_archivos = ControladorArchivos::getInstance();
	ControladorEscena* controlador_escena = ControladorEscena::getInstance();

	imagen* img_resultado = controlador_render->whitted_ray_tracing();

	if (!controlador_archivos->guardar_resultado(img_resultado)) {
		cerr << "Error al guardar la imagen" << endl;
		exit(1);
	}

	delete controlador_render;
	delete controlador_archivos;
	delete controlador_escena;

	return 0;
}