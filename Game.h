#ifndef GAMEHPP
#define GAMEHPP

#include "Snake.h"
#include "Screen.h"

class Game{
    private:
        Snake *cobra;       //cobra composta por nodes
        Screen *tela_atual;  //estado atual da tela do jogo
        int **comidas;      //array de comida
        int comidas_ativas;
    public:
        Game(int alt,int larg,int tamanho_cobra);
        ~Game();
        Screen& getScreen(){return *tela_atual;};
        bool step(int dr,int dc);
        void addFood(int linha,int coluna,int ttl);
        int getNumFood(){return comidas_ativas;};
        void removeComida(int dr,int dc);
};

#endif