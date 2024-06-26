#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


typedef struct {
    int id;
    char nome[100];
    int idade;
    float saldo;
} cadastro; //struct para armazenar os dados de um usuário

typedef struct {
    int id_origem;
    int id_destino;
    float quantia;
} transf; // struct para armazenar as informações necessárias para uma transferência

cadastro* usuarios = NULL; // ponteiro para armazenar os usuários
int cont_usuarios = 0; // contador de usuário
int prox_id = 1; // próximo ID a ser atribuído

void insercaounica() {
    int idade;
    float saldo;
    char nome[100];

    printf("\nDigite o Nome, A idade e o Saldo: \n");
    scanf(" %99[^,], %d, %f", nome, &idade, &saldo);

    usuarios = realloc(usuarios, (cont_usuarios + 1) * sizeof(cadastro)); // alocando  memória à variável usuarios conforme a inserção de novos usuários

    if (usuarios == NULL) {

        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(1);
    }

    usuarios[cont_usuarios].id = prox_id; //atribuindo ID para os usuários
    strcpy(usuarios[cont_usuarios].nome, nome); //armazenando o nome recebido pelo usuário na variável "usuários"
    usuarios[cont_usuarios].idade = idade; // armazenando a idade recebida pelo usuário na variável "usuários"
    usuarios[cont_usuarios].saldo = saldo; // armazenando o saldo recebido pelo usuário na variável "usuários"

    cont_usuarios++; //adicionando um a contagem de usuários
    prox_id++; //adicionando um ao ID do próximo usuário
    printf("\nUsuário inserido com sucesso\n");
}

void insercaovarios() {
    int n;
    printf("\nQuantos usuários deseja?\n");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {

        insercaounica();//chama a função inserção única
    }
}

cadastro* buscarid(int id) {
    for (int i = 0; i < cont_usuarios; i++) {

        if (usuarios[i].id == id) {

            return &usuarios[i]; //retorna todos os dados do usuário buscado
        }
    }
    return NULL;
}

void transferencia() {
    transf t; //declarando a variável "t" como sendo do tipo struct transf
    int opc;
    FILE *arqtransf;

    do {
        printf("\n\nDigite o Id de origem, o Id de Destino e a quantia que deseja transferir:\n");
        scanf("%d, %d, %f", &t.id_origem, &t.id_destino, &t.quantia); //armazenando o Id de Origem digitado na varíavel da struct de transferência

        cadastro* origem = buscarid(t.id_origem); //declarando e inicializando a variável "origem" ao chamar a função para ver se o Id informado de fato existe

        if (origem == NULL) {

            printf("Id de origem não existente. Digite um Id válido.\n");
            continue;
        }



        cadastro* destino = buscarid(t.id_destino);

        if (destino == NULL) {

            printf("Id de destino não existente. Digite um Id válido.\n");
            continue;
        }
/*
. é utilizado para variaveis diretas para chamar na struct
-> é utilizado para ponteiros para chamar na struct
*/

        if (origem->saldo < t.quantia) { //verificando se o saldo do Id de origem é suficiente para realizar a transferência

            printf("Não foi possível realizar a transferência. Saldo insuficiente.\n");
        }
        else {

            origem->saldo -= t.quantia;
            destino->saldo += t.quantia;
            printf("Transferência realizada com sucesso.\n");
            arqtransf = fopen("arqtransf.txt", "a");
            fprintf(arqtransf,"%s, %d, %s, %d, %.2f\n\n ",origem->nome, origem->id, destino->nome, destino->id, t.quantia);
            fclose(arqtransf);
            }
        printf("Deseja realizar outra transferência? 1(SIM) 2(NAO)\n");
        scanf("%d", &opc);
    } while (opc == 1);
}

void remocao(int id){
    int num=-1;
    cadastro* remocao = buscarid(id);
     if (remocao == NULL) {
        printf("Usuário não encontrado\n");
        return;
    }

    // Encontra a posição do usuário no array
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

        usuarios = realloc(usuarios, cont_usuarios * sizeof(cadastro));

        printf("\nUsuário removido com sucesso.\n");
    }
    else {
        printf("\nUsuário não encontrado.\n");
    }
}

void salvarusuarios() {
    FILE *arquivo;
    arquivo = fopen("usuarios.txt", "w"); // abre o arquivo txt sempre no modo w pq ele reescreve toda vez

    if (arquivo == NULL) {

        fprintf(stderr, "Erro ao abrir o arquivo usuarios.txt.\n");
        exit(1);
    }
    for (int i = 0; i < cont_usuarios; i++) {

        fprintf(arquivo, "%d,%s,%d,%.2f\n", usuarios[i].id, usuarios[i].nome, usuarios[i].idade, usuarios[i].saldo);
    }

    fclose(arquivo);
}



void carregarusuarios() {
    setlocale(LC_NUMERIC, ""); // é usado para definir os pontos flutuantes com . ao invez de , do portugues
    FILE *arquivo;
    arquivo = fopen("usuarios.txt", "r");

    if (arquivo == NULL) {
        printf("Nenhum arquivo de usuários encontrado. Continuando sem carregar dados.\n");
        return;
    }

    while (1) {
        cadastro temp; // struct temporaria de cadastro
        if (fscanf(arquivo, "%d,%99[^,],%d,%f", &temp.id, temp.nome, &temp.idade, &temp.saldo) != 4) {
            break; // Sai do loop se a leitura falhar
        }

        usuarios = realloc(usuarios, (cont_usuarios + 1) * sizeof(cadastro)); // aloca memória para mais um usuário
        if (usuarios == NULL) {
            fprintf(stderr, "Erro ao alocar memória.\n");
            exit(1);
        }

        usuarios[cont_usuarios] = temp; // copia a struct temporaria para o ponteiro geral

        if (temp.id >= prox_id) {
            prox_id = temp.id + 1; // aumenta o id
        }
        cont_usuarios++; // incrementa o contador de usuários
    }

    fclose(arquivo);
}

void menu() {
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
            {
            int id;
            printf("\nOpção 3 selecionada: Busca de usuário por id.\n");
            printf("Digite o ID do usuário que deseja buscar: ");
            scanf("%d", &id);
            cadastro* encontrado = buscarid(id); // cria um um ponteiro para a localização daquela struct
            if (encontrado != NULL){
                printf("\nUsuário encontrado:\n");
                printf("%d, %s, %d, %.2f", encontrado->id, encontrado->nome, encontrado->idade, encontrado->saldo);
            }
            else {
                printf("\nUsuário com ID %d não encontrado.\n", id);
            }
            break;
        }

        case 4:
            printf("\nOpção 4 selecionada: Transferência entre usuários.\n");
            transferencia();
            break;

        case 5:
            printf("\nOpção 5 selecionada: Remoção de um usuário.\n");
            int id;
            printf("Digite o ID do usuário que deseja remover: ");
            scanf("%d", &id);
            remocao(id);
            break;

        case 6:
            printf("\nSaindo...");
            printf("\nObrigado por utilizar o UaiBank!!!\n");
            exit(0);
            break;

        default:
            printf("\nOpção inválida.\n");
            break;
    }
}

int nova(){
    int opc;
    printf("\nDeseja realizar outra ação? 1 [SIM] 2 [NÃO]\n");
    scanf("%d", &opc);
    if(opc==1){
        return 1;
    }
    else if(opc==2){
        printf("\nObrigado por utilizar o UaiBank!!!\n");
        printf("Saindo...\n");
        salvarusuarios();
        free(usuarios);
        exit(0);
    }
    else{
        printf("\nOpção inválida.\n");
        opc=nova();
    }
}


int main() {

    carregarusuarios(); // inicia carregando todos os usuarios
    int opc = 0;
    setlocale(LC_ALL, "Portuguese");

    printf("Seja bem-vindo(a) ao UaiBank!\n");

    do{
        menu();
        opc=nova();
        if(opc!=2 && opc!=1){
            printf("\nOpção inválida.\n");
            opc=nova();
        }
    } while (opc==1);
    printf("\nObrigado por utilizar o UaiBank!!!\n");
    salvarusuarios();
    free(usuarios); // libera a memória alocada
    return 0;
}
