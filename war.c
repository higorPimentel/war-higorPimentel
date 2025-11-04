// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


//Territorio territorios[6]; // Vetor para armazenar 5 territórios
Territorio *territorios = NULL; // ponteiro dinâmico
int qtdTerritorios = 0;         // quantidade criada
int i;



void alocarMapa() {
  printf("Quantos territórios deseja criar? ");
  scanf("%d", &qtdTerritorios); // salva na variável global
  
   territorios = calloc(qtdTerritorios, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        return ;
    }
}

void inicializarTerritorios(){
  
     printf("====================== Cadastro de Territórios ======================\n\n Pressione Enter para começar \n\n");

    // Entrada de dados dos territórios
    for (i = 1; i < qtdTerritorios + 1; i++) {
        
        // Limpeza do buffer de entrada antes de ler strings
        getchar();
        
        printf("Digite o nome do território: %d: ", i );
        // printf("Digite o nome do território: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // Remove o '\n'

        printf("Digite a cor do exército: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0'; // Remove o '\n'

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }
}


void exibirMapa() {
    
    // Exibição dos dados cadastrados
    printf("====================== MAPA DO MUNDO ====================== \n\n");
    for (i = 1; i < qtdTerritorios + 1; i++) {
        printf("Território %d. %s (Exército %s, Tropas %d)\n", i,territorios[i].nome,territorios[i].cor,territorios[i].tropas);
    }
}



int exibirMenuPrincipal() {
    int opcao;

        printf("----------- MENU DE AÇÕES -----------\n");
        printf("1 - Atacar \n");
        printf("2 - Verificar Missão \n");
        printf("0 - Sair\n");
        printf("Enter your choice: ");
        scanf("%d", &opcao);
        return opcao;
}


// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.


    int opcaoSelecionada;
    
 
    // alocar mapa dinamicamente
    void(*ptr_alocaMapa)() = alocarMapa;
    ptr_alocaMapa();     

    // ponteiro pra inicilizar os territorios
    void(*ptr_initerritorio)() = inicializarTerritorios;
    ptr_initerritorio();
    
    // Exibir territorios
    void(*ptr_exibirMapa)() = exibirMapa;
    ptr_exibirMapa();  
    
    
    // DEFINIR MISSÃO

    // MENU DE AÇÕES - ATACAR - VERIFICAR MISSÃO - SAIR
    

    printf("\n\n----------- FASE DE ATAQUE -----------\n\n");

  
    
      /*free(territorios);*/

    printf("Fim do programa.\n");

    return 0;

}

// --- Implementação das Funções ---



// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.




// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
