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
            printf("Opção 1 selecionada: Inserção de um novo usuário.\n");
            insercaounica();
            break;
        case 2:
            printf("Opção 2 selecionada: Inserção de varios usuários.\n");
            insercaovarios();
            break;
        case 3:
            printf("Opção 3 selecionada: Busca de usuário por id.\n");
            buscarid();
            break;
        case 4:
            printf("Opção 4 selecionada: Transferência entre usuários.\n");
            transferencia();
            break;
        case 5:
            printf("Opção 5 selecionada: Remoção de um usuário.\n");
            remocao();
            break;
        case 6:
            printf("Obrigado por utilizar o UaiBank!\nSaindo...");
            break;
        default:
            printf("Por favor, insira uma opção válida.\n");
            menu();
            break;
    }
}

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
    int redo = 1;

    do{printf("Seja bem-vindo(a) ao UaiBank!\n");
        printf("Por favor, selecione a opção desejada:");
        printf("\n(1) Inserção de um novo usuário.\n(2) Inserção de varios usuários.\n(3) Busca de usuário por id.\n(4) Transferência entre usuários.\n(5)Remoção de um usuário.\n(6) Sair.");
        scanf("%d", &opc);
        menu(opc);
        printf("Deseja realizar uma nova ação?\n(1) Sim\n(2) Não");
        scanf("%d", &redo);
    }while(redo==1);
    printf("Obrigado por utilizar o UaiBank!");
    return 0;
}
