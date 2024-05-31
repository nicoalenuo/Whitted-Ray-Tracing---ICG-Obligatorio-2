#include "../../lib/controladores/ControladorEscena.h"

ControladorEscena* ControladorEscena::instancia = nullptr;

ControladorEscena::ControladorEscena() {
	ControladorArchivos::getInstance()->cargar_xml(objetos, luces, Camara);
}

ControladorEscena::~ControladorEscena() {
	for (size_t i = 0; i < objetos.size(); i++) {
		delete objetos[i];
	}

	for (size_t i = 0; i < luces.size(); i++) {
		delete luces[i];
	}

	delete Camara;
}

ControladorEscena* ControladorEscena::getInstance() {
	if (instancia == nullptr)
		instancia = new ControladorEscena();
	return instancia;
}

bool ControladorEscena::obtener_objeto_intersecado_mas_cercano(rayo rayo_in, objeto*& objeto_out, vector_3& punto_interseccion_out) {
	vector_3 punto_interseccion_aux;
	float distancia_aux;
	bool interseca = false;
	objeto_out = nullptr;
	punto_interseccion_out = vector_3();
	for (size_t i = 0; i < objetos.size(); i++) {
		if (objetos[i]->interseca(rayo_in, punto_interseccion_aux)) {
			if (!interseca) {
				interseca = true;
				distancia_aux = (punto_interseccion_aux - rayo_in.get_origen()).norma();
				punto_interseccion_out = punto_interseccion_aux;
				objeto_out = objetos[i];
			}
			else if ((punto_interseccion_aux - rayo_in.get_origen()).norma() < distancia_aux) {
				distancia_aux = (punto_interseccion_aux - rayo_in.get_origen()).norma();
				punto_interseccion_out = punto_interseccion_aux;
				objeto_out = objetos[i];
			}
		}
	}

	return interseca;
}

float ControladorEscena::obtener_cantidad_de_luz_bloqueada(rayo Rayo, vector_3 punto_destino) {
	vector_3 punto_interseccion_aux;
	float luz_bloqueada = 1.f;
	for (size_t i = 0; i < objetos.size(); i++) {
		if (objetos[i]->interseca(Rayo, punto_interseccion_aux) && (Rayo.get_origen() - punto_interseccion_aux).norma() < (Rayo.get_origen() - punto_destino).norma()) {
			luz_bloqueada *= objetos[i]->get_coeficiente_transmicion();
		}
	}

	return luz_bloqueada;
}
