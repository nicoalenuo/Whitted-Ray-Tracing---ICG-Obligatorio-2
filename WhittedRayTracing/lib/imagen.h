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
	void set_pixel(const int x, const int y, const color color) { pixeles[x][y] = color; };

	FIBITMAP* float_to_bitmap();
};

#endif
