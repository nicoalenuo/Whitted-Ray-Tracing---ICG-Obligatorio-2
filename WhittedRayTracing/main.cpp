#include "lib/controladores/ControladorRender.h"
#include "lib/controladores/ControladorArchivos.h"

#include <iostream>

int main(int argc, char* argv[]) {
	ControladorRender* controlador_render = ControladorRender::getInstance();
	ControladorArchivos* controlador_archivos = ControladorArchivos::getInstance();

	std::cout << "funciona" << std::endl;

	delete controlador_render;
	delete controlador_archivos;

	return 0;
}