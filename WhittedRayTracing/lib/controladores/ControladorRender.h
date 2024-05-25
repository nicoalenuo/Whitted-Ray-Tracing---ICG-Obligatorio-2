#pragma once

#ifndef CONTROLADOR_RENDER_H
#define CONTROLADOR_RENDER_H

class ControladorRender{
private:
	static ControladorRender* instancia;
	ControladorRender();

public:
	static ControladorRender* getInstance();

};

#endif
