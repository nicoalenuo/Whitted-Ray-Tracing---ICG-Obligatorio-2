#pragma once

#ifndef CAMARA_H
#define CAMARA_H

#include "vector_3.h"

class camara {
private:
	vector_3 posicion_camara;
	vector_3 posicion_imagen;

public:
	camara(vector_3 posicion_camara, vector_3 posicion_imagen) : posicion_camara(posicion_camara), posicion_imagen(posicion_imagen) {};

	vector_3 getPosicionCamara() const { return posicion_camara; };
	vector_3 getPosicionImagen() const { return posicion_imagen; };
};

#endif