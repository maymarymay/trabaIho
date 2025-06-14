#include <stdlib.h>

typedef struct {
    double distancia;
    void *infos;
} nodeHeap;

typedef struct {
    nodeHeap *lista;
    int cap;
    int tam;
} theap;

void troca(nodeHeap *a, nodeHeap *b);
int pai(int i);
int filhoEsq(int i);
int filhoDir(int i);
theap *construir_heap(int i);
void desce(theap *heap, int i);
void sobe(theap *heap, int i);
void insere(theap *heap, nodeHeap n);
void liberar(theap *heap);
