#pragma once
#ifndef DESCUENTOS_H
#define DESCUENTOS_H
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;
const int MAX_DIAS = 7;
const int MAX_SECC = 8;

typedef int tDescuento[MAX_DIAS][MAX_SECC];

bool cargardescuento(string nombre,tDescuento &descuento);


#endif // !DESCUENTOS_H

