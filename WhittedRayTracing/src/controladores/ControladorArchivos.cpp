#include "../../lib/controladores/ControladorArchivos.h"

ControladorArchivos* ControladorArchivos::instancia = nullptr;

ControladorArchivos::ControladorArchivos() {

}

ControladorArchivos* ControladorArchivos::getInstance() {
	if (instancia == nullptr)
		instancia = new ControladorArchivos();
	return instancia;
}
