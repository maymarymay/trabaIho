#include <stdio.h>
#include <stdlib.h>
#include <float.h> 
#include <string.h>
#include <assert.h>
#include <math.h> 

/*Definições desenvolvedor usuario*/
#define embtamanho 128 
#define idtamanho 100 

typedef struct _reg {
    float embedding[idtamanho];
    char pessoa[idtamanho];  
} treg;

void *aloca_reg(float *embedding, char *id) {
    treg *reg;
    reg = malloc(sizeof(treg));
    memcpy(reg->embedding, embedding, idtamanho * sizeof(float));
    strncpy(reg->pessoa, id, idtamanho-1);
    return reg;
}

int comparador(void *a, void *b, int pos){
    int ret;
    if (pos == 0){
        ret = ((treg *)a)->embedding[pos] - ((treg *)b)->embedding[pos];
    }else if (pos == 1){
        ret = ((treg *)a)->embedding[pos] - ((treg *)b)->embedding[pos];
    }
    return ret;
}

double distancia(void * a, void *b){
    double soma = 0.0;
    for (int i = 0; i<idtamanho; i++)
    {
        double diferenca = ((treg *)a)->embedding[i] - ((treg*)b)->embedding[i];
        soma += diferenca*diferenca;
    }
        return sqrt(soma);
}


/*Definições desenvolvedor da biblioteca*/
typedef struct _node{
    void * key;
    struct _node * esq;
    struct _node * dir;
}tnode;

typedef struct _arv{
    tnode * raiz;
    int (*cmp)(void *, void *, int);
    double (*dist) (void *, void *);
    int k;
}tarv;



/*funções desenvolvedor da biblioteca*/

void kdtree_constroi(tarv * arv, int (*cmp)(void *a, void *b, int ),double (*dist) (void *, void *),int k){
    arv->raiz = NULL;
    arv->cmp = cmp;
    arv->dist = dist;
    arv->k = k;
}

void _kdtree_insere(tnode **raiz, void * key, int (*cmp)(void *a, void *b, int),int profund, int k){
    if(*raiz == NULL){
        *raiz = malloc(sizeof(tnode));
        (*raiz)->key = key;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
    }else{
        int pos = profund % k;
        if (cmp( (*(*raiz)).key , key ,pos) <0){
            _kdtree_insere( &((*(*raiz)).dir),key,cmp,profund + 1,k);
        }else{
            _kdtree_insere( &((*raiz)->esq),key,cmp,profund +1,k);
        }
    }
}

void kdtree_insere(tarv *arv, void *key){
    _kdtree_insere(&(arv->raiz),key,arv->cmp,0,arv->k);
}


void _kdtree_destroi(tnode * node){
    if (node!=NULL){
        _kdtree_destroi(node->esq);
        _kdtree_destroi(node->dir);
        free(node->key);
        free(node);
    }
}

void kdtree_destroi(tarv *arv){
    _kdtree_destroi(arv->raiz);
}


void _kdtree_busca(tarv *arv, tnode ** atual, void * key, int profund, double *menor_dist, tnode **menor){
    tnode ** lado_principal; 
    tnode ** lado_oposto;    
    if (*atual != NULL){
        double dist_atual = arv->dist((*atual)->key, key);
        if (dist_atual < *menor_dist){
            *menor_dist = dist_atual;
            *menor = *atual;
        }
        int pos = profund % arv->k;
        int comp = arv->cmp(key, (*atual)->key, pos);

        printf("%s dist %4.3f menor_dist %4.3f comp %d\n", ((treg *)((tnode *)*atual)->key)->pessoa,dist_atual,*menor_dist,comp);

        /* define lado principal para buscar */
        if (comp < 0){
            lado_principal =  &((*atual)->esq);
            lado_oposto    =  &((*atual)->dir); 
        }else{
            lado_principal =  &((*atual)->dir);
            lado_oposto    =  &((*atual)->esq); 
        }

        _kdtree_busca(arv, lado_principal, key, profund + 1, menor_dist, menor);

        /* Verifica se deve buscar também no outro lado*/

        if (comp*comp < *menor_dist) {
            printf("tentando do outro lado %f\n",comp*comp);
            _kdtree_busca(arv, lado_oposto, key, profund + 1, menor_dist, menor);
        }
    }
}


tnode * kdtree_busca(tarv *arv, void * key){
    tnode * menor = NULL;
    double menor_dist = DBL_MAX;
    _kdtree_busca(arv,&(arv->raiz),key,0,&menor_dist,&menor);
    return menor;
}

tarv arvore_global;

tarv* get_tree() {
    return &arvore_global;
}

void inserir_ponto(treg p) {
    treg *novo = aloca_reg(p.embedding, p.pessoa);
    kdtree_insere(&arvore_global,novo);
}
void kdtree_construir() {
    arvore_global.k = idtamanho;
    arvore_global.dist = distancia;
    arvore_global.cmp = comparador;
    arvore_global.raiz = NULL;
}


int main(void){
    printf("SUCCESS!!\n");
    return EXIT_SUCCESS;
}
