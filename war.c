// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
//         UPDATE - 1.1.3
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
    char nome[100];
    char cor[10];
    int tropas;
} Territorio;


//Territorio territorios[6]; // Vetor para armazenar 5 territórios
Territorio *territorios = NULL; // ponteiro dinâmico
int qtdTerritorios = 0;         // quantidade criada
int i;
int id_territorio_missao;   // armazena o id do territorio atacante, responsavel pela missão
char nome_missao[50];
int statusMissao = 0; //define um status da missão - 0 missão ainda pendente / 1 missão realizada


void liberarMemoria() {
    // Libera a memória previamente alocada para o mapa usando free.
    // Finaliza programa
    
    // if (territorios != NULL) {
    //     free(territorios);
    //     territorios = NULL;
    // }
    printf("Encerrando o programa...\n");
    exit(0);
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
            limparBufferEntrada();
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

    printf("\n %d territórios alocados com sucesso!\n\n", qtdTerritorios);
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

    // sorteia um território para a missão
    aleatorio = min + rand() % (max - min + 1);
    id_territorio_missao = aleatorio;

    strcpy(nome_missao, "Missão Atual -  "); 
    strcat(nome_missao, territorios[aleatorio].nome);
    strcat(nome_missao, " deverá conquistar um território inimigo"); 


    //return aleatorio;
}

void exibeMissaoAtual(int vlr) {

     if(vlr == 2) {
         printf("\n\n");	
      }

    printf("====================== MISSÃO ATUAL ======================\n");
    printf("%s\n", nome_missao);
    printf("==========================================================\n\n");	

     if(vlr == 2) {
         printf("Jogo Finalizado...\n");
         exit(0);
      }
    
}



void simularAtaque(int IdAtacante,int IdDefensor){
    int min,max,dado;
    int idVencedor,idPerdedor;
    int qtd_dado_atcante, qtd_dado_defensor;
    char mensagem_ataque[100];
    char tropa_vencedora[100];
    
    //   printf("id atacante -  %d: ", IdAtacante);
    //   printf("id defensor -  %d: ", IdDefensor);    

    //  Lógica de decisão. Sorteia dois número de 1 a 6  e atribui aos dois competidores. Maior vence
    min = 1;
    max = 6;

    
    // gera o dado pros dois competidores
    dado = min + rand() % (max - min + 1);
    qtd_dado_atcante = dado;
    dado = min + rand() % (max - min + 1);
    qtd_dado_defensor = dado;


    //  verifica quem foi o vencedor (Atacante ou defensor)

    if(qtd_dado_atcante >=qtd_dado_defensor) {
        territorios[IdAtacante].tropas ++;
        territorios[IdDefensor].tropas --;
        strcpy(tropa_vencedora, territorios[IdAtacante].nome);        


        // valida se a missão foi finalizada
        if(territorios[IdDefensor].tropas ==0) {
            if(IdAtacante == id_territorio_missao){
                // missão foi finalizada com exito 
                statusMissao = 1;     
            }else if(IdDefensor == id_territorio_missao) {
                // missão foi finalizada com falha 
                statusMissao = 2;     
            }     
                      
            idVencedor = IdAtacante;
            idPerdedor = IdDefensor;              
        }           

    } else {
        
        territorios[IdAtacante].tropas --;
        territorios[IdDefensor].tropas ++;
        strcpy(tropa_vencedora, territorios[IdDefensor].nome);

        // valida se a missão foi finalizada com falha
        // NESSA CONDIÇÃO, INVERTO AS POSSBILIDADES, CONSIDERANDO QUE O ATACANTE PERDEU TODAS AS TROPAS
        if(territorios[IdAtacante].tropas ==0) {
            if(IdAtacante == id_territorio_missao){
                // missão foi finalizada com falha 
                statusMissao = 2;     
            }else if(IdDefensor == id_territorio_missao) {
                // missão foi finalizada com exito 
                statusMissao = 1;     
            }     
                      
            idVencedor = IdDefensor;
            idPerdedor = IdAtacante;      
                    
        } 


    }


    // SE statusMissao = 1, SUCESSO
    // SE statusMissao = 2, FALHOU


    // altera informação do territorio dominado
    if(statusMissao ==1 || statusMissao == 2) {
        strcat(territorios[idPerdedor].nome, " - dominado pelo Território - ");
        strcat(territorios[idPerdedor].nome,territorios[idVencedor].nome);             
    }
    
    // altera informação da missão
    if(statusMissao ==1) {
        strcat(nome_missao, " | Missão Finalizada (Sucesso)");   
        exibeMissaoAtual(2);     
    } else if(statusMissao == 2){
        strcat(nome_missao, " | Missão Finalizada (Falhou)");    
        exibeMissaoAtual(2);    
    }



    // exibe mensagem com teitorio vencedor
    strcpy(mensagem_ataque, "\nTerritório "); 
    strcat(mensagem_ataque, tropa_vencedora);
    strcat(mensagem_ataque, " Venceu essa rodada\n"); 
    printf("%s\n", mensagem_ataque);


    // printf("dado defensor -  %d: \n", qtd_dado_defensor);


    
}

void faseDeAtaque() {
   int IdAtacante,IdDefensor;
   
   printf("----------------------- FASE DE ATAQUE ---------------------- \n\n");
   printf("Escolha o territorio atacante (1 a %d): ", qtdTerritorios);
   scanf("%d", &IdAtacante);
   printf("Escolha o territorio defensor (1 a %d): ", qtdTerritorios);
   scanf("%d", &IdDefensor);
   
    // verifica se o atacante selecionado é o mesmo que o defesenor, caso sim, realiza chamada recursiva    
    if(IdAtacante == IdDefensor) {
        printf("\n O Defensor, tem que ser uma opção diferente do atacante \n\n");
        faseDeAtaque();
    } else {

        // passa os id's do atacante e defensor, via parametro
        simularAtaque(IdAtacante,IdDefensor);
    }
   
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
    printf("\n");
    
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
                exibeMissaoAtual(1);
                break;
            case 3:
                exibirMapa();
                break;
        }


    } while (opcao != 0);
}


int main() {

   
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
    void(*ptr_exibeMissaoAtual)(int) = exibeMissaoAtual;
    ptr_exibeMissaoAtual(1); 
    

    // exibe menu
    void(*ptr_exibirMenuPrincipal)() = exibirMenuPrincipal;
    ptr_exibirMenuPrincipal();  


   liberarMemoria();
   return 0;

}

