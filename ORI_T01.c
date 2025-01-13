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


/* Bibliotecas */
#include "ORI_T01_HEADER.h"
#include "ORI_T01_HEADER.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <ctype.h>
#include <string.h>


int main() {
    // variáveis utilizadas pelo interpretador de comandos
    char input[500];
    uint64_t seed = 2;
    char datetime[TAM_DATETIME] = "202103181430"; // UTC 18/03/2021 14:30:00

    char data_cadastro[TAM_DATETIME];
    char id_jogador[TAM_ID_JOGADOR];
    char apelido_jogador[TAM_MAX_APELIDO];
    int vitorias;
    double valor;

    char id_kit[TAM_ID_KIT];
    char nome_kit[TAM_MAX_NOME_KIT];
    char poder_kit[TAM_MAX_PODER_KIT];
    double preco_kit;

    char id_partida[TAM_ID_PARTIDA];
    char horario_inicio[TAM_DATETIME];
    char horario_fim[TAM_DATETIME];
    char duracao[TAM_TIME];
    char cenario[TAM_CENARIO];
    char jogadores[TAM_ID_JOGADORES];
    char kits_jogadores[TAM_KITS_JOGADORES];
    char duracoes_jogadores[TAM_DURACAO_JOGADORES];
    char eliminacoes[TAM_ELIMINACOES_JOGADORES];
	double premio;

    scanf("SET ARQUIVO_JOGADORES TO '%[^']';\n", ARQUIVO_JOGADORES);
    int temp_len = strlen(ARQUIVO_JOGADORES);
    qtd_registros_jogadores = temp_len / TAM_REGISTRO_JOGADOR;
    ARQUIVO_JOGADORES[temp_len] = '\0';

    scanf("SET ARQUIVO_KITS TO '%[^']';\n", ARQUIVO_KITS);
    temp_len = strlen(ARQUIVO_KITS);
    qtd_registros_kits = temp_len / TAM_REGISTRO_KIT;
    ARQUIVO_KITS[temp_len] = '\0';

    scanf("SET ARQUIVO_PARTIDAS TO '%[^']';\n", ARQUIVO_PARTIDAS);
    temp_len = strlen(ARQUIVO_PARTIDAS);
    qtd_registros_partidas = temp_len / TAM_REGISTRO_PARTIDA;
    ARQUIVO_PARTIDAS[temp_len] = '\0';

    scanf("SET ARQUIVO_RESULTADOS TO '%[^']';\n", ARQUIVO_RESULTADOS);
    temp_len = strlen(ARQUIVO_RESULTADOS);
    qtd_registros_resultados = temp_len / TAM_REGISTRO_RESULTADO;
    ARQUIVO_RESULTADOS[temp_len] = '\0';
		
    // inicialização do gerador de números aleatórios e função de datas
    prng_srand(seed);
    putenv("TZ=UTC");
    set_time(datetime);

    criar_jogadores_idx();
    criar_kits_idx();
    criar_partidas_idx();
    criar_resultados_idx();
    criar_preco_kit_idx();
    criar_jogador_kits_idx();
    criar_data_idx();


    while (1) {

        fgets(input, 500, stdin);
        printf("%s", input);
        clear_input(input);

        if (strcmp("", input) == 0)
            continue; // não avança o tempo nem imprime o comando caso esteja em branco

            /* Funções principais */
        if (sscanf(input, "INSERT INTO jogadores VALUES ('%[^']', '%[^']');", id_jogador, apelido_jogador) == 2)
            cadastrar_jogador_menu(id_jogador, apelido_jogador);
        else if (sscanf(input, "DELETE FROM jogadores WHERE id_jogador = '%[^']';", id_jogador) == 1)
            remover_jogador_menu(id_jogador);
        else if (sscanf(input, "UPDATE jogadores SET saldo = saldo + %lf WHERE id_jogador = '%[^']';", &valor, id_jogador) == 2)
            adicionar_saldo_menu(id_jogador, valor);
        else if (sscanf(input, "UPDATE jogadores SET kits = array_append(kits, '%[^']') WHERE id_jogador = '%[^']';", id_kit, id_jogador) == 2)
            comprar_kit_menu(id_jogador, id_kit);
        else if (sscanf(input, "INSERT INTO kits VALUES ('%[^']', '%[^']', %lf);", nome_kit, poder_kit, &preco_kit) == 3)
            cadastrar_kit_menu(nome_kit, poder_kit, preco_kit);
        else if(sscanf(input, "INSERT INTO partidas VALUES ('%[^']', '%[^']', '%[^']', '%[^']', '%[^']', '%[^']', '%[^']');", horario_inicio, duracao, cenario, jogadores, kits_jogadores, duracoes_jogadores, eliminacoes) == 7)
            executar_partida_menu(horario_inicio, duracao, cenario, jogadores, kits_jogadores, duracoes_jogadores, eliminacoes);
        else if (sscanf(input, "RECOMPENSAR_VENCEDORES('%[^']', '%[^']', %lf);", horario_inicio, horario_fim, &premio) == 3)
            recompensar_vencedores_menu(horario_inicio, horario_fim, premio);
		
		

        /* Busca */
        else if (sscanf(input, "SELECT * FROM jogadores WHERE id_jogador = '%[^']';", id_jogador) == 1)
            buscar_jogador_id_menu(id_jogador);
        else if (sscanf(input, "SELECT * FROM kits WHERE id_kit = '%[^']';", id_kit) == 1)
            buscar_kit_id_menu(id_kit);
        else if (sscanf(input, "SELECT * FROM partidas WHERE id_partida = '%[^']';", id_partida) == 1)
            buscar_partida_id_menu(id_partida);


        /* Listagem */
        else if (strcmp("SELECT * FROM jogadores ORDER BY id_jogador ASC;", input) == 0)
            listar_jogadores_id_menu();
        else if (sscanf(input, "SELECT * FROM jogadores WHERE '%[^']' IN array_append(kits) ORDER BY id_jogador ASC;", nome_kit) == 1)
            listar_jogadores_kits_menu(nome_kit);
        else if (sscanf(input, "SELECT * FROM kits WHERE preco <= ('SELECT saldo FROM jogadores WHERE id_jogador = '%[^']' ');", id_jogador) == 1)
            listar_kits_compra_menu(id_jogador);
        else if (sscanf(input, "SELECT * FROM partidas WHERE inicio BETWEEN '%[^']' AND '%[^']' ORDER BY inicio ASC;", horario_inicio, horario_fim) == 2)
            listar_partidas_periodo_menu(horario_inicio, horario_fim);


        /* Liberar espaço */
        else if (strcmp("VACUUM jogadores;", input) == 0)
            liberar_espaco_menu();


        /* Imprimir arquivos de dados */
        else if (strcmp("\\echo file ARQUIVO_JOGADORES", input) == 0)
            imprimir_arquivo_jogadores_menu();
        else if (strcmp("\\echo file ARQUIVO_KITS", input) == 0)
            imprimir_arquivo_kits_menu();
        else if (strcmp("\\echo file ARQUIVO_PARTIDAS", input) == 0)
            imprimir_arquivo_partidas_menu();
        else if (strcmp("\\echo file ARQUIVO_RESULTADOS", input) == 0)
            imprimir_arquivo_resultados_menu();


        /* Imprimir índices primários */
        else if (strcmp("\\echo index jogadores_idx", input) == 0)
            imprimir_jogadores_idx_menu();
        else if (strcmp("\\echo index kits_idx", input) == 0)
            imprimir_kits_idx_menu();
        else if (strcmp("\\echo index partidas_idx", input) == 0)
            imprimir_partidas_idx_menu();
        else if (strcmp("\\echo index resultados_idx", input) == 0)
            imprimir_resultados_idx_menu();


        /* Imprimir índices secundários */
        else if (strcmp("\\echo index preco_kit_idx", input) == 0)
            imprimir_preco_kit_idx_menu();
        else if (strcmp("\\echo index data_idx", input) == 0)
            imprimir_data_idx_menu();
        else if (strcmp("\\echo index jogador_kits_secundario_idx", input) == 0)
            imprimir_jogador_kits_secundario_idx_menu();
        else if (strcmp("\\echo index jogador_kits_primario_idx", input) == 0)
            imprimir_jogador_kits_primario_idx_menu();


        /* Liberar memória eventualmente alocada e encerrar programa */
        else if (strcmp("\\q", input) == 0)
        { liberar_memoria_menu(); return 0; }
        else if (sscanf(input, "SET SRAND %lu;", &seed) == 1)
        { prng_srand(seed); printf(SUCESSO); continue; }
        else if (sscanf(input, "SET TIME '%[^']';", datetime) == 1)
        { if (set_time(datetime)) printf(SUCESSO); else printf(ERRO_VALOR_INVALIDO); continue; }


        else
            printf(ERRO_OPCAO_INVALIDA);

        tick_time();
    }

    return 0;
}
