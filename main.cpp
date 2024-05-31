#include "WhittedRayTracing/lib/controladores/ControladorRender.h"
#include "WhittedRayTracing/lib/controladores/ControladorArchivos.h"
#include "WhittedRayTracing/lib/controladores/ControladorEscena.h"

#include <iostream>

using namespace std;

int main() {
	cout << "Cargando objetos del archivo xml..." << endl;
	ControladorRender* controlador_render = ControladorRender::getInstance();
	ControladorArchivos* controlador_archivos = ControladorArchivos::getInstance();
	ControladorEscena* controlador_escena = ControladorEscena::getInstance();
	cout << "Cargados " << controlador_escena->get_objetos().size() << " objetos" << endl;
	
	cout << "Generando imagen...." << endl;
	chrono::steady_clock::time_point comienzo_generacion_imagen = chrono::high_resolution_clock::now();
	imagen* img_resultado = controlador_render->whitted_ray_tracing();
	chrono::steady_clock::time_point fin_generacion_imagen = chrono::high_resolution_clock::now();

	chrono::duration<double> tiempo_transcurrido_generacion_imagen = fin_generacion_imagen - comienzo_generacion_imagen;
	cout << "Imagen generada en " << tiempo_transcurrido_generacion_imagen.count() << " segundos" << endl;

	cout << "Guardando resultado..." << endl;
	controlador_archivos->guardar_resultado(img_resultado);

	delete img_resultado;
	delete controlador_render;
	delete controlador_archivos;
	delete controlador_escena;

	return 0;
}