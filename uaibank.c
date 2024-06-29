#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Declaração da struct para a variável de tipo USUARIO
struct USUARIO {
  int id;
  char nome[100];
  int idade;
  double saldo;
};

// Limpa o buffer do teclado, removendo o \n
void limpar_buffer(void) {
  char c;
  while ((c = getchar()) != '\n' && c != EOF); 
}

void adiciona_usuario(struct USUARIO **array, int *tamanho) {
  // gera um numero aleatorio para o id
  srand(time(NULL));

  // realoca o tamanho do array
  *array = realloc(*array, (*tamanho + 1) * sizeof(struct USUARIO));

  // Verifica se a realocação de memória, informando o erro caso ocorra
  if (*array == NULL) {
    printf("Erro ao alocar memoria.\n");
    exit(1);
  }

  // Remove '\n' do buffer
  limpar_buffer();

  printf("\n\nDigite o primeiro e o ultimo nome do usuario (Exemplo: Ana Silva):\n\n");

  // Recebe o nome do usuario com espaço
  fgets((*array)[*tamanho].nome, sizeof((*array)[*tamanho].nome),stdin); 

  // representação do tamanho do nome do usuario em bytes na variável len
  size_t len = strlen((*array)[*tamanho].nome); 

  // Remove o '\n' do final da última string digitada
  if (len > 0 && (*array)[*tamanho].nome[len - 1] == '\n') {(*array)[*tamanho].nome[len - 1] = '\0';}

  printf("\n\nDigite a idade e o saldo do usuario (Exemplo: 32 900.50):\n\n");

  // Recebe a idade e o saldo do usuario
  scanf("%d %lf", &(*array)[*tamanho].idade, &(*array)[*tamanho].saldo);

  // gera um numero aleatorio para o id
  (*array)[*tamanho].id = rand();

  printf("\n\nUsuario inserido com ID %d: %s, %d, %.2lf\n",
         (*array)[*tamanho].id, (*array)[*tamanho].nome,
         (*array)[*tamanho].idade, (*array)[*tamanho].saldo);

  // Aumenta o tamanho do array usuários
  (*tamanho)++; 
}

void adiciona_varios_usuario(struct USUARIO **array, int *tamanho) {
  int qnt_usuarios; 

  srand(time(NULL));

  printf("\nQuantos usuarios deseja cadastrar?\n\nQuantidade: ");

  scanf("%d", &qnt_usuarios);

  // Verifica se o valor digitado é maior ou menor que zero
  if (qnt_usuarios <= 0) {
    printf("\nO valor digitado deve ser maior que zero.\n");
    return;
  } 

  // Realoca o tamanho do array para receber a quantidade de usuários a serem adicionados
  *array = realloc(*array, (*tamanho + qnt_usuarios) * sizeof(struct USUARIO)); 

  // Verifica se a realocação de memória, informando o erro caso ocorra
  if (*array == NULL) {
    printf("Erro ao alocar memoria.\n");
    exit(1);
  }

  for (int i = 0; i < qnt_usuarios; i++) {

    // Remove '\n' do buffer
    limpar_buffer();

    printf("\n\nDigite o primeiro e o ultimo nome do usuario (Exemplo: Ana Silva):\n\n");

    // Recebe o nome do usuario com espaço
    fgets((*array)[*tamanho].nome, sizeof((*array)[*tamanho].nome), stdin); 

    // representação do tamanho do nome do usuario em bytes na variável len
    size_t len = strlen((*array)[*tamanho].nome);

    // Remove o '\n' do final da última string digitada
    if (len > 0 && (*array)[*tamanho].nome[len - 1] == '\n') {
      (*array)[*tamanho].nome[len - 1] = '\0';
    }

    printf("\n\nDigite a idade e o saldo do usuario (Exemplo: 32 900.50):\n\n");

     // Recebe a idade e o saldo do usuario
    scanf("%d %lf", &(*array)[*tamanho].idade, &(*array)[*tamanho].saldo);

    // Gera um numero aleatorio para o id
    (*array)[*tamanho].id = rand();

    printf("\n\nUsuario inserido com ID %d: %s, %d, %.2lf\n",
           (*array)[*tamanho].id, (*array)[*tamanho].nome,
           (*array)[*tamanho].idade,
           (*array)[*tamanho].saldo);

    // Aumenta o tamanho do array usuários
    (*tamanho)++;
  }
}

void busca_de_usuario_id(struct USUARIO **array, int *tamanho) {
  int id;

  printf("\n\nDigite o ID do usuário a ser buscado\n");
  scanf("%i", &id);

  // Percorre todo o array de usuários para encontrar o usuário com o id informado
  for (int i = 0; i < *tamanho; i++) {
    if ((*array)[i].id == id) {
      printf("\n\nUsuario %d tem saldo de %.2f", id, (*array)[i].saldo);
      return;
    }
  }
  printf("\n\nErro: Usuario com o id %d nao encontrado", id);
}

void transferencia_entre_usuarios(struct USUARIO **array, int *tamanho) {
  int idOrigem, idDestino, indiceOrigem = -1, indiceDestino = -1, i;
  double quantia;

  printf("Digite o ID de origem da transação:\n");
  scanf("%i", &idOrigem);

  printf("Digite o ID de destino da transação:\n");
  scanf("%i", &idDestino);

  printf("Agora, digite a quantia a ser transferida:\n");
  scanf("%lf", &quantia);

  // Percorre todo o array de usuários para encontrar os usuários com os ids informados
  for (i = 0; i < *tamanho; i++) {

    if ((*array)[i].id == idOrigem) {
      indiceOrigem = i;
    }

    if ((*array)[i].id == idDestino) {
      indiceDestino = i;
    }
  }
  // Verifica se os usuários foram encontrados
  if ((indiceOrigem == -1) || (indiceDestino == -1)) {
    printf("\n\nErro: usuário não encontrado.");
    return;
  }
  if ((*array)[indiceOrigem].saldo < quantia) {
    printf("\n\nErro: Saldo insuficiente! Impossível ralizar a transferência.");
    return;
  }
  (*array)[indiceOrigem].saldo -= quantia;
  (*array)[indiceDestino].saldo += quantia;

  printf("\n\nTransferência realizada!");
}

void remove_usuario(struct USUARIO **array, int *tamanho) {
  int id, i;

  printf("\n\nDigite o ID do usuário a ser removido\n");
  scanf("%i", &id);

  // Percorre todo o array de usuários
  for (i = 0; i < *tamanho; i++) {
    // Verifica se o id do usuário atual é igual ao id informado
    if ((*array)[i].id == id) {
      // Move o usuario informado para a ultima posicao do array
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

void limpar_memoria_usuarios(struct USUARIO **array, int *tamanho) {
  // Libera a memória do array de usuários
  free(*array);
  // Evita o uso de um ponteiro para uma região de memória já liberada
  *array = NULL;
}

// Abre o arquivo de banco de dados e carrega os dados para o array de usuários
void carrega_dados(struct USUARIO **array, int *tamanho) {
  // Declaração da variável linha
  char linha[256]; 
  FILE *dados;
  // Tenta abrir o arquivo de banco de dados no modo leitura
  dados = fopen("dados_uaibank.csv", "r");

  // Caso o arquivo não exista ele é criado e caso haja erro ao criar o arquivo o programa é encerrado
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

  // Lê o arquivo linha por linha e armazena os dados no array de usuários
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
  limpar_memoria_usuarios(&arrayUsuarios, &tamanho);

  return 0;
}