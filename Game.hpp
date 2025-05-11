#include "Snake.hpp"
#include "Screen.hpp"

class Game{
    private:
        Snake *cobra;
        Screen *tela_atual;  //estado atual da tela do jogo
        int *comidas;   //talvez nao seja int
        //quanto mais recente for a comida, mais ao inicio do vetor ela se encontra
        int comidas_ativas;
    public:
        Game(int alt,int larg,int tamanho_cobra);
        ~Game();
        Screen getScreen();
        bool step(int dr,int dc);
        void addFood(int linha,int coluna,int ttl);
        int getNumFood(){return comidas_ativas;};
};

Game::Game(int alt,int larg,int tamanho_cobra){

    tela_atual=new Screen(alt,larg);
    cobra=new Snake(tamanho_cobra);
    comidas=new int[10];  //alocando 10 posicoes(maximo)
    comidas_ativas=0;
}
Game::~Game(){
    //deletando a memoria alocada pela classe
    delete tela_atual;
    delete cobra;
    delete[] comidas;

    //impedindo o armazenamento de lixo de memória
    comidas_ativas=0;
    cobra=tela_atual=comidas=NULL;
}

void Game::addFood(int dr, int dc,int ttl){
    if(tela_atual->get(dr,dc)==tela_atual->EMPTY){
        //se já há comida nessa posicao, a funcao nao deve fazer nada
        return;
    }
    tela_atual->set(dr,dc,tela-_atual->FOOD);
    comidas[10-getNumFood]=ttl;
    comidas_ativas++;
}

bool Game::step(int dr,int dc){
    
}