/*Lucas Tavares dos Santos - 10295180*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERRO 0
#define OK   1
#define TAM_CAB 285
#define TAM_DAD 80
#define TAM_PAGE 16000
#define TAM_IND 5
#define TAM_DAD_IND 32

/* Struct que define o registro de cabeçalho do arquivo de indice */
typedef struct{
    char status;
    int nroRegistros;
}Cabecalho_ind;

/* Struct que define o registro de dados do arquivo de indice */
typedef struct{
    char chaveBusca[28];
    int RRN;
}Dados_ind;

/* Struct que define o registro de cabeçalho do arquivo de dados */
typedef struct{
    char status;
    int topoPilha;
    char tagCampo1, desCampo1[55], tagCampo2, desCampo2[55], tagCampo3, desCampo3[55], tagCampo4, desCampo4[55], tagCampo5, desCampo5[55];
}Cabecalho;

/* Struct que define o registro de dados do arquivo de dados */
typedef struct{
    char removido;
    int encadeamento;
    int nroInscricao;
    double nota;
    char data[10];
    int indCid;
    char tagCampo4;
    char* cidade;
    int indEsc;
    char tagCampo5;
    char* nomeEscola;
}Dados;

/* Definindo nomes para os ponteiros das structs acima */
typedef Dados* Dados_PTR;
typedef Cabecalho* Header;
typedef Dados_ind* Dados_ind_PTR;
typedef Cabecalho_ind* Header_ind;

/* Cabeçalho das funções */
void ler_nomeEscola(char, FILE*, char*); /* Função que lê o campo nomeEscola e associa a um vetor */
void print_nomeEscola(char, FILE*); /* Função que imprime o campo nomeEscola */
int compara_string(char*, char*, int); /* Função que compara duas strings e retorna 1 se forem iguais e 0 se forem diferentes */
void limpa_string (char*, int); /* Função que preenche a string com \0, evitando conflitos com outras strings que utilizam uma mesma variável */
void ler_string (FILE*, char*, int); /* Função que lê as strings de um arquivo binário */
void escrever_string (FILE*, char*, int); /* Função que escreve as strings em um arquivo binário */
void preenche_registros(FILE*, int, int); /* Função que preenche os registros com @, para que eles possuam tamanho fixo */
void iniciar_cabecalho(Header); /* Define os valores iniciais do cabeçalho */
void escrever_cabecalho(Header, FILE*); /* Escreve o cabeçalho no arquivo binário */
int escrever_file_binario(Header, char*);   /* Função responsável por ler o csv e escrever os dados no arquivo binário */
void sub_string (char*, char*, int, char, int*); /* Função responsável por separar strings de uma posição até encontrar um delimitador */
void preenche_data(char*, char*, int*); /* Função responsável por preencher o campo data caso exista ou, caso seja nulo, faz as devidas mudanças */
void escrever_data_null(FILE*); /* Função que faz o tratamento quando a data é nula */
void consultar_file_binario(char*);     /* Função responsável por ler e exibir todos os registros presentes no arquivo binário */
void consultar_dado(char*, char*, char*);    /* Função responsável por procurar e exibir registros de algum dado específico no arquivo binário */
void consultar_rrn(char*, int, int);      /* Função responsável por consultar e exibir o registro do rrn solicitado */
void remover_registro(char*, char*, char*, int); /* Função que remove registros que satisfaçam o critério de busca do usuario */
void insercao_adicional(char*, int, char*, int); /* Função que insere dados nos registros removidos */
void atualizar_registro(char*, int, char*, char*, int); /* Função que atualiza um registro */
void ordenaInteiro(char*, char*); /* Função que lê e ordena os registros para inseri-los em um novo arquivo, já ordenados */
int qtdRegistro(FILE*); /* Retorna a quantidade de registros (sem considerar os removidos) */
int guardaDados(FILE*, Dados_PTR); /* Função que armazena todos os registros do arquivo em vetores */
void merge(Dados_PTR*, int, int, int); /* Função utilizada pelo mergeSort para ordenar o vetor */
void mergeSort(Dados_PTR*, int, int); /* Ordena o vetor */
void escrever_dados(Dados_PTR, FILE*, int*, char*, char*); /* Função que escreve os registros no arquivo */
void troca_reg(Dados_PTR, Dados_PTR, int, int); /* Função que associa os campos dos registros do arquivo antigo com o novo */
void merging(char*, char*, char*); /* Função que realiza o processo de merging entre dois arquivos */
void matching(char*, char*, char*); /* Função que realiza o processo de matching entre dois arquivos */
void cria_indice(char*, char*);
void escreve_cabecalhoInd(FILE*, Header_ind);
void escreve_DadosInd(FILE*, Dados_ind_PTR);
int cria_indDados(FILE*, Dados_ind_PTR, int);
void merge_ind(Dados_ind_PTR*, int, int, int); /* Função utilizada pelo mergeSort para ordenar os registros do indice */
void mergeSort_ind(Dados_ind_PTR*, int, int); /* Ordena os registros do indice*/
void recupera_reg_ind(char*, char*, char*);
int ler_chave_ind(FILE*, char *);
int binarySearch(Dados_ind_PTR, int, int, char*);
void binarioNaTela1(FILE*); /* Função que mostra a saída do arquivo binário */
