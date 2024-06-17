#pragma once

#ifndef CONTROLADOR_RENDER_H
#define CONTROLADOR_RENDER_H

#include <omp.h>
#include <SDL.h>

#include "../camara.h"
#include "../imagen.h"
#include "../rayo.h"
#include "../vector_3.h"
#include "../color.h"

#include "./ControladorArchivos.h"

class ControladorRender{
private:
	static ControladorRender* instancia;
	ControladorRender();

	vector<objeto*> objetos;
	vector<luz*> luces;
	camara* Camara;

	color traza_rr_por_coeficiente(rayo Rayo, tipo_imagen tipo);
	color traza_rr(rayo Rayo, int profundidad, tipo_imagen tipo);
	color sombra_rr(objeto* objeto, rayo Rayo, vector_3 punto_interseca, vector_3 normal, int profundidad, tipo_imagen tipo);

	// Devuelve true si interseca con algun objeto, y si lo hace, devuelve cual y donde en las variables _out
	bool obtener_objeto_intersecado_mas_cercano(rayo rayo_in, objeto*& objeto_out, vector_3& punto_interseccion_out);

	// Devuelve un valor entre 0 y 1 que indica cuanta luz esta bloqueada. 0 es totalmente bloqueada, 1 es no bloqueada
	float obtener_cantidad_de_luz_bloqueada(rayo Rayo, vector_3 punto_destino);

	// Devuelve la direccion refljeada de un rayo respecto a una normal
	vector_3 direccion_reflejada(vector_3 L, vector_3 N);

	// Componentes de color
	color get_componente_ambiente(objeto* objeto);
	color get_componente_luz(objeto* objeto_in, rayo Rayo, vector_3 punto_interseca, vector_3 normal, tipo_imagen tipo);
	color get_componente_difuso(objeto* objeto, vector_3 N, vector_3 L_i);
	color get_componente_especular(objeto* objeto, vector_3 V, vector_3 N, vector_3 L);
	color get_componente_reflectivo(objeto* objeto_in, rayo I, vector_3 punto_interseca, vector_3 N, int profundidad, tipo_imagen tipo);
	color get_componente_refractivo(objeto* objeto_in, rayo I, vector_3 punto_interseca, vector_3 N, int profundidad, tipo_imagen tipo);

	// Variables para mostrar la imagen mientras se crea
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	Uint32* SDL_pixeles; //Los pixeles que se muestran en la ventana generada por SDL
public:
	static ControladorRender* getInstance();
	~ControladorRender();

	vector<objeto*> get_objetos() const { return objetos; };
	vector<luz*> get_luces() const { return luces; };
	camara* get_camara() const { return Camara; };

	imagen* whitted_ray_tracing(tipo_imagen imagen);
};

#endif
