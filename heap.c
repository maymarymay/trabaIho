#include <stdio.h> 
#include <stdlib.h> 
#include "heap.h" 

/* FUNCOES HEAP */
void troca(nodeHeap *a, nodeHeap *b){
    nodeHeap aux = *a;
    *a  = *b;
    *b  = aux;
}
int pai(int i){
    return (i-1)/2;
}
int filho_esq(int i){
    return i*2 +1;
}
int filho_dir(int i){
    return i*2 +2;
}

theap *contstroi_heap (int i){
    theap*heap = (theap*)malloc(sizeof(theap));
    if (heap==NULL)
    {
        exit(EXIT_FAILURE);
    }
    heap->lista = (nodeHeap*)malloc(i*sizeof(nodeHeap));
    if (heap->lista==NULL)
    {
        free(heap);
        exit(EXIT_FAILURE);
    }
    heap->cap=i;
    heap->tam=0;
    return heap;
}

void desce(theap * heap,int i){
    int e = filho_esq(i);
    int d = filho_dir(i);
    int maior = i;
    if (e < heap->tam && heap->lista[e].distancia > heap->lista[maior].distancia) {
        maior = esq;
    }
    if (d < heap->tam && heap->lista[d].distancia > heap->lista[maior].distancia) {
        maior = d;
    }

    if (maior != i) {
        troca(&heap->lista[i], &heap->lista[maior]);
        desce(heap, maior);
    }
}

void sobe(theap *heap, int i) {
    int p;
    while (i > 0) {
        p = pai(i);
        if (heap->lista[i].distancia < heap->lista[p].distancia) {
            troca(&heap->lista[i], &heap->lista[p]);
            i = p; 
        }
    }
}

void insere(theap *heap, nodeHeap n) {
    if (heap->tam < heap->cap) {
        heap->lista[heap->tam] = n;
        sobe(heap, heap->tam);
        heap->tam++;
    } else if (n.distancia < heap->lista[0].distancia) {
        heap->lista[0] = n;
        desce(heap, 0);
    }
}

void liberar(theap *heap) 
{
    if (heap == NULL)
    {
        return;
    }
    free(heap->lista);
    free(heap);
}
