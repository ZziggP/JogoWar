#include <stdio.h>
#include <string.h> // Para manipulação de strings com strcspn
#include <stdlib.h> // Para malloc
#include <time.h> // Para srand e rand

//============================================================================

// Definindo a estrutura para representar um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

//limpar o buffer de entrada para evitar problemas com fgets
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para adicionar um novo território (Modularizada)
void adicionarTerritorio(Territorio mapa[], int tamanhoMax, int *numTerritorios) {

    if (*numTerritorios < tamanhoMax) {
        printf("====================================\n");
        printf("Cadastro do Território %d:\n", *numTerritorios + 1); // Exibe o número do território que está sendo cadastrado (começando de 1)
        printf("Digite o nome do território: ");
        fgets(mapa[*numTerritorios].nome, 30, stdin); // Lê o nome do território
        mapa[*numTerritorios].nome[strcspn(mapa[*numTerritorios].nome, "\n")] = '\0'; // Remove a nova linha

        printf("Digite a cor do território: ");
        fgets(mapa[*numTerritorios].cor, 10, stdin); // Lê a cor do território
        mapa[*numTerritorios].cor[strcspn(mapa[*numTerritorios].cor, "\n")] = '\0'; // Remove a nova linha

        printf("Digite o número de tropas: ");
        scanf("%d", &mapa[*numTerritorios].tropas); // Lê o número de tropas

        limparBuffer(); // Limpa o buffer de entrada após ler o número de tropas
        
        // Incrementa o número de territórios cadastrados
        (*numTerritorios)++;
    } else {
        printf("Limite de territórios atingido!\n");
    }
}

// Funcão para listar os territórios cadastrados (Modularizada)
void listarTerritorios(Territorio mapa[], int numTerritorios) {
    printf("====================================\n");
    printf("Mapa dos Territórios:\n");
    printf("====================================\n");
    for (int i = 0; i < numTerritorios; i++) { // Loop para listar os territórios cadastrados
        printf("%d. %s - Cor: %s - Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas); // Exibe as informações do território
    
    }
    printf("\n");
}

void atacar(int numTerritorios, Territorio mapa[]) {
    int territorioAtacante, territorioDefensor;
    printf("===================================\n");
    printf("Fase de Ataque\n");
    printf("===================================\n");
    printf("Escolha o território de origem e o território de destino para realizar o ataque.\n");
    
    printf("Escolha o territorio atacante (1-%d): ", numTerritorios);
    scanf("%d", &territorioAtacante);
    printf("Escolha o territorio defensor (1-%d): ", numTerritorios);
    scanf("%d", &territorioDefensor);

    // Converter para índice do vetor
    territorioAtacante--;
    territorioDefensor--;

    // Validar índices
    if (territorioAtacante < 0 || territorioAtacante >= numTerritorios ||
        territorioDefensor < 0 || territorioDefensor >= numTerritorios) {
        printf("Territorio invalido!\n");
        return;
    }

    // Impedir ataque ao mesmo território
    if (territorioAtacante == territorioDefensor) {
        printf("Um territorio nao pode atacar ele mesmo!\n");
        return;
    }

    // Validar tropas
    if (mapa[territorioAtacante].tropas < 1) {
        printf("\nO territorio atacante precisa ter pelo menos 1 tropa para atacar!\n");
        return;
    }

    if (mapa[territorioDefensor].tropas < 1) {
        printf("\nO territorio defensor nao possui tropas para defender!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("===================================\n");
    printf("Rolando os dados...\n");
    printf("===================================\n");


    printf("O atacante %s rolou um dado e tirou: %d\n", mapa[territorioAtacante].nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou: %d\n", mapa[territorioDefensor].nome, dadoDefensor);
    printf("\n");
    
    if (dadoAtacante > dadoDefensor)
    {
        printf("O atacante %s venceu o ataque!\n", mapa[territorioAtacante].nome);
        mapa[territorioDefensor].tropas--;
        
        if (mapa[territorioDefensor].tropas == 0) {
            printf("Territorio conquistado!\n");
            strcpy(mapa[territorioDefensor].cor, mapa[territorioAtacante].cor);
            mapa[territorioAtacante].tropas--;
            mapa[territorioDefensor].tropas = 1;
        }
    } else if (dadoDefensor > dadoAtacante) {
        printf("O defensor %s defendeu o ataque!\n", mapa[territorioDefensor].nome);
        mapa[territorioAtacante].tropas--;
    } else {
        printf("Empate! Ninguem ganha ou perde tropas.\n");
    }
    
}

void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main (){
    
    // Inicializar a semente para geração de números aleatórios
    srand(time(NULL));

    int tamanhoMax; // Variavel para armaezar tamanho máximo do mapa (número máximo de territórios)
    
    printf("===================================\n");
    printf("Bem-vindo ao Jogo de Guerra!\n");
    printf("===================================\n");
    printf("Vamos começar cadastrando os territórios do jogo.\n");
    printf("Quantos territórios você deseja cadastrar?\n");
    scanf("%d", &tamanhoMax);
    limparBuffer();

    // Alocar memória para o mapa de territórios usando malloc
    Territorio *mapa = malloc(tamanhoMax * sizeof(Territorio)); // Criar um array de territórios
    
    // Verificar se a alocação de memória foi bem-sucedida
    if (mapa == NULL) {
        printf("Erro ao alocar memória para o mapa!\n");
        return 1; // Encerra o programa com código de erro
    }

    int numTerritorios = 0; // Variável para contar o número de territórios cadastrados

    printf("Aperte Enter para começar a cadastrar os territórios...");
    getchar(); 

    while (numTerritorios < tamanhoMax) {
        // Adicionar um novo território
        adicionarTerritorio(mapa, tamanhoMax, &numTerritorios);
    }
                
    // Listando os territórios cadastrados pós cadastro de todos os territórios
    listarTerritorios(mapa, numTerritorios);

    // Espera o usuário pressionar Enter para continuar
    printf("Pressione Enter para ir para fase de ataque...");
    getchar(); // Espera o usuário pressionar Enter
    
    int resposta;
    do {
        // Chama a função de ataque (ainda em desenvolvimento)
        atacar(numTerritorios, mapa); 

        // Listando os territórios após o ataque para mostrar as mudanças
        listarTerritorios(mapa, numTerritorios);

        printf("Deseja realizar outro ataque? Digite 1 para continuar ou 0 caso deseje encerrar o jogo");
        scanf(" %d", &resposta);
        limparBuffer();
    } while (resposta != 0);
    

    printf("Obrigado por jogar! Encerrando o jogo...\n");

    // Liberar a memória alocada para o mapa de territórios
    liberarMemoria(mapa);
    return 0; // Encerra o programa com sucesso

}
