#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Paciente {
    int id;
    char nome[50];
    struct Paciente* esquerda;
    struct Paciente* direita;
} Paciente;

Paciente* criarPaciente(int id, const char* nome) {
    Paciente* novo = (Paciente*)malloc(sizeof(Paciente));
    novo->id = id;
    strcpy(novo->nome, nome);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

Paciente* inserir(Paciente* raiz, int id, const char* nome) {
    if (raiz == NULL) {
        return criarPaciente(id, nome);
    }

    if (id < raiz->id) {
        raiz->esquerda = inserir(raiz->esquerda, id, nome);
    } 
    else if (id > raiz->id) {
        raiz->direita = inserir(raiz->direita, id, nome);
    }

    return raiz;
}

Paciente* buscar(Paciente* raiz, int id) {
    if (raiz == NULL || raiz->id == id) {
        return raiz;
    }

    if (id < raiz->id) {
        return buscar(raiz->esquerda, id);
    }

    return buscar(raiz->direita, id);
}

void exibirEmOrdem(Paciente* raiz) {
    if (raiz != NULL) {
        exibirEmOrdem(raiz->esquerda);
        printf("[ID: %d] Nome: %s\n", raiz->id, raiz->nome);
        exibirEmOrdem(raiz->direita);
    }
}

int main() {
    Paciente* hospital = NULL;
    int idBusca;

    hospital = inserir(hospital, 50, "Carlos Silva");
    hospital = inserir(hospital, 30, "Ana Souza");
    hospital = inserir(hospital, 70, "Lucas Santos");
    hospital = inserir(hospital, 20, "Mariana Costa");
    hospital = inserir(hospital, 60, "Rodrigo Lima");

    printf("--- Pacientes Cadastrados no Sistema ---\n");
    exibirEmOrdem(hospital);
    printf("----------------------------------------\n\n");

    printf("Digite o ID do paciente que deseja procurar: ");
    scanf("%d", &idBusca);

    printf("\nBuscando paciente com ID %d...\n", idBusca);
    Paciente* resultado = buscar(hospital, idBusca);

    if (resultado != NULL) {
        printf("=> Sucesso! Paciente encontrado: %s\n", resultado->nome);
    } else {
        printf("=> Erro: Paciente com ID %d nao consta no sistema.\n", idBusca);
    }

    return 0;
}
