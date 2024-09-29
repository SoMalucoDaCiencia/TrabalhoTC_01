#include <stdio.h>
#include <string.h>

#define MAX_SIMBOLOS 30
#define MAX_ESTADOS 50
#define MAX_TRANSICOES 100
#define MAX_TAMANHO_FITA 100
#define MAX_PALAVRAS 10

typedef struct {
    int estadoAtual;
    char simboloLido;
    char simboloGravado;
    char movimento;
    int estadoDestino;
} Transicao;

int numEstados, numTransicoes;
char alfabeto[MAX_SIMBOLOS + 1]; 
Transicao transicoes[MAX_TRANSICOES];
int estadoAceitacao;
char fita[MAX_TAMANHO_FITA + 1]; 
int cabecote; 

int executaTransicao(int estadoAtual) {
    for (int i = 0; i < numTransicoes; i++) {
        char simboloLido = (fita[cabecote] == ' ' || fita[cabecote] == '\000') ? '-' : fita[cabecote];
        
        if (transicoes[i].estadoAtual == estadoAtual && transicoes[i].simboloLido == simboloLido) {
            fita[cabecote] = (transicoes[i].simboloGravado == '-') ? ' ' : transicoes[i].simboloGravado;

            if (transicoes[i].movimento == 'D')
                cabecote++; 
            else if (transicoes[i].movimento == 'E')
                cabecote--; 

            printf("Estado atual: %d, Cabeçote: %d, Fita: %s\n", transicoes[i].estadoAtual, cabecote, fita); // Debugging

            return transicoes[i].estadoDestino;
        }
    }
    return -1;
}

void processaPalavra(char *palavra, int numeroPalavra) {
    strcpy(fita, palavra);
    cabecote = 0;
    int estadoAtual = 1;

    while (estadoAtual != estadoAceitacao && estadoAtual != -1) {
        estadoAtual = executaTransicao(estadoAtual);
    }

    printf("%d: %s %s\n", numeroPalavra, palavra, (estadoAtual == estadoAceitacao) ? "OK" : "not OK");
}

int main() {
    FILE *arquivoEntrada = fopen("entrada.txt", "r");
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fscanf(arquivoEntrada, "%s", alfabeto);

    fscanf(arquivoEntrada, "%d", &numEstados);
    estadoAceitacao = numEstados; 

    fscanf(arquivoEntrada, "%d", &numTransicoes);

    for (int i = 0; i < numTransicoes; i++) {
        fscanf(arquivoEntrada, "%d %c %c %c %d",
               &transicoes[i].estadoAtual,
               &transicoes[i].simboloLido,
               &transicoes[i].simboloGravado,
               &transicoes[i].movimento,
               &transicoes[i].estadoDestino);
    }

    int numPalavras;
    fscanf(arquivoEntrada, "%d", &numPalavras);

    for (int i = 0; i < numPalavras; i++) {
        char palavra[MAX_TAMANHO_FITA + 1];
        fscanf(arquivoEntrada, "%s", palavra);
        processaPalavra(palavra, i + 1);
    }

    fclose(arquivoEntrada);
    return 0;
}
