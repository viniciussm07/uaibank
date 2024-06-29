#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct USUARIO {
  int id;
  char nome[100];
  int idade;
  double saldo;
};

void limparBuffer(void) {
  char c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void adiciona_usuario(struct USUARIO **array, int *tamanho) {
  srand(time(NULL));

  *array = realloc(*array, (*tamanho + 1) * sizeof(struct USUARIO));
  if (*array == NULL) {
    printf("Erro ao alocar memoria.\n");
    exit(1);
  }

  limparBuffer();

  printf("\n\nDigite o primeiro e o ultimo nome do usuario (Exemplo: Ana "
         "Silva):\n\n");
  fgets((*array)[*tamanho].nome, sizeof((*array)[*tamanho].nome), stdin);

  size_t len = strlen((*array)[*tamanho].nome);
  if (len > 0 && (*array)[*tamanho].nome[len - 1] == '\n') {
    (*array)[*tamanho].nome[len - 1] = '\0';
  }

  printf("\n\nDigite a idade e o saldo do usuario (Exemplo: 32 900.50):\n\n");
  scanf("%d %lf", &(*array)[*tamanho].idade, &(*array)[*tamanho].saldo);

  (*array)[*tamanho].id = rand();

  printf("\n\nUsuario inserido com ID %d: %s, %d, %.2lf\n",
         (*array)[*tamanho].id, (*array)[*tamanho].nome,
         (*array)[*tamanho].idade, (*array)[*tamanho].saldo);

  for (int i = 0; i <= *tamanho; i++) {
    printf("\nUsuario %i: %i, %s, %d, %.2lf\n", i, (*array)[i].id,
           (*array)[i].nome, (*array)[i].idade, (*array)[i].saldo);
  } // Mostra os usuários adicionados até então

  (*tamanho)++;
}

void adiciona_varios_usuario(struct USUARIO **array, int *tamanho) {
  int qnt_usuarios;
  srand(time(NULL));

  printf("\nQuantos usuarios deseja cadastrar?\n\nQuantidade: ");
  scanf("%d", &qnt_usuarios);

  if (qnt_usuarios <= 0) {
    printf("\nO valor digitado deve ser maior que zero.\n");
    return;
  }

  *array = realloc(*array, (*tamanho + qnt_usuarios) * sizeof(struct USUARIO));
  if (*array == NULL) {
    printf("Erro ao alocar memoria.\n");
    exit(1);
  }

  for (int i = 0; i < qnt_usuarios; i++) {
    limparBuffer();

    printf("\n\nDigite o primeiro e o ultimo nome do usuario (Exemplo: Ana "
           "Silva):\n\n");
    fgets((*array)[*tamanho].nome, sizeof((*array)[*tamanho].nome), stdin);

    size_t len = strlen((*array)[*tamanho].nome);

    if (len > 0 && (*array)[*tamanho].nome[len - 1] == '\n') {
      (*array)[*tamanho].nome[len - 1] = '\0';
    }

    printf("\n\nDigite a idade e o saldo do usuario (Exemplo: 32 900.50):\n\n");

    scanf("%d %lf", &(*array)[*tamanho].idade, &(*array)[*tamanho].saldo);

    (*array)[*tamanho].id = rand();

    printf("\n\nUsuario inserido com ID %d: %s, %d, %.2lf\n",
           (*array)[*tamanho].id, (*array)[*tamanho].nome,
           (*array)[*tamanho].idade, (*array)[*tamanho].saldo);

    for (int j = 0; j <= *tamanho; j++) {
      printf("\nUsuario %i: %i, %s, %d, %.2lf\n", j, (*array)[j].id,
             (*array)[j].nome, (*array)[j].idade,
             (*array)[j].saldo); // Mostra os usuários adicionados até então
    }

    (*tamanho)++;
  }
}

void remove_usuario(struct USUARIO **array, int *tamanho) {
    int id, i;

    printf("\n\nDigite o ID do usuário a ser removido\n");
    scanf("%i", &id);

    for (i = 0; i < *tamanho; i++) {
        if ((*array)[i].id == id) {
            // Mover todos os elementos após o índice i uma posição para trás
            for (int j = i; j < *tamanho - 1; j++) {
                (*array)[j] = (*array)[j + 1];
            }

            // Realocar o array para o novo tamanho
            *tamanho -= 1;
            *array = realloc(*array, (*tamanho) * sizeof(struct USUARIO));
            if (*array == NULL && *tamanho > 0) {
                printf("Erro ao alocar memoria.\n");
                exit(1);
            }

            printf("\n\nUsuario %d removido com sucesso", id);
            return;
        }
    }
    printf("\n\nErro: Usuario com o id %d nao encontrado", id);
}

void busca_de_usuario_id(struct USUARIO **array, int *tamanho) {
  int id;

  printf("Digite o ID do usuário a ser buscado\n");
  scanf("%i", &id);

  for (int i = 0; i < *tamanho; i++) {
    if ((*array)[i].id == id) {
      printf("Usuario %d tem saldo de %.2f", id, (*array)[i].saldo);
      return;
    }
  }
  printf("Erro: Usuario com o id %d nao encontrado", id);
}

void transferencia_entre_usuarios(struct USUARIO **array, int *tamanho) {
  int idOrigem, idDestino, quantia, indiceOrigem, indiceDestino, i;
  printf("Digite o ID de origem da transação:\n");
  scanf("%i", &idOrigem);
  printf("Digite o ID de destino da transação:\n");
  scanf("%i", &idDestino);
  printf("Agora, digite a quantia a ser transferida:\n");
  scanf("%i", &quantia);

  for (i = 0; i < *tamanho; i++) {
    indiceOrigem = -1;
    indiceDestino = -1;

    if (array[i]->id == idOrigem) {
      idOrigem = i;
      return;
    }
    if (array[i]->id == idDestino) {
      idDestino = i;
      return;
    }
  }
  if ((indiceOrigem = -1) || (indiceDestino = -1)) {
    printf("Erro: usuário não encontrado.");
  }
  if (array[indiceOrigem]->saldo < quantia) {
    printf("Erro: Saldo insuficiente! Impossível ralizar a transferência.");
  }
  array[indiceOrigem]->saldo -= quantia;
  array[indiceDestino]->saldo += quantia;

  printf("Transferência realizada!");
}

void limparMemoriaUsuarios(struct USUARIO **array, int *tamanho) {
  free(*array); // Libera a memória do array de usuários
  *array = NULL; // Evita o uso de um ponteiro para uma região de memória já liberada
}

// Abre o arquivo de banco de dados e carrega os dados para o array de usuários
void carrega_dados(struct USUARIO **array, int *tamanho) {
  char linha[256]; // Ajuste o tamanho conforme necessário para acomodar a linha
                   // inteira
  FILE *dados;
  dados = fopen("dados_uaibank.csv", "r");

  // Caso o arquivo não exista ele é criado e caso haja erro ao criar o arquivo
  // o programa é encerrado
  if (dados == NULL) {
    printf("Criando arquivo\n");
    dados = fopen("dados_uaibank.csv", "w");
    if (dados == NULL) {
      printf("Erro ao criar arquivo.\n");
      exit(1);
    }
    fclose(dados);
    return;
  }

  // Lê o arquivo linha por linha e armazena os dados no array
  while (fgets(linha, sizeof(linha), dados) != NULL) {
    *array = realloc(*array, (*tamanho + 1) * sizeof(struct USUARIO));
    if (*array == NULL) {
      printf("Erro ao alocar memoria.\n");
      exit(1);
    }

    // Divide a linha nos campos desejados
    (*array)[*tamanho].id = atoi(strtok(linha, ","));
    strcpy((*array)[*tamanho].nome, strtok(NULL, ","));
    (*array)[*tamanho].idade = atoi(strtok(NULL, ","));
    (*array)[*tamanho].saldo = atof(strtok(NULL, ","));
    (*tamanho)++;
  }
  fclose(dados);
}

// Printa o array no terminal
void print_array(struct USUARIO *array, int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    printf("Usuario %d: %d, %s, %d, %.2lf\n", i, array[i].id, array[i].nome,
           array[i].idade, array[i].saldo);
  }
}

// Salva os dados do array no arquivo de banco de dados
void salva_dados(struct USUARIO **array, int *tamanho) {
  FILE *dados;
  dados = fopen("dados_uaibank.csv", "w");

  if (dados == NULL) {
    printf("Erro ao abrir arquivo.\n");
    exit(1);
  }

  for (int i = 0; i < *tamanho; i++) {
    fprintf(dados, "%d,%s,%d,%.2lf\n", (*array)[i].id, (*array)[i].nome,
            (*array)[i].idade, (*array)[i].saldo);
  }
  fclose(dados);
}

int main(void) {
  struct USUARIO *arrayUsuarios = NULL;
  int tamanho = 0;
  int opc;

  // Carregar os dados do arquivo
  carrega_dados(&arrayUsuarios, &tamanho);
  // print_array(arrayUsuarios, tamanho);

  printf("\n\n:::: BEM-VINDOS AO UAIBANK ::::\n\n");

  printf("\n\nEscolha uma das opcoes a seguir:\n (1) - Inserir um usuario; \n "
         "(2) - Inserir varios usuarios; \n (3) - Buscar usuario por id; \n "
         "(4) - Transferir entre usuarios; \n (5) - Remover usuario por id; \n "
         "(6) - Para printar usuarios cadastrados; \n "
         "Digite algo diferente para sair do programa; \n\n Digite sua opcao "
         "... ");
  scanf("%d", &opc);

  while (opc < 7 && opc > 0) {

    switch (opc) {
    case 1:
      // insere usuario
      adiciona_usuario(&arrayUsuarios, &tamanho);
      break;

    case 2:
      // insere varios usuariosusuario
      adiciona_varios_usuario(&arrayUsuarios, &tamanho);
      break;

    case 3:
      // busca usuario por id
      busca_de_usuario_id(&arrayUsuarios, &tamanho);
      break;

    case 4:
      // transferencia entre usuarios
      transferencia_entre_usuarios(&arrayUsuarios, &tamanho);
      break;

    case 5:
      // remove usuario por id
      remove_usuario(&arrayUsuarios, &tamanho);
      break;

    case 6:
      // Printa banco de dados
      print_array(arrayUsuarios, tamanho);
      break;

    default:
      // Sair do programa
      break;
    }
    printf(
        "\n\nEscolha outra das opcoes a seguir:\n (1) - Inserir um usuario; \n "
        "(2) - Inserir varios usuarios; \n (3) - Buscar usuario por id; \n "
        "(4) - Transferir entre usuarios; \n (5) - Remover usuario por id; \n "
        "(6) - Para printar usuarios cadastrados; \n "
        "Digite algo diferente para sair do programa; \n\n Digite sua opcao "
        "... ");
    scanf("%d", &opc);
  }

  // Salvar os dados no arquivo
  salva_dados(&arrayUsuarios, &tamanho);

  // Limpa a memória alocada
  limparMemoriaUsuarios(&arrayUsuarios, &tamanho);

  return 0;
}