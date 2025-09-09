// Pelo tempo não pude comentar muito espero que entenda.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NOME 50

typedef struct {
    char nome[MAX_NOME];
    char cpf[12];
    int idade;
} Pessoa;

// Ajudar na verificação
int acentos[8] = {30, 40, 50, 60, 70, 80, 90, 100};

// O único erro que eu tratei pelo tempo foi o range de poltranmos, peço que entenda.
int verificarValidade(int lin, int col){
    if(col >= 0 && ((lin == 0 && col <= 29) || (lin == 1 && col <= 39) ||(lin == 2 && col <= 49) ||(lin == 3 && col <= 59) ||(lin == 4 && col <= 69) ||(lin == 5 && col <= 79) || (lin == 6 && col <= 89) || (lin == 7 && col <= 99))){
        return 1;
    }
    return 0;
}

Pessoa **inicializar_teatro(){
    Pessoa **teatro = (Pessoa**) malloc(8 * sizeof(Pessoa*));
    // Boa prática
    if(teatro == NULL){
        printf("Problema de alocacao!\n");
        free(teatro);
        exit(1);
    }

    int qtdAcentos = 30;
    for(int i = 0; qtdAcentos <= 100; i++, qtdAcentos+=10){
        teatro[i] =  (Pessoa*) malloc(qtdAcentos * sizeof(Pessoa));
        // Boa prática
        if(teatro[i] == NULL){
            printf("Problema de alocacao!\n");
            free(teatro);
            exit(1);
        }

        for(int z = 0; z < qtdAcentos; z++){
            // idade = -1 flag de não inicializada 
            teatro[i][z].idade = -1;
            // Inicializei cpf para poder comparar em remover pessoa
            strcpy(teatro[i][z].cpf, "-1");
        }
    }

    return teatro;
}


// Decidir pedir informações de pessoas na função
int cadastrar_pessoa(Pessoa **teatro, int linha, int coluna){
    Pessoa pessoaAux;
    if(teatro[linha][coluna].idade == -1){
        printf("Informações da pessoa.\n");
        printf("Nome: ");scanf(" %[^\n]", pessoaAux.nome);
        printf("CPF: ");scanf(" %[^\n]", pessoaAux.cpf);
        printf("Idade: ");scanf("%d", &pessoaAux.idade);

        strcpy(teatro[linha][coluna].nome, pessoaAux.nome);
        strcpy(teatro[linha][coluna].cpf, pessoaAux.cpf);
        teatro[linha][coluna].idade = pessoaAux.idade;

        printf("Pessoa cadastrada com sucesso!\n");
        return 1;
    }
    else{
        printf("Lugar já ocupado!\n");
        return 0;
    }

}

double arrecadacao(Pessoa **teatro){
    int qtdAcentos = 30;
    double soma = 0;
    for(int i = 0; qtdAcentos <= 100; i++, qtdAcentos+=10){
        for(int z = 0; z < qtdAcentos; z++){
            if(teatro[i][z].idade != -1){
                if(teatro[i][z].idade <= 18 || teatro[i][z].idade >= 60){
                    soma += 150;
                }
                else{
                    soma += 300;
                }
            }
        }
    }
    return soma;
}

int remover_pessoa(Pessoa **teatro, char *cpf){
    int qtdAcentos = 30;
    double soma = 0;
    for(int i = 0; qtdAcentos <= 100; i++, qtdAcentos+=10){
        for(int z = 0; z < qtdAcentos; z++){
            // Verificar cpf's
            if(!strcmp(teatro[i][z].cpf, cpf)){
                // Eu simulei a exclução pela flag idade.
                teatro[i][z].idade = -1;
                printf("Pessoa excluida com sucesso!\n");
                return 1;
            }
        }
    }
    // Caso o CPF não seja enocntrado.
    printf("Pessoa não encontrada\n");
    return 0;
}

void listar_assentos(Pessoa **teatro){
    int qtdAcentos = 30;
    double soma = 0;
    for(int i = 0; qtdAcentos <= 100; i++, qtdAcentos+=10){
        int qtdPessoas = 0;
        printf("Linha %d \n", i);
        for(int z = 0; z < qtdAcentos; z++){
            if(teatro[i][z].idade != -1){
                qtdPessoas++;
                printf("Nome: %s \nCPF: %s\nIdade: %d\n", teatro[i][z].nome, teatro[i][z].cpf, teatro[i][z].idade);
            }
        }
        printf("Quantidade de pessoas na linha %d: %d \n\n", i, qtdPessoas);
    }
}


void desalocar_teatro(Pessoa **teatro){
    int qtdAcentos = 30;
    double soma = 0;

    for(int i= 0; i < 8; i++){
        free(teatro[i]);
    }
    free(teatro);
    printf("Memória liberada");
}

void menu(){
    int comando;

    Pessoa **teatro = inicializar_teatro();

    do{
        printf("(1) Cadastra pessoas\n");
        printf("(2) Arrecadação\n");
        printf("(3) Remover pessoa\n");
        printf("(4) Listar assentos\n");
        printf("(5) Sair\n");

        printf("Insira o número do comando: "); scanf("%d", &comando);

        if(comando == 1){
            int linha, coluna;
            printf("Informe linha: "); scanf("%d", &linha);
            printf("Informe coluna: "); scanf("%d", &coluna);
            if(verificarValidade(linha, coluna)){
                cadastrar_pessoa(teatro, linha, coluna);
            }
            else{
                printf("Não existe essa poltrona!\n");
            }
        }
        else if(comando == 2){
            printf("Arrcadação %.2lf reais\n", arrecadacao(teatro));
        }
        else if(comando == 3){
            char cpf[12];
            printf("Informe o CPF da pessoa: "); scanf(" %[^\n]", cpf);
            remover_pessoa(teatro, cpf);
        }
        else if(comando == 4){
            listar_assentos(teatro);
        }
        else if(comando == 5){
            desalocar_teatro(teatro);
        }

    }while(comando != 5);
}

int main(){
    menu();
    return 0;
}