#include "Snake.hpp"
#include <cstdlib>

class Node{
    class Friend Snake;
    private:
        Node* prev;
        Node* next;
        int posX;
        int posY;
    public:
        Node(int x,int y){prev=next=NULL; posX=x;posY=y};
        ~Node(){prev=next=NULL;};
};