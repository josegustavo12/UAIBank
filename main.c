#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[100];
    int idade;
    int saldo_atual;
} User;

User* users = NULL;
int user_count = 0;
int next_id = 1;

struct trasnf{
int idorigem, iddestino;
float quantia;
};

void insercaounica(char* nome, int idade, int saldo_atual) {

    users = realloc(users, (user_count + 1) * sizeof(User));
    users[user_count].id = next_id++;
    strcpy(users[user_count].nome, nome);
    users[user_count].idade = idade;
    users[user_count].saldo_atual = saldo_atual;
    user_count++;
}

void insercaovarios(int qnt_usuarios, char* nomes[], int idades[], int saldos[]) {
    for (int i = 0; i < qnt_usuarios; i++) {
        insercaounica(nomes[i], idades[i], saldos[i]);
    }
}

void buscarid(int id) {
}

void transferencia(int id_origem, int id_destino, int quantia) {
     int opc;
    do{
        printf ("Digite o Id de destino:\n");
    scanf ("%d", &iddestino);
    if (iddestino == NULL){
        printf ("Id não existente. Digite um Id válido");
    }
    else {
        printf ("Digite a quantia a ser transferida:\n");
        scanf ("%f", &quantia);
        if (saldo[Idorigem]<quantia){
            printf ("Não foi possível realizar a transferencia. Saldo insuficiente.")
        }
        else {
            saldo[IdOrigem]= saldoatual - quantia;
            saldo [IdDestino] = saldoatual + quantia;
            printf ("Transferencia realizada com sucesso.")
            printf ("Deseja realizar outra transferencia? 1(SIM) 2(NAO)")
        }
     while (opc==1)
           
        }
    }
}

void remocao(int id) {
}

int main() {
    int opc;
    do{
        printf ("Digite o Id de destino:\n");
    scanf ("%d", &iddestino);
    if (iddestino == NULL){
        printf ("Id não existente. Digite um Id válido");
    }
    else {
        printf ("Digite a quantia a ser transferida:\n");
        scanf ("%f", &quantia);
        if (saldo[Idorigem]<quantia){
            printf ("Não foi possível realizar a transferencia. Saldo insuficiente.")
        }
        else {
            saldo[IdOrigem]= saldoatual - quantia;
            saldo [IdDestino] = saldoatual + quantia;
            printf ("Transferencia realizada com sucesso.")
            printf ("Deseja realizar outra transferencia? 1(SIM) 2(NAO)")
        }
     while (opc==1)
           
        }
    }
    return 0;
}
