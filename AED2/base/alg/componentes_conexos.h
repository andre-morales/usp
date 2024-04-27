#pragma once
#include "grafo_fwd.h"

struct ListaT;
typedef struct ListaT Lista;

int componentesConexos(Grafo* g, Lista** componentesPtr);