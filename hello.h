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

/* Struct que define o registro de cabe�alho do arquivo de indice */
typedef struct{
    char status;
    int nroRegistros;
}Cabecalho_ind;

/* Struct que define o registro de dados do arquivo de indice */
typedef struct{
    char chaveBusca[28];
    int RRN;
}Dados_ind;

/* Struct que define o registro de cabe�alho do arquivo de dados */
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

/* Cabe�alho das fun��es */
void ler_nomeEscola(char, FILE*, char*); /* Fun��o que l� o campo nomeEscola e associa a um vetor */
void print_nomeEscola(char, FILE*); /* Fun��o que imprime o campo nomeEscola */
int compara_string(char*, char*, int); /* Fun��o que compara duas strings e retorna 1 se forem iguais e 0 se forem diferentes */
void limpa_string (char*, int); /* Fun��o que preenche a string com \0, evitando conflitos com outras strings que utilizam uma mesma vari�vel */
void ler_string (FILE*, char*, int); /* Fun��o que l� as strings de um arquivo bin�rio */
void escrever_string (FILE*, char*, int); /* Fun��o que escreve as strings em um arquivo bin�rio */
void preenche_registros(FILE*, int, int); /* Fun��o que preenche os registros com @, para que eles possuam tamanho fixo */
void iniciar_cabecalho(Header); /* Define os valores iniciais do cabe�alho */
void escrever_cabecalho(Header, FILE*); /* Escreve o cabe�alho no arquivo bin�rio */
int escrever_file_binario(Header, char*);   /* Fun��o respons�vel por ler o csv e escrever os dados no arquivo bin�rio */
void sub_string (char*, char*, int, char, int*); /* Fun��o respons�vel por separar strings de uma posi��o at� encontrar um delimitador */
void preenche_data(char*, char*, int*); /* Fun��o respons�vel por preencher o campo data caso exista ou, caso seja nulo, faz as devidas mudan�as */
void escrever_data_null(FILE*); /* Fun��o que faz o tratamento quando a data � nula */
void consultar_file_binario(char*);     /* Fun��o respons�vel por ler e exibir todos os registros presentes no arquivo bin�rio */
void consultar_dado(char*, char*, char*);    /* Fun��o respons�vel por procurar e exibir registros de algum dado espec�fico no arquivo bin�rio */
void consultar_rrn(char*, int, int);      /* Fun��o respons�vel por consultar e exibir o registro do rrn solicitado */
void remover_registro(char*, char*, char*, int); /* Fun��o que remove registros que satisfa�am o crit�rio de busca do usuario */
void insercao_adicional(char*, int, char*, int); /* Fun��o que insere dados nos registros removidos */
void atualizar_registro(char*, int, char*, char*, int); /* Fun��o que atualiza um registro */
void ordenaInteiro(char*, char*); /* Fun��o que l� e ordena os registros para inseri-los em um novo arquivo, j� ordenados */
int qtdRegistro(FILE*); /* Retorna a quantidade de registros (sem considerar os removidos) */
int guardaDados(FILE*, Dados_PTR); /* Fun��o que armazena todos os registros do arquivo em vetores */
void merge(Dados_PTR*, int, int, int); /* Fun��o utilizada pelo mergeSort para ordenar o vetor */
void mergeSort(Dados_PTR*, int, int); /* Ordena o vetor */
void escrever_dados(Dados_PTR, FILE*, int*, char*, char*); /* Fun��o que escreve os registros no arquivo */
void troca_reg(Dados_PTR, Dados_PTR, int, int); /* Fun��o que associa os campos dos registros do arquivo antigo com o novo */
void merging(char*, char*, char*); /* Fun��o que realiza o processo de merging entre dois arquivos */
void matching(char*, char*, char*); /* Fun��o que realiza o processo de matching entre dois arquivos */
void cria_indice(char*, char*);
void escreve_cabecalhoInd(FILE*, Header_ind);
void escreve_DadosInd(FILE*, Dados_ind_PTR);
int cria_indDados(FILE*, Dados_ind_PTR, int);
void merge_ind(Dados_ind_PTR*, int, int, int); /* Fun��o utilizada pelo mergeSort para ordenar os registros do indice */
void mergeSort_ind(Dados_ind_PTR*, int, int); /* Ordena os registros do indice*/
void recupera_reg_ind(char*, char*, char*);
int ler_chave_ind(FILE*, char *);
int binarySearch(Dados_ind_PTR, int, int, char*);
void binarioNaTela1(FILE*); /* Fun��o que mostra a sa�da do arquivo bin�rio */
