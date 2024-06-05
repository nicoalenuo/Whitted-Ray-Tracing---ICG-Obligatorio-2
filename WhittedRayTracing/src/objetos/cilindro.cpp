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
        (rayo_in.get_origen().get_z() - posicion.get_z()) -
        (radio * radio);

    float d = b * b - 4 * a * c;

    if (d < 0) {
        return false;
    }

    float t1 = (-b - sqrt(d)) / (2 * a);
    float t2 = (-b + sqrt(d)) / (2 * a);

    if (t1 > t2) {
        swap(t1, t2);
    }

    float t = t1;
    if (t < 0) {
        t = t2;
        if (t < 0) {
            return false;
        }
    }

    float r = rayo_in.get_origen().get_y() + rayo_in.get_direccion().get_y() * t;

    if (r >= posicion.get_y() - altura / 2 && r <= posicion.get_y() + altura / 2) {
        punto_interseccion_out = rayo_in.get_origen() + rayo_in.get_direccion() * t;
        return true;
    }

    if (rayo_in.get_direccion().get_y() != 0) {
        float t_base_superior = (posicion.get_y() + altura / 2 - rayo_in.get_origen().get_y()) / rayo_in.get_direccion().get_y();
        vector_3 punto_superior = rayo_in.get_origen() + rayo_in.get_direccion() * t_base_superior;
        if (t_base_superior >= 0 &&
            (punto_superior.get_x() - posicion.get_x()) * (punto_superior.get_x() - posicion.get_x()) +
            (punto_superior.get_z() - posicion.get_z()) * (punto_superior.get_z() - posicion.get_z()) <= radio * radio) {
            punto_interseccion_out = punto_superior;
            return true;
        }

        float t_base_inferior = (posicion.get_y() - altura / 2 - rayo_in.get_origen().get_y()) / rayo_in.get_direccion().get_y();
        vector_3 punto_inferior = rayo_in.get_origen() + rayo_in.get_direccion() * t_base_inferior;
        if (t_base_inferior >= 0 &&
            (punto_inferior.get_x() - posicion.get_x()) * (punto_inferior.get_x() - posicion.get_x()) +
            (punto_inferior.get_z() - posicion.get_z()) * (punto_inferior.get_z() - posicion.get_z()) <= radio * radio) {
            punto_interseccion_out = punto_inferior;
            return true;
        }
    }

    return false;
}

vector_3 cilindro::normal(vector_3 punto, rayo Rayo) {
    return 
        (punto.get_y() >= posicion.get_y() + altura / 2) ? vector_3(0, 1, 0) :
        (punto.get_y() <= posicion.get_y() - altura / 2) ? vector_3(0, -1, 0) :
        vector_3(posicion.get_x() - punto.get_x(), 0, posicion.get_z() - punto.get_z()).normalizado();
}
