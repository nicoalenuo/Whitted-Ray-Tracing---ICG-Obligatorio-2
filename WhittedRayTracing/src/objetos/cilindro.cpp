#include "../../lib/objetos/cilindro.h"

bool cilindro::interseca(rayo rayo_in, vector_3& punto_interseccion_out) {
    float a = 
        (rayo_in.get_direccion().get_x() * rayo_in.get_direccion().get_x()) +
        (rayo_in.get_direccion().get_z() * rayo_in.get_direccion().get_z());

    float b = 
        2 * (
        rayo_in.get_direccion().get_x() *
        (rayo_in.get_origen().get_x() - posicion.get_x()) +
        rayo_in.get_direccion().get_z() * (rayo_in.get_origen().get_z() - posicion.get_z())
        );
    float c = 
        (rayo_in.get_origen().get_x() - posicion.get_x()) * 
        (rayo_in.get_origen().get_x() - posicion.get_x()) +
        (rayo_in.get_origen().get_z() - posicion.get_z()) *
        (rayo_in.get_origen().get_x() - posicion.get_z()) -
        (radio * radio);

    float delta = b * b - 4 * (a * c);
    if (fabs(delta) < 0.001 || delta < 0.0) {
        return false;
    }

    float t1 = (-b - sqrt(delta)) / (2 * a);
    float t2 = (-b + sqrt(delta)) / (2 * a);
    float t;

    if (t1 > t2) {
        t = t2;
    }
    else {
        t = t1;
    }

    float r = rayo_in.get_origen().get_y() + rayo_in.get_direccion().get_y() * t;

    if ((r >= posicion.get_y()) && (r <= posicion.get_y() + altura)) {
        punto_interseccion_out = rayo_in.get_origen() + rayo_in.get_direccion() * t;
        return true;
    }
    else {
        return false;
    }
}


vector_3 cilindro::normal(vector_3 punto) {
    return 
        (punto.get_y() >= posicion.get_y() + altura / 2 ? vector_3(0, 1, 0) :
        punto.get_y() <= posicion.get_y() - altura / 2 ? vector_3(0, -1, 0) :
        vector_3(posicion.get_x() - punto.get_x(), 0, posicion.get_z() - punto.get_z())).normalizado();
}
