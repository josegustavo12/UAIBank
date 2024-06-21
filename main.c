#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { // struct que guarda todos os usuarios
    int id;
    char nome[100];
    int idade;
    int saldo_atual;
} User;

User* users = NULL; // declaração de um ponteiro para fazer a alocação de memória, declara com null pq no momento ele não aponta para nada
int user_count = 0;
int next_id = 1;

typedef struct trasnf{
int id_origem, id_destino;
float quantia;
} transf;

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
    scanf("%s %d %f", nome, &idade, &saldo_atual);
    users = realloc(users, (user_count + 1) * sizeof(User));
    users[user_count].id = next_id++;
    strcpy(users[user_count].nome, nome);
    users[user_count].idade = idade;
    users[user_count].saldo_atual = saldo_atual;
    user_count++;
    printf("\n======================Inserção realizada com sucesso======================\n");
}

void insercaovarios() {
    int n;
    printf("\nQuantos usuários deseja?\n");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        insercaounica();
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

void transf (){
        int opc;
    do{
        printf ("Digite o Id de destino:\n");
    scanf ("%d", &transf.id_destino);
    if (id_destino == NULL){
        printf ("Id não existente. Digite um Id válido");
    }
    else {
        printf ("Digite a quantia a ser transferida:\n");
        scanf ("%f", &transf.quantia);
        if (Users[user_count].saldo_atual < transf.quantia){
            printf ("Não foi possível realizar a transferencia. Saldo insuficiente.")
        }
        else {
            Users[usar_count].saldo_atual= Users[usar_count].saldo_atual- transf.quantia;
            saldo [id_destino] = saldoatual + quantia;
            printf ("Transferencia realizada com sucesso.")
            printf ("Deseja realizar outra transferencia? 1(SIM) 2(NAO)")
        }
     while (opc==1)

        }
    }
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

