#include "WhittedRayTracing/lib/controladores/ControladorRender.h"
#include "WhittedRayTracing/lib/controladores/ControladorArchivos.h"

#include <iostream>

using namespace std;

int main(int argc, char* args[]) {
	cout << "Cargando objetos del archivo xml..." << endl;
	ControladorRender* controlador_render = ControladorRender::getInstance();
	ControladorArchivos* controlador_archivos = ControladorArchivos::getInstance();
	cout << "Cargados " << controlador_render->get_objetos().size() << " objetos" << endl;

	cout << endl;

	// Sin antialiasing

	cout << "Generando imagen sin antialiasing..." << endl;
	chrono::steady_clock::time_point comienzo_generacion_imagen = chrono::high_resolution_clock::now();
	imagen* img_resultado = controlador_render->whitted_ray_tracing(SIN_ANTIALIASING);
	chrono::steady_clock::time_point fin_generacion_imagen = chrono::high_resolution_clock::now();

	chrono::duration<double> tiempo_transcurrido_generacion_imagen = fin_generacion_imagen - comienzo_generacion_imagen;
	cout << "Imagen generada en " << tiempo_transcurrido_generacion_imagen.count() << " segundos" << endl;

	cout << "Guardando resultado..." << endl;
	controlador_archivos->guardar_resultado(img_resultado, SIN_ANTIALIASING);
	delete img_resultado;

	// -----------------

	cout << endl;

	// Con antialiasing

	cout << "Generando imagen con antialiasing..." << endl;
	comienzo_generacion_imagen = chrono::high_resolution_clock::now();
	img_resultado = controlador_render->whitted_ray_tracing(CON_ANTIALIASING);
	fin_generacion_imagen = chrono::high_resolution_clock::now();

	tiempo_transcurrido_generacion_imagen = fin_generacion_imagen - comienzo_generacion_imagen;
	cout << "Imagen generada en " << tiempo_transcurrido_generacion_imagen.count() << " segundos" << endl;

	cout << "Guardando resultado..." << endl;
	controlador_archivos->guardar_resultado(img_resultado, CON_ANTIALIASING);
	delete img_resultado;

	// -----------------

	cout << endl;

	// Resultados auxiliares

	cout << "Generando imagenes auxiliares para representar los componentes (sin antialiasing)" << endl;

	cout << endl;

	cout << "Coeficiente ambiental..." << endl;
	img_resultado = controlador_render->whitted_ray_tracing(COEF_AMBIENTAL);
	controlador_archivos->guardar_resultado(img_resultado, COEF_AMBIENTAL);
	delete img_resultado;

	cout << endl;

	cout << "Coeficiente difuso..." << endl;
	img_resultado = controlador_render->whitted_ray_tracing(COEF_DIFUSO);
	controlador_archivos->guardar_resultado(img_resultado, COEF_DIFUSO);
	delete img_resultado;

	cout << endl;

	cout << "Coeficiente especular..." << endl;
	img_resultado = controlador_render->whitted_ray_tracing(COEF_ESPECULAR);
	controlador_archivos->guardar_resultado(img_resultado, COEF_ESPECULAR);
	delete img_resultado;

	cout << endl;

	cout << "Coeficiente reflexion..." << endl;
	img_resultado = controlador_render->whitted_ray_tracing(COEF_REFLEXIVO);
	controlador_archivos->guardar_resultado(img_resultado, COEF_REFLEXIVO);
	delete img_resultado;

	cout << endl;
	
	cout << "Coeficiente transmision..." << endl;
	img_resultado = controlador_render->whitted_ray_tracing(COEF_TRANSMISION);
	controlador_archivos->guardar_resultado(img_resultado, COEF_TRANSMISION);
	delete img_resultado;

	cout << endl;
	
	cout << "Color ambiente..." << endl;
	img_resultado = controlador_render->whitted_ray_tracing(COLOR_AMBIENTE);
	controlador_archivos->guardar_resultado(img_resultado, COLOR_AMBIENTE);
	delete img_resultado;

	cout << endl;

	cout << "Color difuso..." << endl;
	img_resultado = controlador_render->whitted_ray_tracing(COLOR_DIFUSO);
	controlador_archivos->guardar_resultado(img_resultado, COLOR_DIFUSO);
	delete img_resultado;

	cout << endl;

	cout << "Color especular..." << endl;
	img_resultado = controlador_render->whitted_ray_tracing(COLOR_ESPECULAR);
	controlador_archivos->guardar_resultado(img_resultado, COLOR_ESPECULAR);
	delete img_resultado;
	

	// -----------------

	delete controlador_render;
	delete controlador_archivos;

	return 0;
}