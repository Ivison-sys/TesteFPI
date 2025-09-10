#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[30];
    int quantidade;
} Produto;

typedef struct {
    int id;
    char nome[30];
    Produto *produtos;     
    int qtdProdutos;
} Armazem;

int main() {
    Armazem *armazens = NULL, *armazensAux = NULL; 
    int qtdAmarzens = 0;
    Produto *produtosAux = NULL;
    Armazem armazemAux;   
    Produto produtoAux;   
    int comando;

    do {
        // Menu de opções
        printf("(1) Cadastrar armazém\n");
        printf("(2) Cadastrar produto\n");
        printf("(3) Buscar armazém:\n");
        printf("(4) Listar estoque\n");
        printf("(5) Sair\n");
        printf("Digite o número referente ao comando: ");
        scanf("%d", &comando);

        // Opção 1: cadastrar armazém
        if (comando == 1) {
            printf("Informe o id do armazém: ");
            scanf("%d", &armazemAux.id);
            printf("Infome o nome do armazém: ");
            scanf(" %[^\n]", armazemAux.nome);

            int isValid = 1;
            // Verifica se o id já existe
            for (int i = 0; i < qtdAmarzens; i++) {
                if (armazens[i].id == armazemAux.id) {
                    isValid = 0;
                }
            }

            if (isValid) {
                // Realoca espaço para mais um armazém
                armazensAux = armazens;
                armazens = (Armazem*) realloc(armazensAux, (qtdAmarzens + 1) * sizeof(armazemAux));

                if (armazens == NULL) {
                    printf("Problema de alocacao!\n");
                    free(armazensAux);
                    exit(1);
                }

                // Preenche os dados do novo armazém
                armazens[qtdAmarzens].id = armazemAux.id;
                strcpy(armazens[qtdAmarzens].nome, armazemAux.nome);
                armazens[qtdAmarzens].produtos = NULL;
                armazens[qtdAmarzens].qtdProdutos = 0;

                printf("Armazem cadastrado com sucesso.\n");
            } else {
                printf("Esse id já existe no sistema!\n");
            }
            qtdAmarzens++;
        }

        // Opção 2: cadastrar produto
        else if (comando == 2) {
            int id = 0, indice = 0;
            printf("Informe o id do armazém a qual o produto pertence: ");
            scanf("%d", &id);

            int isValid = 0;
            // Verifica se armazém existe
            for (int i = 0; i < qtdAmarzens; i++) {
                indice = i;
                if (armazens[i].id == id) {
                    isValid = 1;
                }
            }

            if (isValid) {
                printf("Informe o nome do produto: ");
                scanf(" %[^\n]", produtoAux.nome);
                printf("Informe a quantidade do produto: ");
                scanf("%d", &produtoAux.quantidade);

                int isExiste = 0;

                // Verifica se produto já existe no armazém
                for (int i = 0; i < armazens[indice].qtdProdutos; i++) {
                    if (!strcmp(armazens[indice].produtos[i].nome, produtoAux.nome)) {
                        isExiste = 1;
                        armazens[indice].produtos[i].quantidade += produtoAux.quantidade;
                        printf("Esse produto já está cadastrado, apenas incrementei a quantidade\n");
                    }
                }

                // Se produto ainda não existe
                if (!isExiste) {
                    produtosAux = armazens[indice].produtos;
                    int qtdP = armazens[indice].qtdProdutos;
                    armazens[indice].produtos = (Produto*) realloc(produtosAux, (qtdP + 1) * sizeof(Produto));

                    if (armazens[indice].produtos == NULL) {
                        printf("Problema de alocacao!\n");
                        free(armazens[indice].produtos);
                        exit(1);
                    }

                    strcpy(armazens[indice].produtos[qtdP].nome, produtoAux.nome);
                    armazens[indice].produtos[qtdP].quantidade = produtoAux.quantidade;
                    armazens[indice].qtdProdutos++;

                    printf("Produto cadastrado com sucesso!\n");
                }
            } else {
                printf("Esse armazem não consta no sistema\n");
            }
        }

        // Opção 3: buscar armazém e listar seus produtos
        else if (comando == 3) {
            int id;
            printf("Informe o id do armazém: ");
            scanf("%d", &id);

            int isExiste = 0, indice = 0;
            for (int i = 0; i < qtdAmarzens; i++) {
                if (armazens[i].id == id) {
                    indice = i;
                    isExiste = 1;
                }
            }

            if (isExiste) {
                // Ordena produtos por quantidade (algoritmo ineficiente, mas funcional)
                for (int i = 0; i < armazens[indice].qtdProdutos; i++) {
                    for (int z = 0; z < armazens[indice].qtdProdutos; z++) {
                        if (armazens[indice].produtos[i].quantidade < armazens[indice].produtos[z].quantidade) {
                            int aux = armazens[indice].produtos[i].quantidade;
                            armazens[indice].produtos[i].quantidade = armazens[indice].produtos[z].quantidade;
                            armazens[indice].produtos[z].quantidade = aux;
                        }
                    }
                }

                // Imprime os produtos do armazém
                printf("Produtos do armázem (%d):\n", id);
                for (int i = 0; i < armazens[indice].qtdProdutos; i++) {
                    printf("(%d) %s: %d \n", i, armazens[indice].produtos[i].nome, armazens[indice].produtos[i].quantidade);
                }
            }
        }

        // Opção 4: listar o estoque de todos os armazéns
        else if (comando == 4) {
            // Ordena os produtos de cada armazém por quantidade
            for (int i = 0; i < qtdAmarzens; i++) {
                for (int w = 0; w < armazens[i].qtdProdutos; w++) {
                    for (int z = 0; z < armazens[i].qtdProdutos; z++) {
                        if (armazens[i].produtos[w].quantidade < armazens[i].produtos[z].quantidade) {
                            int aux = armazens[i].produtos[w].quantidade;
                            armazens[i].produtos[w].quantidade = armazens[i].produtos[z].quantidade;
                            armazens[i].produtos[z].quantidade = aux;
                        }
                    }
                }
            }

            // Imprime produtos de todos os armazéns
            for (int i = 0; i < qtdAmarzens; i++) {
                for (int z = 0; z < armazens[i].qtdProdutos; z++) {
                    printf("(%d) %s: %d \n", i, armazens[i].produtos[z].nome, armazens[i].produtos[z].quantidade);
                }
            }
        }

        printf("---------------------------------------------------------------------------\n");

    } while (comando != 5);

    // Liberação da memória alocada dinamicamente
    for (int i = 0; i < qtdAmarzens; i++) {
        free(armazens[i].produtos); // Libera produtos de cada armazém
    }
    free(armazens); // Libera vetor de armazéns

    return 0;
}