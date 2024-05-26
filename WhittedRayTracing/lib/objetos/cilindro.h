#pragma once

#ifndef CILINDRO_H
#define CILINDRO_H

#include "objeto.h"

class cilindro : public objeto{
private:
	float radio, altura;
public:
	cilindro(vector_3 posicion, float radio, float altura) : objeto(posicion), radio(radio), altura(altura) {}

	bool interseca(rayo rayo_in, vector_3& punto_interseccion_out);
	vector_3 normal(vector_3 punto);
};

#endif

