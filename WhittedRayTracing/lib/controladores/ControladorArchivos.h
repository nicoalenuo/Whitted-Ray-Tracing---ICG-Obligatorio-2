#pragma once

#ifndef CONTROLADOR_ARCHIVOS_H
#define CONTROLADOR_ARCHIVOS_H

#include <vector>
#include <iostream>
#include <filesystem>
#include <chrono>

#include "../objetos/objeto.h"
#include "../imagen.h"
#include "../camara.h"
#include "../luz.h"
#include "../../constantes/constantes.h"
#include "../objetos/esfera.h"
#include "../objetos/cilindro.h"
#include "../objetos/malla_poligonal.h"
#include "../tinyxml2.h"

using namespace std;

class ControladorArchivos{
private:
	static ControladorArchivos* instancia;
	ControladorArchivos();

	vector<objeto*> cargar_objetos(tinyxml2::XMLElement* configuracion);
	vector<luz*> cargar_luces(tinyxml2::XMLElement* configuracion);
	camara* cargar_camara(tinyxml2::XMLElement* configuracion);
public:
	static ControladorArchivos* getInstance();
	~ControladorArchivos();

	void cargar_xml(vector<objeto*>& objetos_out, vector<luz*>& luces_out, camara*& camara_out);
	void guardar_resultado(imagen* resultado); 
};

#endif