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

	int imagen_width;
	int imagen_height;

	vector<objeto*> objetos;
	vector<luz*> luces;
	camara* Camara;
public:
	static ControladorEscena* getInstance();
	~ControladorEscena();

	vector<objeto*> get_objetos() const { return objetos; };
	vector<luz*> get_luces() const { return luces; };
	camara* get_camara() { return Camara; };
	int get_imagen_width() const { return imagen_width; };
	int get_imagen_height() const { return imagen_height; };

	//Devuelve true si interseca con algun objeto, y si lo hace, devuelve cual y donde
	bool obtener_objeto_intersecado_mas_cercano(rayo rayo_in, objeto*& objeto_out, vector_3& punto_interseccion_out);

};

#endif