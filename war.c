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

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


//Territorio territorios[6]; // Vetor para armazenar 5 territórios
Territorio *territorios = NULL; // ponteiro dinâmico
int qtdTerritorios = 0;         // quantidade criada
int i;
int id_Territorio_missao;
char nome_missao[50];


void liberarMemoria() {
    // Libera a memória previamente alocada para o mapa usando free.
    // Finaliza programa
    free(territorios);
    printf("Encerrando o programa...\n");
    exit(0); // encerra o programa
}


void limparBufferEntrada(void) {
    int c;
    // Lê e descarta caracteres até encontrar '\n' (Enter) ou EOF (fim do arquivo)
    while ((c = getchar()) != '\n' && c != EOF) {
        // apenas descarta o caractere
    }
}

void alocarMapa() {
  do {
        printf("Quantos territórios deseja criar (0 para sair)? ");
        if (scanf("%d", &qtdTerritorios) != 1) {
            // Entrada inválida (ex: texto)
            printf("Entrada inválida! Tente novamente.\n");
            while (getchar() != '\n'); // limpa o buffer
            continue;
        }

        if (qtdTerritorios == 0) {
           liberarMemoria();       
        }

        if (qtdTerritorios < 2) {
            printf("Quantidade mínima é 2!\n");
        }

    } while (qtdTerritorios < 2);

    territorios = calloc(qtdTerritorios, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    printf("%d territórios alocados com sucesso!\n\n", qtdTerritorios);
}

void inicializarTerritorios(){
  
     //printf("====================== Cadastro de Territórios ======================\n\n Pressione Enter para começar \n\n");
     printf("====================== Cadastro de Territórios ======================\n\n");

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
    printf("====================== MAPA DO MUNDO ======================\n");
    for (i = 1; i < qtdTerritorios + 1; i++) {
        printf("Território %d. %s (Exército %s, Tropas %d)\n", i,territorios[i].nome,territorios[i].cor,territorios[i].tropas);
    }
    printf("===========================================================\n\n");	
}

void sortearMissao(){
    int min,max,aleatorio;

    min = 1;
    max = qtdTerritorios;

    aleatorio = min + rand() % (max - min + 1);

    strcpy(nome_missao, "Missão Atual -  "); 
    strcat(nome_missao, territorios[aleatorio].nome);
    strcat(nome_missao, " deverá conquistar um território"); 


    //return aleatorio;
}

void exibeMissaoAtual() {
    printf("====================== MISSÃO ATUAL ======================\n");
    printf("%s\n", nome_missao);
    printf("==========================================================\n\n");	
}



void faseDeAtaque() {
   int IdTerritorioAtacante,IdTerritorioDefensor;
   
   printf("----------------------- FASE DE ATAQUE ---------------------- \n");
   printf("Escolha o territorio atacante (1 a %d)\n", qtdTerritorios);
   scanf("%d", &IdTerritorioAtacante);

   printf("opção selecionada -  %d)", IdTerritorioAtacante);
   
}


void simularAtaque(){


}


void exibirMenuPrincipal() {

 int ret;
    int opcao;	
do {
    
    printf("============================================================= \n");	
    printf("                         MENU DE AÇÕES                        \n");
    printf("============================================================= \n");	
    printf("1 - Atacar \n");
    printf("2 - Verificar Missão \n");
    printf("3 - Exibir mapa do mundo \n");
    printf("0 - Sair\n");
    printf("Selecione uma Opção: ");
    scanf("%d", &opcao);

        if (opcao != 0 && opcao != 1 && opcao != 2 && opcao != 3) {
            // entrada inválida: descarta a linha e repete
            printf("Entrada inválida. Digite uma das 4 opções acima.\n\n");
            limparBufferEntrada();
            continue;
        }

        limparBufferEntrada(); // remove o '\n' deixado no buffer
        // printf("opção selecionada - %d\n\n", opcao);
      
        switch (opcao)
        {
            case 1:
                faseDeAtaque();
                break;
            case 2:
                exibeMissaoAtual();
                break;
            case 3:
                exibirMapa();
                break;
        }


    } while (opcao != 0);
}


// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.



// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {

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
    srand(time(NULL));  // semente do gerador aleatorio
    setlocale(LC_ALL,"portuguese");
 
 
    // alocar mapa dinamicamente
    void(*ptr_alocaMapa)() = alocarMapa;
    ptr_alocaMapa();     

    // ponteiro pra inicilizar os territorios
    void(*ptr_initerritorio)() = inicializarTerritorios;
    ptr_initerritorio();
    
    // Exibir territorios
    void(*ptr_exibirMapa)() = exibirMapa;
    ptr_exibirMapa();  
    

    // Definir missão atual
    void(*ptr_sortearMissao)() = sortearMissao;
    ptr_sortearMissao();  
    

    // exibir missão atual
    void(*ptr_exibeMissaoAtual)() = exibeMissaoAtual;
    ptr_exibeMissaoAtual(); 
    

    // exibe menu
    void(*ptr_exibirMenuPrincipal)() = exibirMenuPrincipal;
    ptr_exibirMenuPrincipal();  


   liberarMemoria();
   return 0;

}

// --- Implementação das Funções ---



// 
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// 
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.



// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.