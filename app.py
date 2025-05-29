# app.py
from fastapi import FastAPI, Query
from kdtree_wrapper import lib, Tarv, TReg
from ctypes import POINTER,c_char, c_float
from pydantic import BaseModel, conlist

app = FastAPI()


class PontoEntrada(BaseModel):
    embedding: conlist(float, max=128, min=128)
    id: str

@app.post("/construir-arvore")
def constroi_arvore():
    lib.kdtree_construir()
    return {"mensagem": "Árvore KD inicializada com sucesso."}

@app.post("/inserir")
def inserir(ponto: PontoEntrada):
    idbytes = ponto.id.encode('utf-8')[:99] 
    vet = (c_float * 128)(*ponto.embedding);
    novo = TReg(embedding=vet, nome=idbytes)
    lib.inserir_ponto(novo)
    return {"mensagem": f"Ponto '{ponto.id}' inserido com sucesso."}

@app.get("/buscar")
def buscar(lat: float = Query(...), lon: float = Query(...)):
    vetor = (c_float*128)(*query.embedding)
    bytesid = query.id.encode("utf-8")[:99]
    query = TReg(embedding = vetor, id = bytesid)

    arv = lib.get_tree()  # Suponha que esta função retorne ponteiro para árvore já construída
    resultado = lib.buscar_mais_proximo(arv, query)

    return {
        "id": resultado.id.decode("utf-8").rstrip("\x00"),
        "embedding": list(resultado.embedding)[:5]
    }
