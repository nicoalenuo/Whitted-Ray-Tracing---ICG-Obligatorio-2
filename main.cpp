#include "WhittedRayTracing/lib/controladores/ControladorRender.h"
#include "WhittedRayTracing/lib/controladores/ControladorArchivos.h"
#include "WhittedRayTracing/lib/controladores/ControladorEscena.h"

#include <iostream>

using namespace std;

int main() {
	cout << "Cargando objetos del archivo xml" << endl;
	ControladorRender* controlador_render = ControladorRender::getInstance();
	ControladorArchivos* controlador_archivos = ControladorArchivos::getInstance();
	ControladorEscena* controlador_escena = ControladorEscena::getInstance();
	
	cout << "Generando imagen" << endl;
	auto start_time_ray_tracing = std::chrono::high_resolution_clock::now();
	imagen* img_resultado = controlador_render->whitted_ray_tracing();
	auto finish_time_ray_tracing = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish_time_ray_tracing - start_time_ray_tracing;
	cout << "Imagen generada en " << elapsed.count() << " segundos" << endl;

	cout << "Guardando resultado" << endl;
	if (!controlador_archivos->guardar_resultado(img_resultado)) {
		cerr << "Error al guardar la imagen" << endl;
		exit(1);
	}

	delete controlador_render;
	delete controlador_archivos;
	delete controlador_escena;

	return 0;
}