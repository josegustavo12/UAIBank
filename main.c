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

User* buscarid(int id) {
}

void transferencia(int id_origem, int id_destino, int quantia) {
}

void remocao(int id) {
}

int main() {

    return 0;
}
