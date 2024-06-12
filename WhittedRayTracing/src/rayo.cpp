#include "../lib/rayo.h"

rayo::rayo(vector_3 origen, vector_3 direccion) {
	this->origen = origen;
	this->direccion = direccion.normalizado();
	this->pila_refraccion = new float[PROFUNDIDAD_MAXIMA];
	this->indice_pila = 0;
}

void rayo::apilarCoefRefraccion(float coeficiente) {
	this->pila_refraccion[this->indice_pila++] = coeficiente;
}

void rayo::desapilarCoefRefraccion() {
	if (indice_pila > 0) {
		indice_pila--;
	}
}

bool rayo::esVaciaPilaRefraccion() {
	return (this->indice_pila == 0);
}

float rayo::obtenerCoefPilaRefrccion() {
	return this->pila_refraccion[this->indice_pila];
}