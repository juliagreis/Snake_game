#ifndef SCREENHPP
#define SCREENHPP

//matriz dinâmica representando a tela. 
//Cada objeto da tela é representado por um código (inteiro) inteiro distinto 
#include <cstdlib>
class Screen{
    private:
        int largura;
        int altura;
        int **data;          //data[c] é a coluna c
        int *dataHeight;     //dataHeight[c] é o tamanho do vetor data[c]

    public:
        const static int FOOD=0, SNAKE=1, EMPTY=2, WALL=-1;

        Screen(int alt,int larg);
        ~Screen();   

        int getWidth() const {return largura;};
        int getHeight() const{return altura;};
        int get(int linha,int coluna) const ;
        void set(int linha,int coluna,int val);

};


#endif