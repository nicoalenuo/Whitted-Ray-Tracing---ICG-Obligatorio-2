#pragma once

#ifndef CONTROLADOR_RENDER_H
#define CONTROLADOR_RENDER_H

#include <omp.h>
#include "SDL.h"

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

	color get_componente_reflectivo(objeto* objeto_in, rayo I, vector_3 punto_interseca, vector_3 N, int profundidad, tipo_imagen tipo);
	color get_componente_refractivo(objeto* objeto_in, rayo I, vector_3 punto_interseca, vector_3 N, int profundidad, tipo_imagen tipo);

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	Uint32* SDL_pixeles; //Los pixeles que se muestran en la ventana generada por SDL
public:
	static ControladorRender* getInstance();
	~ControladorRender();

	imagen* whitted_ray_tracing(tipo_imagen imagen);
};

#endif
