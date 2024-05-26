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
	camara* camara;
public:
	static ControladorEscena* getInstance();
	~ControladorEscena();

	//Devuelve true si intersecta con algun objeto, y si lo hace, devuelve cual y donde
	bool obtener_objeto_intersecado_mas_cercano(rayo rayo_in, objeto*& objeto_out, vector_3& punto_interseccion_out);
};

#endif