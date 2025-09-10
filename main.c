#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    fogo,
    agua,
    eletricidade,
    planta
} Elemento;

typedef struct {
    char nome[30];
    Elemento tipo;
    int xp;
    int ataque;
    int defesa;
} Pokemon;

typedef struct {
    char nome[30];
    char cpf[14];
    int idade;
    Pokemon *pokemons;
    int qtdPokemons;
} Treinador;
int qtdTreinadores = 0;

// Funcões auxiliares
int isValidCpf(Treinador* treinadores, char cpf[14]){
    for(int i = 0; i < qtdTreinadores; i++){
        if(!strcmp(treinadores[i].cpf, cpf)) return 0;
    }

    return 1;
}

Treinador* cadastrarJogador(Treinador* treinadores){
    printf("Cadastrado!!\n");
    Treinador treinadorAux;

    // Dados do treinador
    printf("Nome: "); scanf(" %s", treinadorAux.nome);
    printf("CPF: "); scanf(" %s", treinadorAux.cpf);
    printf("Idade: "); scanf("%d", &treinadorAux.idade);
    treinadorAux.pokemons = NULL;
    treinadorAux.qtdPokemons = 0;
    
    // Verificando se o cpf é único
    if(!isValidCpf(treinadores, treinadorAux.cpf)){
        printf("Esse CPF já consta no sistema!\n");
        return treinadores;
    }

    // Adicionado um espaço para o novo treinador
    Treinador* treinadoresAux = treinadores;
    treinadores = (Treinador*) realloc(treinadoresAux, (qtdTreinadores + 1) * sizeof(treinadorAux));

    // Boas práticas: Verifcar se a realocação foi bem sucedida.
    if(treinadores == NULL){
        printf("Problema de alocacao!\n");
        free(treinadoresAux);
        exit(1);
    }

    treinadores[qtdTreinadores] = treinadorAux;
    printf("Treinador cadastrado com sucesso!\n\n");
    qtdTreinadores++;
    return treinadores;
    
}

Treinador* cadastrarPokemon(Treinador* treinadores, char cpf[14]){
    Pokemon pokemonAux;

    // Dados do pokémon
    printf("Nome: "); scanf(" %s", pokemonAux.nome);
    printf("XP (Quantidade de vida): "); scanf("%d", &pokemonAux.xp);
    printf("Ataque: "); scanf("%d", &pokemonAux.ataque);
    printf("Defesa: "); scanf("%d", &pokemonAux.defesa);
    
    printf("Elemento: "); scanf("");

}


int main(){
    Treinador *treinadores = NULL, *treinadoresAux = NULL;

    Pokemon *pokemonsAux = NULL;
    int comando;

    do{
        printf("(1) Cadastrar treinador\n");
        printf("(2) Cadastrar pokémon\n");
        printf("(3) Buscar treinador\n");
        printf("Digite o comando: "); scanf("%d", &comando);
        switch (comando)
        {
        case 1:
            treinadores = cadastrarJogador(treinadores);
            break;
        
        default:
            break;
        }

    }while(comando != 0);



    return 0;
}