#pragma once

#ifndef CONTROLADOR_ESCENA_H
#define CONTROLADOR_ESCENA_H

#include <vector>

#include "../objetos/objeto.h"
#include "../luz.h"
#include "../camara.h"
#include "../rayo.h"
#include "../vector_3.h"

#include "ControladorArchivos.h"

using namespace std;

class ControladorEscena {
private:
	static ControladorEscena* instancia;

	ControladorEscena();

	vector<objeto*> objetos;
	vector<luz*> luces;
	camara* Camara;
public:
	static ControladorEscena* getInstance();
	~ControladorEscena();

	vector<objeto*> get_objetos() const { return objetos; };
	vector<luz*> get_luces() const { return luces; };
	camara* get_camara() { return Camara; };

	// Devuelve true si interseca con algun objeto, y si lo hace, devuelve cual y donde
	bool obtener_objeto_intersecado_mas_cercano(rayo rayo_in, objeto*& objeto_out, vector_3& punto_interseccion_out);

	// No se me ocurre un mejor nombre, devuelve un valor entre 0 y 1 que devuelve cuanta luz esta bloqueada. 0 es totalmente bloqueada, 1 es no bloqueada
	// Rayo es el rayo de luz (duh) y punto_destino es el punto donde esta la luz 
	float obtener_cantidad_de_luz_bloqueada(rayo Rayo, vector_3 punto_destino);


};

#endif