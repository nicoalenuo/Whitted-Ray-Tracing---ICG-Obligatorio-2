#pragma once

#ifndef IMAGEN_H
#define IMAGEN_H

#include <iostream>

#include "../constantes/constantes.h"

#include "FreeImage.h"

class imagen {
private:
	color** pixeles;
	int imagen_width;
	int imagen_height;
public:
	imagen(int width, int height);
	~imagen();
	
	color** get_pixeles() const { return pixeles; };
	void set_pixel(const int i, const int j, const color color) { pixeles[i][j] = color; };

	FIBITMAP* obtener_bitmap();
};

#endif
