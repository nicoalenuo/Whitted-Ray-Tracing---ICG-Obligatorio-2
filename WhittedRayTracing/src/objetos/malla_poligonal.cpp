#include "../../lib/objetos/malla_poligonal.h"

bool malla_poligonal::interseca(rayo rayo_in, vector_3& punto_interseccion_out) {
    bool interseca = false;
    poligono_triangulo* triangulo;
    vector_3 normal;
    float distancia_minima;
    float paralelo;

    for (size_t i = 0; i < poligonos.size(); i++) {
        triangulo = poligonos[i];
        normal = triangulo->normal();
        paralelo = normal.producto_interno(rayo_in.get_direccion());
        if (paralelo != 0) {
            float distancia = -(normal.producto_interno(rayo_in.get_origen()) - normal.producto_interno(triangulo->get_coord_1())) / paralelo;

            if (distancia > 0) {
                vector_3 punto_interseccion = rayo_in.get_origen() + rayo_in.get_direccion() * distancia;

                vector_3 artista_1 = triangulo->get_coord_2() - triangulo->get_coord_1();
                vector_3 artista_2 = triangulo->get_coord_3() - triangulo->get_coord_2();
                vector_3 artista_3 = triangulo->get_coord_1() - triangulo->get_coord_3();

                vector_3 C1 = punto_interseccion - triangulo->get_coord_1();
                vector_3 C2 = punto_interseccion - triangulo->get_coord_2();
                vector_3 C3 = punto_interseccion - triangulo->get_coord_3();

                if ((artista_1 * C1).producto_interno(normal) >= 0 && (artista_2 * C2).producto_interno(normal) >= 0 && (artista_3 * C3).producto_interno(normal) >= 0) {
                    if (!interseca) {
                        distancia_minima = distancia;
                        interseca = true;
                    }
                    else {
                        distancia_minima = min(distancia, distancia_minima);
                    }
                }
            }
        }
    }

    if (interseca) {
        punto_interseccion_out = rayo_in.get_origen() + rayo_in.get_direccion() * distancia_minima;
    }

    return interseca;
}

vector_3 malla_poligonal::normal(vector_3 punto, rayo Rayo) {
    vector_3 normal;
    poligono_triangulo* poligono;

    for (size_t i = 0; i < poligonos.size(); i++) {

        poligono = poligonos[i];
        normal = poligono->normal();

        vector_3 arista_1 = poligono->get_coord_2() - poligono->get_coord_1();
        vector_3 arista_2 = poligono->get_coord_3() - poligono->get_coord_2();
        vector_3 arista_3 = poligono->get_coord_1() - poligono->get_coord_3();

        vector_3 C1 = punto - poligono->get_coord_1();
        vector_3 C2 = punto - poligono->get_coord_2();
        vector_3 C3 = punto - poligono->get_coord_3();

        if ((arista_1 * C1).producto_interno(normal) >= 0 && (arista_2 * C2).producto_interno(normal) >= 0 && (arista_3 * C3).producto_interno(normal) >= 0) {
            if (Rayo.get_direccion().producto_interno(normal) <= 0)
                return normal.normalizado();
            else
                return -normal.normalizado();
        }
    }

    return vector_3();
}