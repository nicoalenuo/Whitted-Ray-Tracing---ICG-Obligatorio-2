#pragma once

#ifndef RAYO_H
#define RAYO_H

#include "vector_3.h"
//#include <stack>
#include "../constantes/parametros.h"

class rayo {
private:
	vector_3 origen;
	vector_3 direccion;

	//stack<float> pila_refraccion;
	//TAD Pila
	float* pila_refraccion;
	int indice_pila;
public:
	rayo(vector_3 origen, vector_3 direccion);
	~rayo() {}

	vector_3 get_origen() const { return origen; };
	vector_3 get_direccion() const { return direccion; };

	void apilarCoefRefraccion(float coeficiente);
	void desapilarCoefRefraccion();
	bool esVaciaPilaRefraccion();
	float obtenerCoefPilaRefrccion();
};

#endif
