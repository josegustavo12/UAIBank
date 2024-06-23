#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
    int id;
    char nome[100];
    int idade;
    float saldo;
} cadastro;

typedef struct {
    int id_origem;
    int id_destino;
    float quantia;
} transf;

cadastro* usuarios = NULL;
int cont_usuarios = 0;
int prox_id = 1;

void insercaounica() {
    int idade;
    float saldo;
    char nome[100];

    printf("\nDigite o Nome, A idade e o Saldo: \n");
    scanf("%99s %d %f", nome, &idade, &saldo);

    cadastro* novo_usuarios = realloc(usuarios, (cont_usuarios + 1) * sizeof(cadastro));
    if (novo_usuarios == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(1);
    }
    usuarios = novo_usuarios;

    usuarios[cont_usuarios].id = prox_id;
    strcpy(usuarios[cont_usuarios].nome, nome);
    usuarios[cont_usuarios].idade = idade;
    usuarios[cont_usuarios].saldo = saldo;

    cont_usuarios++;
    prox_id++;
}

void insercaovarios() {
    int n;
    printf("\nQuantos usuários deseja?\n");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        insercaounica();
    }
}

cadastro* buscarid(int id) {
    for (int i = 0; i < cont_usuarios; i++) {
        if (usuarios[i].id == id) {
            return &usuarios[i];
        }
    }
    return NULL;
}

void transferencia() {
    transf t;
    int opc;
    FILE *arqtransf;

    do {
        printf("\n\nDigite o Id de origem, o Id de Destino e a quantia que deseja transferir:\n");
        scanf("%d %d %f", &t.id_origem, &t.id_destino, &t.quantia);

        cadastro* origem = buscarid(t.id_origem);
        if (origem == NULL) {
            printf("Id de origem não existente. Digite um Id válido.\n");
            continue;
        }

        cadastro* destino = buscarid(t.id_destino);
        if (destino == NULL) {
            printf("Id de destino não existente. Digite um Id válido.\n");
            continue;
        }

        if (origem->saldo < t.quantia) {
            printf("Não foi possível realizar a transferência. Saldo insuficiente.\n");
        } else {
            origem->saldo -= t.quantia;
            destino->saldo += t.quantia;
            printf("Transferência realizada com sucesso.\n");
            arqtransf = fopen("arqtransf.txt", "a");
            if (arqtransf != NULL) {
                fprintf(arqtransf, "%s, %d, %s, %d, %.2f\n", origem->nome, origem->id, destino->nome, destino->id, t.quantia);
                fclose(arqtransf);
            } else {
                printf("Erro ao abrir o arquivo de transferência.\n");
            }
        }

        printf("Deseja realizar outra transferência? 1(SIM) 2(NAO)\n");
        scanf("%d", &opc);
    } while (opc == 1);
}

void remocao(int id) {
    int num = -1;
    cadastro* remocao = buscarid(id);
    if (remocao == NULL) {
        printf("Usuário não encontrado\n");
        return;
    }

    for (int i = 0; i < cont_usuarios; i++) {
        if (usuarios[i].id == id) {
            num = i;
            break;
        }
    }

    if (num != -1) {
        for (int i = num; i < cont_usuarios - 1; i++) {
            usuarios[i] = usuarios[i + 1];
        }
        cont_usuarios--;

        cadastro* novo_usuarios = realloc(usuarios, cont_usuarios * sizeof(cadastro));
        if (novo_usuarios == NULL && cont_usuarios > 0) {
            fprintf(stderr, "\nErro ao realocar memória.\n");
            exit(1);
        }
        usuarios = novo_usuarios;

        printf("\nUsuário removido com sucesso.\n");
    } else {
        printf("\nUsuário não encontrado.\n");
    }
}

void salvarusuarios() {
    FILE *arquivo = fopen("usuarios.txt", "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo usuarios.txt.\n");
        exit(1);
    }

    for (int i = 0; i < cont_usuarios; i++) {
        fprintf(arquivo, "%d, %s, %d, %.2f\n", usuarios[i].id, usuarios[i].nome, usuarios[i].idade, usuarios[i].saldo);
    }

    fclose(arquivo);
}

void carregarusuarios() {
    FILE *arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo de usuários encontrado. Continuando sem carregar dados.\n");
        return;
    }

    while (1) {
        cadastro novo_usuario;
        if (fscanf(arquivo, "%d, %99[^,], %d, %f\n", &novo_usuario.id, novo_usuario.nome, &novo_usuario.idade, &novo_usuario.saldo) != 4) {
            break;
        }

        cadastro* novo_usuarios = realloc(usuarios, (cont_usuarios + 1) * sizeof(cadastro));
        if (novo_usuarios == NULL) {
            fprintf(stderr, "Erro ao alocar memória.\n");
            exit(1);
        }
        usuarios = novo_usuarios;

        usuarios[cont_usuarios] = novo_usuario;

        if (novo_usuario.id >= prox_id) {
            prox_id = novo_usuario.id + 1;
        }
        cont_usuarios++;
    }

    fclose(arquivo);
}

void menu() {
    int opc;
    printf("\n(1) Inserção de um novo usuário.\n(2) Inserção de varios usuários.\n(3) Busca de usuário por id.\n(4) Transferência entre usuários.\n(5) Remoção de um usuário.\n(6) Sair.\n\n");

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

        case 3: {
            int id;
            printf("\nOpção 3 selecionada: Busca de usuário por id.\n");
            printf("Digite o ID do usuário que deseja buscar: ");
            scanf("%d", &id);
            cadastro* encontrado = buscarid(id);
            if (encontrado != NULL) {
                printf("\nUsuário encontrado:\n");
                printf("%d, %s, %d, %.2f\n", encontrado->id, encontrado->nome, encontrado->idade, encontrado->saldo);
            } else {
                printf("\nUsuário com ID %d não encontrado.\n", id);
            }
            break;
        }

        case 4:
            printf("\nOpção 4 selecionada: Transferência entre usuários.\n");
            transferencia();
            break;

        case 5: {
            int id;
            printf("\nOpção 5 selecionada: Remoção de um usuário.\n");
            printf("Digite o ID do usuário que deseja remover: ");
            scanf("%d", &id);
            remocao(id);
            break;
        }

        case 6:
            printf("\nSaindo...\nObrigado por utilizar o UaiBank!!!\n");
            salvarusuarios();
            free(usuarios);
            exit(0);

        default:
            printf("\nOpção inválida.\n");
            break;
    }
}

int main() {
    carregarusuarios();
    printf("Seja bem-vindo(a) ao UaiBank!\n");

    int opc;
    do {
        menu();
        printf("\nDeseja realizar outra ação? 1 [SIM] 2 [NÃO]\n");
        scanf("%d", &opc);
    } while (opc == 1);

    printf("\nObrigado por utilizar o UaiBank!!!\n");
    salvarusuarios();
    free(usuarios);
    return 0;
}
