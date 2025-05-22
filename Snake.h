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

    public:
        Snake(const int& n);
        ~Snake();
        void draw(Screen& s,const int state);
        void move(int dr, int dc, bool eating);
        int getLength()const{return snakeSize;};

        //funcoes auxiliares
        int get_posx_cabeca()const {return cabeca->posX;};
        int get_posy_cabeca() const{return cabeca->posY;};

        int get_posx_cauda() const { return calda->posX; }  
        int get_posy_cauda() const { return calda->posY; }  

        int get_posx_prev_cabeca()const{return cabeca->prev ? cabeca->prev->posX : cabeca->posX;};
        int get_posy_prev_cabeca()const{return cabeca->prev ? cabeca->prev->posY : cabeca->posY;};
};

#endif