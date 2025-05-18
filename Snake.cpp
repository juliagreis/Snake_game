#include "Snake.h"
#include <iostream>

//------------------construtor e destrutor----------------//

//N-> tamanho inicial do jogador.
// Ao construir uma cobra de tamanho N suas coordenadas sempre serão: (0,0), (0,1), (0,2)...,
// (0,N-1) (a cabeça estará na posição (0,N-1) ).
//É garantido que o parâmetro sempre será maior ou igual a 1 
Snake::Snake(const int& n):cabeca(NULL), calda(NULL), snakeSize(0){
    
    for(int i = 0; i < n; i++) {
        Node* novo = new Node(i, 0);
        if(snakeSize == 0) {
            cabeca = calda = novo;
        } else {
            novo->prev = cabeca;
            cabeca->next = novo;
            cabeca = novo;
        }
        snakeSize++;
    }
}

Snake::~Snake(){
    Node* aux = calda;
    while (aux != NULL) {
        Node* prox = aux->next;
        delete aux;
        aux = prox;
}
}

void Snake::draw(Screen& s,int state){
    Node* aux=calda;
    while(aux!=NULL){
        s.set(aux->posY,aux->posX,state);
        aux=aux->next;
    }
}
//correto ta se mexendo direitinho. mas o corpo nao ta acompanhando
void Snake::move(int dr,int dc,bool eating){
    if(cabeca == NULL) return;

    //registrar uma nova cabeca
    Node *aux=new Node(cabeca->posX+dr,cabeca->posY+dc);

    aux->prev=cabeca;
    cabeca->next=aux;
    cabeca=aux;
    
    if(!eating){
        //deletar a calda
        Node *antigo=calda;
        calda=calda->next;
        if(calda!= NULL)
            calda->prev=NULL;
        delete antigo;            //mas tem que apaga-lo da tela
    }
    else{
        snakeSize++;
    }
}
