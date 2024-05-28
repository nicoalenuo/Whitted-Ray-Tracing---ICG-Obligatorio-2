#pragma once

#ifndef POLIGONO_TRIANGULO_H
#define POLIGONO_TRIANGULO_H

#include "../vector_3.h"

class poligono_triangulo {
private:
	vector_3 coord_1, coord_2, coord_3;

public:
	poligono_triangulo(vector_3 coord_1, vector_3 coord_2, vector_3 coord_3) : coord_1(coord_1), coord_2(coord_2), coord_3(coord_3) {}

	vector_3 get_coord_1() const { return coord_1; };
	vector_3 get_coord_2() const { return coord_2; };
	vector_3 get_coord_3() const { return coord_2; };

	vector_3 normal();
};

#endif