#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { // struct que guarda todos os usuarios
    int id;
    char nome[100];
    int idade;
    int saldo_atual;
}User;

User* users = NULL; // declaração de um ponteiro para fazer a alocação de memória, declara com null pq no momento ele não aponta para nada
int user_count = 0;
int next_id = 1;


void menu(){
    int opc;
    printf("\n(1) Inserção de um novo usuário.\n(2) Inserção de varios usuários.\n(3) Busca de usuário por id.\n(4) Transferência entre usuários.\n(5)Remoção de um usuário.\n(6) Sair.\n\n");
    printf("Por favor, selecione a opção desejada: ");
    scanf("%d", &opc);
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

void buscarid() {
    int id;
    printf("\nInsira o ID do usuário que deseja buscar: ");
    scanf("%d", &id);
    int existe = 0;
    for (int i = 0; i < user_count; i++) {
        if (users[i].id == id) {
            printf("\nUsuário encontrado: %s %d, %.2f",users[i].nome, users[i].idade, users[i].saldo_atual);
            existe = 1;
        }
    }
    if (!existe) {
        printf("\nUsuário com ID %d não encontrado.\n", id);
    }
}

void remocao(int id) {
}

typedef struct trasnf{
int *id_origem, *id_destino;
id_origem = &Users.id;
id_destino = &Users.id;
float quantia;
} transf;

void transf (){
        int opc;
    do{
        printf ("Digite o Id de destino:\n");
        Users[

        
    //scanf ("%d", &transf.id_destino);
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
            Users.saldo_atual [id_destino] = saldoatual + quantia;
            printf ("Transferencia realizada com sucesso.")
            printf ("Deseja realizar outra transferencia? 1(SIM) 2(NAO)")
        }
     while (opc==1)

        }
    }
}



int main() {
    int nova = 0;
    printf("Seja bem-vindo(a) ao UaiBank!\n");
    menu();
    do {
        printf("\nDeseja realizar uma nova ação?\n(1)Sim (2)Não\n");
        scanf("%d", &nova);
        switch (nova) {
            case 1:
                menu();
                break;
            case 2:
                break;
            default:
                printf("\nOpção inválida! Por favor, insira outra opção.\n");
                break;
        }
    } while (nova != 2);

    printf("\nObrigado por utilizar o UaiBank!!!\n");
    printf("\nSaindo...");
    return 0;
}

