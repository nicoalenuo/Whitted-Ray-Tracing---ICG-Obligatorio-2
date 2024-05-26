#pragma once

#ifndef OBJETO_H
#define OBJETO_H

#include "../vector_3.h"
#include "../rayo.h"

class objeto {
protected:
	vector_3 posicion;
public:
	objeto(vector_3 posicion) : posicion(posicion) {}

	vector_3 get_posicion() const { return posicion; };

	virtual bool interseca(rayo rayo_in, vector_3& punto_interseccion_out) = 0;
	virtual vector_3 normal(vector_3 punto) = 0;
};

#endif

