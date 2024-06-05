#pragma once

#ifndef IMAGEN_H
#define IMAGEN_H

#include <iostream>

#include "../constantes/constantes.h"
#include "color.h"

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
	void set_pixel(int i, int j, color color) { pixeles[i][j] = color; };

	FIBITMAP* obtener_bitmap();
};

#endif
