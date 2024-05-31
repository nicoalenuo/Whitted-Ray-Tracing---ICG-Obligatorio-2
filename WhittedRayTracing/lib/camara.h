#pragma once

#ifndef CAMARA_H
#define CAMARA_H

#include "vector_3.h"

class camara {
private:
	vector_3 posicion_camara, posicion_imagen;

	int imagen_width, imagen_height;

public:
	camara(vector_3 posicion_camara, vector_3 posicion_imagen, int imagen_width, int imagen_height) : 
		posicion_camara(posicion_camara), posicion_imagen(posicion_imagen), imagen_width(imagen_width), imagen_height(imagen_height) {}

	vector_3 getPosicionCamara() const { return posicion_camara; };
	vector_3 getPosicionImagen() const { return posicion_imagen; };

	int get_imagen_width() const { return imagen_width; };
	int get_imagen_height() const { return imagen_height; };
};

#endif