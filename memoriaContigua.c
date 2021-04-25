#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define false 0
#define true 1

#define tamanho_da_memoria 12
int memoria_dispo = tamanho_da_memoria;
int numero_de_processos = 0;
int start = true;

typedef struct BlocoDeMemoria
{
    char id_do_processo[16];
} Bloco;

Bloco memoria[tamanho_da_memoria];


typedef struct Processo
{
    int endereco_inicial;
    int endereco_final;
    char processo_id[16];
    int memoria_requisitada;
} Processo;

void print(Processo processo);
void inicializarMemoria();

int first_fit(char algo[1], Processo *processo);
int best_fit(char algo[1], Processo *processo);
void status_report();
int first_fit(char algo[1], Processo *processo)
{
    int i, j, tamanho = 0;
    if (strcmp(algo, "F") == 0)
    {
        for (i = 0; i < tamanho_da_memoria; i++)
        {
            if (strcmp(memoria[i].id_do_processo, "-1") == 0)
            {
                tamanho = tamanho + 1;
                if (tamanho >= (processo->memoria_requisitada))
                {

                    //printf("tamanho: %i, processo: %i i: %i \n",tamanho,(processo->memoria_requisitada),i);
                    int aux = (i - (tamanho - 1));
                    for (j = aux; j <= i; j++)
                    {
                        strcpy(memoria[j].id_do_processo, processo->processo_id);
                        processo->endereco_inicial = aux;
                        processo->endereco_final = i;
                    }
                    return 1;
                }
            }
            else
            {
                tamanho = 0;
            }
        }
        printf("\n Infelizmente nao e' possivel alocar o processo: %s, de tamanho: %ikB !\n", processo->processo_id, processo->memoria_requisitada);
        return 0;
    }
    else
    {
        printf("\nPor favor insira um comando valido!\n");
        return 0;
    }
}

int best_fit(char algo[1], Processo *processo)
{
    int i, j, contiguous = 0;
    int aloc = false;
    int pivot = 999999;
    int endereco_inicial = 0;
    int endereco_final = 0;
    if (strcmp(algo, "B") == 0)
    {
        for (i = 0; i <= tamanho_da_memoria; i++)
        {
            if (strcmp(memoria[i].id_do_processo, "-1") == 0)
            {
                contiguous++;
                if ((aloc == false))
                {
                    aloc = true;
                }
            }
            else if (!(strcmp(memoria[i].id_do_processo, "-1") == 0) && (aloc == true))
            {
                if (contiguous < pivot && contiguous >= processo->memoria_requisitada)
                {
                    pivot = contiguous;
                    endereco_inicial = i - pivot;
                }
                contiguous = 0;
                aloc = false;
            }
        }
        if (pivot != 999999 && (pivot >= processo->memoria_requisitada))
        {
            int b;
            for (b = endereco_inicial; b < (endereco_inicial + (processo->memoria_requisitada)); b++)
            {
                strcpy(memoria[b].id_do_processo, processo->processo_id);
                processo->endereco_inicial = endereco_inicial;
                processo->endereco_final = (endereco_inicial + pivot);
            }
        }
        else
        {
            printf("\n Best:: Infelizmente nao e' possivel alocar o processo: %s, de tamanho: %ikB !\n", processo->processo_id, processo->memoria_requisitada);
        }
    }
}

int worst_fit(char algo[1], Processo *processo)
{
    int i, j, contiguous = 0;
    int aloc = false;
    int pivot = -1;
    int endereco_inicial = 0;
    int endereco_final = 0;
    if (strcmp(algo, "W") == 0)
    {
        for (i = 0; i <= tamanho_da_memoria; i++)
        {
            if (strcmp(memoria[i].id_do_processo, "-1") == 0)
            {
                contiguous++;
                if ((aloc == false))
                {
                    aloc = true;
                }
            }
            else if (!(strcmp(memoria[i].id_do_processo, "-1") == 0) && (aloc == true))
            {
                if (contiguous > pivot && contiguous >= processo->memoria_requisitada)
                {
                    pivot = contiguous;
                    endereco_inicial = i - pivot;
                }
                contiguous = 0;
                aloc = false;
            }
        }
        if (pivot != -1 && (pivot >= processo->memoria_requisitada))
        {
            int b;
            for (b = endereco_inicial; b < (endereco_inicial + (processo->memoria_requisitada)); b++)
            {
                strcpy(memoria[b].id_do_processo, processo->processo_id);
                processo->endereco_inicial = endereco_inicial;
                processo->endereco_final = (endereco_inicial + pivot);
            }
        }
        else
        {
            printf("\n Best:: Infelizmente nao e' possivel alocar o processo: %s, de tamanho: %ikB !\n", processo->processo_id, processo->memoria_requisitada);
        }
    }
}

void dealocar(char processo_id[16])
{
    int i = 0;
    while (i < tamanho_da_memoria)
    {
        if (strcmp(memoria[i].id_do_processo, processo_id) == 0)
        {
            printf("dealocando o processo: %s \n", processo_id);
            strcpy(memoria[i].id_do_processo, "-1");
        }
        i++;
    }
}

int main()
{
    if(start ==true){
        inicializarMemoria();
    }
    printf("+---------------------------------------------------+\n");
    printf("+------------------ Comandos -----------------------+\n");
    printf("+ 1. RQ Requisitar Memoria a um processo            +\n");
    printf("+ 2. RL Desalocar Processo                          +\n");
    printf("+ 3. ST Status do Processo/Processos                +\n");
    printf("+ @. [opcoes]                                       +\n");
    printf("+  1. [id do processso] [Algoritmo] [tamanho]KB     +\n");
    printf("+  2. [id do processso]                             +\n");
    printf("+  Ex: RQ P1 B 12                                   +\n");
    printf("+  Ex: RL P1                                        +\n");
    printf("+  Ex: ST P1                                        +\n");
    printf("+  Ex: ST                                           +\n");
    printf("+---------------------------------------------------+\n");
    printf("+  1. Requisitar Processo                           +\n");
    printf("+  2. Desalocar  Processo                           +\n");
    printf("+  3. Status                                        +\n");
    printf("+  4. Sair                                          +\n");
    printf("+---------------------------------------------------+\n");
    printf("+ Selecione uma das opcoes acima::> ");
    Processo processo;
    char opcao[12],algoritmo[1];
    gets(opcao);

    if(strcmp(opcao, "1") == 0){
        start = false;
        printf("+ ID do processo::>  RQ --");
        gets(processo.processo_id);
        
        printf("+ Tamanho do processo::> ");
        scanf("%i",&processo.memoria_requisitada);
        scanf("%*c");
        printf("+ Algoritmo::> ");
        gets(algoritmo);
        printf("algo,%s", algoritmo);
        print(processo);
        if(strcmp(algoritmo,"F")==0){
            first_fit(algoritmo, &processo);
            status_report();
        }
        else if (strcmp(algoritmo, "B")==0)
        {
            best_fit(algoritmo, &processo);
            status_report();
        }
        else if (strcmp(algoritmo, "W")==0)
        {
            worst_fit(algoritmo, &processo);
            status_report();
        }
    }
    else if (strcmp(opcao, "2") == 0){
        char processo_id[16];
        printf("+ ID do processo::>  RL --");
        gets(processo_id);
        dealocar(processo_id);
        status_report();
    }
    else if(strcmp(opcao, "3") == 0) {
        status_report();
    }else{
        return 0;
    }

    /**
     * [RQ] == requisitar memoria para processo [P1]
     * com o algoritmo [B] best fit de tamanho [4] 4kilobytes(kb).
     * [RL]  desolocar processo [P1] da memoria.
     * [ST] mostart status da memoria.
     * [ST P1] mostrar status do processo [P1]
     **/
    return 0;
}

void print(Processo processo)
{
    printf("+ Id do processo: %s      \n", processo.processo_id);
    printf("+ Endereco inicial: %i    \n", processo.endereco_inicial);
    printf("+ Endereco final: %i      \n", processo.endereco_final);
    printf("+ Tamanho do processo: %ikB \n", processo.memoria_requisitada);
}

void inicializarMemoria()
{
    int i;
    for (i = 0; i < tamanho_da_memoria; i++)
    {
        strcpy(memoria[i].id_do_processo, "-1");
    }
}

void status_report()
{
    int i;
    for (i = 0; i < tamanho_da_memoria;i++){
        if(strcmp(memoria[i].id_do_processo, "-1") == 0){
            printf("%i. [  ] \n", i);
        }else
        printf("%i. [processo_id: \' %s \' ] \n",i,memoria[i].id_do_processo);
    }
    system("pause");
    system("cls");
    main();
}
