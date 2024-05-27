#pragma once

#ifndef PARAMETROS_H
#define PARAMETROS_H

const int IMAGEN_WIDTH = 1024;
const int IMAGEN_HEIGHT = 1024;

const int HALF_IMAGE_WIDTH = 512;
const int HALF_IMAGEN_HEIGHT = 512;

const int PROFUNDIDAD_MAXIMA = 5; // Profunidad maxima en recursion de ray tracing
const float EPSILON = 0.001f; // Para mitigar colisiones de rayos con su lugar de partida

#endif