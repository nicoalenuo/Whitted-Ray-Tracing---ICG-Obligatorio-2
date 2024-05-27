#pragma once

#ifndef CONTROLADOR_RENDER_H
#define CONTROLADOR_RENDER_H

#include "../camara.h"
#include "../imagen.h"
#include "../rayo.h"
#include "../vector_3.h"

#include "./ControladorEscena.h"

class ControladorRender{
private:
	static ControladorRender* instancia;
	ControladorRender();

	color traza_rr(rayo* rayo, int profundidad);

public:
	static ControladorRender* getInstance();
	~ControladorRender();

	imagen* whitted_ray_tracing();
};

#endif
