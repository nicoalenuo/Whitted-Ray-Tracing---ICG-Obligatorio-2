#pragma once

#ifndef ESFERA_H
#define ESFERA_H

#include "objeto.h"

class esfera : public objeto {
private:
	float radio;
public:
	esfera(vector_3 posicion, float radio) : objeto(posicion), radio(radio) {}

	bool interseca(rayo rayo_in, vector_3& punto_interseccion_out);
	vector_3 normal(vector_3 punto);
};

#endif

