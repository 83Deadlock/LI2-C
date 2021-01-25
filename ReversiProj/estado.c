#include <stdio.h>
#include "estado.h"
#include "botfunction.h"

// Função que imprime o estado do jogo (Tabuleiro)
void printa(ESTADO e, int *contaX,int *contaO)
{
    char c = ' ';
    *contaX = 0;
    *contaO = 0;
    printf("  1 2 3 4 5 6 7 8\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ",i+1);
        for (int j = 0; j < 8; j++) {
            switch (e.grelha[i][j]) {
                case VALOR_O: {
                    c = 'O';
                    (*contaO) ++;
                    break;
                }
                case VALOR_X: {
                    c = 'X';
                    (*contaX) ++;
                    break;
                }
                case VAZIA: {
                    c = '-';
                    break;
                }
            }
            printf("%c ", c);

        }
        printf("\n");
    }

}

// Função que coloca a peça no tabuleiro, de acordo com as posições recebidas

void poepeca (ESTADO *e,int x, int y){
    e->grelha[x][y] = e->peca;
}

// Função que modifica as peças contrárias numa jogada

void joga (ESTADO *e, int x, int y){
    int c=y,l=x;
    VALOR p;
    if (e->peca == VALOR_X) p = VALOR_O; // p -> peça contrária
    else p = VALOR_X;

    // modificar para a direita--------------------------
    c++;
    while (e->grelha[l][c] == p && c < 8) c++;
    if (c==8); //&& e->grelha[l][c] == p);
    else if (e->grelha[l][c] == e->peca){
        for(;c!=y;c--) e->grelha[l][c] = e->peca;
        poepeca(e,x,y);
    }

    else;
    //----------------------------------------------------
    c=y,l=x;

    // modificar para a esquerda-------------------------
    c--;
    while (e->grelha[l][c] == p && c >= 0) c--;
    if (c==-1); // && e->grelha[l][c] == p);
    else if (e->grelha[l][c] == e->peca){
        for (;c!=y;c++) e->grelha[l][c] = e->peca;
        poepeca(e,x,y);
    }
    else;
    //-----------------------------------------------------
    c=y,l=x;

    // modificar para baixo--------------------------------
    l++;
    while (e->grelha[l][c] == p && l < 8) l++;
    if (l == 8); // && e->grelha[l][c] == p);
    else if (e->grelha[l][c] == e->peca){
        for (;l!=x;l--) e->grelha[l][c] = e->peca;
        poepeca(e,x,y);
    }
    else;
    //-----------------------------------------------------
    c=y,l=x;

    // modificar para cima
    l--;
    while (e->grelha[l][c] == p && l >= 0) l--;
    if (l == -1); // && e->grelha[l][c] == p);
    else if (e->grelha[l][c] == e->peca) {
        for (;l!=x;l++) e->grelha[l][c] = e->peca;
        poepeca(e,x,y);
    }
    else;
    //-----------------------------------------------------
    c=y,l=x;

    // modificar cima direita
    l--;c++;
    while (e->grelha[l][c] == p && c < 8 && l >= 0) {
        l--;
        c++;
    }
    if ((l == -1 || c == 8)); // && e->grelha[l][c] == p );
    else if (e->grelha[l][c] == e->peca) {
        for (;l!=x;l++,c--) e->grelha[l][c] = e->peca;
        poepeca(e,x,y);
    }
    else;
    //-----------------------------------------------------
    c=y,l=x;

    // modificar cima esquerda
    l--;c--;
    while (e->grelha[l][c] == p && c >= 0 && l >= 0) {
        l--;
        c--;
    }
    if ((l == -1 || c == -1)); // && e->grelha[l][c] == p);
    else if (e->grelha[l][c] == e->peca) {
        for (;l!=x;l++,c++) e->grelha[l][c] = e->peca;
        poepeca(e,x,y);
    }
    else;
    //-----------------------------------------------------
    c=y,l=x;

    // modificar baixo esquerda
    l++;c--;
    while (e->grelha[l][c] == p && c >= 0 && l < 8) {
        l++;
        c--;
    }
    if ((l == 8 || c == -1)); // && e->grelha[l][c] == p);
    else if (e->grelha[l][c] == e->peca) {
        for (;l!=x;c++,l--) e->grelha[l][c] = e->peca;
        poepeca(e,x,y);
    }
    else;
    //-----------------------------------------------------
    c=y,l=x;

    // modificar baixo direita
    l++;c++;
    while ( c < 8 && l < 8 && e->grelha[l][c] == p) {
        l++;
        c++;
    }
    if ((l == 8 || c == 8) && e->grelha[l][c] == p);
    else if (e->grelha[l][c] == e->peca) {
        for (;l!=x;l--,c--) e->grelha[l][c] = e->peca;
        poepeca(e,x,y);
    }
    else;
    //-----------------------------------------------------
}

// Função que cria um "tabuleiro imaginário" com as jogadas que forem válidas

void verificajogada2 (ESTADO *e){
    int i,k;
    for (i=0;i<8;i++){
        for (k=0;k<8;k++){
            e->validade[i][k] = verificajogada(e,i,k);
        }
    }
}

// Função que verifica se uma jogada é válida nas diferentes direções

int verificajogada (ESTADO *e, int x, int y) {
    int flag = 0;
    if (e->grelha[x][y] != VAZIA);
    else {
        int l = x, c = y;
        VALOR p;
        if (e->peca == VALOR_X) p = VALOR_O; // p -> peça contrária
        else p = VALOR_X;

        //direita
        if (e->grelha[x][y + 1] == p) {
            c++;
            while (e->grelha[l][c] == p && c < 8) c++;
            if (e->grelha[l][c] == e->peca && c < 8) flag = 1;
        }
        l = x, c = y;

        //esquerda
        if (flag == 0 && e->grelha[x][y - 1] == p) {
            c--;
            while (e->grelha[l][c] == p && c >= 0) c--;
            if (e->grelha[l][c] == e->peca && c >= 0) flag = 1;
        }
        l = x, c = y;

        //cima
        if (flag == 0 && e->grelha[x - 1][y] == p) {
            l--;
            while (e->grelha[l][c] == p && l >= 0) l--;
            if (e->grelha[l][c] == e->peca && l >= 0) flag = 1;
        }
        l = x, c = y;

        //baixo
        if (flag == 0 && e->grelha[x + 1][y] == p) {
            l++;
            while (e->grelha[l][c] == p && l < 8) l++;
            if (e->grelha[l][c] == e->peca && l < 8) flag = 1;
        }
        l = x, c = y;

        //cima direita
        if (flag == 0 && e->grelha[x - 1][y + 1] == p) {
            l--;c++;
            while (e->grelha[l][c] == p && l >= 0 && c < 8) {
                l--;
                c++;
            }
            if (e->grelha[l][c] == e->peca && l >= 0 && c < 8) flag = 1;
        }
        l = x, c = y;

        //baixo direita
        if (flag == 0 && e->grelha[x + 1][y + 1] == p) {
            l++;c++;
            while (e->grelha[l][c] == p && l < 8 && c < 8) {
                l++;
                c++;
            }
            if (e->grelha[l][c] == e->peca && l < 8 && c < 8) flag = 1;
        }
        l = x, c = y;

        //baixo esquerda
        if (flag == 0 && e->grelha[x + 1][y - 1] == p) {
            l++;c--;
            while (e->grelha[l][c] == p && l < 8 && c >= 0) {
                l++;
                c--;
            }
            if (e->grelha[l][c] == e->peca && l < 8 && c >= 0) flag = 1;
        }
        l = x, c = y;

        //cima esquerda
        if (flag == 0 && e->grelha[x - 1][y - 1] == p) {
            l--;c--;
            while (e->grelha[l][c] == p && l >= 0 && c >= 0) {
                l--;
                c--;
            }
            if (e->grelha[l][c] == e->peca && l >= 0 && c >= 0) flag = 1;
        }
    }

    return flag;
}

// Função que lê um jogo que tenha sido gravado

int readGame (ESTADO *e, char linha[]) {
    FILE *file;
    char modo;
    char peca;
    char ficheiro[50];
    char nivel;
    int i, k, j;
    int aux = 0;
    sscanf(linha, "%c %s", &modo, ficheiro);
    file = fopen(strcat(ficheiro, ".txt"), "r");
    if (file == NULL) printf("O ficheiro não existe\n");
    else {
        aux = 1;
        fscanf(file, "%c %c ", &modo, &peca);
        if (modo == 'M') e->modo = 0;
        else {
            e->modo = 1;
            fscanf(file, "%c ", &nivel);
            e->nivel = atoi(&nivel);
        }

        if (peca == 'X') e->peca = VALOR_X;
        else e->peca = VALOR_O;
        for (i = 0; i < 8; i++) {
            fgets(linha, 50, file);
            j = 0;
            for (k = 0; linha[k] != '\n' && j < 8; k++) {
                if (linha[k] == 'X') {
                    e->grelha[i][j] = VALOR_X;
                    j++;
                } else if (linha[k] == 'O') {
                    e->grelha[i][j] = VALOR_O;
                    j++;
                } else if (linha[k] == '-' || linha[k] == '.') {
                    e->grelha[i][j] = VAZIA;
                    j++;
                }
            }

        }
        fclose(file);

    }
    return aux;
}

// FUnção que guarda o jogo, isto é o seu estado e todas as informações necessárias

void guardajogo (ESTADO *e , char linha[]) {
    FILE *file;
    char modo;
    char peca;
    char ficheiro[50];
    int i,k;
    char nivel;
    sscanf(linha,"%c %s",&modo, ficheiro);
    file = fopen(strcat(ficheiro, ".txt"), "w");

    if (e->peca == VALOR_X) peca = 'X';
    else peca = 'O';
    if (e->modo == 0) {
        modo = 'M';
        fprintf(file,"%c %c\n",modo,peca);
    }
    else {
        modo = 'A';
        if (e->nivel == 1) nivel = '1';
        else if (e->nivel == 2) nivel = '2';
        else nivel = '3';
        fprintf(file,"%c %c %c\n",modo,peca,nivel);
    }


    for (i = 0;i<8;i++){
        for (k = 0; k<8;k++){
            if (e->grelha[i][k] == VALOR_X) fprintf(file,"X ");
            else if (e->grelha[i][k] == VALOR_O) fprintf(file,"O ");
            else fprintf(file,"- ");
        }
        fprintf(file,"\n");
    }
    fclose(file);
}

// Função de auxílio ao jogador que mostra locais de jogada válida

void whereCanIPut (ESTADO *e){
    int i,k;
    printf("  1 2 3 4 5 6 7 8\n");
    for (i = 0;i<8;i++){
        printf("%d ",i+1);
        for (k = 0; k<8;k++){
            if (e->grelha[i][k] == VALOR_X) printf("X ");
            else if (e->grelha[i][k] == VALOR_O) printf("O ");
            else if (e->validade[i][k]) printf(". ");
            else printf("- ");
        }
        putchar('\n');
    }
}

// Função que cria um nova estado, utilizada aquando da criação de um novo jogo

void novoEstado (ESTADO *e, char linha[]){
    int i,k;
    char c1,c2;
    for (i=0;i<8;i++){
        for (k=0;k<8;k++){
            e->grelha[i][k] = VAZIA;
        }
    }
    e->modo = 0;
    // estado inicial do tabuleiro. Inicio do jogo!
    e->grelha[3][4] = VALOR_X;
    e->grelha[4][3] = VALOR_X;
    e->grelha[3][3] = VALOR_O;
    e->grelha[4][4] = VALOR_O;
    sscanf(linha,"%c %c",&c1,&c2);
    if (toupper(c1) == 'N') {
        if (toupper(c2) == 'X') e->peca = VALOR_X;
        else e->peca = VALOR_O;
        e->nivel = 0;
    }
    else e->peca = VALOR_X;
    verificajogada2(e);
}

// Função que copia um estado

void copyEstado (ESTADO *e, ESTADO *aux){
    aux->peca = e->peca;
    aux->modo = e->modo;
    aux->nivel = e->nivel;
    int i,k;
    for (i=0;i<8;i++){
        for (k=0;k<8;k++){
            aux->grelha[i][k] = e->grelha[i][k];
            aux->validade[i][k] = e->validade[i][k];
        }
    }
    aux->ant = e->ant;
}

// Função que indica ao jogador a melhor jogada de acordo com o tabuleiro

void giveHint (ESTADO *e) {
    int x,y;
    maxplay(e,&x,&y,5,5,9999,-9999);
    char c = ' ';

    printf("  1 2 3 4 5 6 7 8\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ",i+1);
        for (int j = 0; j < 8; j++) {
            switch (e->grelha[i][j]) {
                case VALOR_O: {
                    c = 'O';
                    break;
                }
                case VALOR_X: {
                    c = 'X';
                    break;
                }
                case VAZIA: {
                    c = '-';
                    break;
                }
            }
            if (i == x && j == y) printf("? ");
            else printf("%c ", c);

        }
        printf("\n");
    }
}

// Função que verifica se as condições de fim de jogo se verificam e, em caso afirmativo, decreta o vencedor

int gameOver (ESTADO *e, int *contaX, int *contaO) {
    int resultado = 0;
    if (*contaX + *contaO == 64) {
        if (*contaX > *contaO) {
            printf("Vencedor ! : X\n");
            resultado = 1;
        } else if (*contaX < *contaO) {
            printf("Vencedor ! : O\n");
            resultado = 1;
        } else {
            printf("Empate!\n");
            resultado = 1;
        }
        e->peca = VAZIA;
    } else {
        if (!checkIfPlayable(e)) {
            resultado = 1;
            if (*contaX > *contaO) printf("Vencedor ! : X\n");
            else if (*contaX < *contaO) printf("Vencedor ! : O\n");
            else printf("Empate!\n");
            e->peca = VAZIA;
        }

    }
    return resultado;
}

// Função que verifica se é possível continuar o jogo

int checkIfPlayable (ESTADO *e){
    int resultado = 0;
    if (!playerPlayable(e) && !oppPlayable(e)) resultado = 0;
    else resultado = 1;
    return resultado;
}

// Função que verifica se é possível o jogador jogar

int playerPlayable (ESTADO *e){
    int i,k;
    int flag1 = 0;
    for (i=0;i<8 && flag1 == 0;i++){
        for (k=0;k<8 && flag1 == 0;k++){
            if (e->validade[i][k]) flag1 = 1;
        }
    }
    return flag1;
}

// Função que verifica se é possível o oponente jogar

int oppPlayable (ESTADO *e){
    int i,k;
    int flag1 = 0;
    trocapeca(e);
    for (i=0;i<8 && flag1 == 0;i++){
        for (k=0;k<8 && flag1 == 0;k++){
            if (e->validade[i][k]) flag1 = 1;
        }
    }
    trocapeca(e);
    return flag1;
}

// Função que troca a peça atual

void trocapeca (ESTADO *e){
    if (e->peca == VALOR_X) e->peca = VALOR_O;
    else if (e->peca == VALOR_O) e->peca = VALOR_X;
    verificajogada2(e);
}

// Função que imprime uma lista de comandos passíveis de serem utilizados pelo jogador

void interface (){
    printf("N <peca> // novo jogo em que o primeiro a jogar é o jogador com peça\n");
    printf("A <peça> <nivel> // novo jogo contra um bot em que o bot joga com a peça especificada e no nível especificado\n");
    printf("L <ficheiro> // ler um jogo de ficheiro\n");
    printf("E <ficheiro> // Guardar jogo\n");
    printf("J <L> <C> // Jogar [linha] [coluna]\n");
    printf("S // Colocar pontos nos locais de jogada válida\n");
    printf("P // Imprimir estado do jogo\n");
    printf("H // Dar sugestão de jogada\n");
    printf("U // Desfazer jogada anterior\n");
}



