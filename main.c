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

void menu(int opc){
    switch (opc) {
        case 1:
            printf("\nOpção 1 selecionada: Inserção de um novo usuário.\n");
            insercaounica();
            break;
        case 2:
            printf("\nOpção 2 selecionada: Inserção de varios usuários.\n");
            insercaovarios();
            break;
        case 3:
            printf("\nOpção 3 selecionada: Busca de usuário por id.\n");
            buscarid();
            break;
        case 5:
            printf("\nOpção 5 selecionada: Remoção de um usuário.\n");
            remocao();
            break;
        case 6:
            printf("\nSaindo...");
            break;
        default:
            printf("\nOpção inválida.\n");
            break;
    }
}

void insercaounica() {
    char nome[100];
    int idade;
    float saldo_atual;
    printf("\nNome, Idade, Saldo atual:\n");
    scanf("%s, %d, %f", &nome, &idade, &saldo_atual);
    users = realloc(users, (user_count + 1) * sizeof(User));
    users[user_count].id = next_id++;
    strcpy(users[user_count].nome, nome);
    users[user_count].idade = idade;
    users[user_count].saldo_atual = saldo_atual;
    user_count++;
    printf("\n======================Inserção realizada com sucesso======================\n");
}

void insercaovarios(int qnt_usuarios, char* nomes[], int idades[], int saldos[]) {
    for (int i = 0; i < qnt_usuarios; i++) {
        insercaounica(nomes[i], idades[i], saldos[i]);
    }
}

void buscarid(User *users) {
    int id;
    printf("Por favor, insira o id que deseja buscar: ");
    scanf("%d", &id);
    while (users->id != -1) {
        if (users->id == id) {
            printf("Usuário encontrado: %s, %d, %.2f\n", users->nome, users->idade, users->saldo_atual);
            return;
        }
        users++;
    }
    printf("Usuário não encontrado\n");
}


void remocao(int id) {
}

int main() {
    int redo = 1;
    int opc;

    do{printf("Seja bem-vindo(a) ao UaiBank!\n");
        printf("Por favor, selecione a opção desejada:");
        printf("\n(1) Inserção de um novo usuário.\n(2) Inserção de varios usuários.\n(3) Busca de usuário por id.\n(4) Transferência entre usuários.\n(5)Remoção de um usuário.\n(6) Sair.\n\n");
        scanf("%d", &opc);
        menu(opc);
        printf("Deseja realizar uma nova ação?\n(1) Sim (2) Não\n\n");
        scanf("%d", &redo);
    }while(redo==1);
    printf("\nObrigado por utilizar o UaiBank!!!");
    return 0;
}
