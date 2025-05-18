#include "Game.h"
#include <iostream>

Game::Game(int alt,int larg,int tamanho_cobra){

    tela_atual=new Screen(alt,larg);
    cobra=new Snake(tamanho_cobra);
    cobra->draw(*tela_atual,Screen::SNAKE);

    comidas=new int*[10];  //alocando 10 posicoes(maximo)  
    for(int i=0;i<10;i++)
        comidas[i]=new int[3]; //iniciando [iteracoes][pos_x][pos_y]

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
    //o objetivo é tornar o acesso ao array comidas o menos custoso possivel
    for (int i = 10 - comidas_ativas; i < 10; ++i) {
        if (comidas[i][1] == x && comidas[i][2] == y) {
            //substitui pela última comida ativa
            comidas[i][0] = comidas[10 - comidas_ativas][0];
            comidas[i][1] = comidas[10 - comidas_ativas][1];
            comidas[i][2] = comidas[10 - comidas_ativas][2];
            comidas_ativas--;
            tela_atual->set(x, y, tela_atual->EMPTY);
            break;
        }
    }
}

bool Game::step(int dr, int dc) {
    // Verifica se estamos tentando inverter a direção
    int prevX = cobra->get_posx_prev_cabeca();
    int prevY = cobra->get_posy_prev_cabeca();
    int cabecaX = cobra->get_posx_cabeca();
    int cabecaY = cobra->get_posy_cabeca();
    
    //se estamos tentando ir na direção oposta/invalida, ignoramos
    if (dr == -1 * (cabecaY - prevY) && dc == -1 * (cabecaX - prevX)) {
        //segue direção atual
        dr = cabecaY - prevY;
        dc = cabecaX - prevX;
    }
    
    //calcula a nova posição da cabeça
    int novoY = cabecaY + dr;
    int novoX = cabecaX + dc;
    
    //colisões
    int elemento = tela_atual->get(novoY, novoX);
    
    //colisão com a parede ou com a própria cobra (exceto a cauda que vai se mover pq pode ficar ciclica)
    if (elemento == Screen::WALL) {
        return false; //derrota
    }
    
    if (elemento == Screen::SNAKE) {
        // se colidir com uma parte que não é a cauda, ou se a cauda não vai se mover(se tiver comendo)
        int caudaX = cobra->get_posx_cauda();
        int caudaY = cobra->get_posy_cauda();

        if (novoX != caudaX || novoY != caudaY) {  //se estiver ciclico  
            return false; //derrota
        }
    }
    
    //verifica se vai comer
    bool eating = (elemento == Screen::FOOD);
    if (eating) {
        removeComida(novoY, novoX);
    }
    
    //apaga a cobra da tela antes de movê-la (obj: fazer com que o rabo seja apagado caso a cobra nao esteja comendo)
    cobra->draw(*tela_atual, Screen::EMPTY);
    
    //move a cobra
    cobra->move(dr, dc, eating);
    
    //desenha a nova posição da cobra
    cobra->draw(*tela_atual, Screen::SNAKE);
    
    //atualiza o tempo de vida das comidas
    for (int i = 10 - comidas_ativas; i < 10; i++) {
        if (comidas[i][0] >0) {
            comidas[i][0]--;
            
            //se o tempo acabou, remove a comida da tela
            if (comidas[i][0] == 0) {
                tela_atual->set(comidas[i][1], comidas[i][2], Screen::EMPTY);
            }
        }
    }
    
    //remove comidas expiradas
    int pos = 10 - comidas_ativas;
    while (comidas_ativas > 0 && pos < 10 && comidas[pos][0] == 0) {
        pos++;
        comidas_ativas--;
    }
    
    return true;
}