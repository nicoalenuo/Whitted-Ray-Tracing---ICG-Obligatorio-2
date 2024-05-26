#include "../lib/rayo.h"

rayo::rayo(vector_3 origen, vector_3 direccion) {
	this->origen = origen;
	this->direccion = direccion.normalizado();
}