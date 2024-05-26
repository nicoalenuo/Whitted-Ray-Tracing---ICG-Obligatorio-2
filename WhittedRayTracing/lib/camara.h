#pragma once

#ifndef CAMARA_H
#define CAMARA_H

#include "vector_3.h"

class camara {
private:
	vector_3 posicion_camara;
	vector_3 direccion_camara;

public:
	camara(vector_3 posicion, vector_3 direccion) : posicion_camara(posicion), direccion_camara(direccion) {};

	vector_3 getPosicionCamara() const { return posicion_camara; };
	vector_3 getDireccionCamara() const { return direccion_camara; };
};

#endif