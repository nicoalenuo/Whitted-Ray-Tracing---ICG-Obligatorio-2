#pragma once

#ifndef MALLA_POLIGONAL_H
#define MALLA_POLIGONAL_H

#include <vector>

#include "objeto.h"
#include "poligono_triangulo.h"

using namespace std;

class malla_poligonal : public objeto {
private:
	vector<poligono_triangulo*> poligonos;
public:
	malla_poligonal(vector_3 posicion,
		color color_difuso, color color_especular,
		float coeficiente_ambiente, float coeficiente_difuso, float coeficiente_especular, float coeficiente_transmicion,
		tipo_material material,
		vector<poligono_triangulo*> poligonos) :
		objeto(posicion, color_difuso, color_especular, coeficiente_ambiente, coeficiente_difuso, coeficiente_especular, coeficiente_transmicion, material),
		poligonos(poligonos) {}

	bool interseca(rayo rayo_in, vector_3& punto_interseccion_out);
	vector_3 normal(vector_3 punto, rayo Rayo);
};

#endif
