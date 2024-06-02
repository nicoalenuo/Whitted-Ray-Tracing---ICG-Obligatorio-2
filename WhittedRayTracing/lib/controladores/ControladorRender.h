#pragma once

#ifndef CONTROLADOR_RENDER_H
#define CONTROLADOR_RENDER_H

#include <omp.h>

#include "../camara.h"
#include "../imagen.h"
#include "../rayo.h"
#include "../vector_3.h"

#include "./ControladorEscena.h"

class ControladorRender{
private:
	static ControladorRender* instancia;
	ControladorRender();

	color traza_rr(rayo Rayo, int profundidad);
	color sombra_rr(objeto* objeto, rayo Rayo, vector_3 punto_interseca, vector_3 normal, int profundidad);

	color get_componente_especular(objeto* objeto, rayo rayo_r, int profundidad);

public:
	static ControladorRender* getInstance();
	~ControladorRender();

	imagen* whitted_ray_tracing();
};

#endif
