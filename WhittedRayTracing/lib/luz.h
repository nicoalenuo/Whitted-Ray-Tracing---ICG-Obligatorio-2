#pragma once

#ifndef LUZ_H
#define LUZ_H

#include "./vector_3.h"
#include "color.h"
#include "../constantes/estructuras.h"

class luz {
private:
	vector_3 posicion;
	color Color;

public:
	luz(vector_3 posicion, color Color) : posicion(posicion), Color(Color) {}
	~luz() {};

	vector_3 get_posicion() const { return posicion; };
	color get_color() const { return Color; };
};

#endif