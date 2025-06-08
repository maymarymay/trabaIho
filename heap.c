#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
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
    int imin = i;
    if (e < heap->tam && heap->lista[e].distancia > heap->lista[imin].distancia)
        imin = e;
    if (d < heap->tam && heap->lista[d].distancia > heap->lista[imin].distancia)
        imin = d;
    if (imin != i){
        troca(&(heap->lista[i]),&(heap->lista[imin]));
        desce(heap,imin);
    }
}

void sobe(theap * heap,int i){
    int p;
    if ((i > 0) && (i < heap->tam)){
        p = pai(i);
        while (heap->lista[i].distancia < heap->lista[p].distancia){
            troca(&heap->lista[i],&heap->lista[p]);
            i = p; 
            p = pai(i);   
        }
    }
}


int heap_insere(theap * heap, nodeHeap n){
   if (heap->tam < heap->cap){
        heap->lista[heap->tam] = n;
        heap->tam++;
        sobe(heap,heap->tam-1);
        return EXIT_SUCCESS;
    }else{
        return EXIT_FAILURE;
    }
}

/////////nsei se daria certo mas vou deixar aqui por preucas..... 
//void insere (theap*heap, nodeHeap n)
//{
//   if (heap->tam == heap->cap)
//   {
//        if (n.distancia<heap->lista[heap->tam-1].distancia)
//        {
//            heap->lista[heap->tam-1] = n;
//            troca(&heap->lista[0], &heap->lista[heap->tam-1]);
//            desce(heap, 0);
//        }
//    }
//    else
//    {
//        heap->lista[heap->tam] = n;
//        heap->tam++;
//        int i = heap->tam-1;
//        sobe(heap,i);
//    }
//}

void libera(theap*heap)
{
    if (heap == NULL)
    {
        return;
    }
    free(heap->lista);
    free(heap);
}
