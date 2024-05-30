#pragma once

#ifndef CILINDRO_H
#define CILINDRO_H

#include "objeto.h"

class cilindro : public objeto{
private:
	float radio, altura;
public:
	cilindro(vector_3 posicion,
		color color_difuso, color color_especular,
		float coeficiente_ambiente, float coeficiente_difuso, float coeficiente_especular, float coeficiente_transmicion,
		tipo_material material,
		float radio, float altura) :
		objeto(posicion, color_difuso, color_especular, coeficiente_ambiente, coeficiente_difuso, coeficiente_especular, coeficiente_transmicion, material),
		radio(radio), altura(altura) {}

	bool interseca(rayo rayo_in, vector_3& punto_interseccion_out);
	vector_3 normal(vector_3 punto, rayo Rayo);
};

#endif

