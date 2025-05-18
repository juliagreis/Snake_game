#include "Screen.h"

Screen::Screen(int alt,int larg){
    largura= larg;
    altura=alt;

    data=new int *[largura];
    dataHeight=new int[largura];
    
    for(int i=0;i<largura;i++){
        data[i]=NULL;
        dataHeight[i]=0;
    }
}

Screen::~Screen(){

    for(int i=0;i<largura;i++)
        delete[] data[i];
    delete[] data;
    delete[] dataHeight;
}

int Screen::get(int linha,int coluna)const{
    if(linha<0 || linha>=altura||coluna<0||coluna>=largura)
        return WALL;
    
    if(linha>=dataHeight[coluna]|| dataHeight[coluna] == 0)
        return EMPTY;
    
    return data[coluna][linha];
    
}
void Screen::set(int linha,int coluna,int val){
    if (linha < 0 || linha >= altura || coluna < 0 || coluna >= largura)
        return;  // fora da tela

    // se precisa aumentar o tamanho da coluna
    if(linha>=dataHeight[coluna]){
        int *novaColuna=new int[linha+1];

        //atualizando valores antigos para a nova coluna
        for(int i=0;i<dataHeight[coluna];i++)
            novaColuna[i]=data[coluna][i];
        //colocando novas posicoes como empty
        for (int i = dataHeight[coluna]; i <= linha; ++i)
            novaColuna[i] = EMPTY;

        delete[] data[coluna];
        data[coluna]=novaColuna;
        dataHeight[coluna]=linha+1;
    }

    data[coluna][linha]=val;

}
