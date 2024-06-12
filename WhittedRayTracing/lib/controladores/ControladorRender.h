#pragma once

#ifndef CONTROLADOR_RENDER_H
#define CONTROLADOR_RENDER_H

#include <omp.h>

#include "../camara.h"
#include "../imagen.h"
#include "../rayo.h"
#include "../vector_3.h"
#include "../color.h"

#include "./ControladorEscena.h"

class ControladorRender{
private:
	static ControladorRender* instancia;
	ControladorRender();

	color traza_rr(rayo Rayo, int profundidad, tipo_imagen tipo);
	color sombra_rr(objeto* objeto, rayo Rayo, vector_3 punto_interseca, vector_3 normal, int profundidad, tipo_imagen tipo);

	color get_componente_reflectivo(objeto* objeto, rayo rayo_r, int profundidad, tipo_imagen tipo);
	color get_componente_refractivo(objeto* objeto, rayo rayo_t, int profundidad, tipo_imagen tipo);
	color get_componente_refractivo(objeto* objecto, rayo I, vector_3 punto_interseca, vector_3 N, int profundidad, tipo_imagen tipo);

public:
	static ControladorRender* getInstance();
	~ControladorRender();

	imagen* whitted_ray_tracing(tipo_imagen imagen);
};

#endif
