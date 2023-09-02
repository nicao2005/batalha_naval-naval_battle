#include <stdio.h>
#include <stdlib.h>

#define AGUA ' '
#define NAVIO '#'

#define MP_X 10
#define MP_Y 10

typedef enum {SUB,TORPEDEIRO,TANQUE,PORTAVIOES} tnavios_t;

/*
Tamanho navios
submarino - 2
torpedeiro - 3
ntanque 4
porta avioes - 5
*/


// Prototipos

/* Exibe o mapa com as posicoes do navio

A primeira linha do mapa consiste na identificacao da coluna
E a primeira coluna a identificacao linha

exemplo:

 A B C
1
2  # #
3

mp � a variavel que contem o mapa
*/

void exibeMapa(char *mp,int nLin, int nCol);


/*
Posiciona um navio no mapa
mp : variavel que armazena o mapa
nLin, nCol - numero de linhas e colunas do mapa
navio - define o tipo de navio
pLin, pCol - posicao inicial do navio no mapa
dire��o - para que lado vai o navio a partir do inici
    'C' - para cima
    'B' - para baixo
    'E' - para esquerda
    'D' - para direita
funcao retorna 1 se o navio foi posicionado, 0 se nao foi possivel
*/

int posicionaNavio(char *mp,int nLin, int nCol, tnavios_t navio,int pLin, int pCol, char direcao);
/* Preenche com AGUA todas as posicoes do mapa
mp : variavel que armazena o mapa
nLin, nCol - numero de linhas e colunas do mapa
*/
void initMapa(char *mp,int nLin, int nCol);

void msgPos(int retorno);

int main()
{
    char mapa[MP_Y][MP_X];
    int p;
    printf("-> Mapa original: \n");

    initMapa(mapa,MP_Y,MP_X);

    exibeMapa(mapa,MP_Y,MP_X);

    p=posicionaNavio(mapa,MP_Y,MP_X,SUB,1,1,'B');
    p=posicionaNavio(mapa,MP_Y,MP_X,PORTAVIOES,2,3,'D');
    p=posicionaNavio(mapa,MP_Y,MP_X,TANQUE,5,5,'C');
    msgPos(p);
    printf("\n-> Mapa atualizado:\n");
    exibeMapa(mapa,MP_Y,MP_X);
}


void msgPos(int retorno)
{
    if (retorno==1)
        printf("Navio posicionado!\n");
    else
        printf("Esse nao coube!\n");
}


/* Implementar estas 3 funcoes */

void initMapa(char *mp,int nLin, int nCol)
{
    for(int i=0; i<nLin; i++){
        for(int j=0; j<nCol; j++){
            *(mp+i*nCol+j)=AGUA;
        }
    }
}

void exibeMapa(char *mp, int nlin, int nCol)
{
    printf("  A B C D E F G H I J\n");
    for(int i=0; i<nlin; i++){
            printf("%i ", i+1);
        for(int j=0; j<nCol; j++){
            printf("%c ", *(mp+i*nCol+j));
        }
        printf("\n");
    }
}

int posicionaNavio(char *mp,int nLin, int nCol, tnavios_t navio,int pLin, int pCol, char direcao)
{
    int tam_navio;
    int i;

    switch(navio){
    case SUB:
        tam_navio=2;
        break;
    case TORPEDEIRO:
        tam_navio=3;
        break;
    case TANQUE:
        tam_navio=4;
        break;
    case PORTAVIOES:
        tam_navio=5;
        break;
    default:
        return -1; // não foi possível posicionar
    }


    switch(direcao)
    {
    case 'C': // preenche para cima
        for(i=0; i<tam_navio; i++)
        {
           if (pLin - tam_navio < 0) return -1; // TESTE: FORA DOS LIMITES DO MAPA
                if(*(mp + nCol*(pLin - i) + pCol) != ' ')
                    return -1; // TESTE: NÃO SOBRESSAIR
                else *(mp + nCol*(pLin - i) + pCol) = NAVIO;
        }
    break;

    case 'B': // preenche para baixo
        for(i=0; i<tam_navio; i++)
        {
           if (pLin + tam_navio > 9) return -1; // TESTE: FORA DOS LIMITES DO MAPA
                if(*(mp + nCol*(pLin + i - 1) + pCol - 1) != ' ') {
                    return -1; // TESTE: NÃO SOBRESSAIR
                } else *(mp + nCol*(pLin + i - 1) + pCol - 1) = NAVIO;
        }
    break;


    case 'E': // preenche para esquerda
        for(i=0; i<tam_navio; i++)
        {
           if (pCol - tam_navio < 0) return -1; // TESTE: FORA DOS LIMITES DO MAPA
                if(*(mp + nCol*(pLin - 1) + (pCol - i + 1)) != ' ') {
                    return -1; // TESTE: NÃO SOBRESSAIR
                } else *(mp + nCol*(pLin - 1) + (pCol - i + 1)) = NAVIO;
        }
    break;

    case 'D': // preenche para direita
        for(i=0; i<tam_navio; i++)
        {
           if (pCol + tam_navio > 9) return -1; // TESTE: FORA DOS LIMITES DO MAPA
                if(*(mp + nCol*(pLin - 1) + (pCol + i -1)) != ' ') {
                    return -1; // TESTE: NÃO SOBRESSAIR
                } else *(mp + nCol*(pLin - 1) + (pCol + i - 1)) = NAVIO;
        }
    break;
    }

    return 1;
}
