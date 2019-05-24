/*Lucas Tavares dos Santos - 10295180*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hello.h"

int main(){
    char nome_file[20], nome_file2[20], nome_file_ord[20], nome_campo[20], valor[40], campos[100];
    int opt, rrn, n, i = 0, valorNroInscricao;

    Header head = calloc(1, sizeof(Cabecalho)); /* Cria a estrutura do cabe�alho */
    scanf("%d", &opt);  /* Digita o n�mero da op��o a ser considerada */
    switch (opt){
    case 1:
        scanf("%s", nome_file); /* Digita o nome do arquivo .csv */
        escrever_file_binario(head, nome_file); /* Fun��o respons�vel por ler o csv e escrever os dados no arquivo bin�rio */
        break;
    case 2:
        scanf("%s", nome_file); /* Digita o nome do arquivo bin�rio */
        consultar_file_binario(nome_file);  /* Fun��o respons�vel por ler e exibir todos os registros presentes no arquivo bin�rio */
        break;
    case 3:
        scanf("%s %s %[^\n]s", nome_file, nome_campo, valor); /* Digita o nome do arquivo bin�rio, o nome do campo e o valor a ser procurado */
        consultar_dado(nome_file, nome_campo, valor); /* Fun��o respons�vel por procurar e exibir registros de algum dado espec�fico no arquivo bin�rio */
        break;
    case 4:
        scanf("%s", nome_file); /* Digita o nome do arquivo bin�rio */
        scanf("%d", &rrn);  /* Digita o nome do rrn a ser consultado */
        consultar_rrn(nome_file, rrn, 0);  /* Fun��o respons�vel por consultar e exibir o registro do rrn solicitado */
        break;
    case 5:
        scanf("%s %d", nome_file, &n); /* Digita o nome do arquivo binario e o numero de iteracoes */
        while(i < n){
            scanf("%s %[^\n]s", nome_campo, valor); /* Digita o nome do campo e o criterio de busca */
            if(i == n-1)
                remover_registro(nome_file, nome_campo, valor, OK); /* Fun��o que remove registros que satisfa�am o crit�rio de busca do usuario */
            else
                remover_registro(nome_file, nome_campo, valor, ERRO); /* Fun��o que remove registros que satisfa�am o crit�rio de busca do usuario */
            i++;
        }
        break;
    case 6:
        scanf("%s %d", nome_file, &n); /* Digita o nome do arquivo binario e o numero de iteracoes */
        while(i < n){
            scanf("%d %[^\n]s", &valorNroInscricao, campos); /* Digita o nroInscricao, nota e, na variavel campos, a data, a cidade e o nomeEscola */
            if(i == n-1)
                insercao_adicional(nome_file, valorNroInscricao, campos, OK); /* Fun��o que insere dados nos registros removidos */
            else
                insercao_adicional(nome_file, valorNroInscricao, campos, ERRO); /* Fun��o que insere dados nos registros removidos */
            i++;
        }
        break;
    case 7:
        scanf("%s %d", nome_file, &n); /* Digita o nome do arquivo binario e o numero de iteracoes */
        while(i < n){
            scanf("%d %s %[^\n]s", &rrn, nome_campo, valor); /* Digita o rrn, o nome do campo e o criterio de busca */
            if(i == n-1)
                atualizar_registro(nome_file, rrn, nome_campo, valor, OK); /* Fun��o que atualiza um registro */
            else
                atualizar_registro(nome_file, rrn, nome_campo, valor, ERRO); /* Fun��o que atualiza um registro */
            i++;
        }
        break;
    case 8:
        scanf("%s %s", nome_file, nome_file_ord); /* Digita o nome dos arquivos bin�rios */
        ordenaInteiro(nome_file, nome_file_ord);
        break;
    case 9:
        scanf("%s %s %s", nome_file, nome_file2, nome_file_ord); /* Digita o nome dos arquivos bin�rios */
        merging(nome_file, nome_file2, nome_file_ord);
        break;
    case 10:
        scanf("%s %s %s", nome_file, nome_file2, nome_file_ord); /* Digita o nome dos arquivos bin�rios */
        matching(nome_file, nome_file2, nome_file_ord);
        break;
    case 11:
        scanf("%s %s", nome_file, nome_file2); /* Digita o nome dos arquivos bin�rios */
        cria_indice(nome_file, nome_file2);
        break;
    case 12:
        scanf("%s %s %s %[^\n]s", nome_file, nome_file2, campos, valor); /* Digita o nome dos arquivos bin�rios */
        recupera_reg_ind(nome_file, nome_file2, valor);
        break;
    }
    return 0;
}
