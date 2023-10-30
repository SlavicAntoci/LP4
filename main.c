#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Bank{
    char codBanca[6],codClient[11],dataOperatiune[11],sumaOperatiune[17];
    struct Bank* next;
}Bank;
Bank * bank = NULL;
struct client{
    char codBanca[6],codClient[11];
    double sumaOperatiuni;
};
void print(){
    Bank* curent = bank;
    while (curent!=NULL){
        printf("%s,%s,%s,%s\n", curent->codBanca,curent->codClient,curent->dataOperatiune,curent->sumaOperatiune);
        curent = curent->next;
    }
}

void insertBank (char *codbanca,char * codclient,char * dataoperatiune,char * sumaoperariune){
    Bank * nou = malloc(sizeof (Bank));
    if(nou == NULL){
        printf("eroare la alocare");
        return;
    }
    strcpy(nou->codClient,codclient);
    strcpy(nou->codBanca,codbanca);
    strcpy(nou->dataOperatiune,dataoperatiune);
    strcpy(nou->sumaOperatiune,sumaoperariune);
    nou->next = bank;
    bank = nou;
}

int main() {
    FILE* file = fopen("C:\\Users\\User\\CLionProjects\\LI4\\ex1.txt","r");
    if(file ==NULL){
        printf("Eroare la deschiderea fisierului");
        return 1;
    }
    char line[48];
    while (fgets(line, sizeof(line), file)){
        Bank *nouaInregistrare = malloc(sizeof(Bank));
        if (nouaInregistrare == NULL) {
            printf( "Eroare la alocarea memoriei \n");
            return 1;
        }
        strncpy(nouaInregistrare->codBanca,line,5);
        nouaInregistrare->codBanca[5] = '\0';
        strncpy(nouaInregistrare->codClient,line+5,10);
        nouaInregistrare->codClient[10] = '\0';
        strncpy(nouaInregistrare->dataOperatiune,line+15,10);
        nouaInregistrare->dataOperatiune[10] = '\0';
        strncpy(nouaInregistrare->sumaOperatiune,line+25,16);
        nouaInregistrare->sumaOperatiune[16] = '\0';

        insertBank(nouaInregistrare->codBanca,nouaInregistrare->codClient,nouaInregistrare->dataOperatiune,nouaInregistrare->sumaOperatiune);
    }
    fclose(file);

    int i = 0;
    struct client clienti[10];
    Bank* curentBank = bank;
    while (curentBank != NULL) {
        int exist = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(clienti[j].codClient, curentBank->codClient) == 0) {
                exist = 1;
                clienti[j].sumaOperatiuni += strtod(curentBank->sumaOperatiune,NULL);
                break;
            }
        }
        if (!exist) {
            strcpy(clienti[i].codBanca, curentBank->codBanca);
            strcpy(clienti[i].codClient, curentBank->codClient);
            clienti[i].sumaOperatiuni = strtod(curentBank->sumaOperatiune,NULL);
            i++;
        }
        curentBank = curentBank->next;
    }
    FILE * output = fopen("C:\\Users\\User\\CLionProjects\\LI4\\output.txt","w");
    if(output == NULL){
        printf("Eroare la deschiderea fisierului");
        return 1;
    }
    double sumaTot = 0;
    for (int j = 0; j < i; j++) {
        fprintf(output,"%s %s %.3lf\n",clienti[j].codBanca,clienti[j].codClient,clienti[j].sumaOperatiuni);
        sumaTot += clienti[j].sumaOperatiuni;
    }
    fprintf(output , "%s 9999999999 %.3lf\n",clienti[0].codBanca,sumaTot);
    fclose(output);
    printf("Datele din lista\n");
    print();
    printf("-----------------------\n");
    printf("date despre clienti\n");
    for (int j = 0; j < i; j++) {
       printf("%s %s %.3lf\n",clienti[j].codBanca,clienti[j].codClient,clienti[j].sumaOperatiuni);
    }
    while (bank != NULL){
        Bank* temp = bank;
        bank = bank->next;
        free(bank);
    }
    return 0;
}