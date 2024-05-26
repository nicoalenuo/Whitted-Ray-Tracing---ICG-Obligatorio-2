#pragma once

#ifndef CONTROLADOR_RENDER_H
#define CONTROLADOR_RENDER_H

#include "../imagen.h"

class ControladorRender{
private:
	static ControladorRender* instancia;
	ControladorRender();

public:
	static ControladorRender* getInstance();
	~ControladorRender();

	imagen* whitted_ray_tracing();
};

#endif
