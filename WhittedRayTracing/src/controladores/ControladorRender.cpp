#include "../../lib/controladores/ControladorRender.h"

ControladorRender* ControladorRender::instancia = nullptr;

ControladorRender::ControladorRender() {

}

ControladorRender* ControladorRender::getInstance() {
	if (instancia == nullptr)
		instancia = new ControladorRender();
	return instancia;
}
