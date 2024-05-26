#include "../../lib/controladores/ControladorEscena.h"

ControladorEscena* ControladorEscena::instancia = nullptr;

ControladorEscena::ControladorEscena() {
	ControladorArchivos::getInstance()->cargar_xml(objetos, luces, Camara);
}

ControladorEscena::~ControladorEscena() {
	for (size_t i = 0; i < objetos.size(); i++) {
		delete objetos[i];
	}
	
	for (size_t i = 0; i < luces.size(); i++) {
		delete luces[i];
	}

	delete Camara;
}

ControladorEscena* ControladorEscena::getInstance() {
	if (instancia == nullptr)
		instancia = new ControladorEscena();
	return instancia;
}

//aca van las funciones de interseca y tal