#pragma once

#ifndef OBJETO_H
#define OBJETO_H

#include "../vector_3.h"
#include "../rayo.h"
#include "../../constantes/estructuras.h"

class objeto {
protected:
	vector_3 posicion;

	color color_difuso, color_especular;

public:
	objeto(vector_3 posicion, color color_difuso, color color_especular) :
		posicion(posicion), 
		color_difuso(color_difuso), color_especular(color_especular)  {}

	vector_3 get_posicion() const { return posicion; };
	color get_color_difuso() const { return color_difuso; };
	color get_color_especular() const { return color_especular; };

	virtual bool interseca(rayo rayo_in, vector_3& punto_interseccion_out) = 0;
	virtual vector_3 normal(vector_3 punto, rayo Rayo) = 0;
};

#endif

