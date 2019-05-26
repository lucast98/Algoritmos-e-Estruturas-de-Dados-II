/*Lucas Tavares dos Santos - 10295180
Luiz Guilherme Martins Adorno - 10392171
Foi utilizado o trabalho do Lucas como base
*/

#include "hello.h"

void ler_nomeEscola(char c, FILE* file, char *str){
    int i = 0;
    c='\0';
    do{
        fread(&c, sizeof(char),1, file); /* lê chars até encontrar um @ */
        if(c=='@' || c == '\0')
            break;
        str[i] = c;
        i++;
    }while(c!='@');
    str[i] = '\0';
}

void print_nomeEscola(char c, FILE* file){
    c='\0';
    do{
        fread(&c, sizeof(char),1, file); /* lê chars até encontrar um @ */
        if(c=='@')
            break;
        printf("%c", c);
    }while(c!='@');
}

int compara_string(char* str1, char* str2, int tam){
    int i=0;
    while(i < tam){ /* de 0 ao tamanho da string */
        if(str1[i] == str2[i]) /* compara cada char das strings */
            i++; /* incrementa i se os chars forem iguais */
        else
            return ERRO; /* caso algum dos chars não sejam iguais, o programa retorna o valor 0 */
    }
    return OK; /* caso todos os chars sejam iguais, temos que as strings são idênticas e retorna o valor 1 */
}

void limpa_string(char* str, int tam){
    int i;
    for (i = 0; i < tam; i++) /* de 0 ao tamanho preenchido da string */
        str[i] = '\0'; /* preenche a string com \0 */
}

void ler_string(FILE *file, char *str, int tam){
    int i = 0;
    while(i<tam){   /* de 0 ao tamanho da string */
        fread(&str[i], sizeof(char), 1, file); /* lê o arquivo e armazena os chars em um vetor de char */
        i++; /* incrementa o i */
    }
    str[i] = '\0'; /* termina a string com \0 */
}

int ler_stringDel (FILE *file, char *str, char del){
    int i=-1;
    do{
        i++;
        fread(&str[i], sizeof(char), 1, file);
    }while(str[i] != del);
    return i;
}

void escrever_string(FILE *file, char *str, int tam){
    int i;
    for (i = 0; i < tam; i++) /* de 0 ao tamanho da string */
        fwrite(&str[i], sizeof(char), 1, file); /* escreve os chars do vetor no arquivo, um por iteração */
}

void preenche_registros(FILE *nome_file, int qtd_bytes, int qtd_preencher){
    int i;
    char lixo = '@'; /* define a variável lixo como @, conforme as especificações */
    for(i = qtd_bytes; i < qtd_preencher; i++) /* vai da quantidade de bytes que o registro já possui até o seu valor máximo */
        fwrite(&lixo, sizeof(char), 1, nome_file); /* preenche o arquivo binário com @ */
}

void iniciar_cabecalho(Header head){
    head->status = '0'; /* Valor inicial da variável status */
    head->topoPilha = -1; /* Valor inicial da variável topoPilha */
    head->tagCampo1 = '1'; /* Valor da tagCampo1 */
    strcpy(head->desCampo1, "numero de inscricao do participante do ENEM"); /* Valor do desCampo1 */
    head->tagCampo2 = '2'; /* Valor da tagCampo2 */
    strcpy(head->desCampo2, "nota do participante do ENEM na prova de matematica"); /* Valor do desCampo2 */
    head->tagCampo3 = '3'; /* Valor da tagCampo3 */
    strcpy(head->desCampo3, "data"); /* Valor do desCampo3 */
    head->tagCampo4 = '4'; /* Valor da tagCampo4 */
    strcpy(head->desCampo4, "cidade na qual o participante do ENEM mora"); /* Valor do desCampo4 */
    head->tagCampo5 = '5'; /* Valor da tagCampo5 */
    strcpy(head->desCampo5, "nome da escola de ensino medio"); /* Valor do desCampo5 */
}

void escrever_cabecalho(Header head, FILE* file){
    char c= '\0';
    fwrite(&(head->status), sizeof(char), 1, file); /* escreve o status no arquivo binário */
    fwrite(&(head->topoPilha), sizeof(head->topoPilha), 1, file); /* escreve o topoPilha no arquivo binário */
    fwrite(&(head->tagCampo1), sizeof(head->tagCampo1), 1, file); /* escreve o tagCampo1 no arquivo binário */
    fwrite(&(head->desCampo1), strlen(head->desCampo1), 1, file); /* escreve o desCampo1 no arquivo binário */
    fwrite(&c, sizeof(c), 1, file); /* escreve o \0 no arquivo binário */
    preenche_registros(file, strlen(head->desCampo1)+1, sizeof(head->desCampo1)); /* tratamento de lixo na variavel */
    fwrite(&(head->tagCampo2), sizeof(head->tagCampo2), 1, file); /* escreve o tagCampo2 no arquivo binário */
    fwrite(&(head->desCampo2), strlen(head->desCampo2), 1, file); /* escreve o desCampo2 no arquivo binário */
    fwrite(&c, sizeof(c), 1, file); /* escreve o \0 no arquivo binário */
    preenche_registros(file, strlen(head->desCampo2)+1, sizeof(head->desCampo2)); /* tratamento de lixo na variavel */
    fwrite(&(head->tagCampo3), sizeof(head->tagCampo3), 1, file); /* escreve o tagCampo3 no arquivo binário */
    fwrite(&(head->desCampo3), strlen(head->desCampo3), 1, file); /* escreve o desCampo3 no arquivo binário */
    fwrite(&c, sizeof(c), 1, file); /* escreve o \0 no arquivo binário */
    preenche_registros(file, strlen(head->desCampo3)+1, sizeof(head->desCampo3)); /* tratamento de lixo na variavel */
    fwrite(&(head->tagCampo4), sizeof(head->tagCampo4), 1, file); /* escreve o tagCampo4 no arquivo binário */
    fwrite(&(head->desCampo4), strlen(head->desCampo4), 1, file); /* escreve o desCampo4 no arquivo binário */
    fwrite(&c, sizeof(c), 1, file); /* escreve o \0 no arquivo binário */
    preenche_registros(file, strlen(head->desCampo4)+1, sizeof(head->desCampo4)); /* tratamento de lixo na variavel */
    fwrite(&(head->tagCampo5), sizeof(head->tagCampo5), 1, file); /* escreve o tagCampo5 no arquivo binário */
    fwrite(&(head->desCampo5), strlen(head->desCampo5), 1, file); /* escreve o desCampo5 no arquivo binário */
    fwrite(&c, sizeof(c), 1, file); /* escreve o \0 no arquivo binário */
    preenche_registros(file, strlen(head->desCampo5)+1, sizeof(head->desCampo5)); /* tratamento de lixo na variavel */
}

int escrever_file_binario(Header head, char* nome_file){
    int cont, int_aux, i = -1, pos = TAM_PAGE;
    char linha_reg[1000];
    char aux[30], cid_aux[30], esc_aux[30], lixo = '@';
    Dados_PTR dado;
    FILE* file2 = fopen(nome_file, "r"); /* abre o arquivo .csv */
    if(!file2){
        printf("Falha no carregamento do arquivo.");
        return ERRO; /* caso o arquivo não exista ou ocorra outro erro, retorna 0 */
    }
    FILE* file = fopen("arquivoTrab1si.bin", "wb"); /* cria o arquivo binário */
    if(!file){
        printf("Falha no carregamento do arquivo.");
        return ERRO; /* caso o arquivo não consiga ser criado ou ocorra outro erro, retorna 0 */
    }

    /* Registros */
    iniciar_cabecalho(head); /* fornece os valores iniciais para o cabeçalho */
    escrever_cabecalho(head, file); /* escreve os valores iniciais do cabeçalho no arquivo binário */
    preenche_registros(file, TAM_CAB, TAM_PAGE); /* como o registro de cabeçalho ocupa uma página de disco inteira, é necessário preencher o resto da página */

    dado = (Dados_PTR) malloc(sizeof(Dados)); /* cria o ponteiro da struct Dados */
    fseek(file, TAM_PAGE, SEEK_SET); /* pula para a segunda página de disco */
    while(!feof(file2)){
        linha_reg[0] = '\0';
        if(!fgets(linha_reg, 1000, file2)) /* se o fgets retornar 0, significa que o arquivo terminou */
            break;
        if(i != -1){
            cid_aux[0] = '\0';
            esc_aux[0] = '\0';
            int_aux = 0;

            /* Removido */
            dado->removido = '-'; /* valor inicial do campo removido */

            /* Encadeamento */
            dado->encadeamento = -1; /* valor inicial do campo encadeamento */

            /* Nro inscricao */
            sub_string(aux, linha_reg, 0, ',', &int_aux); /* quebra a linha de 0 até a primeira virgula encontrada, resultando na string aux */
            dado->nroInscricao = atoi(aux); /* converte a string pra inteiro e associa o campo nroInscricao com o valor obtido */
            limpa_string(aux, strlen(aux)); /* preenche a string aux com \0 */

            /* Nota */
            sub_string(aux, linha_reg, int_aux+1, ',', &int_aux); /* quebra a linha da posição posterior a virgula anterior até a proxima virgula encontrada, resultando na string aux */
            if(strcmp(aux, "") != 0)
                dado->nota = atof(aux); /* se aux possuir um valor, converter a string para double e associa o campo nota com o valor obtido */
            else
                dado->nota = -1; /* se aux não possuir um valor, associar o valor -1 ao campo nota */
            limpa_string(aux, strlen(aux)); /* preenche a string aux com \0 */

            /* Data */
            preenche_data(dado->data, linha_reg, &int_aux); /* preencher o campo data com o seu valor ou, caso seja nulo, com \0@@@@@@@@@ */

            /* Cidade */
            sub_string(aux, linha_reg, int_aux+1, ',', &int_aux); /* quebra a linha da posição posterior a virgula anterior até a proxima virgula encontrada, resultando na string aux */
            if(strcmp(aux, "") != 0){
                dado->indCid = strlen(aux) + 2; /* se aux possuir um valor, associar o tamanho da string aux com o indicador de tamanho */ /* +2 devido a tag e \0 */
                dado->tagCampo4 = '4'; /* associa o campo tagCampo4 com o char '4' */
                strcpy(cid_aux, aux); /* copia a string aux para a variavel cid_aux */
                cid_aux[strlen(aux)] = '\0';
            }
            else
                dado->indCid = 0; /* caso aux não possua um valor, o indicador de tamanho é 0 */
            limpa_string(aux, strlen(aux)); /* preenche a string aux com \0 */

            /* Nome _escola */
            sub_string(aux, linha_reg, int_aux+1, ',', &int_aux);
            if(strcmp(aux, "") != 0){
                dado->indEsc = strlen(aux) + 2; /* se aux possuir um valor, associa o tamanho da string aux com o indicador de tamanho */
                dado->tagCampo5 = '5'; /* associa o campo tagCampo5 com o char '5' */
                strcpy(esc_aux, aux); /* copia a string aux para a variavel esc_aux */
                esc_aux[strlen(aux)] = '\0';
            }
            else
                dado->indEsc = 0; /* caso aux não possua um valor, o indicador de tamanho é 0 */
            limpa_string(aux, strlen(aux)); /* preenche a string aux com \0 */

            escrever_dados(dado, file, &cont, cid_aux, esc_aux); /* Escrever no arquivo binário */
            pos = cont+2+pos; /* método para inserir os @s no fim dos registros */
            while(pos < (TAM_PAGE+(i+1)*80)){
                fwrite(&lixo, sizeof(lixo), 1, file);
                pos++;
            }
            if((i != 0 && dado->indCid <= 0) || (i != 0 && dado->indEsc <= 0)){ /* caso um dos campos variaveis seja nulo, é necessário inserir mais um @ */
                fwrite(&lixo, sizeof(lixo), 1, file);
                if(dado->indCid <= 0 && dado->indEsc <= 0) /* caso os dois campos variaveis sejam nulos, é necessário inserir um @ extra */
                    fwrite(&lixo, sizeof(lixo), 1, file);
            }
        }
        i++;
        limpa_string(dado->data, sizeof(dado->data));
        limpa_string(cid_aux, sizeof(cid_aux)); /* preenche a string com \0 */
        limpa_string(esc_aux, sizeof(esc_aux)); /* preenche a string com \0 */
    }
    head->status = '1'; /* depois que o arquivo foi escrito, atualiza o valor do status */
    fseek(file, 0, SEEK_SET); /* retorna para o inicio do arquivo binario */
    fwrite(&(head->status), sizeof(char), 1, file); /* reescreve o status no cabeçalho */
    fclose(file2);
    fclose(file);
    printf("arquivoTrab1si.bin");
    //printf("%d reg escritos em %s\n", i, nome_file);
    return OK; /* retorna 1 */
}

/* função pega uma parte de uma string definida entre o índice inicial(ind_in) e o caractere de corte (carac_fim) */
/* caso não encontre o caractere de corte a partir do índice inicial, ele retorna a string que corresponde do índice inicial(ind_in) e o fim da string */
/* o inteiro (pos) retorna para a função que chamou sub_string a posição da primeira ocorrência do caractere de corte (carac_fim) a partir do índice inicial */
void sub_string (char *aux, char* str_in, int ind_in, char carac_fim, int* pos){
    char* str_out = NULL;
    int tam = strlen(str_in);
    *pos = tam;
    for(int i = ind_in; i < tam; i++){ /*percorre caractere por caractere do índice inicial ao fim da string */
        if(str_in[i] == carac_fim || str_in[i] == '\n'){ /* caso encontre o caractere de corte */
            str_out = (char*) realloc(str_out, (i - ind_in + 1) * sizeof(char));
            str_out[i-ind_in] = '\0';
            *pos = i;
            strcpy(aux, str_out); /* copia para a variável de retorno o conteúdo de parte da string */
            return; /* retorna caso encontre o caractere de corte */
        } /* se terminou o for, logo o caractere de corte não foi localizado na string */
        str_out = (char*) realloc(str_out, (i - ind_in + 2) * sizeof(char));
        str_out[i-ind_in] = str_in[i];
        str_out[i-ind_in+1] = '\0';
    }
    strcpy(aux, str_out); /* copia para a variável de retorno o conteúdo de parte da string */
    return;/* retorna caso não encontre o caractere de corte */
}

void preenche_data(char* data, char* line, int* range){
    char data_aux[10];
    sub_string(data_aux, line, *range+1, ',', range); /* obtem a string que representa o campo data */
    if(data_aux[0] == '\0'){
        for(int i = 1; i < 10; i++)
            data_aux[i] = '@'; /* preenche a string data_aux com \0@@@@@@@@@ se o primeiro char for um \0 */
    }
    strcpy(data, data_aux); /* associa a string data com o valor de data_aux (pode ser o valor da sub_string ou \0@@@@@@@@@) */
}

void escrever_data_null(FILE* file){
    char lixo = '\0';
    char lixo2 = '@';
    int i;
    fwrite(&lixo, sizeof(lixo), 1, file);
    for(i = 1; i < 10; i++)
        fwrite(&lixo2, sizeof(lixo2), 1, file);
}

void consultar_file_binario(char* nome_file){
    int i = 0, pos, ret_fun, cont = 0;
    char status;
    FILE* file = fopen(nome_file, "rb");
    if(!file){
        printf("Falha no processamento do arquivo.");
        return; /* caso o arquivo não exista ou ocorra outro erro, retorna para a main */
    }
    fread(&status, sizeof(status), 1, file);
    if(status == '0'){
        printf("Falha no processamento do arquivo.");
        return;
    }
    fseek(file, TAM_PAGE, SEEK_SET); /* pula para o inicio da segunda pagina de disco */

    Dados_PTR dado;
    dado = (Dados_PTR) malloc(sizeof(Dados));
    dado->nomeEscola = (char*) calloc(30, sizeof(char));
    dado->cidade = (char*)calloc(30, sizeof(char));

    while(!feof(file)){
        fread(&(dado->removido), sizeof(dado->removido), 1, file); /* lê o campo removido no arquivo binario */
        if(dado->removido == '*')
            cont++;
        else{
            fread(&(dado->encadeamento), sizeof(dado->encadeamento), 1, file); /* lê o campo encadeamento no arquivo binario */

            ret_fun = fread(&(dado->nroInscricao), sizeof(dado->nroInscricao), 1, file); /* lê o campo nroInscricao no arquivo binario */
            if(ret_fun == 0)   /* condicao de saida */
                break;
            printf("%d", dado->nroInscricao);

            fread(&(dado->nota), sizeof(dado->nota), 1, file); /* lê o campo nota no arquivo binario */
            if(dado->nota != -1)
                printf(" %.1lf", dado->nota); /* imprime apenas se nota for diferente de 0 */

            ler_string(file, dado->data, sizeof(dado->data)); /* lê o campo data no arquivo binario */
            if(strcmp(dado->data, "\0@@@@@@@@@") != 0)
                printf(" %s", dado->data); /* imprime apenas se data existir */

            fread(&(dado->indCid), sizeof(dado->indCid), 1, file); /* lê o campo indicador de tamanho (cidade) no arquivo binario */
            dado->indCid = dado->indCid - 2;
            if(dado->indCid > 0){ /* se o indicador de tamanho for maior que 0, significa que o campo cidade ou nomeEscola existe */
                fread(&(dado->tagCampo4), sizeof(dado->tagCampo4), 1, file); /* lê o campo tagCampo4 no arquivo binario */
                if(dado->tagCampo4 == '4'){ /* se tagCampo4 for igual a '4', o campo cidade cidade existe */
                    printf(" %d", dado->indCid);
                    ler_string(file, dado->cidade, dado->indCid); /* lê o campo cidade */
                    printf(" %s", dado->cidade);
                    limpa_string(dado->cidade, dado->indCid); /* preenche string com \0 */
                }
                else{
                    if(dado->tagCampo4 == '5'){ /* se o campo tagCampo4 for igual a '5', o campo cidade não existe, mas o campo nomeEscola sim */
                        printf(" %d", dado->indCid);
                        ler_string(file, dado->nomeEscola, dado->indCid); /* lê o campo nomeEscola */
                        printf(" %s", dado->nomeEscola);
                        limpa_string(dado->nomeEscola, dado->indCid); /* preenche string com \0 */
                    }
                }
            }

            fseek(file, 1, SEEK_CUR); /* pula o \0 */
            fread(&(dado->indEsc), sizeof(dado->indEsc), 1, file); /* lê o campo indicador de tamanho (nomeEscola) no arquivo binario */
            dado->indEsc = dado->indEsc - 2;
            if(dado->tagCampo4 != '5'){ /* significa que o campo cidade existe */
                if(dado->indEsc > 0){ /* se o indicador de tamanho for maior que 0, significa que o campo nomeEscola existe */
                    fread(&(dado->tagCampo5), sizeof(dado->tagCampo5), 1, file); /* lê o campo tagCampo5 no arquivo binario */
                    if(dado->tagCampo5 == '5'){ /* significa que o campo nomeEscola existe */
                        printf(" %d", dado->indEsc);
                        ler_string(file,dado->nomeEscola, dado->indEsc); /* lê e imprime o campo nomeEscola */
                        printf(" %s", dado->nomeEscola);
                    }
                }
            }
            printf("\n");
        }
        i++;
        fseek(file, (TAM_PAGE+i*80), SEEK_SET); /* pula para o começo de um novo registro */
    }


    fclose(file);
    //printf("%d reg lidos de %s\n",i,nome_file);
    pos = (TAM_PAGE+i*80); /* expressão que determina o numero de paginas de disco acessadas */
    if((pos % TAM_PAGE) == 0)
        printf("Número de páginas de disco acessadas: %d", (pos / TAM_PAGE));
    else
        printf("Número de páginas de disco acessadas: %d", (pos / TAM_PAGE)+1);
}

void consultar_dado(char* nome_file, char* nome_campo, char* valor){
    int i = 0, pos, ret_fun, convert_int, found = 0;
    double convert_double;
    char cid_aux[30], esc_aux[30], c = '\0', status;
    FILE* file = fopen(nome_file, "rb");
    if(!file){
        printf("Falha no processamento do arquivo.");
        return; /* caso o arquivo não exista ou ocorra outro erro, retorna para a main */
    }
    fread(&status, sizeof(status), 1, file);
    if(status == '0'){
        printf("Falha no processamento do arquivo.");
        return;
    }

    limpa_string(esc_aux, 30); /* preenche string com \0 */

    Dados_PTR dado;
    dado = (Dados_PTR) malloc(sizeof(Dados));

    while(!feof(file)){
        pos = TAM_PAGE + TAM_DAD*i; /* expressão para pular entre registros */
        fseek(file, pos, SEEK_SET); /* pular registros */
        fread(&(dado->removido), sizeof(dado->removido), 1, file); /* lê o campo removido */
        fread(&(dado->encadeamento), sizeof(dado->encadeamento), 1, file); /* lê o campo encadeamento */
        ret_fun = fread(&(dado->nroInscricao), sizeof(dado->nroInscricao), 1, file); /* lê o campo nroInscricao */
        if(ret_fun == 0){
            if(found == 0)
                printf("Registro inexistente.");   /* caso não tenha encontrado nenhum registro que atendesse os criterios */
            break;
        }
        if(strcmp(nome_campo, "nroInscricao") == 0){ /* se o campo digitado for nroInscricao */
            convert_int = atoi(valor); /* converte para inteiro o valor digitado */
            if(dado->nroInscricao == convert_int){
                found = 1; /* indica que foi encontrado algum registro com o valor digitado */

                printf("%d", dado->nroInscricao);

                fread(&(dado->nota), sizeof(dado->nota), 1, file); /* lê o campo nota */
                if(dado->nota != -1)
                    printf(" %.1lf", dado->nota);

                ler_string(file, dado->data, sizeof(dado->data)); /* lê o campo data */
                if(strcmp(dado->data, "\0@@@@@@@@@") != 0)
                    printf(" %s", dado->data);

                fread(&(dado->indCid), sizeof(dado->indCid), 1, file); /* lê o campo indicador de tamanho (cidade) */
                dado->indCid = dado->indCid - 2; /* devido ao \0 e a tag */
                if(dado->indCid > 0){
                    fread(&(dado->tagCampo4), sizeof(dado->tagCampo4), 1, file); /* lê o campo tagCampo4 */
                    if(dado->tagCampo4 == '4'){ /* se o campo tagCampo4 tiver valor '4', o campo cidade existe */
                        dado->cidade = (char*)malloc(sizeof(char)*dado->indCid);
                        printf(" %d", dado->indCid);
                        ler_string(file, dado->cidade, dado->indCid); /* lê o campo cidade */
                        printf(" %s", dado->cidade);
                    }
                    else{
                        if(dado->tagCampo4 == '5'){ /* indica que o campo cidade não existe, enquanto o campo nomeEscola existe */
                            dado->nomeEscola = (char*) malloc(sizeof(char)*dado->indCid);
                            printf(" %d", dado->indCid);
                            ler_string(file, dado->nomeEscola, dado->indCid); /* lê o campo nomeEscola */
                            printf(" %s", dado->nomeEscola);
                        }
                    }
                }
                fread(&(dado->indEsc), sizeof(dado->indEsc), 1, file); /* lê o campo indicador de tamanho (nomeEscola) */
                dado->indEsc = dado->indEsc - 2;
                if(dado->tagCampo4 != '5'){
                    if(dado->indEsc > 0){ /* indica que o campo nomeEscola existe */
                        fread(&(dado->tagCampo5), sizeof(dado->tagCampo5), 1, file); /* lê o campo tagCampo5 */
                        if(dado->tagCampo5 == '5'){
                            dado->nomeEscola = (char*)malloc(sizeof(char)*dado->indEsc);
                            printf(" %d", dado->indEsc);
                            ler_string(file, dado->nomeEscola, dado->indEsc); /* lê o campo nomeEscola */
                            printf(" %s", dado->nomeEscola);
                        }
                    }
                }
                printf("\n");
                break;
            }
            i++;
        }
        else{
            fread(&(dado->nota), sizeof(dado->nota), 1, file); /* lê o campo nota */
            if(strcmp(nome_campo, "nota") == 0){
                convert_double = atof(valor); /* converte o valor digitado para double e associa com a variavel convert_double */
                if(dado->nota == convert_double){
                    found = 1;  /* indica que foi encontrado algum registro com o valor digitado */
                    printf("%d", dado->nroInscricao);
                    printf(" %.1lf", dado->nota);

                    ler_string(file, dado->data, sizeof(dado->data)); /* lê o campo data */
                    if(strcmp(dado->data, "\0@@@@@@@@@") != 0)
                        printf(" %s", dado->data);

                    fread(&(dado->indCid), sizeof(dado->indCid), 1, file); /* lê o campo indicador de tamanho (cidade) */
                    dado->indCid = dado->indCid - 2;
                    if(dado->indCid > 0){
                        fread(&(dado->tagCampo4), sizeof(dado->tagCampo4), 1, file); /* lê o campo tagCampo4 */
                        if(dado->tagCampo4 == '4'){ /* se o campo tagCampo4 tiver valor '4', o campo cidade existe */
                            dado->cidade = (char*)malloc(sizeof(char)*dado->indCid);
                            printf(" %d", dado->indCid);
                            ler_string(file, dado->cidade, dado->indCid); /* lê o campo cidade */
                            printf(" %s", dado->cidade);
                        }
                        else{
                            if(dado->tagCampo4 == '5'){ /* indica que o campo cidade não existe, enquanto o campo nomeEscola existe */
                                dado->nomeEscola = (char*) malloc(sizeof(char)*dado->indCid);
                                printf(" %d", dado->indCid);
                                ler_string(file, dado->nomeEscola, dado->indCid); /* lê o campo nomeEscola */
                                printf(" %s", dado->nomeEscola);
                            }
                        }
                    }
                    fseek(file, 1, SEEK_CUR); /* pula o \0 */
                    fread(&(dado->indEsc), sizeof(dado->indEsc), 1, file); /* lê o campo indicador de tamanho (nomeEscola) */
                    dado->indEsc = dado->indEsc - 2;
                    if(dado->tagCampo4 != '5'){
                        if(dado->indEsc > 0){ /* indica que o campo nomeEscola existe */
                            fread(&(dado->tagCampo5), sizeof(dado->tagCampo5), 1, file); /* lê o campo tagCampo5 */
                            if(dado->tagCampo5 == '5'){
                                dado->nomeEscola = (char*)malloc(sizeof(char)*dado->indEsc);
                                printf(" %d", dado->indEsc);
                                ler_string(file, dado->nomeEscola, dado->indEsc); /* lê o campo nomeEscola */
                                printf(" %s", dado->nomeEscola);
                            }
                        }
                    }
                    printf("\n");
                }
            }
            else{
                ler_string(file, dado->data, sizeof(dado->data)); /* lê o campo data */
                if(strcmp(nome_campo, "data") == 0){
                    if(strcmp(dado->data, valor) == 0){
                        found = 1; /* indica que foi encontrado algum registro com o valor digitado */
                        printf("%d", dado->nroInscricao);
                        if(dado->nota != -1)
                            printf(" %.1lf", dado->nota);
                        printf(" %s", dado->data);
                        fread(&(dado->indCid), sizeof(dado->indCid), 1, file); /* lê o campo indicador de tamanho (cidade) */
                        dado->indCid = dado->indCid - 2;
                        if(dado->indCid > 0){
                            fread(&(dado->tagCampo4), sizeof(dado->tagCampo4), 1, file); /* lê o campo tagCampo4 */
                            if(dado->tagCampo4 == '4'){ /* se o campo tagCampo4 tiver valor '4', o campo cidade existe */
                                dado->cidade = (char*)malloc(sizeof(char)*dado->indCid);
                                printf(" %d", dado->indCid);
                                ler_string(file, dado->cidade, dado->indCid); /* lê o campo cidade */
                                printf(" %s", dado->cidade);
                            }
                            else{
                                if(dado->tagCampo4 == '5'){ /* indica que o campo cidade não existe, enquanto o campo nomeEscola existe */
                                    dado->nomeEscola = (char*) malloc(sizeof(char)*dado->indCid);
                                    printf(" %d", dado->indCid);
                                    ler_string(file, dado->nomeEscola, dado->indCid); /* lê o campo nomeEscola */
                                    printf(" %s", dado->nomeEscola);
                                }
                            }
                        }
                        fseek(file, 1, SEEK_CUR); /* pula o \0 */
                        fread(&(dado->indEsc), sizeof(dado->indEsc), 1, file); /* lê o campo indicador de tamanho (nomeEscola) */
                        dado->indEsc = dado->indEsc - 2;
                        if(dado->tagCampo4 != '5'){
                            if(dado->indEsc > 0){ /* indica que o campo nomeEscola existe */
                                fread(&(dado->tagCampo5), sizeof(dado->tagCampo5), 1, file); /* lê o campo tagCampo5 */
                                if(dado->tagCampo5 == '5'){
                                    dado->nomeEscola = (char*)malloc(sizeof(char)*dado->indEsc);
                                    printf(" %d", dado->indEsc);
                                    ler_string(file, dado->nomeEscola, dado->indEsc); /* lê o campo nomeEscola */
                                    printf(" %s", dado->nomeEscola);
                                }
                            }
                        }
                        printf("\n");
                    }
                }
                else{
                    fread(&(dado->indCid), sizeof(dado->indCid), 1, file); /* lê o campo indicador de tamanho (cidade) */
                    dado->indCid = dado->indCid - 2;
                    if(dado->indCid > 0){
                        fread(&(dado->tagCampo4), sizeof(dado->tagCampo4), 1, file); /* lê o campo tagCampo4 */
                        if(dado->tagCampo4 == '4'){ /* se o campo tagCampo4 tiver valor '4', o campo cidade existe */
                            ler_string(file, cid_aux, dado->indCid); /* lê o campo cidade */
                        }
                        else{
                            if(dado->tagCampo4 == '5'){
                                ler_string(file, esc_aux, dado->indCid); /* lê o campo nomeEscola */
                            }
                        }
                    }
                    if(strcmp(nome_campo, "cidade") == 0){
                        if(dado->tagCampo4 == '4'){ /* indica que o campo cidade existe */
                            if(strcmp(cid_aux, valor) == 0){
                                found = 1; /* indica que foi encontrado algum registro com o valor digitado */
                                printf("%d", dado->nroInscricao);
                                if(dado->nota != -1)
                                    printf(" %.1lf", dado->nota);
                                if(strcmp(dado->data, "\0@@@@@@@@@") != 0)
                                    printf(" %s", dado->data);
                                printf(" %d", dado->indCid);
                                printf(" %s", cid_aux);
                                fseek(file, 1, SEEK_CUR); /* pula o \0 */
                                fread(&(dado->indEsc), sizeof(dado->indEsc), 1, file); /* lê o campo indicador de tamanho (nomeEscola) */
                                dado->indEsc = dado->indEsc - 2;
                                fread(&(dado->tagCampo5), sizeof(dado->tagCampo5), 1, file); /* lê o campo tagCampo5 */
                                if(dado->tagCampo5 == '5'){ /* indica que o campo nomeEscola também existe */
                                    printf(" %d ", dado->indEsc);
                                    ler_nomeEscola(c, file, esc_aux); /* imprime o campo nomeEscola */
                                    printf("%s", esc_aux);
                                }
                                printf("\n");
                            }
                        }
                    }
                    else{
                        if(strcmp(nome_campo, "nomeEscola") == 0){
                            if(dado->tagCampo4 == '5'){ /* indica que o campo cidade não existe, enquanto o campo nomeEscola existe */
                                if(compara_string(esc_aux, valor, strlen(valor))){ /* retorna 1 se as strings forem iguais */
                                    found = 1; /* indica que foi encontrado algum registro com o valor digitado */
                                    printf("%d", dado->nroInscricao);
                                    if(dado->nota != -1)
                                        printf(" %.1lf", dado->nota);
                                    if(strcmp(dado->data, "\0@@@@@@@@@") != 0)
                                        printf(" %s", dado->data);
                                    printf(" %d", dado->indEsc);
                                    printf(" %s\n", esc_aux);
                                }
                            }
                            else{
                                fseek(file, 1, SEEK_CUR); /* pula o \0 */
                                fread(&(dado->indEsc), sizeof(dado->indEsc), 1, file); /* lê o campo indicador de tamanho (nomeEscola) */
                                dado->indEsc = dado->indEsc - 2;
                                fread(&(dado->tagCampo5), sizeof(dado->tagCampo5), 1, file); /* lê o campo tagCampo5 */
                                if(dado->tagCampo5 == '5'){
                                    ler_nomeEscola(c, file, esc_aux);
                                    if(compara_string(esc_aux, valor, strlen(valor))){ /* retorna 1 se as strings forem iguais */
                                        found = 1; /* indica que foi encontrado algum registro com o valor digitado */
                                        printf("%d", dado->nroInscricao);
                                        if(dado->nota != -1)
                                            printf(" %.1lf", dado->nota);
                                        if(strcmp(dado->data, "\0@@@@@@@@@") != 0)
                                            printf(" %s", dado->data);
                                        printf(" %d", dado->indCid);
                                        printf(" %s", cid_aux);
                                        printf(" %d", dado->indEsc);
                                        printf(" %s\n", esc_aux);
                                    }
                                }
                            }
                        }
                        else{
                            printf("Falha no processamento do arquivo."); /* foi digitado um campo que não existe */
                            break;
                        }
                    }
                }
            }
        i++;
        }
    }
    fclose(file);
    if(found == 1){
        if(strcmp(nome_campo, "nroInscricao") == 0){
            if((pos%TAM_PAGE) == 0)
                printf("Número de páginas de disco acessadas: %d", (pos/TAM_PAGE)+1); /* caso especial: campo nroInscrição, pois não precisa percorrer todos os registros */
            else
                printf("Número de páginas de disco acessadas: %d", (pos/TAM_PAGE));
        }
        else{
            if((pos%TAM_PAGE) == 0)
                printf("Número de páginas de disco acessadas: %d", (pos/TAM_PAGE));
            else
                printf("Número de páginas de disco acessadas: %d", (pos/TAM_PAGE)+1); /* quando a divisão não dá um numero inteiro, é preciso somar 1 */
        }
    }
}

void consultar_rrn(char* nome_file, int rrn){
    int pos, found = 0, num_page = 0;
    char status;
    FILE* file = fopen(nome_file, "rb");
    if(!file){
        printf("Falha no processamento do arquivo.");
        return; /* caso o arquivo não exista ou ocorra outro erro, retorna para a main */
    }
    fread(&status, sizeof(status), 1, file);
    if(status == '0'){
        printf("Falha no processamento do arquivo.");
        return;
    }
    num_page++; /* variavel que determina o numero de paginas de disco acessadas */
    pos = TAM_PAGE + TAM_DAD*rrn; /* expressão para pular até o registro que deve ser acessado */
    fseek(file, pos, SEEK_SET); /* pula para o registro procurado */
    Dados_PTR dado;
    dado = (Dados_PTR) malloc(sizeof(Dados));

    fread(&(dado->removido), sizeof(dado->removido), 1, file); /* lê o campo removido */
    if(dado->removido != '-'){
        printf("Registro inexistente."); /* se o registro não existe, o campo removido terá um valor diferente */
        return;
    }
    fread(&(dado->encadeamento), sizeof(dado->encadeamento), 1, file); /* lê o campo encadeamento */

    fread(&(dado->nroInscricao), sizeof(dado->nroInscricao), 1, file); /* lê o campo nroInscricao */
    printf("%d", dado->nroInscricao);

    fread(&(dado->nota), sizeof(dado->nota), 1, file); /* lê o campo nota */
    if(dado->nota != -1)
        printf(" %.1lf", dado->nota);

    ler_string(file, dado->data, sizeof(dado->data)); /* lê o campo data */
    if(strcmp(dado->data, "\0@@@@@@@@@") != 0)
        printf(" %s", dado->data);

    fread(&(dado->indCid), sizeof(dado->indCid), 1, file); /* lê o campo indicador de tamanho (cidade) */
    dado->indCid = dado->indCid - 2;
    if(dado->indCid > 0){
        fread(&(dado->tagCampo4), sizeof(dado->tagCampo4), 1, file); /* lê o campo tagCampo4 */
        if(dado->tagCampo4 == '4'){
            dado->cidade = (char*)malloc(sizeof(char)*dado->indCid);
            printf(" %d", dado->indCid);
            ler_string(file, dado->cidade, dado->indCid); /* lê o campo cidade */
            printf(" %s", dado->cidade);
        }
        else{
            if(dado->tagCampo4 == '5'){
                dado->nomeEscola = (char*) malloc(sizeof(char)*dado->indCid);
                printf(" %d", dado->indCid);
                ler_string(file, dado->nomeEscola, dado->indCid); /* lê o campo nomeEscola */
                printf(" %s", dado->nomeEscola);
            }
        }
    }
    fseek(file, 1, SEEK_CUR); /* pula o \0 */
    fread(&(dado->indEsc), sizeof(dado->indEsc), 1, file); /* lê o campo indicador de tamanho (nomeEscola) */
    dado->indEsc = dado->indEsc - 2;
    if(dado->tagCampo4 != '5'){
        if(dado->indEsc > 0){
            fread(&(dado->tagCampo5), sizeof(dado->tagCampo5), 1, file); /* lê o campo tagCampo5 */
            if(dado->tagCampo5 == '5'){
                dado->nomeEscola = (char*)malloc(sizeof(char)*dado->indEsc);
                printf(" %d", dado->indEsc);
                ler_string(file, dado->nomeEscola, dado->indEsc); /* lê o campo nomeEscola */
                printf(" %s", dado->nomeEscola);
            }
        }
    }
    found = 1; /* indica que encontrou o registro */
    num_page++;
    fclose(file);
    if(found == 1)
        printf("\nNúmero de páginas de disco acessadas: %d", num_page);
}

int remover_registro(char *nome_file, char *nome_campo, char *valor, char *nomeEscola, int *rrn, int ultimo){
    int i = 0, pos, ret_fun, convert_int, found = 0, int_aux = 0, cont, aux, aux2, rep = 0;
    double convert_double;
    char cid_aux[30], esc_aux[30], str_aux[30], c = '\0', lixo = '@', aux_c;
    FILE* file = fopen(nome_file, "rb+");
    if(!file){
        if(ultimo)
            printf("Falha no processamento do arquivo.");
        return -1; /* caso o arquivo não exista ou ocorra outro erro, retorna para a main */
    }

    Dados_PTR dado;
    Header head;
    dado = (Dados_PTR) malloc(sizeof(Dados));
    head = (Header) malloc(sizeof(Cabecalho));

    fread(&(head->status), sizeof(head->status), 1, file); /* lê o status */
    if(head->status == '0'){
        if(ultimo)
            printf("Falha no processamento do arquivo."); /* se o status for igual a 0, não é possivel ler o resto do arquivo */
        return -1;
    }
    fread(&(head->topoPilha),sizeof(head->topoPilha), 1, file); /* lê o topo da pilha */

    while(!feof(file)){
        pos = TAM_PAGE + TAM_DAD*i; /* expressão para pular entre registros */
        fseek(file, pos, SEEK_SET); /* pular registros */
        fread(&(dado->removido), sizeof(dado->removido), 1, file); /* lê o campo removido */
        fread(&(dado->encadeamento), sizeof(dado->encadeamento), 1, file); /* lê o campo encadeamento */
        ret_fun = fread(&(dado->nroInscricao), sizeof(dado->nroInscricao), 1, file); /* lê o campo nroInscricao */

        if(ret_fun == 0)
            break;
        if(strcmp(nome_campo, "nroInscricao") == 0){ /* se o campo digitado for nroInscricao */
            convert_int = atoi(valor); /* converte para inteiro o valor digitado */
            if(dado->nroInscricao == convert_int){
                found = 1; /* indica que foi encontrado algum registro com o valor digitado */
                rrn[rep] = i;
                rep++;
            }
        }
        else{
            fread(&(dado->nota), sizeof(dado->nota), 1, file); /* lê o campo nota */
            if(strcmp(nome_campo, "nota") == 0){
                convert_double = atof(valor); /* converte o valor digitado para double e associa com a variavel convert_double */
                if(dado->nota == convert_double){
                    found = 2;  /* indica que foi encontrado algum registro com o valor digitado */
                    rrn[rep] = i;
                    rep++;
                }
            }
            else{
                if(valor[0] == '"')
                    sub_string(str_aux, valor, 1, '"', &int_aux); /* quebra a linha de 1 até as primeiras aspas encontradas, resultando na string str_aux */
                else
                    strcpy(str_aux, valor);
                ler_string(file, dado->data, sizeof(dado->data)); /* lê o campo data */
                if(strcmp(nome_campo, "data") == 0){
                    if(strcmp(dado->data, str_aux) == 0){
                        found = 2; /* indica que foi encontrado algum registro com o valor digitado */
                        rrn[rep] = i;
                        rep++;
                    }
                }
                else{
                    fread(&(dado->indCid), sizeof(dado->indCid), 1, file); /* lê o campo indicador de tamanho (cidade) */
                    dado->indCid = dado->indCid - 2;
                    if(dado->indCid > 0){
                        fread(&(dado->tagCampo4), sizeof(dado->tagCampo4), 1, file); /* lê o campo tagCampo4 */
                        if(dado->tagCampo4 == '4') /* se o campo tagCampo4 tiver valor '4', o campo cidade existe */
                            ler_string(file, cid_aux, dado->indCid); /* lê o campo cidade */
                        else{
                            if(dado->tagCampo4 == '5')
                                ler_string(file, esc_aux, dado->indCid); /* lê o campo nomeEscola */
                        }
                    }
                    if(strcmp(nome_campo, "cidade") == 0){
                        if(dado->tagCampo4 == '4'){ /* indica que o campo cidade existe */
                            if(strcmp(cid_aux, str_aux) == 0){
                                found = 2; /* indica que foi encontrado algum registro com o valor digitado */
                                rrn[rep] = i;
                                rep++;
                            }
                        }
                    }
                    else{
                        if(strcmp(nome_campo, "nomeEscola") == 0){
                            if(dado->tagCampo4 == '5'){ /* indica que o campo cidade não existe, enquanto o campo nomeEscola existe */
                                if(compara_string(esc_aux, str_aux, strlen(str_aux))){ /* retorna 1 se as strings forem iguais */
                                    found = 2; /* indica que foi encontrado algum registro com o valor digitado */
                                    rrn[rep] = i;
                                    rep++;
                                }
                            }
                            else{
                                fseek(file, 1, SEEK_CUR); /* pula o \0 */
                                fread(&(dado->indEsc), sizeof(dado->indEsc), 1, file); /* lê o campo indicador de tamanho (nomeEscola) */
                                dado->indEsc = dado->indEsc - 2; /* desconsidera a tag e o \0 */
                                fread(&(dado->tagCampo5), sizeof(dado->tagCampo5), 1, file); /* lê o campo tagCampo5 */
                                if(dado->tagCampo5 == '5'){
                                    ler_nomeEscola(c, file, esc_aux); /* lê o campo nomeEscola */
                                    if(compara_string(esc_aux, str_aux, strlen(str_aux))){ /* retorna 1 se as strings forem iguais */
                                        found = 2; /* indica que foi encontrado algum registro com o valor digitado */
                                        rrn[rep] = i;
                                        rep++;
                                    }
                                }
                            }
                        }
                        else
                            return -1; /* não encontrou nenhum dos campos */
                    }
                }
            }
        }
        if(found != 0 && found != 3){ /* found é 0 quando não encontra nenhum valor e found é 3 quando, em alguma iteração anterior, found era 2 */
            dado->removido = '*'; /* altera o removido de '-' para '*' */
            dado->encadeamento = head->topoPilha; /* o encadeamento do registro possui o topo da pilha */
            head->topoPilha = i; /* o topo da pilha possui o rrn do registro */

            /* atualização do cabeçalho */
            head->status = '0'; /* associa o status '0' enquanto não termina as modificacoes */
            fseek(file, 0, SEEK_SET); /* volta para o inicio do arquivo */
            fwrite(&(head->status), sizeof(head->status), 1, file); /* escreve o novo status */
            fwrite(&(head->topoPilha), sizeof(head->topoPilha), 1, file); /* escreve o novo topoPilha */

            aux = 27; /* 27 representa a soma dos tamanhos dos campos de tamanho fixo */
            fseek(file, pos+aux, SEEK_SET); /* pular registros */
            fread(&aux2, sizeof(aux2), 1, file); /* lê o primeiro indicador de tamanho */
            if(aux2 > 0){
                fread(&aux_c, sizeof(aux_c), 1, file); /* lê a primeira tag */
                if(aux_c == '4'){ /* primeira tag é a cidade */
                    aux += sizeof(aux2)+aux2; /* associa o tamanho do indicador e o tamanho da string + tag */
                    fseek(file, aux2-1, SEEK_CUR); /* passa pela string */
                    fread(&aux2, sizeof(aux2), 1, file); /* lê o segundo indicador de tamanho */
                    fread(&aux_c, sizeof(aux_c), 1, file); /* lê a segunda tag */
                    if(aux_c == '5'){ /* segunda tag é o nomeEscola */
                        aux += sizeof(aux2)+aux2; /* associa o tamanho do indicador e o tamanho da string + tag */
                        ler_string(file, nomeEscola, aux2-2);
                    }
                }
                else{
                    if(aux_c == '5'){ /* primeira tag é o nomeEscola */
                        aux += sizeof(aux2)+aux2; /* associa o tamanho do indicador e o tamanho da string + tag */
                        ler_string(file, nomeEscola, aux2-2);
                    }
                }
            }
            fseek(file, pos, SEEK_SET); /* pular registros */
            fwrite(&(dado->removido), sizeof(dado->removido), 1, file); /* escreve o novo removido no registro */
            fwrite(&(dado->encadeamento), sizeof(dado->encadeamento), 1, file); /* escreve o novo encadeamento no registro */

            cont = sizeof(dado->removido)+sizeof(dado->encadeamento);
            while(cont < aux){
                fwrite(&lixo, sizeof(lixo), 1, file); /* escreve @ no registro */
                cont++;
            }
            fseek(file, 0, SEEK_SET); /* volta para o inicio do arquivo */
            head->status = '1'; /* associa o status '1' para marcar o fim das modificacoes */
            fwrite(&(head->status), sizeof(head->status), 1, file); /* escreve o novo status */

            if(found == 1) /* se found for 1, estamos tratando do nroInscricao, que é unico e, portanto, nao precisa checar os outros registros */
                break;
            else /* se found for 2, é qualquer um dos outros registros */
                found = 3;
        }
        i++;
    }
   // *rrn = (int**)malloc(rep*sizeof(int));
    if(ultimo == 1)
        binarioNaTela1(file); /* quando for o ultimo registro, printa o binario */
    fclose(file);
    return rep;
}

void insercao_adicional(char *nome_file, int nroInscricao, char *campos, int ultimo){
    int aux, cont = 0, aux2 = 0;
    char lixo = '@', fim = '\0';
    char data[10], nota[10];
    char cidade[30], nomeEscola[30];
    double nota_aux;
    FILE* file = fopen(nome_file, "rb+");
    if(!file){
        printf("Falha no processamento do arquivo.");
        return; /* caso o arquivo não exista ou ocorra outro erro, retorna para a main */
    }
    Dados_PTR dado;
    Header head;
    dado = (Dados_PTR) malloc(sizeof(Dados));
    head = (Header) malloc(sizeof(Cabecalho));

    sub_string(nota, campos, 0, ' ', &aux2); /* quebra a linha de 0 até o primeiro espaço encontrado, resultando na string nota */
    if(campos[aux2+1] == 'N'){ /* se comeca com 'N', temos que data é "NULO" */
        strcpy(data, "NULO");
        aux2 += 4;
    }
    else
        sub_string(data, campos, aux2+2, '"', &aux2); /* quebra a linha de 1 até o primeiro espaço encontrado, resultando na string data */

    if(campos[aux2+2] == 'N'){ /* se comeca com 'N', temos que cidade é "NULO" */
        strcpy(cidade, "NULO");
        aux2 += 5;
    }
    else
        sub_string(cidade, campos, aux2+3, '"', &aux2); /* quebra a linha de aux2+3 até as primeiras aspas encontradas, resultando na string cidade */

    if(campos[aux2+2] == 'N') /* se comeca com 'N', temos que nomeEscola é "NULO" */
        strcpy(nomeEscola, "NULO");
    else
        sub_string(nomeEscola, campos, aux2+3, '"', &aux2); /* quebra a linha de aux2+3 até as primeiras aspas encontradas, resultando na string nomeEscola */
    //printf("%s %s %s %s\n", nota, data, cidade, nomeEscola);
    fread(&(head->status), sizeof(head->status), 1, file); /* lê o status */
    if(head->status == '0'){
        printf("Falha no processamento do arquivo.");
        return; /* se o status for igual a 0, não é possivel ler o resto do arquivo */
    }
    fread(&(head->topoPilha),sizeof(head->topoPilha), 1, file); /* lê o topoPilha */

    if(head->topoPilha == -1){
        /* atualização do cabeçalho */
        head->status = '0'; /* associa o '0' com o status */
        fseek(file, 0, SEEK_SET); /* volta para o inicio do arquivo */
        fwrite(&(head->status), sizeof(head->status), 1, file); /* escreve o novo status */
        fwrite(&(head->topoPilha), sizeof(head->topoPilha), 1, file); /* escreve o novo topoPilha */

        fseek(file, 0, SEEK_END); /* vai para depois do ultimo registro */
        dado->removido = '-'; /* associa o '-' com o novo dado->removido */
        dado->encadeamento = -1; /* associa o -1 com o encadeamento do registro */

        fwrite(&(dado->removido), sizeof(dado->removido), 1, file); /* escreve o novo removido */
        cont += sizeof(dado->removido); /* incrementa o contador com o tamanho do removido */

        fwrite(&(dado->encadeamento), sizeof(dado->encadeamento), 1, file); /* escreve o novo encadeamento */
        cont += sizeof(dado->encadeamento); /* incrementa o contador com o tamanho do encadeamento */

        fwrite(&nroInscricao, sizeof(nroInscricao), 1, file); /* escreve o novo nroInscricao */
        cont += sizeof(nroInscricao); /* incrementa o contador com o tamanho do nroInscricao */

        if(strcmp(nota, "NULO") != 0)
            nota_aux = atof(nota); /* converte string para double */
        else
            nota_aux = -1; /* tratamento da nota quando for nula */
        fwrite(&nota_aux, sizeof(nota_aux), 1, file); /* escreve a nova nota */
        cont += sizeof(nota_aux); /* incrementa o contador com o tamanho da nota */

        if(strcmp(data, "NULO") != 0)
            escrever_string(file, data, strlen(data)); /* escreve a nova data */
        else
            escrever_data_null(file); /* faz o tratamento da data nula e escreve no arquivo */
        cont += 10; /* incrementa o contador com o tamanho da data */

        if(strcmp(cidade, "NULO") != 0){
            dado->indCid = strlen(cidade) + 2; /* considerando a tag e o \0 */
            dado->tagCampo4 = '4'; /* a tagCampo4 é '4' */
            fwrite(&(dado->indCid), sizeof(dado->indCid), 1, file); /* escreve o indicador de tamanho da cidade */
            cont += sizeof(dado->indCid); /* incrementa o contador com o tamanho do indicador de tamanho da cidade */
            fwrite(&(dado->tagCampo4), sizeof(dado->tagCampo4), 1, file); /* escreve a tagCampo4 */
            cont += sizeof(dado->tagCampo4); /* incrementa o contador com o tamanho da tagCampo4 */
            escrever_string(file, cidade, dado->indCid-2); /* escreve a cidade */
            cont += dado->indCid - 2; /* incrementa o contador com o tamanho da cidade, sem a tag e o \0 */
            fwrite(&fim, sizeof(char), 1, file); /* escreve um \0 */
        }
        else
            dado->indCid = 0;

        if(strcmp(nomeEscola, "NULO") != 0){
            dado->indEsc = strlen(nomeEscola) + 2; /* considerando a tag e o \0 */
            dado->tagCampo5 = '5'; /* a tagCampo4 é '5' */
            fwrite(&(dado->indEsc), sizeof(dado->indEsc), 1, file); /* escreve o indicador de tamanho do nomeEscola */
            cont += sizeof(dado->indEsc); /* incrementa o contador com o tamanho do indicador de tamanho do nomeEscola */
            fwrite(&(dado->tagCampo5), sizeof(dado->tagCampo5), 1, file); /* escreve a tagCampo5 */
            cont += sizeof(dado->tagCampo5); /* incrementa o contador com o tamanho da tagCampo5 */
            escrever_string(file, nomeEscola, dado->indEsc-2); /* incrementa o contador com o tamanho do nomeEscola, sem a tag e o \0 */
            cont += dado->indEsc - 2; /* incrementa o contador com o tamanho do nomeEscola, sem a tag e o \0 */
            fwrite(&fim, sizeof(char), 1, file); /* escreve um \0 */
        }
        else
            dado->indEsc = 0;

        while(cont < 78){
            fwrite(&lixo, sizeof(lixo), 1, file); /* escreve @ no registro */
            cont++;
        }
        if(dado->indCid <= 0 || dado->indEsc <= 0){ /* caso um dos campos variaveis seja nulo, é necessário inserir mais um @ */
            fwrite(&lixo, sizeof(lixo), 1, file);
            if(dado->indCid <= 0 && dado->indEsc <= 0){ /* caso os dois campos variaveis sejam nulos, é necessário inserir um @ extra */
                fwrite(&lixo, sizeof(lixo), 1, file);
            }
        }
        fseek(file, 0, SEEK_SET); /* volta para o inicio do arquivo */
        head->status = '1'; /* associa o status com um '1' */
        fwrite(&(head->status), sizeof(head->status), 1, file); /* escreve o status */
    }
    else{
        aux = TAM_PAGE + head->topoPilha*TAM_DAD; /* expressao para ir para o registro procurado */
        fseek(file, aux, SEEK_SET); /* pula até o registro procurado */

        fread(&(dado->removido), sizeof(dado->removido), 1, file); /* lê o campo removido */
        if(dado->removido == '*'){ /* se removido for '*', é possivel realizar a insercao */
            fread(&(dado->encadeamento), sizeof(dado->encadeamento), 1, file); /* lê o campo encadeamento */
            aux = head->topoPilha; /* associa aux com o topoPilha */
            head->topoPilha = dado->encadeamento; /* topoPilha é o encadeamento do registro atual */

            /* atualização do cabeçalho */
            head->status = '0'; /* associa o '0' com o status */
            fseek(file, 0, SEEK_SET); /* volta para o inicio do arquivo */
            fwrite(&(head->status), sizeof(head->status), 1, file); /* escreve o novo status */
            fwrite(&(head->topoPilha), sizeof(head->topoPilha), 1, file); /* escreve o novo topoPilha */

            dado->removido = '-'; /* associa o '-' com o novo dado->removido */
            dado->encadeamento = -1; /* associa o -1 com o encadeamento do registro */
            fseek(file, (TAM_PAGE+aux*TAM_DAD), SEEK_SET); /* volta para o inicio do registro a ser inserido */

            fwrite(&(dado->removido), sizeof(dado->removido), 1, file); /* escreve o novo removido */
            cont += sizeof(dado->removido); /* incrementa o contador com o tamanho do removido */

            fwrite(&(dado->encadeamento), sizeof(dado->encadeamento), 1, file); /* escreve o novo encadeamento */
            cont += sizeof(dado->encadeamento); /* incrementa o contador com o tamanho do encadeamento */

            fwrite(&nroInscricao, sizeof(nroInscricao), 1, file); /* escreve o novo nroInscricao */
            cont += sizeof(nroInscricao); /* incrementa o contador com o tamanho do nroInscricao */

            if(strcmp(nota, "NULO") != 0)
                nota_aux = atof(nota);
            else
                nota_aux = -1;
            fwrite(&nota_aux, sizeof(nota_aux), 1, file); /* escreve a nova nota */
            cont += sizeof(nota_aux); /* incrementa o contador com o tamanho da nota */

            if(strcmp(data, "NULO") != 0)
                escrever_string(file, data, strlen(data)); /* escreve a nova data */
            else
                escrever_data_null(file); /* faz o tratamento da data nula e escreve no arquivo */
            cont += 10; /* incrementa o contador com o tamanho da data */

            if(strcmp(cidade, "NULO") != 0){
                dado->indCid = strlen(cidade) + 2; /* considerando a tag e o \0 */
                dado->tagCampo4 = '4'; /* a tagCampo4 é '4' */
                fwrite(&(dado->indCid), sizeof(dado->indCid), 1, file); /* escreve o indicador de tamanho da cidade */
                cont += sizeof(dado->indCid); /* incrementa o contador com o tamanho do indicador de tamanho da cidade */
                fwrite(&(dado->tagCampo4), sizeof(dado->tagCampo4), 1, file); /* escreve a tagCampo4 */
                cont += sizeof(dado->tagCampo4); /* incrementa o contador com o tamanho da tagCampo4 */
                escrever_string(file, cidade, dado->indCid-2); /* escreve a cidade */
                cont += dado->indCid - 2; /* incrementa o contador com o tamanho da cidade, sem a tag e o \0 */
                fwrite(&fim, sizeof(char), 1, file); /* escreve um \0 */
            }
            if(strcmp(nomeEscola, "NULO") != 0){
                dado->indEsc = strlen(nomeEscola) + 2; /* considerando a tag e o \0 */
                dado->tagCampo5 = '5'; /* a tagCampo4 é '5' */
                fwrite(&(dado->indEsc), sizeof(dado->indEsc), 1, file); /* escreve o indicador de tamanho do nomeEscola */
                cont += sizeof(dado->indEsc); /* incrementa o contador com o tamanho do indicador de tamanho do nomeEscola */
                fwrite(&(dado->tagCampo5), sizeof(dado->tagCampo5), 1, file); /* escreve a tagCampo5 */
                cont += sizeof(dado->tagCampo5); /* incrementa o contador com o tamanho da tagCampo5 */
                escrever_string(file, nomeEscola, dado->indEsc-2); /* incrementa o contador com o tamanho do nomeEscola, sem a tag e o \0 */
                cont += dado->indEsc - 2; /* incrementa o contador com o tamanho do nomeEscola, sem a tag e o \0 */
                fwrite(&fim, sizeof(char), 1, file); /* escreve um \0 */
            }
            while(cont < 78){
                fwrite(&lixo, sizeof(lixo), 1, file); /* escreve @ no registro */
                cont++;
            }
            if(dado->indCid <= 0 || dado->indEsc <= 0){ /* caso um dos campos variaveis seja nulo, é necessário inserir mais um @ */
                fwrite(&lixo, sizeof(lixo), 1, file);
                if(dado->indCid <= 0 && dado->indEsc <= 0) /* caso os dois campos variaveis sejam nulos, é necessário inserir um @ extra */
                    fwrite(&lixo, sizeof(lixo), 1, file);
            }
            fseek(file, 0, SEEK_SET); /* volta para o inicio do arquivo */
            head->status = '1'; /* associa o status com um '1' */
            fwrite(&(head->status), sizeof(head->status), 1, file); /* escreve o status */
        }
    }

    if(ultimo == 1)
        binarioNaTela1(file); /* quando for o ultimo registro, printa o binario */
    fclose(file);
}

void atualizar_registro(char *nome_file, int rrn, char *nome_campo, char *valor, int ultimo){
    int pos = TAM_PAGE + rrn*TAM_DAD;
    int ind, ret, int_aux;
    char tag_aux, fim = '\0';
    char str_aux[30];
    FILE* file = fopen(nome_file, "rb+");
    if(!file){
        printf("Falha no processamento do arquivo.");
        return; /* caso o arquivo não exista ou ocorra outro erro, retorna para a main */
    }

    Dados_PTR dado;
    Header head;
    dado = (Dados_PTR) malloc(sizeof(Dados));
    head = (Header) malloc(sizeof(Cabecalho));

    fread(&(head->status), sizeof(head->status), 1, file); /* lê o status */
    if(head->status == '0'){
        printf("Falha no processamento do arquivo.");
        return; /* se o status for igual a 0, não é possivel ler o resto do arquivo */
    }
    fseek(file, pos, SEEK_SET); /* volta para o inicio do registro que será atualizado */
    fread(&(dado->removido), sizeof(dado->removido), 1, file); /* lê o campo removido */
    if(dado->removido != '-'){ /* não é possivel atualizar um campo removido */
        if(ultimo)
            binarioNaTela1(file); /* quando for o ultimo registro, printa o binario */
        return;
    }
    fseek(file, sizeof(dado->encadeamento), SEEK_CUR); /* pula o encadeamento */
    if(strcmp(nome_campo, "nroInscricao") == 0){
        dado->nroInscricao = atoi(valor); /* se o campo a ser atualizado for o nroInscricao, converte a string para int */
        fwrite(&(dado->nroInscricao), sizeof(dado->nroInscricao), 1, file); /* escreve o novo nroInscricao */
    }
    else{
        fseek(file, sizeof(dado->nroInscricao), SEEK_CUR); /* pula o nroInscricao */
        if(strcmp(nome_campo, "nota") == 0){
            dado->nota = atof(valor); /* se o campo a ser atualizado for a nota, converte a string para double */
            fwrite(&(dado->nota), sizeof(dado->nota), 1, file); /* escreve a nova nota */
        }
        else{
            fseek(file, sizeof(dado->nota), SEEK_CUR); /* pula a nota */
            if(valor[0] == '"')
                sub_string(str_aux, valor, 1, '"', &int_aux); /* quebra a linha de 1 até as primeiras aspas encontradas, resultando na string str_aux */
            if(strcmp(nome_campo, "data") == 0){
                escrever_string(file, str_aux, strlen(str_aux)); /* escreve a nova data */
            }
            else{
                fseek(file, sizeof(dado->data), SEEK_CUR); /* pula a data */
                fread(&(dado->indCid), sizeof(dado->indCid), 1, file); /* lê o indicador de tamanho */
                ind = strlen(str_aux)+2; /* considera a tag e \0 */
                if(strcmp(nome_campo, "cidade") == 0){
                    tag_aux = '4'; /* associa a tag '4' */
                    if(dado->indCid > 0){
                        fread(&(dado->tagCampo4), sizeof(dado->tagCampo4), 1, file); /* lê a tagCampo4 */
                        if(dado->tagCampo4 == '4'){
                            fseek(file, dado->indCid-1, SEEK_CUR); /* pula a cidade */
                            fread(&(dado->indEsc), sizeof(dado->indEsc), 1, file); /* lê o indicador de tamanho */
                            fread(&(dado->tagCampo5), sizeof(dado->tagCampo5), 1, file); /* lê a tagCampo5 */
                            dado->nomeEscola = (char*)malloc(sizeof(char)*(dado->indEsc)-2); /* cria o nomeEscola */
                            ler_string(file, dado->nomeEscola, dado->indEsc-2); /* lê a nomeEscola */

                            ret = -(sizeof(dado->tagCampo4)+sizeof(dado->indCid)+dado->indCid+dado->indEsc+sizeof(dado->tagCampo5)+sizeof(dado->indEsc)-3); /* valor necessario para voltar até o indicador de tamanho (cidade) */
                            fseek(file, ret, SEEK_CUR); /* volta até o indicador de tamanho (cidade) */

                            if(valor[0] == '"'){
                                fwrite(&ind, sizeof(ind), 1, file); /* escreve o indicador de tamanho da cidade */
                                fwrite(&tag_aux, sizeof(tag_aux), 1, file); /* escreve a tag da cidade */
                                escrever_string(file, str_aux, ind-2); /* escreve a cidade */
                                fwrite(&fim, sizeof(fim), 1, file); /* escreve o \0 */
                            }
                            fwrite(&(dado->indEsc), sizeof(dado->indEsc), 1, file); /* escreve o indicador de tamanho do nomeEscola */
                            fwrite(&(dado->tagCampo5), sizeof(dado->tagCampo5), 1, file); /* escreve a tagCampo5 */
                            escrever_string(file, dado->nomeEscola, dado->indEsc-2); /* escreve o nomeEscola */
                            fwrite(&fim, sizeof(fim), 1, file); /* escreve o \0 */
                            if(valor[0] != '"'){
                                //fseek(file, -1, SEEK_CUR);
                                preenche_registros(file, 0, 2*dado->indEsc-dado->indCid); /* preenche o resto do registro com @ */
                            }
                            else{
                                if(ind < dado->indCid)
                                    preenche_registros(file, ind, dado->indCid); /* preenche o resto do registro com @ */
                            }
                        }
                        else{
                            if(dado->tagCampo4 == '5'){
                                dado->nomeEscola = (char*)malloc(sizeof(char)*(dado->indCid)); /* cria o nomeEscola */
                                ler_string(file, dado->nomeEscola, dado->indCid-2); /* lê o campo nomeEscola */

                                fseek(file, -(dado->indCid + sizeof(dado->indCid) + sizeof(dado->tagCampo4)-2), SEEK_CUR); /* volta até o indicador de tamanho */

                                /* Escrever o campo cidade */
                                fwrite(&ind, sizeof(ind), 1, file); /* escreve o indicador de tamanho da cidade */
                                fwrite(&tag_aux, sizeof(tag_aux), 1, file); /* escreve a tag da cidade */
                                escrever_string(file, str_aux, ind-2); /* escreve a cidade */
                                fwrite(&fim, sizeof(fim), 1, file); /* escreve o \0 */

                                /* Reescrever o campo nomeEscola */
                                fwrite(&(dado->indCid), sizeof(dado->indCid), 1, file); /* escreve o indicador de tamanho do nomeEscola */
                                fwrite(&(dado->tagCampo4), sizeof(dado->tagCampo4), 1, file); /* escreve a tag do nomeEscola */
                                escrever_string(file, dado->nomeEscola, dado->indCid - 1); /* escreve o nomeEscola */
                           }
                        }
                    }
                    else{
                        fwrite(&ind, sizeof(ind), 1, file); /* escreve o indicador de tamanho da cidade */
                        fwrite(&tag_aux, sizeof(tag_aux), 1, file); /* escreve a tag da cidade */
                        escrever_string(file, str_aux, ind); /* escreve a cidade */
                    }
                }
                else{
                    if(strcmp(nome_campo, "nomeEscola") == 0){
                        tag_aux = '5'; /* associa a tag_aux com '5' */
                        if(dado->indCid > 0){
                            fread(&(dado->tagCampo4), sizeof(dado->tagCampo4), 1, file); /* lê a tagCampo4 */
                            if(dado->tagCampo4 == '4'){
                                fseek(file, (dado->indCid-1), SEEK_CUR); /* pula o campo cidade */
                                fread(&(dado->indEsc), sizeof(dado->indEsc), 1, file);
                                fread(&(dado->tagCampo5), sizeof(dado->tagCampo5), 1, file);
                                fseek(file, -(sizeof(dado->indEsc)+sizeof(dado->tagCampo5)), SEEK_CUR);
                                fwrite(&ind, sizeof(ind), 1, file); /* escreve o indicador de tamanho do nomeEscola */
                                fwrite(&tag_aux, sizeof(tag_aux), 1, file); /* escreve a tag do nomeEscola */
                                escrever_string(file, str_aux, ind-2); /* escreve o nomeEscola */
                                fwrite(&fim, sizeof(fim), 1, file); /* escreve o \0 */
                                if(dado->tagCampo5 == '5' && ind < dado->indEsc)
                                    preenche_registros(file, ind, dado->indEsc); /* preenche o resto do registro com @ */
                            }
                            else{
                                if(dado->tagCampo4 == '5'){
                                    fseek(file, -(sizeof(dado->indCid) + sizeof(dado->tagCampo4)), SEEK_CUR); /* pula até o inicio dos campos variaveis */
                                    fwrite(&ind, sizeof(ind), 1, file); /* escreve o indicador de tamanho do nomeEscola */
                                    fwrite(&tag_aux, sizeof(tag_aux), 1, file); /* escreve a tag do nomeEscola */
                                    escrever_string(file, str_aux, ind-2); /* escreve o nomeEscola */
                                    fwrite(&fim, sizeof(fim), 1, file); /* escreve o \0 */
                                    if(ind < dado->indCid)
                                        preenche_registros(file, ind, dado->indCid); /* preenche o resto do registro com @ */
                                }
                            }
                        }
                        else{
                            fwrite(&ind, sizeof(ind), 1, file); /* escreve o indicador de tamanho do nomeEscola */
                            fwrite(&tag_aux, sizeof(tag_aux), 1, file); /* escreve a tag do nomeEscola */
                            escrever_string(file, str_aux, ind); /* escreve o nomeEscola */
                        }
                    }
                }
            }
        }
    }
    if(ultimo == 1)
        binarioNaTela1(file); /* quando for o ultimo registro, printa o binario */
    fclose(file);
}

void ordenaInteiro(char *file_in, char *file_out){
    int qtd, i, cont, pos = TAM_PAGE;
    char lixo = '@';
    FILE* file = fopen(file_in, "rb");
    FILE* file2 = fopen(file_out, "wb+");
    if(!file2 || !file){
        printf("Falha no carregamento do arquivo.");
        return; /* caso o arquivo não exista ou ocorra outro erro, retorna */
    }
    Dados_PTR dado;
    Header head;
    head = (Header) malloc(sizeof(Cabecalho));
    fread(&(head->status), sizeof(head->status), 1, file); /* lê o status */
    if(head->status == '0'){
        printf("Falha no processamento do arquivo.");
        return; /* se o status for igual a 0, não é possivel ler o resto do arquivo */
    }
    qtd = qtdRegistro(file); /* retorna a quantidade de registros (sem considerar os campos removidos) */
    dado = (Dados_PTR) malloc(qtd*sizeof(Dados));
    fseek(file, TAM_PAGE, SEEK_SET); /* pula para o fim da pagina de disco do cabecalho */
    qtd = guardaDados(file, dado); /* guarda os campos do arquivo e retorna a quantidade real de registros */
    mergeSort(&dado, 0, qtd-1); /* ordena o vetor */

    /* Registros */
    iniciar_cabecalho(head); /* fornece os valores iniciais para o cabeçalho */
    escrever_cabecalho(head, file2); /* escreve os valores iniciais do cabeçalho no arquivo binário */
    preenche_registros(file2, TAM_CAB, TAM_PAGE); /* como o registro de cabeçalho ocupa uma página de disco inteira, é necessário preencher o resto da página */
    for(i = 0; i < qtd; i++){
        if(dado[i].removido != '*'){ /* confere se não há registro removido */
            dado[i].indCid = strlen(dado[i].cidade); /* associa a quantidade de caracteres ao indicador de tamanho */
            if(dado[i].indCid > 0){
                dado[i].indCid += 2; /* acrescenta tag e \0 */
                dado[i].tagCampo4 = '4';
            }
            dado[i].indEsc = strlen(dado[i].nomeEscola); /* associa a quantidade de caracteres ao indicador de tamanho */
            if(dado[i].indEsc > 0){
                dado[i].indEsc += 2; /* acrescenta tag e \0 */
                dado[i].tagCampo5 = '5';
            }
            escrever_dados(&dado[i], file2, &cont, dado[i].cidade, dado[i].nomeEscola); /* escreve os campos de dados no arquivo */
            pos = cont+2+pos; /* método para inserir os @s no fim dos registros */
            while(pos < (TAM_PAGE+(i+1)*80)){
                fwrite(&lixo, sizeof(lixo), 1, file2);
                pos++;
            }
            if(dado[i].indCid <= 0 || dado[i].indEsc <= 0){ /* caso um dos campos variaveis seja nulo, é necessário inserir mais um @ */
                fwrite(&lixo, sizeof(lixo), 1, file2);
                if(dado[i].indCid <= 0 && dado[i].indEsc <= 0) /* caso os dois campos variaveis sejam nulos, é necessário inserir um @ extra */
                    fwrite(&lixo, sizeof(lixo), 1, file2);
            }
        }
    }
    head->status = '1'; /* depois que o arquivo foi escrito, atualiza o valor do status */
    fseek(file2, 0, SEEK_SET); /* retorna para o inicio do arquivo binario */
    fwrite(&(head->status), sizeof(char), 1, file2); /* reescreve o status no cabeçalho */
    binarioNaTela1(file2);
    fclose(file2);
    fclose(file);
}

int qtdRegistro(FILE *file){
    int qtd;
    int pos_ant = ftell(file); /* armazena posição atual do arquivo */
    fseek(file, 0, SEEK_END); /* vai para o fim do arquivo */
    qtd = (ftell(file) - TAM_PAGE)/TAM_DAD; /* expressao para o calculo do numero de registros */
    fseek(file, pos_ant, SEEK_SET); /* retorna para a posição anterior */
    return qtd;
}

int guardaDados(FILE *file, Dados_PTR dado){
    int i = 0, j = 0, ret_fun;
    while(!feof(file)){
        fread(&(dado[i].removido), sizeof(dado[i].removido), 1, file); /* lê o campo removido no arquivo binario */
        if(dado[i].removido != '*'){
            dado[i].nomeEscola = (char*) calloc(30, sizeof(char));
            dado[i].cidade = (char*)calloc(30, sizeof(char));
            fread(&(dado[i].encadeamento), sizeof(dado[i].encadeamento), 1, file); /* lê o campo encadeamento no arquivo binario */
            ret_fun = fread(&(dado[i].nroInscricao), sizeof(dado[i].nroInscricao), 1, file); /* lê o campo nroInscricao no arquivo binario */
            if(ret_fun == 0)   /* condicao de saida */
                break;

            fread(&(dado[i].nota), sizeof(dado[i].nota), 1, file); /* lê o campo nota no arquivo binario */

            ler_string(file, dado[i].data, sizeof(dado[i].data)); /* lê o campo data no arquivo binario */

            fread(&(dado[i].indCid), sizeof(dado[i].indCid), 1, file); /* lê o campo indicador de tamanho (cidade) no arquivo binario */
            dado[i].indCid = dado[i].indCid - 2;
            if(dado[i].indCid > 0){ /* se o indicador de tamanho for maior que 0, significa que o campo cidade ou nomeEscola existe */
                fread(&(dado[i].tagCampo4), sizeof(dado[i].tagCampo4), 1, file); /* lê o campo tagCampo4 no arquivo binario */
                if(dado[i].tagCampo4 == '4') /* se tagCampo4 for igual a '4', o campo cidade cidade existe */
                    ler_string(file, dado[i].cidade, dado[i].indCid); /* lê o campo cidade */
                else{
                    if(dado[i].tagCampo4 == '5'){ /* se o campo tagCampo4 for igual a '5', o campo cidade não existe, mas o campo nomeEscola sim */
                        ler_string(file, dado[i].nomeEscola, dado[i].indCid); /* lê o campo nomeEscola */
                        dado[i].indEsc = dado[i].indCid;
                        dado[i].indCid = 0;
                    }
                }
            }

            fseek(file, 1, SEEK_CUR); /* pula o \0 */
            fread(&(dado[i].indEsc), sizeof(dado[i].indEsc), 1, file); /* lê o campo indicador de tamanho (nomeEscola) no arquivo binario */
            dado[i].indEsc = dado[i].indEsc - 2;
            if(dado[i].tagCampo4 != '5'){ /* significa que o campo cidade existe */
                if(dado[i].indEsc > 0){ /* se o indicador de tamanho for maior que 0, significa que o campo nomeEscola existe */
                    fread(&(dado[i].tagCampo5), sizeof(dado[i].tagCampo5), 1, file); /* lê o campo tagCampo5 no arquivo binario */
                    if(dado[i].tagCampo5 == '5'){ /* significa que o campo nomeEscola existe */
                        ler_string(file,dado[i].nomeEscola, dado[i].indEsc); /* lê e imprime o campo nomeEscola */
                    }
                }
            }
            i++;
        }
        j++;
        fseek(file, (TAM_PAGE+j*80), SEEK_SET); /* pula para o começo de um novo registro */
    }
    return i;
}

void merge(Dados_PTR *arr, int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    char L_rev[n1], R_rev[n2];
    int L_enc[n1], R_enc[n2];
    int L_Insc[n1], R_Insc[n2];
    double L_nota[n1], R_nota[n2];
    char L_data[n1][11], R_data[n2][11];
    int L_indCid[n1], R_indCid[n2];
    char L_tag4[n1], R_tag4[n2];
    char L_cid[n1][30], R_cid[n2][30];
    int L_indEsc[n1], R_indEsc[n2];
    char L_tag5[n1], R_tag5[n2];
    char L_esc[n1][30], R_esc[n2][30];

    for (i = 0; i < n1; i++){
        L_rev[i] = (*arr+l+i)->removido;
        L_enc[i] = (*arr+l+i)->encadeamento;
        L_Insc[i] = (*arr+l+i)->nroInscricao;
        L_nota[i] = (*arr+l+i)->nota;
        strcpy(L_data[i], (*arr+l+i)->data);
        L_indCid[i] = (*arr+l+i)->indCid;
        L_tag4[i] = (*arr+l+i)->tagCampo4;
        if(L_indCid[i] > 0)
            strcpy(L_cid[i], (*arr+l+i)->cidade);
        else
            L_cid[i][0] = '\0';
        L_indEsc[i] = (*arr+l+i)->indEsc;
        L_tag5[i] = (*arr+l+i)->tagCampo5;
        strcpy(L_esc[i], (*arr+l+i)->nomeEscola);
    }
    for (j = 0; j < n2; j++){
        R_rev[j] = (*arr+m+1+j)->removido;
        R_enc[j] = (*arr+m+1+j)->encadeamento;
        R_Insc[j] = (*arr+m+1+j)->nroInscricao;
        R_nota[j] = (*arr+m+1+j)->nota;
        strcpy(R_data[j], (*arr+m+1+j)->data);
        R_indCid[j] = (*arr+m+1+j)->indCid;
        R_tag4[j] = (*arr+m+1+j)->tagCampo4;
        if(R_indCid[j] > 0)
            strcpy(R_cid[j], (*arr+m+1+j)->cidade);
        else
            R_cid[j][0] = '\0';
        R_indEsc[j] = (*arr+m+1+j)->indEsc;
        R_tag5[j] = (*arr+m+1+j)->tagCampo5;
        strcpy(R_esc[j], (*arr+m+1+j)->nomeEscola);
    }

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2){
        if (L_Insc[i] <= R_Insc[j]){
            (*arr+k)->removido = L_rev[i];
            (*arr+k)->encadeamento = L_enc[i];
            (*arr+k)->nroInscricao = L_Insc[i];
            (*arr+k)->nota = L_nota[i];
            strcpy((*arr+k)->data, L_data[i]);
            (*arr+k)->indCid = L_indCid[i];
            (*arr+k)->tagCampo4 = L_tag4[i];
            strcpy((*arr+k)->cidade, L_cid[i]);
            (*arr+k)->indEsc = L_indEsc[i];
            (*arr+k)->tagCampo5 = L_tag5[i];
            strcpy((*arr+k)->nomeEscola, L_esc[i]);
            i++;
        }
        else{
            (*arr+k)->removido = R_rev[j];
            (*arr+k)->encadeamento = R_enc[j];
            (*arr+k)->nroInscricao = R_Insc[j];
            (*arr+k)->nota = R_nota[j];
            strcpy((*arr+k)->data, R_data[j]);
            (*arr+k)->indCid = R_indCid[j];
            (*arr+k)->tagCampo4 = R_tag4[j];
            strcpy((*arr+k)->cidade, R_cid[j]);
            (*arr+k)->indEsc = R_indEsc[j];
            (*arr+k)->tagCampo5 = R_tag5[j];
            strcpy((*arr+k)->nomeEscola, R_esc[j]);
            j++;
        }
        k++;
    }

    while(i<n1){
        (*arr+k)->removido = L_rev[i];
        (*arr+k)->encadeamento = L_enc[i];
        (*arr+k)->nroInscricao = L_Insc[i];
        (*arr+k)->nota = L_nota[i];
        strcpy((*arr+k)->data, L_data[i]);
        (*arr+k)->indCid = L_indCid[i];
        (*arr+k)->tagCampo4 = L_tag4[i];
        strcpy((*arr+k)->cidade, L_cid[i]);
        (*arr+k)->indEsc = L_indEsc[i];
        (*arr+k)->tagCampo5 = L_tag5[i];
        strcpy((*arr+k)->nomeEscola, L_esc[i]);
        i++;
        k++;
    }

    while(j<n2){
        (*arr+k)->removido = R_rev[j];
        (*arr+k)->encadeamento = R_enc[j];
        (*arr+k)->nroInscricao = R_Insc[j];
        (*arr+k)->nota = R_nota[j];
        strcpy((*arr+k)->data, R_data[j]);
        (*arr+k)->indCid = R_indCid[j];
        (*arr+k)->tagCampo4 = R_tag4[j];
        strcpy((*arr+k)->cidade, R_cid[j]);
        (*arr+k)->indEsc = R_indEsc[j];
        (*arr+k)->tagCampo5 = R_tag5[j];
        strcpy((*arr+k)->nomeEscola, R_esc[j]);
        j++;
        k++;
    }
}

void mergeSort(Dados_PTR *arr, int l, int r){
    if (l < r){
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void escrever_dados(Dados_PTR dado, FILE *file, int *cont, char *cid_aux, char *esc_aux){
    int i;
    char c = '\0', lixo = '@';
    /* Escrever no arquivo binário */
    *cont = 0; /* variavel que conta a quantidade de bytes que o registro possui */
    fwrite(&(dado->removido), sizeof(dado->removido), 1, file); /* escreve o campo removido no arquivo binario */
    *cont += sizeof(dado->removido);
    fwrite(&(dado->encadeamento), sizeof(dado->encadeamento), 1, file); /* escreve o campo encadeamento no arquivo binario */
    *cont += sizeof(dado->encadeamento);
    fwrite(&(dado->nroInscricao), sizeof(dado->nroInscricao), 1, file); /* escreve o campo nroInscricao no arquivo binario */
    *cont += sizeof(dado->nroInscricao);
    fwrite(&(dado->nota), sizeof(dado->nota), 1, file); /* escreve o campo nota no arquivo binario */
    *cont += sizeof(dado->nota);
    if(strcmp(dado->data, "\0@@@@@@@@@") != 0)
        escrever_string(file, dado->data, sizeof(dado->data)); /* função que escreve o campo data no arquivo binario */
    else{
        fwrite(&c, sizeof(c), 1, file);
        for(i = 0; i < 9; i++)
            fwrite(&lixo, sizeof(lixo), 1, file);
    }
    *cont += sizeof(dado->data);
    if(strlen(dado->cidade) > 0){ /* se o indicador de tamanho for maior que 0, significa que o campo cidade existe */
        fwrite(&(dado->indCid), sizeof(dado->indCid), 1, file); /* escreve o campo indicador de tamanho (cidade) no arquivo binario */
        *cont += sizeof(dado->indCid);
        fwrite(&(dado->tagCampo4), sizeof(dado->tagCampo4), 1, file); /* escreve o campo tagCampo4 no arquivo binario */
        *cont += sizeof(dado->tagCampo4);
        cid_aux[dado->indCid-1] = '\0';
        escrever_string(file, cid_aux, (dado->indCid - 2)); /* função que escreve o campo cidade no arquivo binario */
        *cont += dado->indCid - 2;
        fwrite(&c, sizeof(c), 1, file); /* escreve o \0 */
    }
    if(strlen(dado->nomeEscola) > 0){ /* se o indicador de tamanho for maior que 0, significa que o campo escola existe */
        fwrite(&(dado->indEsc), sizeof(dado->indEsc), 1, file); /* escreve o campo indicador de tamanho (escola) no arquivo binario */
        *cont += sizeof(dado->indEsc);
        fwrite(&(dado->tagCampo5), sizeof(dado->tagCampo5), 1, file); /* escreve o campo tagCampo5 no arquivo binario */
        *cont += sizeof(dado->tagCampo5);
        esc_aux[dado->indEsc-1] = '\0';
        escrever_string(file, esc_aux, (dado->indEsc - 2)); /* função que escreve o campo nomeEscola no arquivo binario */
        *cont += dado->indEsc - 2;
        fwrite(&c, sizeof(c), 1, file); /* escreve o \0 */
    }
}

void troca_reg(Dados_PTR dado_novo, Dados_PTR dado, int i, int ind){
    dado_novo[i].removido = dado[ind].removido; /* associa o campo removido do arquivo antigo com o do novo */
    dado_novo[i].encadeamento = dado[ind].encadeamento; /* associa o campo encadeamento do arquivo antigo com o do novo */
    dado_novo[i].nroInscricao = dado[ind].nroInscricao; /* associa o campo nroInscricao do arquivo antigo com o do novo */
    dado_novo[i].nota = dado[ind].nota; /* associa o campo nota do arquivo antigo com o do novo */
    strcpy(dado_novo[i].data, dado[ind].data); /* associa o campo data do arquivo antigo com o do novo */

    dado_novo[i].indCid = dado[ind].indCid; /* associa o campo indicador de tamanho (cidade) do arquivo antigo com o do novo */
    dado_novo[i].tagCampo4 = dado[ind].tagCampo4; /* associa o campo tagCampo4 do arquivo antigo com o do novo */
    dado_novo[i].cidade = (char *)calloc(sizeof(char), strlen(dado[ind].cidade)+1); /* é necessário realizar o malloc toda vez, pois há comparações em que o campo pode não existir, o que, sem o malloc, dará erro */
    if(strlen(dado[ind].cidade) > 0)
        strcpy(dado_novo[i].cidade, dado[ind].cidade); /* associa o campo cidade do arquivo antigo com o do novo */

    dado_novo[i].indEsc = dado[ind].indEsc; /* associa o campo indicador de tamanho (nomeEscola) do arquivo antigo com o do novo */
    dado_novo[i].tagCampo5 = dado[ind].tagCampo5; /* associa o campo tagCampo5 do arquivo antigo com o do novo */
    dado_novo[i].nomeEscola = (char *)calloc(sizeof(char), strlen(dado[ind].nomeEscola)+1); /* é necessário realizar o malloc toda vez, pois há comparações em que o campo pode não existir, o que, sem o malloc, dará erro */
    if(strlen(dado[ind].nomeEscola) > 0)
        strcpy(dado_novo[i].nomeEscola, dado[ind].nomeEscola); /* associa o campo nomeEscola do arquivo antigo com o do novo */
}

void merging(char *file_in1, char *file_in2, char *file_out){
    int qtd1, qtd2, ind1 = 0, ind2 = 0, i = 0, rep = 0, cont = 0, pos = TAM_PAGE;
    char lixo = '@';
    FILE* file = fopen(file_in1, "rb");
    FILE* file2 = fopen(file_in2, "rb");
    FILE* file3 = fopen(file_out, "wb");
    if(file3 == NULL || file2 == NULL || file == NULL){
        printf("Falha no carregamento do arquivo.");
        return; /* caso o arquivo não exista ou ocorra outro erro, retorna */
    }
    Dados_PTR dado1, dado2, dado3;
    Header head1, head2, head3;
    head1 = (Header) malloc(sizeof(Cabecalho));
    head2 = (Header) malloc(sizeof(Cabecalho));
    head3 = (Header) malloc(sizeof(Cabecalho));
    fread(&(head1->status), sizeof(head1->status), 1, file); /* lê o status do arquivo1*/
    fread(&(head2->status), sizeof(head2->status), 1, file); /* lê o status do arquivo2*/
    if(head1->status == '0' || head2->status == '0'){
        printf("Falha no processamento do arquivo.");
        return; /* se o status for igual a 0, não é possivel ler o resto do arquivo */
    }
    qtd1 = qtdRegistro(file); /* retorna a quantidade de registros (sem considerar os campos removidos) */
    qtd2 = qtdRegistro(file2); /* retorna a quantidade de registros (sem considerar os campos removidos) */
    dado1 = (Dados_PTR) malloc(qtd1*sizeof(Dados));
    dado2 = (Dados_PTR) malloc(qtd2*sizeof(Dados));
    fseek(file, TAM_PAGE, SEEK_SET); /* pula para o fim do cabeçalho */
    fseek(file2, TAM_PAGE, SEEK_SET); /* pula para o fim do cabeçalho */
    qtd2 = guardaDados(file2, dado2); /* quantidade real de registros */
    qtd1 = guardaDados(file, dado1); /* quantidade real de registros */
    dado3 = (Dados_PTR) malloc((qtd1+qtd2)*sizeof(Dados)); /* dado3 representa os registros do novo arquivo */
    //mergeSort(&dado1, 0, qtd1-1); /* ordena o vetor com os registros do primeiro arquivo */
    //mergeSort(&dado2, 0, qtd2-1); /* ordena o vetor com os registros do segundo arquivo */
    while(ind1 < qtd1 && ind2 < qtd2){
        if(dado1[ind1].nroInscricao <= dado2[ind2].nroInscricao){
            troca_reg(dado3, dado1, i, ind1); /* Função que associa os campos dos registros do arquivo antigo com o novo */
            ind1++;

            if(dado1[ind1].nroInscricao == dado2[ind2].nroInscricao){
                ind2++;
                rep++; /* variacao que indica quando há repetições de registros */
            }
        }
        else{
            if(dado1[ind1].nroInscricao > dado2[ind2].nroInscricao){
                troca_reg(dado3, dado2, i, ind2); /* Função que associa os campos dos registros do arquivo antigo com o novo */
                ind2++;
            }
        }
        i++;
    }
    while(ind1 < qtd1){
        troca_reg(dado3, dado1, i, ind1); /* Função que associa os campos dos registros do arquivo antigo com o novo */
        i++;
        ind1++;
    }
    while(ind2 < qtd2){
        troca_reg(dado3, dado2, i, ind2); /* Função que associa os campos dos registros do arquivo antigo com o novo */
        i++;
        ind2++;
    }
    /* Registros */
    iniciar_cabecalho(head3); /* fornece os valores iniciais para o cabeçalho */
    escrever_cabecalho(head3, file3); /* escreve os valores iniciais do cabeçalho no arquivo binário */
    preenche_registros(file3, TAM_CAB, TAM_PAGE); /* como o registro de cabeçalho ocupa uma página de disco inteira, é necessário preencher o resto da página */
    for(i = 0; i < qtd1+qtd2-rep; i++){
        cont = 0;
        dado3[i].indCid = strlen(dado3[i].cidade); /* associa a quantidade de caracteres ao indicador de tamanho */
        if(dado3[i].indCid != 0){
            dado3[i].indCid += 2; /* acrescenta tag e \0 */
            dado3[i].tagCampo4 = '4';
        }
        dado3[i].indEsc = strlen(dado3[i].nomeEscola); /* associa a quantidade de caracteres ao indicador de tamanho */
        if(dado3[i].indEsc != 0){
            dado3[i].indEsc += 2; /* acrescenta tag e \0 */
            dado3[i].tagCampo5 = '5';
        }
        escrever_dados(&dado3[i], file3, &cont, dado3[i].cidade, dado3[i].nomeEscola); /* função que escreve os campos do registro no arquivo */
        pos = cont+2+pos; /* método para inserir os @s no fim dos registros */
        while(pos < (TAM_PAGE+(i+1)*80)){
            fwrite(&lixo, sizeof(lixo), 1, file3);
            pos++;
        }
        if((i != 0 && dado3[i].indCid <= 0) || (i != 0 && dado3[i].indEsc <= 0)){ /* caso um dos campos variaveis seja nulo, é necessário inserir mais um @ */
            fwrite(&lixo, sizeof(lixo), 1, file3);
            if(dado3[i].indCid <= 0 && dado3[i].indEsc <= 0) /* caso os dois campos variaveis sejam nulos, é necessário inserir um @ extra */
                fwrite(&lixo, sizeof(lixo), 1, file3);
        }
    }

    head3->status = '1'; /* depois que o arquivo foi escrito, atualiza o valor do status */
    fseek(file3, 0, SEEK_SET); /* retorna para o inicio do arquivo binario */
    fwrite(&(head3->status), sizeof(char), 1, file3); /* reescreve o status no cabeçalho */
    binarioNaTela1(file3);

    fclose(file2);
    fclose(file);
    //fclose(file3);
}

void matching(char *file_in1, char *file_in2, char *file_out){
    int qtd1, qtd2, ind1 = 0, ind2 = 0, i = 0, j = 0, cont, pos = TAM_PAGE;
    char lixo = '@';
    FILE* file = fopen(file_in1, "rb");
    FILE* file2 = fopen(file_in2, "rb");
    FILE* file3 = fopen(file_out, "wb");
    if(!file3 || !file2 || !file){
        printf("Falha no carregamento do arquivo.");
        return; /* caso o arquivo não exista ou ocorra outro erro, retorna */
    }
    Dados_PTR dado1, dado2, dado3;
    Header head1, head2, head3;
    head1 = (Header) malloc(sizeof(Cabecalho));
    head2 = (Header) malloc(sizeof(Cabecalho));
    head3 = (Header) malloc(sizeof(Cabecalho));
    fread(&(head1->status), sizeof(head1->status), 1, file); /* lê o status do arquivo1*/
    fread(&(head2->status), sizeof(head2->status), 1, file); /* lê o status do arquivo2*/
    if(head1->status == '0' || head2->status == '0'){
        printf("Falha no processamento do arquivo.");
        return; /* se o status for igual a 0, não é possivel ler o resto do arquivo */
    }
    qtd1 = qtdRegistro(file);  /* retorna a quantidade de registros (sem considerar os campos removidos) */
    qtd2 = qtdRegistro(file2);  /* retorna a quantidade de registros (sem considerar os campos removidos) */
    dado1 = (Dados_PTR) malloc(qtd1*sizeof(Dados));
    dado2 = (Dados_PTR) malloc(qtd2*sizeof(Dados));
    fseek(file, TAM_PAGE, SEEK_SET); /* pula para o fim do cabeçalho */
    fseek(file2, TAM_PAGE, SEEK_SET); /* pula para o fim do cabeçalho */
    dado3 = (Dados_PTR) malloc((qtd1+qtd2)*sizeof(Dados));
    qtd2 = guardaDados(file2, dado2); /* quantidade real de registros */
    qtd1 = guardaDados(file, dado1); /* quantidade real de registros */
    //mergeSort(&dado1, 0, qtd1-1); /* ordena os registros */
    //mergeSort(&dado2, 0, qtd2-1); /* ordena os registros */
    j=0;
    while(ind1 < qtd1 && ind2 < qtd2){
        if(dado1[ind1].nroInscricao < dado2[ind2].nroInscricao)
            ind1++;
        else{
            if(dado1[ind1].nroInscricao > dado2[ind2].nroInscricao)
                ind2++;
            else{
                troca_reg(dado3, dado1, j, ind1); /* Função que associa os campos dos registros do arquivo antigo com o novo */
                ind1++;
                ind2++;
                j++;
            }
        }
    }
    /* Registros */
    iniciar_cabecalho(head3); /* fornece os valores iniciais para o cabeçalho */
    escrever_cabecalho(head3, file3); /* escreve os valores iniciais do cabeçalho no arquivo binário */
    preenche_registros(file3, TAM_CAB, TAM_PAGE); /* como o registro de cabeçalho ocupa uma página de disco inteira, é necessário preencher o resto da página */
    for(i = 0; i < j; i++){
        dado3[i].indCid = strlen(dado3[i].cidade); /* associa a quantidade de caracteres ao indicador de tamanho */
        if(dado3[i].indCid > 0){
            dado3[i].indCid += 2; /* acrescenta tag e \0 */
            dado3[i].tagCampo4 = '4';
        }
        dado3[i].indEsc = strlen(dado3[i].nomeEscola); /* associa a quantidade de caracteres ao indicador de tamanho */
        if(dado3[i].indEsc > 0){
            dado3[i].indEsc += 2; /* acrescenta tag e \0 */
            dado3[i].tagCampo5 = '5';
        }
        escrever_dados(&dado3[i], file3, &cont, dado3[i].cidade, dado3[i].nomeEscola); /* função que escreve os campos do registro no arquivo */
        pos = cont+2+pos; /* método para inserir os @s no fim dos registros */
        while(pos < (TAM_PAGE+(i+1)*80)){
            fwrite(&lixo, sizeof(lixo), 1, file3);
            pos++;
        }
        if(dado3[i].indCid <= 0 || dado3[i].indEsc <= 0){ /* caso um dos campos variaveis seja nulo, é necessário inserir mais um @ */
            fwrite(&lixo, sizeof(lixo), 1, file3);
            if(dado3[i].indCid <= 0 && dado3[i].indEsc <= 0) /* caso os dois campos variaveis sejam nulos, é necessário inserir um @ extra */
                fwrite(&lixo, sizeof(lixo), 1, file3);
        }
    }
    head3->status = '1'; /* depois que o arquivo foi escrito, atualiza o valor do status */
    fseek(file3, 0, SEEK_SET); /* retorna para o inicio do arquivo binario */
    fwrite(&(head3->status), sizeof(char), 1, file3); /* reescreve o status no cabeçalho */
    binarioNaTela1(file3);

    fclose(file3);
    fclose(file2);
    fclose(file);
}

void cria_indice(char *nome_file1, char *nome_file2){
    int qtd, i = 0, j = 0, rep = 0;
    FILE* file = fopen(nome_file1, "rb");
    FILE* file2 = fopen(nome_file2, "wb");
    Dados_ind_PTR dado;
    Header_ind head;

    /* Cabecalho */
    head = (Header_ind) malloc(sizeof(Cabecalho_ind));
    head->status = '0';
    head->nroRegistros = 0;
    escreve_cabecalhoInd(file2, head); /* escreve o cabecalho com as condicoes iniciais */
    preenche_registros(file2, TAM_IND, TAM_PAGE); /* preenche o cabecalho para que ocupe uma pagina de disco */

    /* Indices */
    qtd = qtdRegistro(file); /* obtem a quantidade de registros do arquivo de dados */
    dado = (Dados_ind_PTR) malloc(qtd * sizeof(Dados_ind));
    for(i = 0; i < qtd; i++){
        fseek(file, TAM_PAGE+i*TAM_DAD, SEEK_SET);
        if(!cria_indDados(file, &dado[j], i))
            rep++; /* indica que registros sem nomeEscola */
        else
            j++;
    }
    qtd = qtd - rep; /* quantidade de registros do arquivo de indice */
    mergeSort_ind(&dado, 0, qtd-1); /* ordena os registros */

    /* Escreve no arquivo de indices */
    for(i = 0; i < qtd; i++)
        escreve_DadosInd(file2, &dado[i]);

    fseek(file2, 0, SEEK_SET); /* volta para o inicio do arquivo de cabecalho */
    head->status = '1'; /* atualiza o valor dos status */
    head->nroRegistros = qtd; /* atualiza o valor do nroRegistros */
    escreve_cabecalhoInd(file2, head); /* escreve os novos valores no cabecalho */
    binarioNaTela1(file2);
    fclose(file2);
    fclose(file);
}

void escreve_cabecalhoInd(FILE *file, Header_ind head){
    fwrite(&(head->status), sizeof(head->status), 1, file); /* escreve o status */
    fwrite(&(head->nroRegistros), sizeof(head->nroRegistros), 1, file); /* escreve o nroRegistros */
}

void escreve_DadosInd(FILE *file, Dados_ind_PTR dado){
    char c='\0';
    escrever_string(file, dado->chaveBusca, strlen(dado->chaveBusca)); /* escreve a chaveBusca */
    fwrite(&c, sizeof(c), 1, file); /* escreve o \0 */
    preenche_registros(file, strlen(dado->chaveBusca)+1, sizeof(dado->chaveBusca)); /* preenche o campo chaveBusca para que ocupe 28 bytes */
    fwrite(&(dado->RRN), sizeof(dado->RRN), 1, file); /* escreve o RRN */
}

int cria_indDados(FILE *file, Dados_ind_PTR dado, int rrn){
    char removido, tag, c = '\0';
    int tam;
    fread(&removido, sizeof(removido), 1, file); /* lê o campo removido */
    if(removido != '*'){
        fseek(file, 26, SEEK_CUR); /* 26 representa a soma dos tamanhos dos campos de tamanho fixo restantes */
        fread(&tam, sizeof(tam), 1, file); /* lê o primeiro indicador de tamanho */
        fread(&tag, sizeof(tag), 1, file); /* lê a primeira tag */
        if(tag == '4'){
            fseek(file, tam-1, SEEK_CUR); /* pula o campo cidade */
            fread(&tam, sizeof(tam), 1, file); /* lê o segundo indicador de tamanho */
            fread(&tag, sizeof(tag), 1, file); /* lê a segunda tag */
            if(tag == '5'){
                ler_nomeEscola(c, file, dado->chaveBusca); /* lê o campo nomeEscola */
                dado->RRN = rrn; /* associa o rrn passado como parametro com a estrutura que possui a chaveBusca correspondente */
            }
            else
                return 0; /* nao há o campo nomeEscola nesse registro */
        }
        else{
            if(tag == '5'){
                ler_nomeEscola(c, file, dado->chaveBusca); /* lê o campo nomeEscola */
                dado->RRN = rrn; /* associa o rrn passado como parametro com a estrutura que possui a chaveBusca correspondente */
            }
            else
                return 0; /* nao há o campo nomeEscola nesse registro */
        }
    }
    else
        return 0; /* nao há o campo nomeEscola nesse registro */
    return 1; /* indica que tem o campo nomeEscola nesse registro */
}

void merge_ind(Dados_ind_PTR *arr, int l, int m, int r){
    int i, j, k;
    int n1 = m-l+1;
    int n2 = r-m;

    char L_chaveBusca[n1][30], R_chaveBusca[n2][30];
    int L_rrn[n1], R_rrn[n2];

    for (i = 0; i < n1; i++){
        strcpy(L_chaveBusca[i], (*arr+l+i)->chaveBusca);
        L_rrn[i] = (*arr+l+i)->RRN;
    }
    for (j = 0; j < n2; j++){
        strcpy(R_chaveBusca[j], (*arr+m+1+j)->chaveBusca);
        R_rrn[j] = (*arr+m+1+j)->RRN;
    }

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2){
        if(strcmp(L_chaveBusca[i], R_chaveBusca[j]) <= 0){
            strcpy((*arr+k)->chaveBusca, L_chaveBusca[i]);
            (*arr+k)->RRN = L_rrn[i];
            i++;
        }
        else{
            strcpy((*arr+k)->chaveBusca, R_chaveBusca[j]);
            (*arr+k)->RRN = R_rrn[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        strcpy((*arr+k)->chaveBusca, L_chaveBusca[i]);
        (*arr+k)->RRN = L_rrn[i];
        i++;
        k++;
    }

    while(j<n2){
        strcpy((*arr+k)->chaveBusca, R_chaveBusca[j]);
        (*arr+k)->RRN = R_rrn[j];
        j++;
        k++;
    }
}

void mergeSort_ind(Dados_ind_PTR *arr, int l, int r){
    if (l < r){
        int m = l+(r-l)/2;
        mergeSort_ind(arr, l, m);
        mergeSort_ind(arr, m+1, r);
        merge_ind(arr, l, m, r);
    }
}

void recupera_reg_ind(char *nome_file1, char *nome_file2, char *valor){
    int i = 0, pos, pag_ind = 0, pag_dad = 0;
    char str_aux[30];
    FILE* file = fopen(nome_file1, "rb");
    FILE* file2 = fopen(nome_file2, "rb");
    Dados_ind_PTR dado;
    Header_ind head;
    Header head1;
    if(!file || !file2){
        printf("Falha no processamento do arquivo.");
        return;
    }
    head1 = (Header) malloc(sizeof(Cabecalho));
    fread(&(head1->status), sizeof(head1->status), 1, file); /* lê o status do arquivo de dados */
    head = (Header_ind) malloc(sizeof(Cabecalho_ind));
    fread(&(head->status), sizeof(head->status), 1, file2); /* lê o status do arquivo de indices */
    if(head->status == '0' || head1->status == '0'){
        printf("Falha no processamento do arquivo.");
        return;
    }
    fread(&(head->nroRegistros), sizeof(head->nroRegistros), 1, file2); /* lê o nroRegistros do arquivo de indices */
    dado = (Dados_ind_PTR) malloc(head->nroRegistros*sizeof(Dados_ind));

    /* Carrega os indices para a memoria */
    while(i < head->nroRegistros){
        fseek(file2, TAM_PAGE+i*TAM_DAD_IND, SEEK_SET); /* pula para o inicio de cada registro do arquivo de indice */
        pos = ler_stringDel(file2, dado[i].chaveBusca, '\0'); /* lê a string até encontrar o '\0'; retorna o numero de caracteres da chave */
        fseek(file2, 27-pos, SEEK_CUR); /* pula para o campo RRN */
        fread(&(dado[i].RRN), sizeof(dado[i].RRN), 1, file2); /* lê o RRN */
        i++;
    }

    pos = binarySearch(dado, 0, head->nroRegistros-1, valor); /* faz a busca binaria e retorna a posicao que o valor procurado se encontra */
    if(pos > 0){
        strcpy(str_aux, dado[pos].chaveBusca); /* str_aux representa o comparador para ter certeza de que encontrou todos os registros com essa mesma chave no arquivo de indice */
        while(pos > 0){
            if(strcmp(str_aux, dado[pos-1].chaveBusca) == 0) /* se é igual ao anterior, volta uma posicao */
                pos--;
            else /* se nao for, há a certeza que é o primeiro registro do arquivo de indice com essa chave */
                break;
        }

        while(strcmp(str_aux, dado[pos].chaveBusca) == 0){
            /* Exibe as mensagens */
            consultar_rrn(nome_file1, dado[pos].RRN); /* provisorio */
            pag_dad++;
            printf("\n");
            pos++;
        }
        printf("Número de páginas de disco para carregar o arquivo de índice: %d\n", pag_ind);
        printf("Número de páginas de disco para acessar o arquivo de dados: %d", pag_dad);
    }
    else
        printf("Registro inexistente.");
    fclose(file2);
    fclose(file);
}

int ler_chave_ind(FILE *file, char *chave){
    char c;
    int i = 0;
    do{
        fread(&c, sizeof(c), 1, file); /* lê um caractere do campo chaveBusca */
        if(c != '\0')
            chave[i] = c; /* se nao for igual a '\0', é parte da chaveBusca */
        i++;
    }while(c != '\0');
    fseek(file, 28-i, SEEK_CUR); /* pula para o campo RRN */
    return i-1;
}

void remover_registroInd(char *nome_file1, char *nome_file2, char *nome_campo, char *valor, int ultimo){
    int pos, i = 0, qtd, rep = 0, pos_ant;
    int rrn[20];
    char nomeEscola[30], str_aux[30];
    FILE* file = fopen(nome_file1, "rb");
    FILE* file2 = fopen(nome_file2, "rb");
    Dados_ind_PTR dado;
    Header_ind head;
    Header head1;
    if(!file || !file2){
        printf("Falha no processamento do arquivo.");
        return;
    }
    head1 = (Header) malloc(sizeof(Cabecalho));
    fread(&(head1->status), sizeof(head1->status), 1, file); /* lê o status do arquivo de dados */
    head = (Header_ind) malloc(sizeof(Cabecalho_ind));
    fread(&(head->status), sizeof(head->status), 1, file2); /* lê o status do arquivo de indice */
    if(head->status == '0' || head1->status == '0'){
        printf("Falha no processamento do arquivo.");
        return;
    }
    fread(&(head->nroRegistros), sizeof(head->nroRegistros), 1, file2); /* lê o nroRegistros do arquivo de indice */
    qtd = head->nroRegistros;
    rep = remover_registro(nome_file1, nome_campo, valor, nomeEscola, rrn, ERRO); /* remove o registro do arquivo de dados e retorna o numero de repeticoes que o campo possui */

    dado = (Dados_ind_PTR) malloc(head->nroRegistros*sizeof(Dados_ind));

    /* Carrega os indices para a memoria */
    while(i < head->nroRegistros){
        fseek(file2, TAM_PAGE+i*TAM_DAD_IND, SEEK_SET); /* pula entre os registros do arquivo de indice */
        pos = ler_stringDel(file2, dado[i].chaveBusca, '\0'); /* lê a string até encontrar o '\0'; retorna o numero de caracteres da chave */
        fseek(file2, 27-pos, SEEK_CUR); /* pula até o campo RRN */
        fread(&(dado[i].RRN), sizeof(dado[i].RRN), 1, file2); /* lê o campo RRN */
        i++;
    }

    pos = binarySearch(dado, 0, head->nroRegistros-1, nomeEscola); /* faz a busca binaria e retorna a posicao que o valor procurado se encontra */
    if(pos > 0){
        strcpy(str_aux, dado[pos].chaveBusca); /* str_aux representa o comparador para ter certeza de que encontrou todos os registros com essa mesma chave no arquivo de indice */
        while(pos > 0){
            if(strcmp(str_aux, dado[pos-1].chaveBusca) == 0) /* se é igual ao anterior, volta uma posicao */
                pos--;
            else /* se nao for, há a certeza que é o primeiro registro do arquivo de indice com essa chave */
                break;
        }
        i=0;
        pos_ant = pos; /* guarda a posicao inicial dos registros removidos do arquivo de indice */
        do{
            if(dado[pos].RRN == rrn[i]){
                dado[pos].RRN = -1; /* valor associado ao RRN para indicar que foi removido */
                dado[pos].chaveBusca[0] = '\0'; /* valor associado ao primeiro caractere da chaveBusca para indicar que foi removida */
                i++;
                pos = pos_ant; /* retorna a posicao para o valor inicial, para que procure o rrn seguinte do inicio */
            }
            pos++;
        }while(i < rep);
    }
    fclose(file2);
    fclose(file);
    if(ultimo){
        FILE* file3 = fopen(nome_file2, "wb+");
        /* Cabecalho */
        head = (Header_ind) malloc(sizeof(Cabecalho_ind));
        head->status = '0';
        head->nroRegistros = 0;
        escreve_cabecalhoInd(file3, head); /* escreve o cabecalho do arquivo de indice */
        preenche_registros(file3, TAM_IND, TAM_PAGE); /* preenche a primeira pagina de disco com '@' */

        /* Escreve no arquivo de indices */
        for(i = 0; i < qtd; i++){
            if(dado[i].RRN != -1)
                escreve_DadosInd(file3, &dado[i]); /* escreve no arquivo de indice */
        }
        fseek(file3, 0, SEEK_SET); /* volta para o inicio do arquivo de disco */
        head->status = '1'; /* altera o valor inicial do status do arquivo de indice */
        head->nroRegistros = qtd; /* atualiza o nroRegistros */
        escreve_cabecalhoInd(file3, head); /* escreve o novo cabecalho */
        binarioNaTela1(file3);
        fclose(file3);
    }
}

int binarySearch(Dados_ind_PTR arr, int l, int r, char* x){
    if(r >= l){
        int mid = l + (r - l) / 2;
        if (strcmp(arr[mid].chaveBusca, x) == 0){
            return mid;
        }
        if (strcmp(arr[mid].chaveBusca, x) > 0)
            return binarySearch(arr, l, mid - 1, x);
        return binarySearch(arr, mid + 1, r, x);
    }
    return 0;
}

void binarioNaTela1(FILE *ponteiroArquivoBinario){

	/* Escolha essa função se você ainda tem o ponteiro de arquivo 'FILE *' aberto.
	*  Lembrando que você tem que ter aberto ele no fopen para leitura também pra funcionar (exemplo: rb, rb+, wb+, ...) */
    /*char jmp = '\n';
    FILE *f;
    f = fopen("teste.txt", "w");*/
	unsigned char *mb;
	unsigned long i;
	size_t fl;
	fseek(ponteiroArquivoBinario, 0, SEEK_END);
	fl = ftell(ponteiroArquivoBinario);
	fseek(ponteiroArquivoBinario, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, ponteiroArquivoBinario);
	for(i = 0; i < fl; i += sizeof(unsigned char)) {
		printf("%02X ", mb[i]);
		//fprintf(f, "%02X ", mb[i]);
		if((i + 1) % 16 == 0)
            printf("\n");
            //fprintf(f, "%c", jmp);
	}
	free(mb);
    //fclose(f);
}
