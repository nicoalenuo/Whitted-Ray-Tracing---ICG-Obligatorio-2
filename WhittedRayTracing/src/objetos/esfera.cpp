#include "../../lib/objetos/esfera.h"

// https://math.stackexchange.com/questions/1939423/calculate-if-vector-intersects-sphere 
bool esfera::interseca(rayo rayo_in, vector_3& punto_interseccion_out) {
	vector_3 Q = rayo_in.get_origen() - posicion;
	
	float a = rayo_in.get_direccion().producto_interno(rayo_in.get_direccion());
	float b = 2 * rayo_in.get_direccion().producto_interno(Q);
	float c = Q.producto_interno(Q) - radio * radio;
	float d = b * b - 4 * a * c;  // discriminant of quadratic

	if (d < 0) {
		return false;
	}
	else {
		float t1 = (-b - sqrt(d)) / 2 * a;
		float t2 = (-b + sqrt(d)) / 2 * a;
		if (t1 >= 0 || t2 >= 0) {
			punto_interseccion_out = rayo_in.get_origen() +
				(t1 >= 0 ? rayo_in.get_direccion() * t1 :
					(t2 >= 0 ? rayo_in.get_direccion() * t2 :
						vector_3(-1, -1, -1)));
			return true;
		} else {
			return false;
		}
	}
}

vector_3 esfera::normal(vector_3 punto) {
	return (punto - posicion).normalizado();
}