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
	malla_poligonal(vector_3 posicion, vector<poligono_triangulo*> poligonos, color color_difuso, color color_especular) : objeto(posicion,color_difuso,color_especular), poligonos(poligonos) {}

	bool interseca(rayo rayo_in, vector_3& punto_interseccion_out);
	vector_3 normal(vector_3 punto);
};

#endif
