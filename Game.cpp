#include "Game.h"
#include <iostream>

Game::Game(int alt,int larg,int tamanho_cobra){

    tela_atual=new Screen(alt,larg);
    cobra=new Snake(tamanho_cobra);
    cobra->draw(*tela_atual,Screen::SNAKE);

    comidas=new int*[10];  //alocando 10 posicoes(maximo)  [iteracoes][x][y]
    for(int i=0;i<10;i++)
        comidas[i]=new int[3]; //iniciando como invalido

    comidas_ativas=0;
}
Game::~Game(){
    //deletando a memoria alocada pela classe
    delete tela_atual;
    delete cobra;
    for(int i=0;i<10;i++)
        delete[] comidas[i];
    delete[] comidas;

    //impedindo o armazenamento de lixo de memória
    comidas_ativas=0;
    cobra=NULL;
    tela_atual=NULL;
    comidas=NULL;
}

void Game::addFood(int dr, int dc,int ttl){
    if(tela_atual->get(dr,dc)!=tela_atual->EMPTY){
        //se já há comida nessa posicao, a funcao nao deve fazer nada
        return;
    }

    //armazenando iteracoes, posx e posy dentro do array de comidas
    comidas[10-getNumFood()-1][0]=ttl+1;
    comidas[10-getNumFood()-1][1]=dr;
    comidas[10-getNumFood()-1][2]= dc;

    comidas_ativas++;
    tela_atual->set(dr,dc,tela_atual->FOOD);
}

void Game::removeComida(int x, int y) {
    for (int i = 10 - comidas_ativas; i < 10; ++i) {
        if (comidas[i][1] == x && comidas[i][2] == y) {
            // Substitui pela última comida ativa
            comidas[i][0] = comidas[10 - comidas_ativas][0];
            comidas[i][1] = comidas[10 - comidas_ativas][1];
            comidas[i][2] = comidas[10 - comidas_ativas][2];
            comidas_ativas--;
            tela_atual->set(x, y, tela_atual->EMPTY);
            break;
        }
    }
}

bool Game::step(int dc,int dr){
    //verificar se é válido o deslocamento que foi solicitado
    //se sim, chamar o funcao de snake pra andar -> atualizar screen->retornar true
    //se nao, retornar falso
    
    int novox,novoy;
    //se tiver querendo andar pra uma posicao inválida
    if(dr == (cobra->get_posx_prev_cabeca() - cobra->get_posx_cabeca())
        && (dc == (cobra->get_posy_prev_cabeca() - cobra->get_posy_cabeca()))){    
        
    //ignoramos e andamos pra direcao anterior
    
        //fluxo normal
        dr=-dr;
        dc=-dc;
        novox= cobra->get_posx_cabeca()+dr;
        novoy= cobra->get_posy_cabeca()+dc;
    }
    else{
        //movimento normal
        novox = cobra->get_posx_cabeca() + dr;
        novoy = cobra->get_posy_cabeca() + dc;
    }
    //colisoes

    int elemento=tela_atual->get(novoy,novox);
    if(elemento==tela_atual->SNAKE){
        if(novoy!=cobra->get_posy_cauda() || novox!=cobra->get_posx_cauda()) //andando em circulos?
            return false; //derrota
    }
    if(elemento==tela_atual->WALL)
        return false; //derrota

    //remove comida se tiver
    bool eating=(elemento==tela_atual->FOOD);
    if(eating){
        removeComida(novoy,novox);
    }

    //guarda posição da cauda ANTES de mover
    int oldTailX = cobra->get_posx_cauda();
    int oldTailY = cobra->get_posy_cauda();

    //Apaga a cobra inteira da tela ANTES de mover
    cobra->draw(*tela_atual, tela_atual->EMPTY);
    // Move a cobra
    cobra->move(dr, dc,eating);
    // Desenha a nova posição
    cobra->draw(*tela_atual, tela_atual->SNAKE);
    

    //verificar a validade das frutas!
    for(int i=10-comidas_ativas;i<10;i++){
        if(comidas[i][0]>0)  //evitar decrementar comidas que ja foram decrementadas
            comidas[i][0]--;

        if(comidas[i][0]==0){  //entao essa comida deve ser removida da tela

            tela_atual->set(comidas[i][1],comidas[i][2],tela_atual->EMPTY);
        }
    }
    //limpar alimentos expirados
    while (comidas_ativas > 0 && comidas[10 - comidas_ativas][0] == 0)
        comidas_ativas--;
    
    return true;

}
