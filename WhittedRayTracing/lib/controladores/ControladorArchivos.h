#pragma once

#ifndef CONTROLADOR_ARCHIVOS_H
#define CONTROLADOR_ARCHIVOS_H

class ControladorArchivos{
private:
	static ControladorArchivos* instancia;
	ControladorArchivos();

public:
	static ControladorArchivos* getInstance();

};

#endif