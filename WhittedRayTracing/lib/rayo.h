#pragma once

#ifndef RAYO_H
#define RAYO_H

#include "vector_3.h"

class rayo {
private:
	vector_3 origen;
	vector_3 direccion;
public:
	rayo(vector_3 origen, vector_3 direccion);

	vector_3 get_origen() const { return origen; };
	vector_3 get_direccion() const { return direccion; };
};

#endif
