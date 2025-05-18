#ifndef GAMEHPP
#define GAMEHPP

#include "Snake.h"
#include "Screen.h"

class Game{
    private:
        Snake *cobra;
        Screen *tela_atual;  //estado atual da tela do jogo
        int **comidas;   //talvez nao seja int
        //quanto mais recente for a comida, mais ao inicio do vetor ela se encontra
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