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
	float coeficiente_ambiente, coeficiente_difuso, coeficiente_especular, coeficiente_transmicion;

	tipo_material material; // Reflectante = 0 / Transparente = 1

public:
	objeto(vector_3 posicion, 
		color color_difuso, color color_especular, 
		float coeficiente_ambiente, float coeficiente_difuso, float coeficiente_especular, float coeficiente_transmicion,
		tipo_material material) :
		posicion(posicion), 
		color_difuso(color_difuso), color_especular(color_especular),
		coeficiente_ambiente(coeficiente_ambiente), coeficiente_difuso(coeficiente_difuso), coeficiente_especular(coeficiente_especular), coeficiente_transmicion(coeficiente_transmicion),
		material(material) {}

	vector_3 get_posicion() const { return posicion; };

	color get_color_difuso() const { return color_difuso; };
	color get_color_especular() const { return color_especular; };

	float get_coeficiente_ambiente() const { return coeficiente_ambiente; };
	float get_coeficiente_difuso() const { return coeficiente_difuso; };
	float get_coeficiente_especular() const { return coeficiente_especular; };
	float get_coeficiente_transmicion() const { return coeficiente_transmicion; };
	tipo_material get_material() const { return material; };

	virtual bool interseca(rayo rayo_in, vector_3& punto_interseccion_out) = 0;
	virtual vector_3 normal(vector_3 punto, rayo Rayo) = 0;
};

#endif

