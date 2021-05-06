#include "campo.h"
#include "fila.h"

void trocaElemento(Campo c, int x, int y, int elem)
{
    int aux = c.matriz[x][y];
    if((x < c.lin && y < c.col) && (x >= 0 && y >= 0))
    {
        c.matriz[x][y] = elem;
        if(c.matriz[x+1][y] == aux)
            trocaElemento(c, x+1, y, elem);
        if(c.matriz[x-1][y] == aux)
            trocaElemento(c, x-1, y, elem);
        if(c.matriz[x][y+1] == aux)
            trocaElemento(c, x, y+1, elem);
        if(c.matriz[x][y-1] == aux)
            trocaElemento(c, x, y-1, elem);
    }
}
int verificaJogo(Campo c)
{
    int elem = c.matriz[1][1];
    for(int i = 1; i < c.lin-1; i++)
    {
        for(int j = 1; j < c.col-1; j++)
        {
            if(c.matriz[i][j] != elem)
                return 1;
        }
    }
    return 0;
}
int melhorCandidato(Campo c)
{
    int elemInundado = c.matriz[1][1];
    for(Queue *i = c.inundado; i != NULL; i = i->next)
    {
        if((i->x < c.lin && i->y < c.col) && (i->x >= 0 && i->y >= 0))
        {
            if(c.matriz[i->x+1][i->y] != elemInundado)
                c.vizinhos = enqueue(c.vizinhos, i->x+1, i->y);
            if(c.matriz[i->x-1][i->y] != elemInundado)
                c.vizinhos = enqueue(c.vizinhos, i->x-1, i->y);
            if(c.matriz[i->x][i->y+1] != elemInundado)
                c.vizinhos = enqueue(c.vizinhos, i->x, i->y+1);
            if(c.matriz[i->x][i->y-1] != elemInundado)
                c.vizinhos = enqueue(c.vizinhos, i->x, i->y-1);
        }
    }
    for(int i = 0; i < c.lin; i++)
    {
        for(int j = 0; j < c.col; j++)
        {
            if(c.matriz[i][j] == elemInundado && verificaNode(c.inundado, i, j))
                c.inundado = enqueue(c.inundado, i, j);
        }
    }
    int vetor[5] = {0};
    for(Queue *i = c.vizinhos; i != NULL; i = i->next)
    {
        if(c.matriz[i->x][i->y] == 0)
            vetor[0]++;
        else if(c.matriz[i->x][i->y] == 1)
            vetor[1]++;
        else if(c.matriz[i->x][i->y] == 2)
            vetor[2]++;
        else if(c.matriz[i->x][i->y] == 3)
            vetor[3]++;
        else if(c.matriz[i->x][i->y] == 4)
            vetor[4]++;
        else
            vetor[5]++;
    }
    int aux = 0;
    int indice = 0;
    for(int i = 0; i < 5; i++)
    {
        if(vetor[i] > aux)
        {
            aux = vetor[i];
            indice = i;
        }
    }
    return indice;
    /* A ideia seria comparar o elemento, olhando atrav�s dos �ndices que seriam armazenados dentro da fila,
       da� existiria um contador que veria qual o que mais se repete, e uma vari�vel que armazenaria qual o elemento que mais se repete,
       ent�o seria retornado esse elemento. O problema fica em ver o vizinho do vizinho, porque a escolha ideal n�o � s� o que mais se repete ao redor
       dos preenchidos, e sim o que mais se estende num contexto geral, ou seja, prevendo o que vai ser preenchido atrav�s dessa escolha.

       Talvez a solu��o seria criar duas filas, uma com os elementos preenchidos, e outra, j� cheia, com os elementos a serem preenchidos ainda.
       E essa compara��o se daria atrav�s da fila dos elementos que ainda precisam preencher. Mas eu ainda n�o consegui pensar num algoritmo bom
       o suficiente para executar essa ideia.*/
}
void resolveJogo(Campo c, int passos)
{
    int x = 1, y = 1;
    c.inundado = enqueue(c.inundado, x, y);

    while(passos < 11)
    {
        //printf("Passo %d insira o numero que quer trocar: ", passos+1);
        //scanf("%d", &elem);
        trocaElemento(c, x, y, melhorCandidato(c));
        imprimeCampo(c);
        printf("\n\n");
        passos++;
    }

}
int jogar(Campo c, int passos)
{
    imprimeCampo(c);
    resolveJogo(c, passos);
/*    while(passos < 11)
    {
        if(!verificaJogo(c, 7))
            return 0;
        printf("Passo %d insira o numero que quer trocar: ", passos+1);
        scanf("%d", &elem);
        resolveJogo(c)
        imprimeCampo(c);
        printf("\n\n");
        passos++;
    }*/
    return verificaJogo(c);
}

int main()
{
    int lin = 7;
    int col = 7;
    Campo c = montaCampo(lin, col);
    if(jogar(c, 10))
        printf("Se Fodeu!\n");
    else
        printf("Ganhou!!\n");
    return 0;
}
