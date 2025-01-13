/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Organização de Recuperação da Informação
 * Prof. Tiago A. Almeida
 *
 * Trabalho 01 - Indexação
 *
 * ========================================================================== *
 *                             <<< NÃO ALTERAR >>>
 * ========================================================================== */

#ifndef ORI_T01_H
#define ORI_T01_H

/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

typedef enum {false, true} bool;

/* Tamanho dos campos dos registros */
/* Campos de tamanho fixo */

#define TAM_DATE 9
#define TAM_TIME 7
#define TAM_DATETIME 13
#define TAM_INT_NUMBER 5
#define TAM_FLOAT_NUMBER 14
#define TAM_ID_JOGADOR 12
#define TAM_ID_KIT 4
#define TAM_ID_PARTIDA 9
#define TAM_CENARIO 5
#define QTD_MAX_KITS 10
#define QTD_MAX_JOGADORES 12


/* Campos multivalorados de tamanho fixo*/
#define TAM_ID_JOGADORES (TAM_ID_JOGADOR * QTD_MAX_JOGADORES - (QTD_MAX_JOGADORES-1))
#define TAM_ELIMINACOES_JOGADORES (TAM_INT_NUMBER * QTD_MAX_JOGADORES - (QTD_MAX_JOGADORES - 1))
#define TAM_KITS_JOGADORES (TAM_ID_KIT * QTD_MAX_JOGADORES - (QTD_MAX_JOGADORES-1))
#define TAM_DURACAO_JOGADORES (TAM_TIME * QTD_MAX_JOGADORES - (QTD_MAX_JOGADORES-1))


/* Campos de tamanho variável (tamanho máximo) */
#define TAM_MAX_APELIDO 44
#define TAM_MAX_NOME_KIT 21
#define TAM_MAX_PODER_KIT 61


#define MAX_REGISTROS 1000

#define TAM_REGISTRO_JOGADOR (TAM_ID_JOGADOR+TAM_MAX_APELIDO+TAM_DATETIME+TAM_DATETIME+TAM_FLOAT_NUMBER+QTD_MAX_KITS*TAM_ID_KIT)
#define TAM_REGISTRO_KIT (TAM_ID_KIT+TAM_MAX_NOME_KIT+TAM_MAX_PODER_KIT+TAM_FLOAT_NUMBER)
#define TAM_REGISTRO_PARTIDA (TAM_ID_PARTIDA+TAM_DATETIME+TAM_TIME+TAM_CENARIO+TAM_ID_JOGADORES-5)
#define TAM_REGISTRO_RESULTADO (TAM_ID_JOGADOR+TAM_ID_PARTIDA+TAM_ID_KIT+TAM_INT_NUMBER+TAM_TIME+TAM_INT_NUMBER-6)
#define TAM_ARQUIVO_JOGADORES (TAM_REGISTRO_JOGADOR * MAX_REGISTROS + 1)
#define TAM_ARQUIVO_KITS (TAM_REGISTRO_KIT * MAX_REGISTROS + 1)
#define TAM_ARQUIVO_PARTIDAS (TAM_REGISTRO_PARTIDA * MAX_REGISTROS + 1)
#define TAM_ARQUIVO_RESULTADOS (TAM_REGISTRO_RESULTADO * MAX_REGISTROS + 1)

#define TAM_RRN_REGISTRO 4
#define TAM_CHAVE_JOGADORES_IDX ((TAM_ID_JOGADOR - 1) + TAM_RRN_REGISTRO)
#define TAM_CHAVE_KITS_IDX ((TAM_ID_KIT - 1) + TAM_RRN_REGISTRO)
#define TAM_CHAVE_PARTIDAS_IDX ((TAM_ID_PARTIDA - 1) + TAM_RRN_REGISTRO)
#define TAM_CHAVE_RESULTADOS_IDX ((TAM_ID_JOGADOR - 1) + (TAM_ID_KIT - 1) + TAM_RRN_REGISTRO)
#define TAM_CHAVE_PRECO_KIT_IDX ((TAM_FLOAT_NUMBER - 1) + (TAM_ID_KIT - 1))
#define TAM_CHAVE_PARTIDA_DATA_IDX ((TAM_DATETIME - 1) + (TAM_ID_PARTIDA - 1))
#define TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX (TAM_ID_JOGADOR - 1)
#define TAM_CHAVE_JOGADOR_KIT_SECUNDARIO_IDX (TAM_MAX_NOME_KIT - 1)

/* Mensagens padrões */
#define SUCESSO                          "OK\n"
#define REGS_PERCORRIDOS                 "Registros percorridos:"
#define INDICE_CRIADO                    "Indice %s criado com sucesso!\n"
#define AVISO_NENHUM_REGISTRO_ENCONTRADO "AVISO: Nenhum registro encontrado\n"
#define ERRO_OPCAO_INVALIDA              "ERRO: Opcao invalida\n"
#define ERRO_MEMORIA_INSUFICIENTE        "ERRO: Memoria insuficiente\n"
#define ERRO_PK_REPETIDA                 "ERRO: Ja existe um registro com a chave %s\n"
#define ERRO_REGISTRO_NAO_ENCONTRADO     "ERRO: Registro nao encontrado\n"
#define ERRO_SALDO_NAO_SUFICIENTE        "ERRO: Saldo insuficiente\n"
#define ERRO_VALOR_INVALIDO              "ERRO: Valor invalido\n"
#define ERRO_ARQUIVO_VAZIO               "ERRO: Arquivo vazio\n"
#define ERRO_NAO_IMPLEMENTADO            "ERRO: Funcao %s nao implementada\n"
#define ERRO_KIT_REPETIDO                "ERRO: O jogador %s já possui o kit %s\n"
#define CONCEDER_PREMIO					 "O jogador %s, com %d vitorias e %d eliminacoes foi recompensado com %.2lf de saldo\n"
#define ERRO_JOGADOR_KIT	             "ERRO: O jogador %s nao possui o kit %s\n"
#define ERRO_JOGADOR_REMOVIDO			 "Devido a remocao do jogador top 1, o premio de %.2lf sera concedido ao jogador %s, com %d vitorias e %d eliminacoes\n"

/* Registro de Jogador */
typedef struct {
	char id_jogador[TAM_ID_JOGADOR];
	char apelido[TAM_MAX_APELIDO];
	char cadastro[TAM_DATETIME];
	char premio[TAM_DATETIME];
	double saldo;
	char kits[QTD_MAX_KITS][TAM_ID_KIT];
} Jogador;

/* Registro de Kit */
typedef struct {
	char id_kit[TAM_ID_KIT];
	char nome[TAM_MAX_NOME_KIT];
	char poder[TAM_MAX_PODER_KIT];
	double preco;
} Kit;

/* Registro de Partida */
typedef struct {
	char id_partida[TAM_ID_PARTIDA];
	char inicio[TAM_DATETIME];
	char duracao[TAM_TIME];
	char cenario[TAM_CENARIO];
	char id_jogadores[TAM_ID_JOGADORES];
} Partida;

/* Registro de Resultado */
typedef struct {
	char id_jogador[TAM_ID_JOGADOR];
	char id_partida[TAM_ID_PARTIDA];
	char id_kit[TAM_ID_KIT];
	int colocacao;
	char sobrevivencia[TAM_TIME];
	int eliminacoes;
} Resultado;

/* Struct auxiliar para a função recompensar_vencedores_menu() */
typedef struct {
	char id_jogador[TAM_ID_JOGADOR];
	int vitorias;
	int eliminacoes;
	char sobrevivencia[TAM_TIME];
} Info_Jogador;


/*----- Registros dos índices -----*/

/* Struct para o índice primário dos jogadores */
typedef struct {
	char id_jogador[TAM_ID_JOGADOR];
	int rrn;
} jogadores_index;

/* Struct para o índice primário dos kits */
typedef struct {
	char id_kit[TAM_ID_KIT];
	int rrn;
} kits_index;

/* Struct para o índice primário das partidas */
typedef struct {
	char id_partida[TAM_ID_PARTIDA];
	int rrn;
} partidas_index;

/* Struct para o índice primário dos resultados do jogador por partida */
typedef struct {
	char id_jogador[TAM_ID_JOGADOR];
	char id_partida[TAM_ID_PARTIDA];
	int rrn;
} resultados_index;

/* Struct para o índice secundário dos preços dos kits */
typedef struct {
	char id_kit[TAM_ID_KIT];
	double preco;
} preco_kit_index;

/* Struct para o índice secundário das datas das partidas */
typedef struct {
	char inicio[TAM_DATETIME];
	char id_partida[TAM_ID_PARTIDA];
} data_index;

/* Struct para o índice secundário dos nomes de kit (lista invertida) */
typedef struct {
	char chave_secundaria[TAM_MAX_NOME_KIT];   //string com o kit
	int primeiro_indice;
} jogador_kits_secundario_index;

/* Struct para o índice primário dos nomes de kit (lista invertida) */
typedef struct {
	char chave_primaria[TAM_ID_JOGADOR];   //string com o CPF do jogador
	int proximo_indice;
} jogador_kits_primario_index;

/* Struct para os parâmetros de uma lista invertida */
typedef struct {
	jogador_kits_secundario_index *jogador_kits_secundario_idx; // Ponteiro para o índice secundário
	jogador_kits_primario_index *jogador_kits_primario_idx; // Ponteiro para o arquivo de índice primário
	unsigned qtd_registros_secundario; // Quantidade de registros de índice secundário
	unsigned qtd_registros_primario; // Quantidade de registros de índice primário
	unsigned tam_chave_secundaria; // Tamanho de uma chave secundária nesse índice
	unsigned tam_chave_primaria; // Tamanho de uma chave primária nesse índice
	int (*compar)(const void *key, const void *elem); // Função utilizada para comparar as chaves do índice secundário.
} inverted_list;


/* Variáveis globais */
/* Arquivos de dados */
char ARQUIVO_JOGADORES[TAM_ARQUIVO_JOGADORES];
char ARQUIVO_KITS[TAM_ARQUIVO_KITS];
char ARQUIVO_PARTIDAS[TAM_ARQUIVO_PARTIDAS];
char ARQUIVO_RESULTADOS[TAM_ARQUIVO_RESULTADOS];


/* Índices */
jogadores_index *jogadores_idx = NULL;
kits_index *kits_idx = NULL;
partidas_index *partidas_idx = NULL;
resultados_index* resultados_idx = NULL;
preco_kit_index *preco_kit_idx = NULL;
data_index *data_idx = NULL;
inverted_list jogador_kits_idx = {
	.jogador_kits_secundario_idx = NULL,
	.jogador_kits_primario_idx = NULL,
	.qtd_registros_secundario = 0,
	.qtd_registros_primario = 0,
	.tam_chave_secundaria = TAM_CHAVE_JOGADOR_KIT_SECUNDARIO_IDX,
	.tam_chave_primaria = TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX,
};


/* Contadores */
unsigned qtd_registros_jogadores = 0;
unsigned qtd_registros_kits = 0;
unsigned qtd_registros_partidas = 0;
unsigned qtd_registros_resultados = 0;


/* Funções auxiliares para o qsort. */
int qsort_jogadores_idx(const void *a, const void *b);
int qsort_kits_idx(const void *a, const void *b);
int qsort_partidas_idx(const void *a, const void *b);
int qsort_resultados_idx(const void *a, const void *b);
int qsort_preco_kit_idx(const void *a, const void *b);
int qsort_data_idx(const void *a, const void *b);
int qsort_info_jogador(const void *a, const void *b);
int qsort_jogador_kits_secundario_idx(const void *a, const void *b);
int qsort_inverted_list_primary_search(const void *a, const void *b);


/* Cria o índice respectivo */
void criar_jogadores_idx();
void criar_kits_idx();
void criar_partidas_idx();
void criar_resultados_idx();
void criar_preco_kit_idx();
void criar_jogador_kits_idx();
void criar_data_idx();


/* Recupera do arquivo o registro com o RRN informado e retorna os dados nas structs */
Jogador recuperar_registro_jogador(int rrn);
Kit recuperar_registro_kit(int rrn);
Partida recuperar_registro_partida(int rrn);
Resultado recuperar_registro_resultado(int rrn);

/* Escreve em seu respectivo arquivo na posição informada (RRN) */
void escrever_registro_jogador(Jogador j, int rrn);
void escrever_registro_kit(Kit k, int rrn);
void escrever_registro_partida(Partida p, int rrn);
void escrever_registro_resultado (Resultado jp, int rrn);


/* Exibe um registro com base no RRN */
bool exibir_jogador(int rrn);
bool exibir_kit(int rrn);
bool exibir_partida(int rrn);


/* Funções principais */
void cadastrar_jogador_menu(char *id_jogador, char *apelido);
void remover_jogador_menu(char *id_jogador);
void adicionar_saldo_menu(char *id_jogador, double valor);
void adicionar_saldo(char *id_jogador, double valor, bool flag);
void cadastrar_kit_menu(char *nome, char *poder, double preco);
void comprar_kit_menu(char *id_jogador, char *id_kit);
void executar_partida_menu(char *inicio, char *duracao, char *cenario, char *id_jogadores, char *kits_jogadores, char *duracoes_jogadores, char *eliminacoes_jogadores);
void recompensar_vencedores_menu (char *data_inicio, char *data_fim, double premio);


/* Busca */
void buscar_jogador_id_menu(char *id_jogador);
void buscar_kit_id_menu(char *id_kit);
void buscar_partida_id_menu(char *id_partida);


/* Listagem */
void listar_jogadores_id_menu();
void listar_jogadores_kits_menu(char *kit);
void listar_kits_compra_menu(char *id_jogador);
void listar_partidas_periodo_menu(char *data_inicio, char *data_fim);


/* Imprimir arquivos de dados */
void imprimir_arquivo_jogadores_menu();
void imprimir_arquivo_kits_menu();
void imprimir_arquivo_partidas_menu();
void imprimir_arquivo_resultados_menu();


/* Imprimir índices primários */
void imprimir_jogadores_idx_menu();
void imprimir_kits_idx_menu();
void imprimir_partidas_idx_menu();
void imprimir_resultados_idx_menu();


/* Imprimir índices secundários */
void imprimir_preco_kit_idx_menu();
void imprimir_data_idx_menu();
void imprimir_jogador_kits_secundario_idx_menu();
void imprimir_jogador_kits_primario_idx_menu();



/* Liberar espaço */
void liberar_espaco_menu();


/* Liberar memória e encerrar programa */
void liberar_memoria_menu();


/* Funções de manipulação de Lista Invertida */

/**
 * Responsável por inserir duas chaves (chave_secundaria e chave_primaria) em uma Lista Invertida (t).<br />
 * Atualiza os parâmetros dos índices primário e secundário conforme necessário.<br />
 * As chaves a serem inseridas devem estar no formato correto e com tamanho t->tam_chave_primario e t->tam_chave_secundario.<br />
 * O funcionamento deve ser genérico para qualquer Lista Invertida, adaptando-se para os diferentes parâmetros presentes em seus structs.<br />
 *
 * @param chave_secundaria Chave a ser buscada (caso exista) ou inserida (caso não exista) no registro secundário da Lista Invertida.
 * @param chave_primaria Chave a ser inserida no registro primário da Lista Invertida.
 * @param t Ponteiro para a Lista Invertida na qual serão inseridas as chaves.
 */
void inverted_list_insert(char *chave_secundaria, char *chave_primaria, inverted_list *t);


/**
 * Responsável por buscar uma chave no índice secundário de uma Lista invertida (T). O valor de retorno indica se a chave foi encontrada ou não.
 * O ponteiro para o int result pode ser fornecido opcionalmente, e conterá o índice inicial das chaves no registro primário.<br />
 * <br />
 * Exemplos de uso:<br />
 * <code>
 * // Exemplo 1. A chave encontrada deverá ser retornada e o caminho não deve ser informado.<br />
 * ...<br />
 * int result;<br />
 * bool found = inverted_list_secondary_search(&result, false, modelo, &corredor_veiculos_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 2. Não há interesse na chave encontrada, apenas se ela existe, e o caminho não deve ser informado.<br />
 * ...<br />
 * bool found = inverted_list_secondary_search(NULL, false, modelo, &corredor_veiculos_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 3. Há interesse no caminho feito para encontrar a chave.<br />
 * ...<br />
 * int result;<br />
 * bool found = inverted_list_secondary_search(&result, true, modelo, &corredor_veiculos_idx);<br />
 * </code>
 *
 * @param result Ponteiro para ser escrito o índice inicial (primeira ocorrência) das chaves do registro primário. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param chave_secundaria Chave a ser buscada.
 * @param t Ponteiro para o índice do tipo Lista invertida no qual será buscada a chave.
 * @return Indica se a chave foi encontrada.
 */
bool inverted_list_secondary_search(int *result, bool exibir_caminho, char *chave_secundaria, inverted_list *t);


/**
 * Responsável por percorrer o índice primário de uma Lista invertida (T). O valor de retorno indica a quantidade de chaves encontradas.
 * O ponteiro para o vetor de strings result pode ser fornecido opcionalmente, e será populado com a lista de todas as chaves encontradas.
 * O ponteiro para o inteiro indice_final também pode ser fornecido opcionalmente, e deve conter o índice do último campo da lista encadeada
 * da chave primaria fornecida (isso é útil na inserção de um novo registro).<br />
 * <br />
 * Exemplos de uso:<br />
 * <code>
 * // Exemplo 1. As chaves encontradas deverão ser retornadas e tanto o caminho quanto o indice_final não devem ser informados.<br />
 * ...<br />
 * char chaves[TAM_CHAVE_CORREDOR_VEICULO_PRIMARIO_IDX][MAX_REGISTROS];<br />
 * int qtd = inverted_list_primary_search(chaves, false, indice, NULL, &corredor_veiculos_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 2. Não há interesse nas chaves encontradas, apenas no indice_final, e o caminho não deve ser informado.<br />
 * ...<br />
 * int indice_final;
 * int qtd = inverted_list_primary_search(NULL, false, indice, &indice_final, &ccorredor_veiculos_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 3. Há interesse nas chaves encontradas e no caminho feito.<br />
 * ...<br />
 * char chaves[TAM_CHAVE_CORREDOR_VEICULO_PRIMARIO_IDX][MAX_REGISTROS];<br />
 * int qtd = inverted_list_primary_search(chaves, true, indice, NULL, &corredor_veiculos_idx);<br />
 * ...<br />
 * <br />
 * </code>
 *
 * @param result Ponteiro para serem escritas as chaves encontradas. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param indice Índice do primeiro registro da lista encadeada a ser procurado.
 * @param indice_final Ponteiro para ser escrito o índice do último registro encontrado (cujo campo indice é -1). É ignorado caso NULL.
 * @param t Ponteiro para o índice do tipo Lista invertida no qual será buscada a chave.
 * @return Indica a quantidade de chaves encontradas.
 */
int inverted_list_primary_search(char result[][TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX], bool exibir_caminho, int indice, int *indice_final, inverted_list *t);


/* Funções de busca binária */

/**
 * Função Genérica de busca binária, que aceita parâmetros genéricos (assinatura baseada na função bsearch da biblioteca C).
 *
 * @param key Chave de busca genérica.
 * @param base0 Base onde ocorrerá a busca, por exemplo, um ponteiro para um vetor.
 * @param nmemb Número de elementos na base.
 * @param size Tamanho do tipo do elemento na base, dica: utilize a função sizeof().
 * @param compar Ponteiro para a função que será utilizada nas comparações.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso. Se true, imprime as posições avaliadas durante a busca, até que todas sejam visitadas ou o elemento seja encontrado (pela 1a vez).
 *                       Caso o número de elementos seja par (p.ex, 10 elementos), então há 2 (duas) possibilidades para a posição da mediana dos elementos (p.ex., 5a ou 6a posição se o total fosse 10).
 *                       Neste caso, SEMPRE escolha a posição mais à direita (p.ex., a posição 6 caso o total for 10).
 * @param posicao_caso_repetido Caso o elemento seja encontrado, se houver mais do que 1 ocorrência, indica qual deve ser retornada. As opções são:
 *                     -1 = primeira : retorna a PRIMEIRA ocorrência (posição mais à esquerda).
 *                      0 = meio : retorna a ocorrência do MEIO (posição central). [modo padrão]
 *                     +1 = ultima : retorna a ÚLTIMA ocorrência (posição mais à direita).
 * @param retorno_se_nao_encontrado Caso o elemento NÃO seja encontrado, indica qual valor deve ser retornado. As opções são:
 *                     -1 = predecessor : retorna o elemento PREDECESSOR (o que apareceria imediatamente antes do elemento procurado, caso fosse encontrado).
 *                      0 = nulo : retorna NULL. [modo padrão]
 *                     +1 = sucessor : retorna o elemento SUCESSOR (o que apareceria imediatamente depois do elemento procurado, caso fosse encontrado).
 * @return Retorna o elemento encontrado ou NULL se não encontrou.
 */
int busca_binaria_com_reps(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int posicao_caso_repetido, int retorno_se_nao_encontrado);
int busca_binaria(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int retorno_se_nao_encontrado);


/* Funções de geração determinística de números pseudo-aleatórios */
struct tm *gmtime_r(const time_t *timer, struct tm *tmbuf);
time_t mktime(struct tm *tmbuf);
bool set_time(char *date);
void tick_time();
void current_date(char buffer[TAM_DATE]);
void current_datetime(char buffer[TAM_DATETIME]);
void prng_srand(uint64_t value);
uint64_t prng_rand();
void new_uuid(char buffer[37]);


/* Remove comentários (--) e caracteres whitespace do começo e fim de uma string */
void clear_input(char *str);


/* Funções auxiliares */
char* strpadright(char *str, char pad, unsigned size);
char* strupr(char *str);
char* strlower(char *str);


/* Implementação das funções geração determinística de números pseudo-aleatórios e das funções auxilares, NÃO EDITAR NADA */

uint64_t prng_seed;

/* Funções de manipulação de data */
time_t epoch;

#define YEAR0                   1900
#define EPOCH_YR                1970
#define SECS_DAY                (24L * 60L * 60L)
#define LEAPYEAR(year)          (!((year) % 4) && (((year) % 100) || !((year) % 400)))
#define YEARSIZE(year)          (LEAPYEAR(year) ? 366 : 365)

#define TIME_MAX                2147483647L

long _dstbias = 0;                  // Offset for Daylight Saving Time
long _timezone = 0;                 // Difference in seconds between GMT and local time

const int _ytab[2][12] = {
	{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};


/* Funções de geração determinística de números pseudo-aleatórios */
void prng_srand(uint64_t value) {
	prng_seed = value;
}

uint64_t prng_rand() {
	// https://en.wikipedia.org/wiki/Xorshift#xorshift*
	uint64_t x = prng_seed; // O estado deve ser iniciado com um valor diferente de 0
	x ^= x >> 12;			// a
	x ^= x << 25;			// b
	x ^= x >> 27;			// c
	prng_seed = x;
	return x * UINT64_C(0x2545F4914F6CDD1D);
}

/**
 * Gera um <a href="https://en.wikipedia.org/wiki/Universally_unique_identifier">UUID Version-4 Variant-1</a>
 * (<i>string</i> aleatória) de 36 caracteres utilizando o gerador de números pseudo-aleatórios
 * <a href="https://en.wikipedia.org/wiki/Xorshift#xorshift*">xorshift*</a>. O UUID é
 * escrito na <i>string</i> fornecida como parâmetro.<br />
 * <br />
 * Exemplo de uso:<br />
 * <code>
 * char chave_aleatoria[37];<br />
 * new_uuid(chave_aleatoria);<br />
 * printf("chave aleatória: %s&#92;n", chave_aleatoria);<br />
 * </code>
 *
 * @param buffer String de tamanho 37 no qual será escrito
 * o UUID. É terminado pelo caractere <code>\0</code>.
 */
void new_uuid(char buffer[37]) {
	uint64_t r1 = prng_rand();
	uint64_t r2 = prng_rand();

	sprintf(buffer, "%08x-%04x-%04lx-%04lx-%012lx", (uint32_t)(r1 >> 32), (uint16_t)(r1 >> 16), 0x4000 | (r1 & 0x0fff), 0x8000 | (r2 & 0x3fff), r2 >> 16);
}

/* Funções de manipulação de data */
struct tm *gmtime_r(const time_t *timer, struct tm *tmbuf) {
	// based on http://www.jbox.dk/sanos/source/lib/time.c.html
	time_t time = *timer;
	unsigned long dayclock, dayno;
	int year = EPOCH_YR;

	dayclock = (unsigned long)time % SECS_DAY;
	dayno = (unsigned long)time / SECS_DAY;

	tmbuf->tm_sec = dayclock % 60;
	tmbuf->tm_min = (dayclock % 3600) / 60;
	tmbuf->tm_hour = dayclock / 3600;
	tmbuf->tm_wday = (dayno + 4) % 7; // Day 0 was a thursday
	while (dayno >= (unsigned long) YEARSIZE(year)) {
		dayno -= YEARSIZE(year);
		year++;
	}
	tmbuf->tm_year = year - YEAR0;
	tmbuf->tm_yday = dayno;
	tmbuf->tm_mon = 0;
	while (dayno >= (unsigned long) _ytab[LEAPYEAR(year)][tmbuf->tm_mon]) {
		dayno -= _ytab[LEAPYEAR(year)][tmbuf->tm_mon];
		tmbuf->tm_mon++;
	}
	tmbuf->tm_mday = dayno + 1;
	tmbuf->tm_isdst = 0;
	return tmbuf;
}

time_t mktime(struct tm *tmbuf) {
	// based on http://www.jbox.dk/sanos/source/lib/time.c.html
	long day, year;
	int tm_year;
	int yday, month;
	/*unsigned*/ long seconds;
	int overflow;
	long dst;

	tmbuf->tm_min += tmbuf->tm_sec / 60;
	tmbuf->tm_sec %= 60;
	if (tmbuf->tm_sec < 0) {
		tmbuf->tm_sec += 60;
		tmbuf->tm_min--;
	}
	tmbuf->tm_hour += tmbuf->tm_min / 60;
	tmbuf->tm_min = tmbuf->tm_min % 60;
	if (tmbuf->tm_min < 0) {
		tmbuf->tm_min += 60;
		tmbuf->tm_hour--;
	}
	day = tmbuf->tm_hour / 24;
	tmbuf->tm_hour= tmbuf->tm_hour % 24;
	if (tmbuf->tm_hour < 0) {
		tmbuf->tm_hour += 24;
		day--;
	}
	tmbuf->tm_year += tmbuf->tm_mon / 12;
	tmbuf->tm_mon %= 12;
	if (tmbuf->tm_mon < 0) {
		tmbuf->tm_mon += 12;
		tmbuf->tm_year--;
	}
	day += (tmbuf->tm_mday - 1);
	while (day < 0) {
		if(--tmbuf->tm_mon < 0) {
			tmbuf->tm_year--;
			tmbuf->tm_mon = 11;
		}
		day += _ytab[LEAPYEAR(YEAR0 + tmbuf->tm_year)][tmbuf->tm_mon];
	}
	while (day >= _ytab[LEAPYEAR(YEAR0 + tmbuf->tm_year)][tmbuf->tm_mon]) {
		day -= _ytab[LEAPYEAR(YEAR0 + tmbuf->tm_year)][tmbuf->tm_mon];
		if (++(tmbuf->tm_mon) == 12) {
			tmbuf->tm_mon = 0;
			tmbuf->tm_year++;
		}
	}
	tmbuf->tm_mday = day + 1;
	year = EPOCH_YR;
	if (tmbuf->tm_year < year - YEAR0)
		return (time_t)-1;
	seconds = 0;
	day = 0; // Means days since day 0 now
	overflow = 0;

	// Assume that when day becomes negative, there will certainly
	// be overflow on seconds.
	// The check for overflow needs not to be done for leapyears
	// divisible by 400.
	// The code only works when year (1970) is not a leapyear.
	tm_year = tmbuf->tm_year + YEAR0;

	if (TIME_MAX / 365 < tm_year - year)
		overflow++;
	day = (tm_year - year) * 365;
	if (TIME_MAX - day < (tm_year - year) / 4 + 1)
		overflow++;
	day += (tm_year - year) / 4 + ((tm_year % 4) && tm_year % 4 < year % 4);
	day -= (tm_year - year) / 100 + ((tm_year % 100) && tm_year % 100 < year % 100);
	day += (tm_year - year) / 400 + ((tm_year % 400) && tm_year % 400 < year % 400);

	yday = month = 0;
	while (month < tmbuf->tm_mon) {
		yday += _ytab[LEAPYEAR(tm_year)][month];
		month++;
	}
	yday += (tmbuf->tm_mday - 1);
	if (day + yday < 0)
		overflow++;
	day += yday;

	tmbuf->tm_yday = yday;
	tmbuf->tm_wday = (day + 4) % 7; // Day 0 was thursday (4)

	seconds = ((tmbuf->tm_hour * 60L) + tmbuf->tm_min) * 60L + tmbuf->tm_sec;

	if ((TIME_MAX - seconds) / SECS_DAY < day)
		overflow++;
	seconds += day * SECS_DAY;

	// Now adjust according to timezone and daylight saving time
	if (((_timezone > 0) && (TIME_MAX - _timezone < seconds)) ||
		((_timezone < 0) && (seconds < -_timezone))) {
		overflow++;
		}
		seconds += _timezone;

	if (tmbuf->tm_isdst) {
		dst = _dstbias;
	} else {
		dst = 0;
	}

	if (dst > seconds){
		overflow++; // dst is always non-negative
		seconds -= dst;
	}

	if (overflow)
		return (time_t)-1;

	if ((time_t)seconds != seconds)
		return (time_t)-1;
	return (time_t)seconds;
}

bool set_time(char *date) {
	// http://www.cplusplus.com/reference/ctime/mktime/
	struct tm tm_;

	if (strlen(date) == TAM_DATETIME-1 && sscanf(date, "%4d%2d%2d%2d%2d", &tm_.tm_year, &tm_.tm_mon, &tm_.tm_mday, &tm_.tm_hour, &tm_.tm_min) == 5) {
		tm_.tm_year -= 1900;
		tm_.tm_mon -= 1;
		tm_.tm_sec = 0;
		tm_.tm_isdst = -1;
		epoch = mktime(&tm_);
		return true;
	}
	return false;
}

void tick_time() {
	epoch += prng_rand() % 864000; // 10 dias
}

/**
 * Escreve a <i>data</i> atual no formato <code>AAAAMMDD</code> em uma <i>string</i>
 * fornecida como parâmetro.<br />
 * <br />
 * Exemplo de uso:<br />
 * <code>
 * char timestamp[TAM_DATE];<br />
 * current_date(timestamp);<br />
 * printf("data atual: %s&#92;n", timestamp);<br />
 * </code>
 *
 * @param buffer String de tamanho <code>TAM_DATE</code> no qual será escrita
 * a <i>timestamp</i>. É terminado pelo caractere <code>\0</code>.
 */
void current_date(char buffer[TAM_DATE]) {
	// http://www.cplusplus.com/reference/ctime/strftime/
	// http://www.cplusplus.com/reference/ctime/gmtime/
	// AAAA MM DD
	// %Y   %m %d
	struct tm tm_;
	if (gmtime_r(&epoch, &tm_) != NULL)
		strftime(buffer, TAM_DATE, "%Y%m%d", &tm_);
}

/**
 * Escreve a <i>data</i> e a <i>hora</i> atual no formato <code>AAAAMMDDHHMM</code> em uma <i>string</i>
 * fornecida como parâmetro.<br />
 * <br />
 * Exemplo de uso:<br />
 * <code>
 * char timestamp[TAM_DATETIME];<br />
 * current_datetime(timestamp);<br />
 * printf("data e hora atual: %s&#92;n", timestamp);<br />
 * </code>
 *
 * @param buffer String de tamanho <code>TAM_DATETIME</code> no qual será escrita
 * a <i>timestamp</i>. É terminado pelo caractere <code>\0</code>.
 */
void current_datetime(char buffer[TAM_DATETIME]) {
	// http://www.cplusplus.com/reference/ctime/strftime/
	// http://www.cplusplus.com/reference/ctime/gmtime/
	// AAAA MM DD HH MM
	// %Y   %m %d %H %M
	struct tm tm_;
	if (gmtime_r(&epoch, &tm_) != NULL)
		strftime(buffer, TAM_DATETIME, "%Y%m%d%H%M", &tm_);
}

/* Remove comentários (--) e caracteres whitespace do começo e fim de uma string */
void clear_input(char *str) {
	char *ptr = str;
	int len = 0;

	for (; ptr[len]; ++len) {
		if (strncmp(&ptr[len], "--", 2) == 0) {
			ptr[len] = '\0';
			break;
		}
	}

	while(len-1 > 0 && isspace(ptr[len-1]))
		ptr[--len] = '\0';

	while(*ptr && isspace(*ptr))
		++ptr, --len;

	memmove(str, ptr, len + 1);
}

/**
 * Preenche uma string str com o caractere pad para completar o tamanho size.<br />
 *
 * @param str Ponteiro para a string a ser manipulada.
 * @param pad Caractere utilizado para fazer o preenchimento à direita.
 * @param size Tamanho desejado para a string.
 */
char* strpadright(char *str, char pad, unsigned size);

/**
 * Converte uma string str para letras maiúsculas.<br />
 *
 * @param str Ponteiro para a string a ser manipulada.
 */
char* strupr(char *str);

/**
 * Converte uma string str para letras minúsculas.<br />
 *
 * @param str Ponteiro para a string a ser manipulada.
 */
char* strlower(char *str);


#endif
