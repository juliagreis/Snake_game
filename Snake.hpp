//esta classe funciona como uma lista duplamente encadeada, portanto
//snake é composto por nodos  -> nodo e snake sao classe amigas
#include "Node.hpp"

// calda -------------[] cabeca
class Snake{
    friend class Node;
    private:
        Node* calda;    //fim
        Node* cabeça;    //cabeca
        int snakeSize;
        void crescer(int x,int y);   //talvez preciso verificar se esta dentro do intervalo
    public:
        Snake(const int& n);
        ~Snake();
        void draw(Screen s,int state);
        void move(int dr, int dc, bool eating);
        int getLength(){return snakeSize;};
};

//------------------construtor e destrutor----------------//

//N-> tamanho inicial do jogador.
// Ao construir uma cobra de tamanho N suas coordenadas sempre serão: (0,0), (0,1), (0,2)...,
// (0,N-1) (a cabeça estará na posição (0,N-1) ).
//É garantido que o parâmetro sempre será maior ou igual a 1 
Snake::Snake(const int& n){
    int contador=0;
    while(cont<n){
        crescer(0,contador);
        cont++;
    }
}

void Snake::crescer(int x,int y){  //logica do push front
    if(snakeSize==0){
        cabeca=calda=new Node(x,y);
    }
    else{
        Node* aux=new Node(x,y);
        calda->prev=aux;
        aux->next=calda;
        calda=aux;
    }
    snakeSize ++;
}

Snake::~Snake(){
    Node* aux=cabeca->prev;
    while(aux!=NULL){
        delete cabeca;
        cabeca=aux;
        aux= cabeca->prev;
    }
    cabeca=calda=NULL;
    snakeSize=0;

}

