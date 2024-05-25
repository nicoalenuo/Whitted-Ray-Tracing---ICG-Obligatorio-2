#include "../lib/imagen.h"

imagen::imagen() {
    pixeles = new color * [IMAGEN_HEIGHT];
    for (int i = 0; i < IMAGEN_HEIGHT; ++i) {
        pixeles[i] = new color[IMAGEN_WIDTH];
    }
}

imagen::~imagen() {
    for (int i = 0; i < IMAGEN_HEIGHT; ++i) {
        delete[] pixeles[i];
    }
    delete[] pixeles;
}