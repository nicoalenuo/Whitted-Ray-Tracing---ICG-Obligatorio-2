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
};

#endif