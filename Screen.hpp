//matriz dinâmica representando a tela. 
//Cada objeto da tela é representado por um código (inteiro) inteiro distinto 
#include <cstdlib>
class Screen{
    private:
        int largura;
        int altura;
        int **data;
        int *dataHeight;    //????????

    public:
        const int FOOD=1, SNAKE=2, EMPTY=3, WALL=4;

        Screen(int alt,int larg);
        ~Screen();   //confirmar se ta deletando corretamente
        int getWidth() const {return largura;};
        int getHeight() const{return altura;};
        int get(int linha,int coluna);
        void set(int linha,int coluna,int val);

};

Screen::Screen(int alt,int larg){
    largura= larg;
    altura=alt;
    **data=NULL;
    *dataHeight=NULL;
}
Screen::~Screen(){
    for(int i=0;i<largura;i++)
        delete[] data;
    delete[] data;
}
int Screen::get(int linha,int coluna){
    return data[linha][coluna];
}

void Screen::set(int linha,int coluna,int val){
    data[linha][coluna]=val;
}