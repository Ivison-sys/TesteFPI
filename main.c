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
    int id;
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
int procurandoJogador(Treinador* treinadores, char cpf[14]){
    for(int i = 0; i < qtdTreinadores; i++){
        if(!strcmp(treinadores[i].cpf, cpf)) return i;
    }

    return -1;
}

void listandoElementos(){
    char tipos[4][15] = {"Fogo", "Água", "Eletricidade", "Planta"};

    for(int i = 0; i < 4; i++){
        printf("(%d) - %s\n", i+1, tipos[i]);
    }
}

int verificarPokemon(Treinador treinador, int idPokemon){
    for(int i = 0; i < treinador.qtdPokemons; i++){
        if(treinador.pokemons[i].id == idPokemon){
            return 0;
        }
    }
    return 1;
}

// Funções principais
Treinador* cadastrarJogador(Treinador* treinadores){
    printf("Cadastrando Jogador!!\n");
    Treinador treinadorAux;

    // Dados do treinador
    printf("Nome: "); scanf(" %s", treinadorAux.nome);
    printf("CPF: "); scanf(" %s", treinadorAux.cpf);
    printf("Idade: "); scanf("%d", &treinadorAux.idade);
    treinadorAux.pokemons = NULL;
    treinadorAux.qtdPokemons = 0;
    
    // Verificando se o cpf é único
    if(procurandoJogador(treinadores, treinadorAux.cpf) != -1){
        printf("Esse CPF já consta no sistema!\n\n");
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

Treinador* cadastrarPokemon(Treinador* treinadores){
    printf("Cadastrando pokémon.\n");
    Pokemon pokemonAux;
    
    char cpf[14];
    printf("Digite o cpf do Treinador: "); scanf(" %s", cpf);
    
    // Procurando a posição do Treinador que corresponde ao cpf
    int idTreinador = procurandoJogador(treinadores, cpf);
    
    if(idTreinador == -1){
        printf("Treinador não encontrado\n\n");
        return treinadores;
    }

    printf("Informações do pokémon\n");
    // Dados do pokémon
    printf("Id: "), scanf("%d", &pokemonAux.id);
    if(!verificarPokemon(treinadores[idTreinador], pokemonAux.id)){
        printf("Esse id já estar cadastrado!\n\n");
        return treinadores;
    }
    printf("Nome: "); scanf(" %s", pokemonAux.nome);
    printf("XP (Quantidade de vida): "); scanf("%d", &pokemonAux.xp);
    printf("Ataque: "); scanf("%d", &pokemonAux.ataque);
    printf("Defesa: "); scanf("%d", &pokemonAux.defesa);
    int elementoAux;
    listandoElementos();
    printf("Elemento (o dígito): "); scanf("%d", &elementoAux);
    pokemonAux.tipo = (Elemento) elementoAux;

    if(!verificarPokemon(treinadores[idTreinador], pokemonAux.id)){
        printf("Esse id já estar cadastrado!\n\n");
        return treinadores;
    }

    Pokemon* pokemonsAux = treinadores[idTreinador].pokemons;
    int qtd = treinadores[idTreinador].qtdPokemons;
    treinadores[idTreinador].pokemons = (Pokemon*) realloc(pokemonsAux, (qtd + 1) * sizeof(Pokemon));

    if(treinadores[idTreinador].pokemons == NULL){
        printf("Problema de alocacao!\n");
        // free(pokemonsAux);
        exit(1);
    }
    treinadores[idTreinador].pokemons[qtd] = pokemonAux;
    treinadores[idTreinador].qtdPokemons++;
    printf("Pokémon cadastrado com sucesso!\n\n");
    return treinadores;
}

void listarTreinadores(Treinador* treinadores){
    printf("Listando jogadores e seus pokémons.\n");
    if(qtdTreinadores == 0){
        printf("Não há treinadores cadastrados!");
    }
    for(int i = 0; i < qtdTreinadores; i++){
        printf("Treinador: %s\n", treinadores[i].nome);
        for(int w = 0; w < treinadores[i].qtdPokemons; w++){
            Pokemon pokemon = treinadores[i].pokemons[w];
            printf("{id: %d, Nome: %s, At: %d, Df: %d, tipo: %d}\n", pokemon.id, pokemon.nome, pokemon.ataque, pokemon.defesa, pokemon.tipo);
        }
        printf("\n");
    }
}

Treinador* removerTreinador(Treinador* treinadores){
    printf("Remover jogador!\n");
    char cpf[14];
    printf("Digite o cpf do Treinador: "); scanf(" %s", cpf);
    int idTreinador = procurandoJogador(treinadores, cpf);

    // verificando se há o cpf
    if(idTreinador == -1){
        printf("Treinador não consta no sistema.\n\n");
        return treinadores;
    }

    // Realocar para 0 é um erro, é necessário verificar antes
    if(qtdTreinadores == 1){
        printf("Treinador Removido com sucesso!\n\n");
        qtdTreinadores--;
        return NULL;
    }

    // Reposicionar as posições antes de realocar
    for(int i = idTreinador + 1; i < qtdTreinadores; i++){
        treinadores[i-1] = treinadores[i];
    }

    Treinador* treinadoresAux = treinadores;
    treinadores = (Treinador*) realloc(treinadoresAux, (qtdTreinadores - 1) * sizeof(Treinador));

    // Boas práticas: Verifcar se a realocação foi bem sucedida.
    if(treinadores == NULL){
        printf("Problema de alocacao!\n");
        free(treinadoresAux);
        exit(1);
    }
    printf("Treinador Removido com sucesso!\n\n");
    qtdTreinadores--;
    return treinadores;
}

Treinador* AtualizarPokemon(Treinador* treinadores){
    printf("Atualizando pokémon!\n");
    char cpf[14];
    printf("Digite o cpf do Treinador: "); scanf(" %s", cpf);
    int idTreinador = procurandoJogador(treinadores, cpf);
    if(idTreinador == -1){
        printf("Treinador não consta no sistema.\n\n");
        return treinadores;
    }
    int keyPokemon;
    printf("Digite o id do pokémon: "); scanf("%d", &keyPokemon);

    int idPokemon = -1;
    for(int i = 0; i < treinadores[idTreinador].qtdPokemons; i++){
        if(treinadores[idTreinador].pokemons->id ==  keyPokemon) idPokemon = i;
    }

    if(idPokemon == -1){
        printf("Pokémon não encontrado.\n\n");
        return treinadores;
    }

    Pokemon pokemonAux;
    // Novos dados do pokémon
    printf("Novas informações do pokémon\n");
    // Dados do pokémon
    printf("Nome: "); scanf(" %s", pokemonAux.nome);
    printf("XP (Quantidade de vida): "); scanf("%d", &pokemonAux.xp);
    printf("Ataque: "); scanf("%d", &pokemonAux.ataque);
    printf("Defesa: "); scanf("%d", &pokemonAux.defesa);
    int elementoAux;
    listandoElementos();
    printf("Elemento (o dígito): "); scanf("%d", &elementoAux);
    pokemonAux.tipo = (Elemento) elementoAux;

    treinadores[idTreinador].pokemons[idPokemon] = pokemonAux;
    printf("Pokémon cadastrado com sucesso!");
    return treinadores;
}

int main(){
    Treinador *treinadores = NULL;
    int comando;

    do{
        printf("(1) Cadastrar treinador\n");
        printf("(2) Cadastrar pokémon\n");
        printf("(3) Listar jogadores\n");
        printf("(4) Remover treinador\n");
        printf("(5) Atualizar pokémon\n");
        printf("(0) Sair");
        printf("Digite o comando: "); scanf("%d", &comando);
        switch (comando){
        case 1:
            treinadores = cadastrarJogador(treinadores);
            break;
        case 2:
            treinadores = cadastrarPokemon(treinadores);
            break;
        case 3:
            listarTreinadores(treinadores);
            break;
        case 4:
            treinadores = removerTreinador(treinadores);
            break;
        case 5:
            treinadores = AtualizarPokemon(treinadores);
            break;
        default:
            break;
        }

    }while(comando != 0);

    return 0;
}