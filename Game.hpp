#include "Snake.hpp"
#include "Screen.hpp

class Game{
    private:
        Snake *cobra;
        Screen *tela_atual;  //estado atual da tela do jogo
        int *comidas;   //talvez nao seja int
    public:
        Game(int alt,int larg,int tamanho_cobra);
        ~Game();
        Screen getScreen();
        bool step(int dr,int dc);
        void addFood(int linha,int coluna,int ttl);
        int getNumFood();
};