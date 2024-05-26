#pragma once

#ifndef CONTROLADOR_ARCHIVOS_H
#define CONTROLADOR_ARCHIVOS_H

#include <vector>
#include <iostream>
#include <windows.h>

#include "../objetos/objeto.h"
#include "../imagen.h"
#include "../camara.h"
#include "../luz.h"
#include "../../constantes/constantes.h"
#include "../tinyxml2.h"

using namespace std;

class ControladorArchivos{
private:
	static ControladorArchivos* instancia;
	ControladorArchivos();

	vector<objeto*> cargar_objetos();
	vector<luz*> cargar_luces();
	camara* cargar_camara();
public:
	static ControladorArchivos* getInstance();
	~ControladorArchivos();

	void cargar_xml(vector<objeto*>& objetos_out, vector<luz*>& luces_out, camara*& camara_out);
	bool guardar_resultado(imagen* resultado); 
};

#endif