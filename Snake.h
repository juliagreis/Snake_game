#ifndef SNAKEHPP
#define SNAKEHPP

//esta classe funciona como uma lista duplamente encadeada, portanto
//snake é composto por nodos
#include "Screen.h"

// first/calda -------------[] cabeca/last
class Snake{
    
    private:
        //------node-------//
        class Node{
            public:
                Node* prev;
                Node* next;
                int posX;
                int posY;
                Node(int x,int y){prev=next=NULL; posX=x;posY=y;};
                ~Node(){prev=next=NULL;};
        };
        // ------node--------//

        Node* calda;    //fim
        Node* cabeca;    //cabeca
        int snakeSize;
        void crescer(int x,int y);   //talvez preciso verificar se esta dentro do intervalo

    public:
        Snake(const int& n);
        ~Snake();
        void draw(Screen& s,int state);
        void move(int dr, int dc, bool eating);
        int getLength(){return snakeSize;};

        int get_posx_cabeca(){return cabeca->posX;};
        int get_posy_cabeca(){return cabeca->posY;};

        int get_posx_cauda() const { return calda->posX; }  
        int get_posy_cauda() const { return calda->posY; }  

        int get_posx_prev_cabeca(){return cabeca->prev ? cabeca->prev->posX : cabeca->posX;};
        int get_posy_prev_cabeca(){return cabeca->prev ? cabeca->prev->posY : cabeca->posY;};
};

#endif