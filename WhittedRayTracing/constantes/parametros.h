#pragma once

#ifndef PARAMETROS_H
#define PARAMETROS_H

const int PROFUNDIDAD_MAXIMA = 6; // Profunidad maxima en recursion de ray tracing
const float EPSILON = 0.01f; // Para mitigar colisiones de rayos con su lugar de partida
const float EXPONENTE_ESPECULAR = 64.f; // https://www.dropbox.com/s/rpbc2rsm6lvmdte/IluminacionLocal-1.mp4?e=2&dl=0 minuto 52

//Para calcular la atenuacion de la luz
const float c1 = 10.0f;
const float c2 = 1/100;
const float c3 = 1/200;

#endif