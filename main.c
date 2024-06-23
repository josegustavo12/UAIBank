#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    scanf("%s %d %f", nome, &idade, &saldo);

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

    do {
        printf("Digite o Id de origem:\n");
        scanf("%d", &t.id_origem); //armazenando o Id de Origem digitado na varíavel da struct de transferência

        cadastro* origem = buscarid(t.id_origem); //declarando e inicializando a variável "origem" ao chamar a função para ver se o Id informado de fato existe

        if (origem == NULL) {
            
            printf("Id de origem não existente. Digite um Id válido.\n");
            continue;
        }

        printf("Digite o Id de destino:\n");
        scanf("%d", &t.id_destino);

        cadastro* destino = buscarid(t.id_destino);

        if (destino == NULL) {
            
            printf("Id de destino não existente. Digite um Id válido.\n");
            continue;
        }

        printf("Digite a quantia a ser transferida:\n");
        scanf("%f", &t.quantia);

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
        }

        printf("Deseja realizar outra transferência? 1(SIM) 2(NAO)\n");
        scanf("%d", &opc);

    } while (opc == 1);
}

void remocao(int id){
    int num;
    cadastro* remocao = buscarid(id);
    for (int i = 0; i < cont_usuarios; i++) {

        if (usuarios[i].id == id) {
            num=i;
        }
    }
    if(remocao==NULL){
        printf("Usuário não encontrado");
        return NULL;
    }
    else{
        if (num >= 0 && num < cont_usuarios){ 
        int i;
        for (i = num;i < cont_usuarios - 1; ++i){
            usuarios[i] = usuarios[i + 1];
        }

        usuarios = realloc(usuarios, --num * sizeof(cadastro)); //reduzir o tamanho do array em 1 unidade
    }
}
    }

void salvarusuarios() {
    FILE *arquivo;
    arquivo = fopen("usuarios.txt", "w");

    if (arquivo == NULL) {
        
        fprintf(stderr, "Erro ao abrir o arquivo usuarios.txt.\n");
        exit(1);
    }

    for (int i = 0; i < cont_usuarios; i++) {
        
        fprintf(arquivo, "%d, %s, %d, %.2f\n", usuarios[i].id, usuarios[i].nome, usuarios[i].idade, usuarios[i].saldo);
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

            if (encontrado != NULL) {
                
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


int main() {
    int opc = 0;

    printf("Seja bem-vindo(a) ao UaiBank!\n");

    do {
        menu();
        printf("\nDeseja realizar outra ação? 1 [SIM] 2 [NÃO]\n");
        scanf("%d", &opc);

    } while (opc != 2);

    printf("\nObrigado por utilizar o UaiBank!!!\n");
    salvarusuarios();
    free(usuarios); // libera a memória alocada

    return 0;
}
