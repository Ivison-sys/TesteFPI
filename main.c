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

Treinador* cadastrarJogador(Treinador* treinadores){
    printf("Cadastrado");
    Treinador treinadorAux;
    printf("Nome");
}


int main(){
    Treinador *treinadores = NULL, *treinadoresAux = NULL;
    int qtdJogadores = 0;
    Pokemon *pokemonsAux = NULL;
    int comando;

    do{
        printf("(1) Cadastrar treinador\n");
        printf("(2) Cadastrar pokémon\n");
        printf("(3) Buscar treinador\n");

        switch (comando)
        {
        case 1:
            // cadastrarJogador();
            break;
        
        default:
            break;
        }

    }while(comando != 0);



    return 0;
}