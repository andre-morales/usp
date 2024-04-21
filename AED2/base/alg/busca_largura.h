#pragma once
#include "busca.h"
#include "../grafo_fwd.h"

// Executa uma busca em profundidade no grafo dado.
// grafo: Grafo alvo da busca
// acessos: Estrutura de configuração de acessos
// objeto: Um ponteiro opcional acessível durante a busca
void buscaLargura(Grafo* grafo, Acessos acessos, void* objeto);
