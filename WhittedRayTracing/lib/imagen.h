#pragma once

#ifndef IMAGEN_H
#define IMAGEN_H

#include <iostream>

#include "../constantes/constantes.h"

#include "FreeImage.h"

class imagen {
private:
	color** pixeles;
public:
	imagen();
	~imagen();
	
	color** get_pixeles() const { return pixeles; };
	void set_pixel(const int i, const int j, const color color) { pixeles[i][j] = color; };

	FIBITMAP* obtener_bitmap();
};

#endif
