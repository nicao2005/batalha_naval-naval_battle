#include <stdio.h>
#include <stdlib.h>

/*
Construa a funcao posicionaNavio(),
segundo as espeficicacoes dadas

*/

#define NLIN 10
#define NCOL 30

/**
@brief posiciona navio no tabuleiro = preenche posicao com #
@param navio a ser posicionado
       P - porta-avioes     - 5
       T - navio-tanque     - 4
       C - contratorpedeiro - 3
       U - submarino        - 2
@param [lin,col] - coordenadas ponta do navio
@param direcao  - direcao da embarcacao a partir no ponto inicial
       N - norte - para cima
       S - sul   - para baixo
       L - leste - para direita
       O - oeste - para esquerda
@param mapa - mapa do jogador x
@param [nlin,ncol] - numero de linhas / colunas do mapa.
@retval 0  - posicionado com sucesso
        -1 - nao foi possivel posicionar o navio
*/
int posicionaNavio(char navio,int lin,int col, char direcao, char *mapa,int nlin,int ncol);

void desenhaMapa(char *mapa,int nlin,int ncol);

int main()
{
    char mapa[NLIN][NCOL];
    int lin,col;
    char navio;
    char direcao;
    for (lin=0;lin<NLIN;lin++)
    {
        for (col=0;col<NCOL;col++)
        {
            mapa[lin][col]=' ';
        }
    }

    printf("Batalha Naval\n\n");
    printf("Navios :\nP - porta-avioes\nT - navio-tanque\nC - contra-torpedeiro\nU - submarino\n");
    printf("APERTE Q PARA SAIR!\n");

    while(1)
    {
       desenhaMapa(mapa,NLIN,NCOL);
       printf("Qual navio deseja posicionar ? : ");
       scanf("%c",&navio);
       fflush(stdin);
       printf("\n");
       navio=toupper(navio);
       switch(navio)
       {
       case 'Q':
            return 0;
       case 'P':
       case 'T':
       case 'C':
       case 'U':
           {
             printf("Posicao inicial [lin,col]: ");
             scanf("%d,%d",&lin,&col);
             fflush(stdin);
             printf("\nDirecao[N,S,L,O]: ");
             scanf("%c",&direcao);
             fflush(stdin);
             direcao=toupper(direcao);
             printf("\n");

             direcao=posicionaNavio(navio,lin,col,direcao,mapa,NLIN,NCOL);

              if (direcao<0)
                {
                printf("Nao foi possivel possicionar o ");

                switch(navio)
                    {
                    case 'P':
                        printf("porta-avioes\n");
                        break;
                    case 'T':
                        printf("navio-tanque\n");
                        break;
                    case 'C':
                        printf("contra-torpedeiro\n");
                        break;
                    case 'U':
                        printf("submarino\n");
                        break;
                    }
                }
            }
    }
   }
}

void linhaLimite(int col)
{
    int c;
    printf("+");
    for (c=0;c<col;c++)
     printf("-");
    printf("+\n");
}

void desenhaMapa(char *mapa,int nlin,int ncol)
{
 int lin,col;
    linhaLimite(ncol);
    for (lin=0;lin<nlin;lin++)
    {
        printf("|");
        for(col=0;col<ncol;col++)
        {
            printf("%c",*(mapa+lin*ncol+col));
        }
         printf("|\n");
    }
     linhaLimite(ncol);
}

int posicionaNavio(char navio,int lin,int col, char direcao, char *mapa,int nlin,int ncol)
{
    int tamanho_navio;

    switch(navio){
    case 'P': // porta-aviões
        tamanho_navio=5;
        break;
    case 'T': // navio-tanque
        tamanho_navio=4;
        break;
    case 'C': // contratorpedeiro
        tamanho_navio=3;
        break;
    case 'U': // submarino
        tamanho_navio=2;
        break;
    default:
        return -1; // não foi possível posicionar o navio
        break;
    }

    switch(direcao){
    case 'S':
    // direciona o navio para o sul
    for(int i=0; i<tamanho_navio; i++){
        if(lin-tamanho_navio>10)
            return -1; // limites do mapa

        if(*(mapa+NCOL*(lin-i)+col)!=' ')
            return -1; // teste para não sobressair navios

        else
            *(mapa+NCOL*(lin-i)+col)='#';
    }
    break;

    case 'N':
    // direciona o navio para o norte
    for(int i=0; i<tamanho_navio; i++){
        if(lin+tamanho_navio<-1)
            return -1; // limites do mapa

        if(*(mapa+NCOL*(lin-i-1)+col)!=' ')
            return -1; // teste para não sobressair navios

        else
            *(mapa+NCOL*(lin-i-1)+col)='#';
    }
    break;

    case 'L':
    // direciona o navio para leste (direita)
    for(int i=0; i<tamanho_navio; i++){
        if(col+tamanho_navio>30)
            return -1; // limites do mapa

        if(*(mapa+NCOL*(lin-1)+(col+i))!=' ')
            return -1; // teste para não sobressair navios

        else
            *(mapa+NCOL*(lin-1)+(col+i))='#';
    }
    break;

    case 'O':
    // direciona o navio para oeste (esquerda)
    for(int i=0; i<tamanho_navio; i++){
        if(col-tamanho_navio<-1)
            return -1; // limites do mapa

        if(*(mapa+NCOL*(lin-1)+(col-i-1))!=' ')
            return -1; // teste para não sobressair navios

        else
            *(mapa+NCOL*(lin-1)+(col-i-1))='#';
    }
    break;

    }
    return 0;
}
