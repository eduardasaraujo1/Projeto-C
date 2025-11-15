#include <stdio.h>
#define maximo 100   //serve para definir o tamanho máximo do vetor que armazena os produtos

struct produto {
    int codigo;
    char nome[30];
    float preco;
    int quantidade;
};

//declarando funções que serão usadas no main():
int ler(struct produto produtos[]);   //número de produtos lidos do arquivo
void adicionar(struct produto produtos[], int *n);   //adiciona um novo produto ao vetor 
void buscar(struct produto produtos[], int n);   //procura um produto pelo código e exibe suas informações
void imprimir(struct produto produtos[], int n);   //imprime na tela todos os produtos armazenados no vetor
void ordenar(struct produto produtos[], int n);   //ordena os produtos em ordem crescente de preço

int main() {
    struct produto produtos[maximo];   //vetor que armazena todos os produtos
    int n = 0;   //quantidade atual de produtos
    int escolha;   //escolha do usuário no menu

    //lê os produtos do arquivo produtos.txt e armazena no vetor
    n = ler(produtos);

    //opções do menu
    do {
        printf("MENU:\n");
        printf("1. Adicione o produto\n");
        printf("2. Buscar produto por codigo\n");
        printf("3. Imprimir produtos\n");
        printf("4. Ordenar por preco e imprimir\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);   //entrada da escolha do usuário

        //verifica qual número o usuário digitou e executa o bloco correspondente
        switch (escolha) {
            case 1:
                adicionar(produtos, &n);
                break;
            case 2:
                buscar(produtos, n);
                break;
            case 3:
                imprimir(produtos, n);
                break;
            case 4:
                ordenar(produtos, n);
                imprimir(produtos, n);
                break;
            case 5:
                printf("Encerrando o programa\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    } while (escolha != 5);

    return 0;
}
   
int ler(struct produto produtos[]) {
    FILE *arquivo = fopen("produtos.txt", "r");   //abre o arquivo no modo leitura ("r")
    if (arquivo == NULL) {   //teste para ver se o arquivo abriu
        printf("Erro ao abrir o arquivo produtos.txt\n");
        return 0;
    }

    int i = 0;
    while (fscanf(arquivo, "%d %s %f %d",   //lê cada linha do arquivo enquanto conseguir ler 4 valores
                  &produtos[i].codigo,
                  produtos[i].nome,
                  &produtos[i].preco,
                  &produtos[i].quantidade) == 4) {   //a quantidade de valores lidos com sucesso
        i++;   //faz o programa ir preenchendo o vetor de produtos posição por posição
    }

    fclose(arquivo);
    return i;
}

//função para adicionar novo produto
void adicionar(struct produto produtos[], int *n) {
    if (*n >= maximo) {   //verifica se o vetor está cheio
        printf("Limite maximo de produtos atingido!\n");
        return;
    }
  
    printf("Codigo: "); 
    scanf("%d", &produtos[*n].codigo);
    printf("Nome: ");
    scanf("%s", produtos[*n].nome);
    printf("Preco: "); 
    scanf("%f", &produtos[*n].preco);
    printf("Quantidade: ");
    scanf("%d", &produtos[*n].quantidade);

    (*n)++;   //avança para a próxima posição do vetor
    printf("Produto adicionado com sucesso!\n");
}

//função para buscar produto por código
void buscar(struct produto produtos[], int n) {
    int codigo;
    printf("\nInforme o codigo do produto: ");
    scanf("%d", &codigo);

    for (int i = 0; i < n; i++) {   //percorre todos os produtos cadastrado
        if (produtos[i].codigo == codigo) {   //verifica se o código da posição i é o código buscado
            //exibe as informações completas do produto encontrado
            printf("\nProduto encontrado:\n");
            printf("Codigo: %d\n", produtos[i].codigo);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Preco: %.2f\n", produtos[i].preco);
            printf("Quantidade: %d\n", produtos[i].quantidade);
            return;
        }
    }

    printf("Produto nao encontrado!\n");
}

//função para imprimir todos os produtos
void imprimir(struct produto produtos[], int n) {
    printf("Lista de Produtos:\n");
    printf("%-10s %-20s %-10s %-12s\n","Codigo", "Nome", "Preco",  "Quantidade");

    for (int i = 0; i < n; i++) {   //percorre todos os produtos existentes no vetor
        printf("%-10d %-20s %-10.2f %-12d\n",
               produtos[i].codigo,
               produtos[i].nome,
               produtos[i].preco,
               produtos[i].quantidade);
    }
}

//função para ordenar produtos por preço (crescente)
void ordenar(struct produto produtos[], int n) {
    struct produto temp;   //usado para guardar um produto temporariamente durante a troca
    for (int i = 0; i < n - 1; i++) {   //laço que percorre o vetor até a penúltima posição
        for (int j = i + 1; j < n; j++) {   //compara o produto da posição i com todos os produtos seguintes
            if (produtos[i].preco > produtos[j].preco) {   //se o preço do produto i for maior que o preço do produto j, eles estão fora de ordem
                 //troca as posições dos produtos
                temp = produtos[i];
                produtos[i] = produtos[j];
                produtos[j] = temp;
            }
        }
    }
    printf("\nProdutos ordenados por preço!\n");
}