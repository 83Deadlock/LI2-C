#include <stdio.h>
#include "estado.h"
#include <string.h>
#include "ctype.h"
#include "botfunction.h"
#include "math.h"



int main() {
    char c1, c2;
    char linha[50];
    int x, y;
    int contaX = 2, contaO = 2;
    int resultado = 0;
    int state = 0;
    int line, col;
    int nivel = 0;
    VALOR piece = VAZIA; // Auxiliar p/ bot
    ESTADO *e = NULL;
    interface();
    do {
        if (e == NULL || e->peca == VAZIA) printf("Reversi ? => ");
        else if (e->peca == VALOR_O) printf("Reversi O => ");
        else printf("Reversi X => ");

        fgets(linha, 50, stdin);
        switch (toupper(linha[0])) {
            case '?' : { // Mostra os comandos disponíveis
                interface();
                break;
            }
            case 'N' : { // Cria novo jogo
                if (e == NULL) {
                    e = malloc(sizeof(struct estado));
                    e->ant = NULL;
                } else {
                    ESTADO *aux = malloc(sizeof(struct estado));
                    copyEstado(e, aux);
                    e->ant = aux;
                }
                novoEstado(e, linha);
                state = 1;
                resultado = 0;
                printa(*e, &contaX, &contaO);
                printf("\n#X = %d   #O = %d\n", contaX, contaO);
                break;
            }
            case 'A' : { // Modo automático
                sscanf(linha, "%c %c %d", &c1, &c2, &nivel);
                if (nivel < 1 || (toupper(c2) != 'X' && toupper(c2) != 'O'));
                else {
                    if (e == NULL) {
                        e = malloc(sizeof(struct estado));
                        e->ant = NULL;
                    } else {
                        ESTADO *aux = malloc(sizeof(struct estado));
                        copyEstado(e, aux);
                        e->ant = aux;
                    }
                    novoEstado(e, linha);
                    state = 1;
                    resultado = 0;
                    e->modo = 1;
                    e->nivel = nivel;
                    if (toupper(c2) == 'X') {
                        piece = VALOR_X;
                        maxplay(e, &line, &col, nivel * 2 + 1, nivel * 2 + 1, 9999, -9999);
                        joga(e, line, col);
                        printa(*e, &contaX, &contaO);
                        printf("O Bot jogou em (%d,%d)\n", line+1, col+1);
                        printf("\n#X = %d   #O = %d\n", contaX, contaO);
                        trocapeca(e);
                    } else {
                        piece = VALOR_O;
                        printa(*e, &contaX, &contaO);
                        printf("\n#X = %d   #O = %d\n", contaX, contaO);
                    }
                }
                break;
            }
            case 'E' : { // Guarda o jogo
                if (state == 1) guardajogo(e, linha);
                break;
            }
            case 'J' : { // Funções de jogada
                if (state == 1 && resultado == 0) {


                    // Modo manual-automatico
                    if (e->modo == 0 || e->modo == 1) {
                        if (e->peca != piece) {
                            sscanf(linha, "%c %d %d", &c1, &x, &y);
                            if (e->validade[x - 1][y - 1]) {

                                // Avançar o estado
                                ESTADO *aux = malloc(sizeof(struct estado));

                                copyEstado(e, aux);
                                aux->ant = e;
                                e = aux;
                                // -----------
                                joga(e, x - 1, y - 1);
                                printa(*e, &contaX, &contaO);
                                printf("\n#X = %d   #O = %d\n", contaX, contaO);
                                if (oppPlayable(e)) trocapeca(e);
                                else if (playerPlayable(e)) {
                                    if (e->peca == VALOR_X) printf("Jogador O sem jogadas válidas!\n");
                                    else printf("Jogador X sem jogadas válidas!\n");
                                } else resultado = gameOver(e, &contaX, &contaO);


                            } else printf("Jogada inválida. Introduza uma jgoada válida.\n");
                        }
                        // Caso de modo automático
                        if (resultado == 0 && e->peca == piece) {
                            // É certo que o bot pode jogar
                            do {
                                maxplay(e, &line, &col, nivel * 2 + 1, nivel * 2 + 1, 9999,
                                        -9999); // a line e a col ficam com as posições onde deve jogar

                                joga(e, line, col);
                                printa(*e, &contaX, &contaO);
                                printf("O Bot jogou em (%d,%d)\n", line+1, col+1);
                                printf("\n#X = %d   #O = %d\n", contaX, contaO);

                            } while (!oppPlayable(e) && playerPlayable(e));
                            if (oppPlayable(e)) trocapeca(e);
                            else resultado = gameOver(e, &contaX, &contaO);

                            // -----------------
                            // Se o jogador não puder jogar


                        }
                        // ---------------------------------------------------------------

                    }
                } else printf("Jogo ainda não criado // N <peça>\n");
                break;
            }

            case 'P' : { // Imprime o estado atual do jogo
                if (state == 1) {
                    printa(*e, &contaX, &contaO);
                    printf("\n#X = %d   #O = %d\n", contaX, contaO);
                } else printf("Jogo ainda não criado // N <peça>\n");
                break;
            }
            case 'S' : { // Coloca pontos nos sítios de jogadas válidas
                if (state == 1) whereCanIPut(e);
                else printf("Jogo ainda não criado // N <peça>\n");
                break;
            }
            case 'U' : { // Desfaz a jogada anterior
                if (state == 1) {
                    if (e->ant == NULL);
                    else {
                        ESTADO *aux;
                        aux = e;
                        e = e->ant;
                        free(aux);
                        resultado = 0;
                        printa(*e, &contaX, &contaO);
                        printf("\n#X = %d   #O = %d\n", contaX, contaO);
                    }
                } else printf("Jogo ainda não criado // N <peça>\n");
                break;
            }
            case 'H' : { // coloca pontos de interrogação em locais sugeridos para jogar
                if (state != 1) printf("Jogo ainda não criado // N <peça>\n");
                else if (playerPlayable(e)) giveHint(e);
                else printf("Jogador sem jogadas válidas");
                break;
            }
            case 'L' : { // Lê um jogo que foi gravado
                    ESTADO *aux = malloc(sizeof(struct estado));
                if (e==NULL) {
                    e = malloc(sizeof(struct estado));
                    e->ant = NULL;
                }
                else {

                    copyEstado(e, aux);
                    e->ant = aux;
                }
                if (readGame(e, linha)) {
                    if (e->modo == 1) {
                        if (e->peca == VALOR_O) piece = VALOR_X;
                        else if (e->peca == VALOR_X) piece = VALOR_O;
                        else piece = VAZIA;
                    }
                    state = 1;
                    verificajogada2(e);
                    nivel = e->nivel;
                    resultado = gameOver(e, &contaX, &contaO);
                    printa(*e, &contaX, &contaO);
                    printf("\n#X = %d   #O = %d\n", contaX, contaO);
                    if (!playerPlayable(e) && oppPlayable(e)) {
                        if (e->peca == VALOR_X) printf("Jogador X sem jogadas válidas!\n");
                        else printf("Jogador O sem jogadas válidas!\n");
                        trocapeca(e);
                        if (e->modo == 1) {
                            maxplay(e, &line, &col, nivel * 2 + 1, nivel * 2 + 1, 9999, -9999);
                            joga(e, line, col);
                            printa(*e, &contaX, &contaO);
                            resultado = gameOver(e, &contaX, &contaO);
                            printf("\n#X = %d   #O = %d\n", contaX, contaO);
                            trocapeca(e);
                        }
                    }
                }
                else {
                    aux = e;
                    e = e->ant;
                    free(aux);
                }

                break;
            }
            case 'Q' : { // Sai do jogo
                exit(0);
            }
        }
    } while (toupper(linha[0] != 'Q'));
}