#include <stdio.h>  // Entrada e saída
#include <string.h> // Necessário para usar as funções relacionadas a manipulação de strings
#include <stdlib.h> // Precisa utilizar os comandos system("clear") ou system("cls")
#include <ctype.h>  // biblioteca que tem uma função para transformar a letra para lowercase;



#define TAMANHO 10 // Define a quantidade máxima de animais cadastrados por vez

// Criação da struct
struct animal
{
    int id, idade;
    char raca[12];
    char data_entrada[11]; // 10 caracteres para dd/mm/yyyy + '\0'
    char sexo[10];
};
// PROTÓTIPO DAS FUNÇÕES
void limpa_tela();
void limpa_buffer();
int verifica_id(int codigo, int qtd_Animais, struct animal a[]);
void busca_raca(struct animal a[], int qtd_Animais, char palavra_chave[]);
void busca_raca_porSexo(struct animal a[], int qtd_Animais, char sexo[]);
void total_animaisPorSexo(struct animal a[], int qtd_Animais);
void media_idade_animaisPorsexo(struct animal a[], int qtd_Animais);
// FIM - PROTOTIPO DAS FUNÇOES

int main()
{
    // DECLARAÇÃO DE VARIÁVEIS
    int escolha, qtd_Animais = 0, i = 0;
    struct animal a[TAMANHO]; // Corrigido o tamanho do array

    memset(&a, 0, sizeof(a)); // Zera nossa struct

    printf("\n---------Sistema de Gerenciamento---------\n");

    // Loop do menu principal
    do
    {
        // Menu de opções
        do
        {
            printf("Escolha uma das opcoes para proceguir (1-5):\n");
            printf("1 - Cadastrar animal\n2 - Pesquisar\n3 - Relatorio\n4 - Animais por sexo\n5 - Sair\n");
            printf("Opcao: ");
            scanf("%d", &escolha);
            limpa_buffer(); // Limpar buffer que é uma maravilha após a leitura

            if (escolha < 1 || escolha > 5)
            {
                printf("\nOpcao invalida. Tente novamente.\n\n");
            }
        } while (escolha < 1 || escolha > 5); // Se tudo der certo, avança

        limpa_tela(); // Limpa a tela anterior

        switch (escolha)
        { // Código de acordo com a rota escolhida pelo usuário
        case 1:
            // Cadastro de animal
            printf("\n------------Interface de cadastro de animal------------\n");
            int entrada_quantidade = 0;
            do
            {
                printf("Insira a quantidade de animais que deseja cadastrar: "); // Evitar entradas de caracteres inválidos ou números quebrados/negativos
                scanf("%d", &entrada_quantidade);
                if (entrada_quantidade <= 0)
                {
                    printf("ERRO! Quantidade ou caractere inválido(a)! Insira um número inteiro maior que zero.\n");
                    limpa_buffer(); // limpa o buffer
                }
            } while (entrada_quantidade <= 0); // se o usuário entrar com algum caractere, entrada_quantidade receberá zero, aparecerá a mensagem do if em seguida o programa requisitara novamente a entrada.

            for (i = 0; i < entrada_quantidade; i++)
            {
                int codigo = 0;
                do
                {
                    printf("Entre com o id do animal: ");
                    if (scanf("%d", &codigo) != 1)//pelo que eu entendi, quando o scanf consegue ler com exito , 
                                              //ele retorna 1, então usei isso para filtrar entradas de caracteres 
                                              // entrar com um valor diferente de um inteiro positivo, então scanf retornará EOF, 
                                              //mas pelo que vi nas respostas, não é bom testar se a saida é EOF e sim
                                              //verificar se a saida pretendida foi atingida, neste caso, 1, que significa que não tem erro 
                                              //mais informações podem ser encontradas no link ---> https://stackoverflow.com/questions/10084224/how-do-we-test-the-return-values-from-the-scanf-function
                    {
                        printf("Entrada inválida! Insira um número inteiro.\n");
                        limpa_buffer(); // limpa buffer
                    }
                } while (verifica_id(codigo, qtd_Animais, a) == 0); // Verifica se o ID é único

                // Se o ID for diferente, então chegamos aqui:
                a[qtd_Animais].id = codigo; // RECEBAAA código /o/

                printf("Entre com a idade do animal: ");

                scanf("%d", &a[qtd_Animais].idade);
                limpa_buffer(); // limpa buffer

                printf("Entre com a raca do animal: ");
                fgets(a[qtd_Animais].raca, sizeof(a[qtd_Animais].raca), stdin);
                a[qtd_Animais].raca[strcspn(a[qtd_Animais].raca, "\n")] = '\0'; // vai procurar na string raça se existe um "\n", se encontrar, vai substitui-lo por um '\0'
                                                                                //  isso serve para eliminar o "\n" no final da string, substituindo-o por um '\0'
                limpa_buffer(); // limpa buffer

                printf("Entre com a data de entrada (dd/mm/yyyy): ");
                fgets(a[qtd_Animais].data_entrada, sizeof(a[qtd_Animais].data_entrada), stdin);
                a[qtd_Animais].data_entrada[strcspn(a[qtd_Animais].data_entrada, "\n")] = '\0'; // removedor de '\0'
                limpa_buffer();

                printf("Entre com o sexo do animal (Ex: Macho, Femea): ");
                fgets(a[qtd_Animais].sexo, sizeof(a[qtd_Animais].sexo), stdin);
                a[qtd_Animais].sexo[strcspn(a[qtd_Animais].sexo, "\n")] = '\0'; // Remove o "\n" no final da string
                limpa_buffer();

                printf("\nAnimal cadastrado com sucesso!\n");

                qtd_Animais++; // +1 na qtd_animais cadastrados
            }
            break; // o caminho foi longo, mas o cadastro finalmente acabou!
        case 2:
            limpa_tela();
            printf("\n------------Interface de pesquisa------------\n");

            char escolha_pesquisa;

            do
            {
                printf("Escolha uma das opções para prosseguir:\n");
                printf("a - Pesquisar por raça.\nb - Pesquisar por sexo.\n");
                printf("Opção(a ou b): ");
                scanf("%c", &escolha_pesquisa);

                limpa_buffer(); // limpador buffer após a leitura, garantir que não dê nenhum erro.

                if (escolha_pesquisa != 'a' && escolha_pesquisa != 'b')
                {
                    printf("\nOpção inválida. Tente novamente.\n\n");
                }

            } while (escolha_pesquisa != 'a' && escolha_pesquisa != 'b');

            if (escolha_pesquisa == 'a')
            {
                char palavra_chave[16];
                printf("Insira a raça que deseja pesquisar: ");
                fgets(palavra_chave, sizeof(palavra_chave), stdin);
                palavra_chave[strcspn(palavra_chave, "\n")] = '\0'; // Removedor de "\n" da string

                busca_raca(a, qtd_Animais, palavra_chave); // Chama a função para pesquisar por raça
            }
            else if (escolha_pesquisa == 'b')
            {
                char sexo[10];
                printf("Insira o sexo que deseja pesquisar (Ex: Macho, Femea): ");
                fgets(sexo, sizeof(sexo), stdin);
                sexo[strcspn(sexo, "\n")] = '\0'; // Remove o "\n" no final da string
                limpa_buffer();

                busca_raca_porSexo(a, qtd_Animais, sexo); // Chama a função para pesquisar por sexo
            }
            break;

        case 3:
            printf("\nInterface de relatorio\n");

            printf("RELATORIO - Informacao dos animais atualmente cadastrados no zoologico:\n\n");
            for (int i = 0; i < qtd_Animais; i++)
            {
                printf("ID: %d\n", a[i].id);
                printf("Raça: %s\n", a[i].raca);
                printf("Idade: %d\n", a[i].idade);
                printf("Data de Entrada: %s\n", a[i].data_entrada);
                printf("Sexo: %s\n\n", a[i].sexo);
            }

            break;

        case 4:
            printf("\nInterface de animais por sexo\n"); // O Boss final!
                                                         // a ideia é pegar a estrutura da opção 2 e adaptar
                                                         // para as especificadades da opção 4. Let's bora
            char escolha;
            do
            {
                printf("Escolha uma das opções para prosseguir:\n");
                printf("a - Apresentar total de animais por sexo\nb - Apresentar a média de idade de animais por sexo\n");
                printf("Opção(a ou b): ");
                scanf("%c", &escolha);

                limpa_buffer(); // limpador buffer após a leitura, garantir que não dê nenhum erro.

                if (escolha != 'a' && escolha != 'b')
                {
                    printf("\nOpção inválida. Tente novamente.\n\n");
                }

            } while (escolha != 'a' && escolha != 'b'); // repete o laço até o usuário inserir uma opção válida

            // chama as funções de acordo com as opção selecionada pelo usuario;
            if (escolha == 'a')
            {
                total_animaisPorSexo(a, qtd_Animais);
            }
            else if (escolha == 'b')
            {
                media_idade_animaisPorsexo(a, qtd_Animais);
            }

            break;
        case 5:
            printf("Saindo do programa... Aeeeee\n\n");
            exit(0);
            break;
        default:
            printf("Erro! entrada inválida!\n");
            sleep(5); // você não deveria estar aqui.
        }

    } while (escolha != 5); // Se o usuário escolher 5, saimos do loop do menu principal

    return 0;
}
void busca_raca(struct animal a[], int qtd_Animais, char palavra_chave[])
{
    int encontrou = 0;
    printf("Resultados da pesquisa por raça \"%s\":\n", palavra_chave);
    for (int i = 0; i < qtd_Animais; i++)
    {
        if (strstr(a[i].raca, palavra_chave) != NULL) // usuario entra com palavra_chave "gato",
        {                                             // a função verifica se existe um "gato" cadastrado,
                                                      // se sim, ele apresenta os dados dos animais daquela raça;
            printf("ID: %d\n", a[i].id);
            printf("Raça: %s\n", a[i].raca);
            printf("Idade: %d\n", a[i].idade);
            printf("Data de Entrada: %s\n", a[i].data_entrada);
            printf("Sexo: %s\n\n", a[i].sexo);
            encontrou = 1;
        }
    }

    if (!encontrou) // esse ! serve para testar se aquela variavel é falsa, se for falsa, se encontrou = 0, então entra no  if
    {
        printf("Nenhum animal da raça \"%s\" foi encontrado.\n", palavra_chave);
    }
}
void busca_raca_porSexo(struct animal a[], int qtd_Animais, char sexo[])
{
    int achou = 0;
    printf("Resultados da pesquisa por sexo \"%s\":\n", sexo);
    for (int i = 0; i < qtd_Animais; i++)
    {
        if (strcmp(a[i].sexo, sexo) == 0)
        {
            printf("ID: %d\n", a[i].id);
            printf("Raça: %s\n", a[i].raca);
            printf("Idade: %d\n", a[i].idade);
            printf("Data de Entrada: %s\n", a[i].data_entrada);
            printf("Sexo: %s\n\n", a[i].sexo);
            achou = 1;
        }
    }

    if (!achou)
    {
        printf("Nenhum animal com o sexo \"%s\" foi encontrado.\n", sexo);
    }
}
// Função para limpar a tela
void limpa_tela()
{
#ifdef __linux__
    system("clear");
#elif _WIN32
    system("cls");
#else
    // Código para outros sistemas operacionais
#endif
}

// Função que limpa o buffer do teclado
void limpa_buffer()                            //Essa função é responsável por limpar o buffer de entrada;
{                                              //tentei utilizar o fflush, mas infelizmente não funcionou muito bem, em algumas horas funcionava
                                              //e em outras dava erro, achando pouco confiável, acabei optando por procurar outra alternativa de limpar o stdin;
    int c;                                    //Encontrei essa função enquanto navegava no Stackoverflow, a pergunta respondida era:
    do {                                      // "Limpar buffer em C com fflush() ou __fpurge()" e "How can I clear an input buffer in C?"
        c = getchar();                        
    } while (c != '\n' && c != EOF); //o EOF é um valor retornado por funções como fgets, ele existe para indicar o final de um arquivo ou entrada. 
}                                             //As perguntas podem serem acessadas através dos seguintes links: 
                                              //"Limpar buffer em C com fflush() ou __fpurge()"
                                              //https://pt.stackoverflow.com/questions/111697/limpar-buffer-em-c-com-fflush-ou-fpurge
                                              //"How can I clear an input buffer in C?"  
                                              //https://stackoverflow.com/questions/7898215/how-can-i-clear-an-input-buffer-in-c

// Função para verificar se o ID já existe
int verifica_id(int codigo, int qtd_Animais, struct animal a[])
{
    for (int i = 0; i < qtd_Animais; i++)
    {
        if (a[i].id == codigo)
        {
            printf("ERRO! O ID já existe. Entre com um ID diferente.\n");
            return 0; // ID já existe
        }
    }
    return 1; // ID único
}

void total_animaisPorSexo(struct animal a[], int qtd_Animais)
{
    int i, totalF = 0, totalM = 0;

    for (i = 0; i < qtd_Animais; i++)
    {
        if (strcmp(a[i].sexo, "Macho") == 0 || strcasecmp(a[i].sexo, "macho") == 0 || strcasecmp(a[i].sexo, "m") == 0 || strcasecmp(a[i].sexo, "M") == 0)
        {
            totalM++;
        }
        else if (strcmp(a[i].sexo, "Femea") == 0 || strcasecmp(a[i].sexo, "femea") == 0 || strcasecmp(a[i].sexo, "f") == 0 || strcasecmp(a[i].sexo, "F") == 0) // compara a o valor da string no campo sexo com o char 'F', se for
        {
            totalF++;
        }
    }
    printf("\nTotal de animais femeas cadastradas no zoologico: %d", totalF);
    printf("\nTotal de animais machos cadastrados no zoologico: %d\n", totalM);
}

void media_idade_animaisPorsexo(struct animal a[], int qtd_Animais)
{

    int i, totalF = 0, totalM = 0, soma_IdadeMacho = 0, soma_IdadeFemea = 0; // totalF e totalM serão responsáveis por armazenar o numero de animais daquele sexo;

    for (i = 0; i < qtd_Animais; i++)
    {
        if (strcmp(a[i].sexo, "Femea") == 0 || strcasecmp(a[i].sexo, "femea") == 0 || strcasecmp(a[i].sexo, "f") == 0 || strcasecmp(a[i].sexo, "F") == 0) // são iguais? Então entra no if;
        {
            totalF++;
            soma_IdadeFemea = soma_IdadeFemea + a[i].idade; // soma as idades e adiciona em soma_IdadeFemea
        }
        if (strcmp(a[i].sexo, "Macho") == 0 || strcasecmp(a[i].sexo, "macho") == 0 || strcasecmp(a[i].sexo, "m") == 0 || strcasecmp(a[i].sexo, "M") == 0)
        {
            totalM++;
            soma_IdadeMacho = soma_IdadeMacho + a[i].idade;
        }
    }
    float mediaM = 0.0; // aqui guardaremos o valor da media das idades; //fiquei 5 minutos me perguntando porque o resultado tava saindo zerado, até notar que deixei essa operação de media
    float mediaF = 0.0; // dentro do for kkk

    if (totalF > 0) // proteção contra divisões por zero!
    {
        mediaF = (float)soma_IdadeFemea / totalF; // cast para float
    }

    if (totalM > 0)
    {
        mediaM = (float)soma_IdadeMacho / totalM;
    }

    printf("A média de idade dos animais fêmeas é: %.2f\n", mediaF);
    printf("A média de idade dos animais machos é: %.2f\n", mediaM);
}
