O trabalho 1 consiste em desenvolver o código para fazer reconhecimento facial, utilizando uma base de embeddings armazenados em uma KDTree (ABB modificada)

Refatorar o código fornecido em sala para que a API de latitude e longitude com as seguintes alterações:

1- incomporar heap para que a busca retorne os N vizinhos mais próximo na árvore KD (opcional)

2- alterar a estrutura de dados para que ela comporte um vetor de 128 floats  e uma string de 100 caracteres para representar respectivamente o embedding de face e o id da pessoa

Depois, faça chamadas a API para armazenar 1000 faces, incluindo a sua (SUA?!?! [no caso minha né]) e de mais duas pessoas e verifique se dentre as 5 mais proximas está a sua da pessoa conhecida com auxilio do códico no Google Collab
