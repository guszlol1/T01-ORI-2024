/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Organização de Recuperação da Informação
 * Prof. Tiago A. Almeida
 *
 * Trabalho 01 - Indexação
 *
 * ========================================================================== *
 *   <<< IMPLEMENTE AQUI!!! COPIE E COLE O CONTEÚDO DESTE ARQUIVO NO AVA >>>
 * ========================================================================== */

/* Bibliotecas */
#include "ORI_T01_HEADER.h"

/* ===========================================================================
 * ================================= FUNÇÕES ================================= */
/* <<< COLOQUE AQUI OS DEMAIS PROTÓTIPOS DE FUNÇÕES, SE NECESSÁRIO >>> */

bool verificaKit(char *id_jogador, char *id_partida);


/* Funções auxiliares para o qsort. */

/* Função de comparação entre chaves do índice jogadores_idx */
int qsort_jogadores_idx(const void *a, const void *b) {
	return strcmp (((jogadores_index*)a)->id_jogador, ((jogadores_index*)b)->id_jogador);
}


/* Função de comparação entre chaves do índice kits_idx */
int qsort_kits_idx(const void *a, const void *b) {
	return strcmp (((kits_index*)a)->id_kit, ((kits_index*)b)->id_kit);
}


/* Função de comparação entre chaves do índice partidas_idx */
int qsort_partidas_idx(const void *a, const void *b) {
	return strcmp (((partidas_index*)a)->id_partida, ((partidas_index*)b)->id_partida);
}


/* Função de comparação entre chaves do índice resultados_idx */
int qsort_resultados_idx(const void *a, const void *b) {
	int compararJogador =  strcmp (((resultados_index*)a)->id_jogador, ((resultados_index*)b)->id_jogador);
	if(compararJogador == 0){
		return strcmp (((resultados_index*)a)->id_partida, ((resultados_index*)b)->id_partida);		
	}
	else{
		return compararJogador;
	}
}

/* Função de comparação entre chaves do índice preco_kit_idx */
int qsort_preco_kit_idx(const void *a, const void *b) {
    preco_kit_index *kitA = (preco_kit_index *)a;
    preco_kit_index *kitB = (preco_kit_index *)b;

    if (kitA->preco < kitB->preco)
	   return -1;
    else if (kitA->preco > kitB->preco)
	   return 1;
	else
	return strcmp (((preco_kit_index*)a)->id_kit, ((preco_kit_index*)b)->id_kit);	
       
}



/* Função usada na comparação entre as chaves do índice data_idx */
int qsort_data_idx(const void *a, const void *b) {
	return strcmp( ( (data_index *)a )->inicio, ( (data_index *)b )->inicio);	
}


/* Função de comparação entre vitórias, eliminacoes e tempo de sobrevivencia dos jogadores
 * Usada na função recompensar_vencedores_periodo; */
int qsort_info_jogador(const void *a, const void *b) {

	Info_Jogador *j1 = (Info_Jogador *)a;
    Info_Jogador *j2 = (Info_Jogador *)b;

	if (j1->vitorias != j2->vitorias) {
        return j1->vitorias - j2->vitorias;
    }

    if (j1->eliminacoes != j2->eliminacoes) {
        return j1->eliminacoes - j2->eliminacoes;
    }
    
    if(strcmp(j1->sobrevivencia, j2->sobrevivencia) != 0) {
        return strcmp(j1->sobrevivencia, j2->sobrevivencia);
    }
    return strcmp(j1->id_jogador, j2->id_jogador);
}



/* Função de comparação entre chaves do índice secundário de jogador_kits_secundario_idx */
int qsort_jogador_kits_secundario_idx(const void *a, const void *b) {
	return strcmp( ( (jogador_kits_secundario_index *)a )->chave_secundaria, ( (jogador_kits_secundario_index *)b )->chave_secundaria);
}


/* Função de comparação entre chaves do índice secundário de jogador_kits_primario_idx */
int qsort_inverted_list_primary_search(const void *a, const void *b) {	
	return strcmp( ( (jogador_kits_primario_index *)a )->chave_primaria, ( (jogador_kits_primario_index *)b )->chave_primaria);
}


/* Cria o índice respectivo */
void criar_jogadores_idx() {
	if (!jogadores_idx)
		jogadores_idx = malloc(MAX_REGISTROS * sizeof(jogadores_index));

	if (!jogadores_idx) {
		printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for (unsigned i = 0; i < qtd_registros_jogadores; ++i) {

		Jogador j = recuperar_registro_jogador(i);

		if (strncmp(j.id_jogador, "*|", 2) == 0)
			jogadores_idx[i].rrn = -1;
		else
			jogadores_idx[i].rrn = i;

		strcpy (jogadores_idx[i].id_jogador, j.id_jogador);
	}

	qsort(jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx);
	printf(INDICE_CRIADO, "jogadores_idx");
}


void criar_kits_idx() {
	if(!kits_idx)
	   kits_idx = malloc(MAX_REGISTROS * sizeof(kits_index));

	if(!kits_idx){
	    printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for(unsigned int i = 0; i < qtd_registros_kits; i++){
		Kit k = recuperar_registro_kit(i);

		if(strncmp(k.id_kit,"*|", 2) == 0)
		   kits_idx[i].rrn = -1;
		else 
		   kits_idx[i].rrn = i;  

		strcpy(kits_idx[i].id_kit, k.id_kit);     
	}

	qsort(kits_idx, qtd_registros_kits, sizeof(kits_index), qsort_kits_idx);
	printf(INDICE_CRIADO, "kits_idx");	   

}


void criar_partidas_idx() {
	if(!partidas_idx)
	   partidas_idx = malloc(MAX_REGISTROS * sizeof(partidas_index));

	if(!partidas_idx){
	    printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for(unsigned int i = 0; i < qtd_registros_partidas; i++){
		Partida p = recuperar_registro_partida(i);

		if(strncmp(p.id_partida, "*|", 2) == 0)
		   partidas_idx[i].rrn = -1;
		else
		   partidas_idx[i].rrn = i;

		strcpy(partidas_idx[i].id_partida, p.id_partida);
	}

	qsort(partidas_idx, qtd_registros_partidas, sizeof(partidas_index), qsort_partidas_idx);
	printf(INDICE_CRIADO, "partidas_idx");	
}


void criar_resultados_idx(){
	if(!resultados_idx)
	   resultados_idx = malloc(MAX_REGISTROS * sizeof(resultados_index));

	if(!partidas_idx){
	    printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for(unsigned int i = 0; i < qtd_registros_partidas; i++){
		Resultado r = recuperar_registro_resultado(i);

		if(strncmp(r.id_partida, "*|", 2) == 0)
		   resultados_idx[i].rrn = -1;
		else
		   resultados_idx[i].rrn = i;

		strcpy(resultados_idx[i].id_partida, r.id_partida);
		strcpy(resultados_idx[i].id_jogador, r.id_jogador);

	}

	qsort(resultados_idx, qtd_registros_resultados, sizeof(resultados_index), qsort_resultados_idx);
	printf(INDICE_CRIADO, "resultados_idx");	
}


void criar_preco_kit_idx() {
	if(!preco_kit_idx)
	   preco_kit_idx = malloc(MAX_REGISTROS * sizeof(preco_kit_index));

	if(!preco_kit_idx){
		printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);		
	}

	for(unsigned int i = 0; i < qtd_registros_kits; i++){
		Kit k = recuperar_registro_kit(i);

		if(strncmp(k.id_kit,"*|", 2) == 0)
		   kits_idx[i].rrn = -1;
		else 
		   kits_idx[i].rrn = i;  

		strcpy(kits_idx[i].id_kit, k.id_kit);
		preco_kit_idx[i].preco = k.preco;
		strcpy(preco_kit_idx[i].id_kit, k.id_kit);
   
	}
	
	qsort(preco_kit_idx, qtd_registros_kits, sizeof(preco_kit_index), qsort_preco_kit_idx);
	printf(INDICE_CRIADO, "preco_kit_idx");
}


void criar_data_idx() {
	if(!data_idx)
	   data_idx = malloc(MAX_REGISTROS * sizeof(data_index));

	if(!data_idx){
		printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for(unsigned int i = 0; i < qtd_registros_partidas; i++){
		Partida p = recuperar_registro_partida(i);

		strcpy(data_idx[i].id_partida, p.id_partida);
		strcpy(data_idx[i].inicio, p.inicio);
	}

	qsort(data_idx, qtd_registros_partidas, sizeof(data_index), qsort_data_idx);
	printf(INDICE_CRIADO, "data_idx");	
}


void criar_jogador_kits_idx() {	
    if (!jogador_kits_idx.jogador_kits_primario_idx) {
        jogador_kits_idx.jogador_kits_primario_idx = malloc(MAX_REGISTROS * sizeof(jogador_kits_primario_index));
    }

    if (!jogador_kits_idx.jogador_kits_secundario_idx) {
        jogador_kits_idx.jogador_kits_secundario_idx = malloc(MAX_REGISTROS * sizeof(jogador_kits_secundario_index));
    }

    if (!jogador_kits_idx.jogador_kits_primario_idx || !jogador_kits_idx.jogador_kits_secundario_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }

    for (unsigned i = 0; i < qtd_registros_jogadores; ++i) {
        Jogador j = recuperar_registro_jogador(i);
        for (unsigned g = 0; g < QTD_MAX_KITS; g++) {
            if (j.kits[g][0] != '\0') {
				kits_index k;
				strcpy(k.id_kit, j.kits[g]);
				int found = busca_binaria((void *)&k, kits_idx, qtd_registros_kits, sizeof(kits_index), qsort_kits_idx, false, 0);
				int rrn = kits_idx[found].rrn;
				Kit K = recuperar_registro_kit(rrn);
                inverted_list_insert(K.nome, j.id_jogador, &jogador_kits_idx);
            }
        }
    }
	
	//qsort(jogador_kits_idx.jogador_kits_secundario_idx, jogador_kits_idx.qtd_registros_secundario, sizeof(jogador_kits_secundario_index), qsort_jogador_kits_secundario_idx);
    printf(INDICE_CRIADO, "jogador_kits_idx");
}



/* Recupera do arquivo o registro com o RRN informado
 * e retorna os dados nas structs */
Jogador recuperar_registro_jogador(int rrn) {
	Jogador j;
	char data[TAM_REGISTRO_JOGADOR + 1], *p;

	strncpy(data, ARQUIVO_JOGADORES + (rrn * TAM_REGISTRO_JOGADOR), TAM_REGISTRO_JOGADOR);
	data[TAM_REGISTRO_JOGADOR] = '\0';

	p = strtok(data, ";");
	strcpy(j.id_jogador, p);

	p = strtok(NULL, ";");
	strcpy(j.apelido, p);

	p = strtok(NULL, ";");
	strcpy(j.cadastro, p);

	p = strtok(NULL, ";");
	strcpy(j.premio, p);

	p = strtok(NULL, ";");
	j.saldo = atof(p);

	p = strtok(NULL, ";");

	for (int i = 0; i < QTD_MAX_KITS; ++i) {
		j.kits[i][0] = '\0';
	}

	if (p[0] != '#') {
		p = strtok(p, "|");
		for (int i = 0; p; p = strtok(NULL, "|"), ++i) {
			strcpy(j.kits[i], p);
		}
	}

	return j;
}


Kit recuperar_registro_kit(int rrn) {
    Kit k;
    char data[TAM_REGISTRO_KIT + 1], *p;

    strncpy(data, ARQUIVO_KITS + (rrn * TAM_REGISTRO_KIT), TAM_REGISTRO_KIT);
    data[TAM_REGISTRO_KIT] = '\0';
    
    p = strtok(data, ";");
    strcpy(k.id_kit, p);

    p = strtok(NULL, ";");
    strcpy(k.nome, p);

    p = strtok(NULL, ";");
    strcpy(k.poder, p);

    p = strtok(NULL, ";");
    k.preco = atof(p);

    return k;
}


Partida recuperar_registro_partida(int rrn) {
	Partida p;
	char *data = ARQUIVO_PARTIDAS + (rrn * TAM_REGISTRO_PARTIDA);
	
	strncpy(p.id_partida, data, TAM_ID_PARTIDA - 1);
	data += (TAM_ID_PARTIDA - 1);
	p.id_partida[TAM_ID_PARTIDA - 1] = '\0';

	strncpy(p.inicio, data, TAM_DATETIME - 1);
	data += (TAM_DATETIME - 1);
	p.inicio[TAM_DATETIME - 1] = '\0';

	strncpy(p.duracao, data, TAM_TIME - 1);
	data += (TAM_TIME - 1);
	p.duracao[TAM_TIME - 1] = '\0';

	strncpy(p.cenario, data, TAM_CENARIO - 1);
	data += (TAM_CENARIO - 1);
	p.cenario[TAM_CENARIO - 1] = '\0';

	strncpy(p.id_jogadores, data, TAM_ID_JOGADORES - 1);
	p.id_jogadores[TAM_ID_JOGADORES - 1] = '\0';

	return p;
}


Resultado recuperar_registro_resultado(int rrn) {
	Resultado r;
	char *data = ARQUIVO_RESULTADOS + (rrn * TAM_REGISTRO_RESULTADO);
	char temp[5];

	strncpy(r.id_jogador, data, TAM_ID_JOGADOR - 1);
	data += (TAM_ID_JOGADOR - 1);
	r.id_jogador[TAM_ID_JOGADOR - 1] = '\0';

	strncpy(r.id_partida, data, TAM_ID_PARTIDA - 1);
	data += (TAM_ID_PARTIDA - 1);
	r.id_partida[TAM_ID_PARTIDA - 1] = '\0';

	strncpy(r.id_kit, data, TAM_ID_KIT - 1);
	data += (TAM_ID_KIT - 1);
	r.id_kit[TAM_ID_KIT - 1] = '\0';

	strncpy(temp, data, 4);
	r.colocacao = atoi(temp);
	data += 4;

	strncpy(r.sobrevivencia, data, TAM_TIME - 1);
	data += (TAM_TIME - 1);
	r.sobrevivencia[TAM_TIME - 1] = '\0';

	strncpy(temp, data, 4);
	r.eliminacoes = atoi(temp);

	return r;
	
}

/* Escreve em seu respectivo arquivo na posição informada (RRN) */
void escrever_registro_jogador(Jogador j, int rrn) {
	char data[TAM_REGISTRO_JOGADOR + 1], number[100];
	data[0] = '\0'; number[0] = '\0';

	strcat(data, j.id_jogador);
	strcat(data, ";");
	strcat(data, j.apelido);
	strcat(data, ";");
	strcat(data, j.cadastro);
	strcat(data, ";");
	strcat(data, j.premio);
	strcat(data, ";");
	sprintf(number, "%013.2lf", j.saldo);
	strcat (data, number);
	strcat(data, ";");

	for (int i = 0; i < QTD_MAX_KITS; ++i) {
		if (strlen(j.kits[i]) > 0) {
			if (i != 0)
				strcat (data, "|");
			strcat(data, j.kits[i]);
		}
	}
	strcat(data, ";");


	strpadright(data, '#', TAM_REGISTRO_JOGADOR);

	strncpy(ARQUIVO_JOGADORES + rrn*TAM_REGISTRO_JOGADOR, data, TAM_REGISTRO_JOGADOR);
}

void escrever_registro_kit(Kit k, int rrn) {
    char data[TAM_REGISTRO_KIT + 1], number[100];
    data[0] = '\0'; 

    
    strcat(data, k.id_kit);
    strcat(data, ";");
    strcat(data, k.nome);
    strcat(data, ";");
    strcat(data, k.poder);
    strcat(data, ";");
    
    sprintf(number, "%013.2lf", k.preco);
    strcat(data, number);
    strcat(data, ";");
    
    strpadright(data, '#', TAM_REGISTRO_KIT);
    
    strncpy(ARQUIVO_KITS + rrn * TAM_REGISTRO_KIT, data, TAM_REGISTRO_KIT);
}



void escrever_registro_partida(Partida p, int rrn) {
    char data[TAM_REGISTRO_PARTIDA + 1]; 
    data[0] = '\0';   
   
    strncat(data, p.id_partida, TAM_ID_PARTIDA - 1);    
    strncat(data, p.inicio, TAM_DATETIME - 1);       
    strncat(data, p.duracao, TAM_TIME - 1);       
    strncat(data, p.cenario, TAM_CENARIO - 1);
	strncat(data, p.id_jogadores, TAM_ID_JOGADORES - 1);    
    

    strncpy(ARQUIVO_PARTIDAS + rrn * TAM_REGISTRO_PARTIDA, data, TAM_REGISTRO_PARTIDA);
}



void escrever_registro_resultado(Resultado jp, int rrn) {
	char data[TAM_REGISTRO_RESULTADO + 1]; 
	data[0] = '\0';
	char aux[5];	

	strncat(data, jp.id_jogador, 11); 	
	strncat(data, jp.id_partida, 8);
	strncat(data, jp.id_kit, 3);

	snprintf(aux, sizeof(aux), "%04d", jp.colocacao);
	strncat(data, aux, 4); 

   strncat(data, jp.sobrevivencia, 6);

   snprintf(aux, sizeof(aux), "%04d", jp.eliminacoes);
   strncat(data, aux, 4);

   strncpy(ARQUIVO_RESULTADOS + rrn * TAM_REGISTRO_RESULTADO, data, TAM_REGISTRO_RESULTADO);

}
    


/* Exibe um registro com base no RRN */
bool exibir_jogador(int rrn) {
	if (rrn < 0)
		return false;

	Jogador j = recuperar_registro_jogador(rrn);

	printf ("%s, %s, %s, %s, %.2lf\n", j.id_jogador, j.apelido, j.cadastro, j.premio, j.saldo);

	return true;
}

bool exibir_kit(int rrn) {
    if (rrn < 0) 
	return false;
    Kit k = recuperar_registro_kit(rrn);
    printf("%s, %s, %s, %.2lf\n", k.id_kit, k.nome, k.poder, k.preco);
    return true;
}


bool exibir_partida(int rrn) {
	if (rrn < 0) 
	return false;
    Partida p = recuperar_registro_partida(rrn);
    printf("%s, %s, %s, %s, %s\n", p.id_partida, p.inicio, p.duracao, p.cenario, p.id_jogadores);
    return true;	
}


/* Funções principais */
void cadastrar_jogador_menu(char *id_jogador, char *apelido) {

  jogadores_index j;
  strcpy(j.id_jogador, id_jogador);

  int found = busca_binaria((void *)&j, jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx, false, 0);

  // se retornar -1, nao existe e pode criar
  if (found != -1) {
    printf(ERRO_PK_REPETIDA, id_jogador);
    return;
  }
  
  Jogador J;
  char data[TAM_DATETIME];
  current_datetime(data);

  strcpy(J.id_jogador, id_jogador);
  strcpy(J.apelido, apelido);
  strcpy(J.cadastro, data);
  strcpy(J.premio, "000000000000");
  J.saldo = 0.00;
  memset(J.kits, '\0', sizeof(J.kits));

	escrever_registro_jogador(J, qtd_registros_jogadores);

	strcpy(jogadores_idx[qtd_registros_jogadores].id_jogador, id_jogador);
	jogadores_idx[qtd_registros_jogadores].rrn = qtd_registros_jogadores;

	qtd_registros_jogadores++;
	
	qsort(jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx);

	printf(SUCESSO);
	
}


void remover_jogador_menu(char *id_jogador) {
	jogadores_index j;
	strcpy(j.id_jogador, id_jogador);
	int found = busca_binaria((void *)&j, jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx, false, 0);
	if(found == -1){
	   printf(ERRO_REGISTRO_NAO_ENCONTRADO);
       return;		
	}

	int rrn = jogadores_idx[found].rrn;
	char aux[2] = "*|";

	strncpy(ARQUIVO_JOGADORES + rrn*TAM_REGISTRO_JOGADOR, aux, 2);

	jogadores_idx[found].rrn = -1;

	qsort(jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx);
	printf(SUCESSO);	

}


void adicionar_saldo_menu(char *id_jogador, double valor) {
	adicionar_saldo(id_jogador, valor, true);
}


void adicionar_saldo(char *id_jogador, double valor, bool flag) {
	jogadores_index j;
	strcpy(j.id_jogador, id_jogador);	
	
  int found = busca_binaria((void *)&j, jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx, false, 0);

  if (found == -1 || jogadores_idx[found].rrn == -1) {
    printf(ERRO_REGISTRO_NAO_ENCONTRADO);
    return;
  }

  if (valor <= 0) {
    printf(ERRO_VALOR_INVALIDO);
    return;
  }

  int rrn = jogadores_idx[found].rrn;
    
  Jogador J = recuperar_registro_jogador(rrn);
  J.saldo += valor;

    
  escrever_registro_jogador(J, rrn);

  printf(SUCESSO);
}


void cadastrar_kit_menu(char *nome, char *poder, double preco) {

	kits_index K;
    K.rrn = qtd_registros_kits;
    sprintf(K.id_kit, "%03d", qtd_registros_kits);
    int found = busca_binaria((void *)&K, kits_idx, qtd_registros_kits, sizeof(kits_index), qsort_kits_idx, false, 0);

    if (found != -1) {
        printf(ERRO_PK_REPETIDA, K.id_kit);        
        return;
    }

    Kit k;
    strcpy(k.id_kit, K.id_kit);
    strcpy(k.nome, nome);
    strcpy(k.poder, poder);
    k.preco = preco;

    escrever_registro_kit(k, qtd_registros_kits);

    strcpy(kits_idx[qtd_registros_kits].id_kit, K.id_kit);
    kits_idx[qtd_registros_kits].rrn = K.rrn;
	
    preco_kit_index P;
    strcpy(P.id_kit, K.id_kit); 
    P.preco = preco;
    preco_kit_idx[qtd_registros_kits].preco = P.preco;
    strcpy(preco_kit_idx[qtd_registros_kits].id_kit, P.id_kit);

    qtd_registros_kits++;
    
    qsort(kits_idx, qtd_registros_kits, sizeof(kits_index), qsort_kits_idx);
    qsort(preco_kit_idx, qtd_registros_kits, sizeof(preco_kit_index), qsort_preco_kit_idx);
    printf(SUCESSO);
	
}


void comprar_kit_menu(char *id_jogador, char *id_kit) {
    jogadores_index j;
    kits_index k;

    strcpy(k.id_kit, id_kit);
    strcpy(j.id_jogador, id_jogador);

    int foundJ = busca_binaria((void *)&j, jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx, false, 0);
    int foundK = busca_binaria((void *)&k, kits_idx, qtd_registros_kits, sizeof(kits_index), qsort_kits_idx, false, 0);

    if (foundJ == -1 || foundK == -1) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }

    int rrn = jogadores_idx[foundJ].rrn;    
    Jogador J = recuperar_registro_jogador(rrn);

    int rrnK = kits_idx[foundK].rrn;    
    Kit K = recuperar_registro_kit(rrnK);

    if (J.saldo < K.preco) {
        printf(ERRO_SALDO_NAO_SUFICIENTE);
    } else {
        int KitRepetido = 0;

        for (int i = 0; i < QTD_MAX_KITS; i++) {
            if (strcmp(J.kits[i], K.nome) == 0) {
                KitRepetido = 1;
                break;
            }
        }

        if (KitRepetido) {
            printf(ERRO_KIT_REPETIDO, J.id_jogador, K.id_kit);
        } else {
            J.saldo -= K.preco;
            for (int i = 0; i < QTD_MAX_KITS; i++) {
                if (J.kits[i][0] == '\0') {  
                    strcpy(J.kits[i], K.id_kit); 
                    break; //escreve no primeiro e para
                }
            }
            escrever_registro_jogador(J, rrn);
            inverted_list_insert(K.nome, J.id_jogador, &jogador_kits_idx);
            printf(SUCESSO);
        }
    }
}


void executar_partida_menu(char *inicio, char *duracao, char *cenario, char *id_jogadores, char *kits_jogadores, char *duracoes_jogadores, char *eliminacoes_jogadores) {
	Partida p;		

	for(int i = 0; i < QTD_MAX_JOGADORES; i++){
		jogadores_index J;	

		strncpy(J.id_jogador, id_jogadores + i * 11, TAM_ID_JOGADOR - 1);
		J.id_jogador[TAM_ID_JOGADOR - 1] = '\0';

		int found = busca_binaria((void *)&J, jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx, false, 0);		  

		if(found == -1 || jogadores_idx[found].rrn == -1 ){
		   printf(ERRO_REGISTRO_NAO_ENCONTRADO);
		   return;
		}	

		kits_index K;
		strncpy(K.id_kit, kits_jogadores + i * 3, TAM_ID_KIT - 1);
		K.id_kit[TAM_ID_KIT - 1] = '\0';

		int nomeKit = busca_binaria((void *)&K, kits_idx, qtd_registros_kits, sizeof(kits_index), qsort_kits_idx, false, 0);
		int rrn = kits_idx[nomeKit].rrn;
		Kit k = recuperar_registro_kit(rrn);	

		if(!verificaKit(J.id_jogador, K.id_kit)){			
			printf(ERRO_JOGADOR_KIT, J.id_jogador, k.nome); //tem um erro aqui quando recupera o nome do kit, ele nao pega a partida, nao consigo resolver
			return;
		}			
				
	}
    //printf("oi\n");
	sprintf(p.id_partida, "%08d", qtd_registros_partidas);
	strcpy(p.inicio, inicio);
	strcpy(p.duracao, duracao);
	strcpy(p.cenario, cenario);
	strcpy(p.id_jogadores, id_jogadores);

	escrever_registro_partida(p, qtd_registros_partidas);

	strcpy(partidas_idx[qtd_registros_partidas].id_partida, p.id_partida);
	partidas_idx[qtd_registros_partidas].rrn = qtd_registros_partidas;

	strcpy(data_idx[qtd_registros_partidas].id_partida, p.id_partida);
	strcpy(data_idx[qtd_registros_partidas].inicio, p.inicio);

	qtd_registros_partidas++;
	
	qsort(partidas_idx, qtd_registros_partidas, sizeof(partidas_index), qsort_partidas_idx);
	qsort(data_idx, qtd_registros_partidas, sizeof(data_index), qsort_data_idx);

	printf(SUCESSO);

	for(int i = 0; i < QTD_MAX_JOGADORES; i++){
		Resultado r;
		char aux[5];
		aux[0] = '\0';		

		sprintf(aux, "%04d", i + 1);
		r.colocacao = atoi(aux);

		strncpy(r.id_partida, p.id_partida, TAM_ID_PARTIDA - 1);
		r.id_partida[TAM_ID_PARTIDA - 1] = '\0';

		strncpy(r.id_jogador, p.id_jogadores + i * (TAM_ID_JOGADOR - 1), TAM_ID_JOGADOR - 1);
		r.id_jogador[TAM_ID_JOGADOR - 1] = '\0';

		strncpy(r.id_kit, kits_jogadores + i * (TAM_ID_KIT- 1),  TAM_ID_KIT- 1);
		r.id_kit[TAM_ID_KIT - 1] = '\0';		

		strncpy(r.sobrevivencia, duracoes_jogadores + i * (TAM_TIME- 1),  TAM_TIME- 1);
		r.sobrevivencia[TAM_TIME - 1] = '\0';

		strncpy(aux, eliminacoes_jogadores + i * 4, 4);
	    r.eliminacoes = atoi(aux);

		escrever_registro_resultado(r, qtd_registros_resultados);		

		strcpy(resultados_idx[qtd_registros_resultados].id_partida, r.id_partida);
		strcpy(resultados_idx[qtd_registros_resultados].id_jogador, r.id_jogador);
	    resultados_idx[qtd_registros_resultados].rrn = qtd_registros_resultados;

		qtd_registros_resultados++;

		qsort(resultados_idx, qtd_registros_resultados, sizeof(resultados_index), qsort_resultados_idx);
		//27 - 11 ficou funcional, antes estava errado	

	}		
}


void recompensar_vencedores_menu (char *data_inicio, char *data_fim, double premio) {
	
	data_index d;
	strcpy(d.inicio, data_inicio);
	int found = busca_binaria_com_reps((void*)&d, data_idx, qtd_registros_partidas, sizeof(data_index), qsort_data_idx, false, -1, 1);
	//printf("%d", found);

	data_index D;
	strcpy(D.inicio, data_fim);
	int founD = busca_binaria_com_reps((void*)&D, data_idx, qtd_registros_partidas, sizeof(data_index), qsort_data_idx, false, 1, -1);
	//printf(" %d\n", founD);

	//printf("oiiiiiiiiiiiiiiiiiiiii\n");

	//if(found == -1 || founD == -1){
		//printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	//	return;
	//}
	//printf("oiiiiiiiiiiiiiiiiiiiii\n");

	Info_Jogador info[qtd_registros_jogadores];
	int count_qsort = 0;

	for (int i = 0; i < qtd_registros_jogadores; i++){
		info[i].eliminacoes = 0;
		info[i].vitorias = 0;
		strcpy(info[i].sobrevivencia, "000000");		
	}

	for(int i = found; i <= founD; i++){

		partidas_index partida;
		strcpy(partida.id_partida, data_idx[i].id_partida);

		int foundPartida = busca_binaria((void*)&partida, partidas_idx, qtd_registros_partidas, sizeof(partidas_index), qsort_partidas_idx, false, 0); //nao pode ser -1, nao faz sentido excluir uma partida
		int rrnPartida = partidas_idx[foundPartida].rrn;

		Partida P = recuperar_registro_partida(rrnPartida);

		for (int j = 0; j < QTD_MAX_JOGADORES; j++){
			resultados_index resultado;

			strncpy(resultado.id_jogador, P.id_jogadores + j * (TAM_ID_JOGADOR - 1), TAM_ID_JOGADOR - 1);
			resultado.id_jogador[TAM_ID_JOGADOR - 1] = '\0';

			strncpy(resultado.id_partida, P.id_partida, TAM_ID_PARTIDA - 1);
		    resultado.id_partida[TAM_ID_PARTIDA - 1] = '\0';

			int foundResultado = busca_binaria((void*)&resultado, resultados_idx, qtd_registros_resultados, sizeof(resultados_index), qsort_resultados_idx, false, 0); //nao pode ser -1 tambem
            int rrnResultado = resultados_idx[foundResultado].rrn;

			Resultado resultadoJogador = recuperar_registro_resultado(rrnResultado);

			int k;
			for(k = 0; k < count_qsort; k++){

				 if(strcmp(resultadoJogador.id_jogador, info[k].id_jogador) == 0){
					if(resultadoJogador.colocacao == 1){
						info[k].vitorias++;
					}

					info[k].eliminacoes += resultadoJogador.eliminacoes;

					//somar sobrevivencia?
					if(strcmp(resultadoJogador.sobrevivencia, info[k].sobrevivencia) > 0) {
                       strcpy(info[k].sobrevivencia, resultadoJogador.sobrevivencia);
					}
					break; //sai do loop
				 }
			}

			if(k == count_qsort){
				strcpy(info[k].id_jogador, resultadoJogador.id_jogador);
				resultadoJogador.id_jogador[TAM_ID_JOGADOR - 1] = '\0';
				info[k].eliminacoes = resultadoJogador.eliminacoes;

				if(resultadoJogador.colocacao == 1){
						info[k].vitorias++;
					}
				strcpy(info[k].sobrevivencia, resultadoJogador.sobrevivencia);

				count_qsort++;
			}

		}	
	}	
	qsort(info, count_qsort, sizeof(Info_Jogador), qsort_info_jogador);

	jogadores_index jogador;
	strcpy(jogador.id_jogador, info[count_qsort - 1].id_jogador);

	int foundJogador = busca_binaria((void*)&jogador, jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx, false, 0);
	int rrnJogador = jogadores_idx[foundJogador].rrn;

	if(rrnJogador == -1){
		jogadores_index second;
		strcpy(second.id_jogador, info[count_qsort - 2].id_jogador);
		int foundSecond = busca_binaria((void*)&second, jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx, false, 0);
		int rrnSecond = jogadores_idx[foundSecond].rrn;

		Jogador secondwinner = recuperar_registro_jogador(rrnSecond);
		printf(ERRO_JOGADOR_REMOVIDO, premio, secondwinner.apelido, info[count_qsort - 2].vitorias, info[count_qsort - 2].eliminacoes);

		strcpy(secondwinner.premio, data_fim);
		secondwinner.saldo += premio;
		escrever_registro_jogador(secondwinner, rrnSecond);
		return;
	}

	Jogador firstwinner = recuperar_registro_jogador(rrnJogador);
	printf(CONCEDER_PREMIO, firstwinner.apelido, info[count_qsort - 1].vitorias, info[count_qsort - 1].eliminacoes, premio);
	strcpy(firstwinner.premio, data_fim);
	firstwinner.saldo += premio;
	escrever_registro_jogador(firstwinner, rrnJogador);

}


/* Busca */
void buscar_jogador_id_menu(char *id_jogador) {
	jogadores_index index;
	strcpy(index.id_jogador, id_jogador);
	int found = busca_binaria((void*)&index, jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx, true, 0);
	if (found == -1)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
		exibir_jogador(jogadores_idx[found].rrn);
}


void buscar_kit_id_menu(char *id_kit) {
    kits_index index;
    strcpy(index.id_kit, id_kit);
    int found = busca_binaria((void*)&index, kits_idx, qtd_registros_kits, sizeof(kits_index), qsort_kits_idx, true, 0);
    if (found == -1) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
    } else {
        exibir_kit(kits_idx[found].rrn);
    }
}


void buscar_partida_id_menu(char *id_partida) {
	partidas_index index;
	strcpy(index.id_partida, id_partida);	
	int found = busca_binaria((void*)&index, partidas_idx, qtd_registros_partidas, sizeof(partidas_index), qsort_partidas_idx, true, 0);
	if (found == -1) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
    } else {
        exibir_partida(partidas_idx[found].rrn);
    }
}


/* Listagem */
void listar_jogadores_id_menu() {
	if (qtd_registros_jogadores == 0)
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	else
		for (unsigned int i = 0; i < qtd_registros_jogadores; i++)
			exibir_jogador(jogadores_idx[i].rrn);
}


void listar_jogadores_kits_menu(char *kit) {
    // procura no primario e no secundario
    // se achar printa o jogador  

	int firstIndex = 0;
	int secondIndex = 0;
	char data[jogador_kits_idx.qtd_registros_primario][11];

	bool found = inverted_list_secondary_search(&firstIndex, false, kit, &jogador_kits_idx);	
	int count = 0;

	if(!found)
	   printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	else{
		inverted_list_primary_search(data, true, firstIndex, &secondIndex, &jogador_kits_idx);
		for(int i = 0; i < jogador_kits_idx.qtd_registros_primario; i++){
			if(strcmp(data[i], "") == 0){
				break;
			}
			count++;
		}

		jogadores_index *jogador = malloc(count * sizeof(jogadores_index));

		for(int i = 0; i < count; i++){
			strncpy(jogador[i].id_jogador, data[i], TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX);
			  for(int j = 0; j < jogador_kits_idx.qtd_registros_primario; j++){
				   if(strncmp(jogador[i].id_jogador, jogadores_idx[j].id_jogador, TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX) == 0){
					 jogador[i].rrn = jogadores_idx[j].rrn;
				   }
			  }
		}
		qsort(jogador, count, sizeof(jogadores_index), qsort_jogadores_idx);

		for(int i = 0; i < count; i++){
			exibir_jogador(jogador[i].rrn);
		}
		free(jogador);
	}
}


void listar_kits_compra_menu(char *id_jogador) {
	if(qtd_registros_kits == 0)
	printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);

	jogadores_index index;
	strcpy(index.id_jogador, id_jogador);

	int found = busca_binaria((void*)&index, jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx, false, 0);
	int rrn = jogadores_idx[found].rrn;

	if(found == -1){
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);		
	}
	else if(rrn == -1){
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
		return;
	}
	else{
		Jogador j = recuperar_registro_jogador(rrn);
		int valor = 0;

		for(int i = 0; i < qtd_registros_kits; i++){			
			valor = preco_kit_idx[i].preco;

			kits_index indexK;
			strcpy(indexK.id_kit, preco_kit_idx[i].id_kit);	
			int foundK = busca_binaria((void*)&indexK, kits_idx, qtd_registros_kits, sizeof(kits_index), qsort_kits_idx, false, 0);
			int rrnK = kits_idx[foundK].rrn;

			if(valor <= j.saldo){			
			exibir_kit(rrnK);
			}
		}
	}

}


void listar_partidas_periodo_menu(char *data_inicio, char *data_fim) {
	data_index d;
	strcpy(d.inicio, data_inicio);
	int found = busca_binaria_com_reps((void*)&d, data_idx, qtd_registros_partidas, sizeof(data_index), qsort_data_idx, true, -1, 1);
	//printf("%d", found);

	data_index D;
	strcpy(D.inicio, data_fim);
	int founD = busca_binaria_com_reps((void*)&D, data_idx, qtd_registros_partidas, sizeof(data_index), qsort_data_idx, false, 1, -1);
	//printf(" %d\n", founD);
	
	if(found == -1 || founD == -1){
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
		return;
	}

	for(int i = found; i <= founD; i++){
		partidas_index indice;
		strcpy(indice.id_partida, data_idx[i].id_partida);

		int Found = busca_binaria((void*)&indice, partidas_idx, qtd_registros_partidas, sizeof(partidas_index), qsort_partidas_idx, false, 0);
		int rrn = partidas_idx[Found].rrn;
		
		exibir_partida(rrn);
	}

}


/* Imprimir arquivos de dados */
void imprimir_arquivo_jogadores_menu() {
	if (qtd_registros_jogadores == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_JOGADORES);
}


void imprimir_arquivo_kits_menu() {
	if (qtd_registros_kits == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_KITS);			
}


void imprimir_arquivo_partidas_menu() {
	if(qtd_registros_partidas == 0)
	   printf(ERRO_ARQUIVO_VAZIO);
	else
	   printf("%s\n", ARQUIVO_PARTIDAS);	   
}


void imprimir_arquivo_resultados_menu() {
	if(qtd_registros_resultados == 0)
	   printf(ERRO_ARQUIVO_VAZIO);
	else
	   printf("%s\n", ARQUIVO_RESULTADOS);	   
}


/* Imprimir índices primários */
void imprimir_jogadores_idx_menu() {
	if (jogadores_idx == NULL || qtd_registros_jogadores == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_jogadores; ++i)
			printf("%s, %d\n", jogadores_idx[i].id_jogador, jogadores_idx[i].rrn);
}


void imprimir_kits_idx_menu() {
	if (kits_idx == NULL || qtd_registros_kits == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_kits; ++i)
			printf("%s, %d\n", kits_idx[i].id_kit, kits_idx[i].rrn);
}


void imprimir_partidas_idx_menu() {
	if (partidas_idx == NULL || qtd_registros_partidas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_partidas; ++i)
			printf("%s, %d\n", partidas_idx[i].id_partida, partidas_idx[i].rrn);
}


void imprimir_resultados_idx_menu() {
	if (resultados_idx == NULL || qtd_registros_resultados == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_resultados; i++)
			printf("%s, %s, %d\n", resultados_idx[i].id_jogador, resultados_idx[i].id_partida, resultados_idx[i].rrn);
}


/* Imprimir índices secundários */
void imprimir_preco_kit_idx_menu() {
    if (preco_kit_idx == NULL || qtd_registros_kits == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        for (unsigned i = 0; i < qtd_registros_kits; i++)
            printf("%.2lf, %.3s\n", preco_kit_idx[i].preco, preco_kit_idx[i].id_kit);
}



void imprimir_data_idx_menu() {
	if (data_idx == NULL || qtd_registros_partidas == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        for (unsigned i = 0; i < qtd_registros_partidas; i++)
            printf("%s, %s\n", data_idx[i].id_partida, data_idx[i].inicio);	
}


void imprimir_jogador_kits_secundario_idx_menu() {
	if(!jogador_kits_idx.jogador_kits_secundario_idx || jogador_kits_idx.qtd_registros_secundario == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
	    for(unsigned int i = 0; i < jogador_kits_idx.qtd_registros_secundario; i++){
			printf("%s, %d\n", strupr(jogador_kits_idx.jogador_kits_secundario_idx[i].chave_secundaria), jogador_kits_idx.jogador_kits_secundario_idx[i].primeiro_indice);
		}
}


void imprimir_jogador_kits_primario_idx_menu() {
	if(!jogador_kits_idx.jogador_kits_primario_idx || jogador_kits_idx.qtd_registros_primario == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
	    for(unsigned int i = 0; i < jogador_kits_idx.qtd_registros_primario; i++){
			printf("%s, %d\n", jogador_kits_idx.jogador_kits_primario_idx[i].chave_primaria, jogador_kits_idx.jogador_kits_primario_idx[i].proximo_indice);
		}
}


/* Liberar espaço */
void liberar_espaco_menu() {
    char data2[TAM_ARQUIVO_JOGADORES + 1];
    data2[0] = '\0';

    Jogador j;
    int auxiliar = 0;

    for (int i = 0; i < qtd_registros_jogadores; i++) {
        j = recuperar_registro_jogador(i);

       
        if (strncmp(j.id_jogador, "*|", 2) != 0) {
            
            jogadores_idx[auxiliar].rrn = auxiliar;
            strcpy(jogadores_idx[auxiliar].id_jogador, j.id_jogador);

            auxiliar++;
            
            char data[TAM_REGISTRO_JOGADOR + 1], number[100];
            data[0] = '\0';
            number[0] = '\0';

            strcat(data, j.id_jogador);
            strcat(data, ";");
            strcat(data, j.apelido);
            strcat(data, ";");
            strcat(data, j.cadastro);
            strcat(data, ";");
            strcat(data, j.premio);
            strcat(data, ";");
            sprintf(number, "%013.2lf", j.saldo);
            strcat(data, number);
            strcat(data, ";");

            for (int k = 0; k < QTD_MAX_KITS; ++k) {
                if (strlen(j.kits[k]) > 0) {
                    if (k != 0)
                        strcat(data, "|");
                    strcat(data, j.kits[k]);
                }
            }
            strcat(data, ";");
            
            strpadright(data, '#', TAM_REGISTRO_JOGADOR);

            strcat(data2, data);
        }
    }
    
    strcpy(ARQUIVO_JOGADORES, data2);
    qtd_registros_jogadores = auxiliar;
   
    qsort(jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx);

    printf(SUCESSO);
}


/* Liberar memória e encerrar programa */
void liberar_memoria_menu() {
	free(jogadores_idx);
	free(kits_idx);
	free(partidas_idx);
	free(resultados_idx);
	free(preco_kit_idx);
	free(jogador_kits_idx.jogador_kits_primario_idx);
	free(jogador_kits_idx.jogador_kits_secundario_idx);
}


/* Funções de manipulação de Lista Invertida */
void inverted_list_insert(char *chave_secundaria, char *chave_primaria, inverted_list *t) {
    int index = 0;

    if (inverted_list_secondary_search(&index, false, chave_secundaria, t)) {        
        int aux = index;
        while (t->jogador_kits_primario_idx[aux].proximo_indice != -1) {
            aux = t->jogador_kits_primario_idx[aux].proximo_indice;
        }
        
        t->jogador_kits_primario_idx[aux].proximo_indice = t->qtd_registros_primario;
        
        t->jogador_kits_primario_idx[t->qtd_registros_primario].proximo_indice = -1;
        strcpy(t->jogador_kits_primario_idx[t->qtd_registros_primario].chave_primaria, chave_primaria);
        t->qtd_registros_primario++;
		
    } else {        
        strcpy(t->jogador_kits_secundario_idx[t->qtd_registros_secundario].chave_secundaria, chave_secundaria);
        t->jogador_kits_secundario_idx[t->qtd_registros_secundario].primeiro_indice = t->qtd_registros_primario;
        
        strcpy(t->jogador_kits_primario_idx[t->qtd_registros_primario].chave_primaria, chave_primaria);
        t->jogador_kits_primario_idx[t->qtd_registros_primario].proximo_indice = -1;
        
        t->qtd_registros_secundario++;
        t->qtd_registros_primario++;
    }
    
    qsort(t->jogador_kits_secundario_idx, t->qtd_registros_secundario, sizeof(jogador_kits_secundario_index), qsort_jogador_kits_secundario_idx);
    //qsort(t->jogador_kits_primario_idx, t->qtd_registros_primario, sizeof(jogador_kits_primario_index), qsort_inverted_list_primary_search);
	
}



bool inverted_list_secondary_search(int *result, bool exibir_caminho, char *chave_secundaria, inverted_list *t) {
	
	jogador_kits_secundario_index j;
	strcpy(j.chave_secundaria, chave_secundaria);	
	int indice = busca_binaria((void*)&j, t->jogador_kits_secundario_idx, t->qtd_registros_secundario, sizeof(jogador_kits_secundario_index), qsort_jogador_kits_secundario_idx, false, 0);
	if(indice == -1) 
	   return false;
	else{
		*result = t->jogador_kits_secundario_idx[indice].primeiro_indice;
		return true;
	}
	
}



int inverted_list_primary_search(char result[][TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX], bool exibir_caminho, int indice, int *indice_final, inverted_list *t) {
    int aux = 0;
    int ultimo_indice = indice;

    if (exibir_caminho)
        printf(REGS_PERCORRIDOS);

    int i = indice;
    while (i != -1) {
        if (exibir_caminho) {
            printf(" %d", i);
        }

        if (result != NULL)
            strcpy(result[aux], t->jogador_kits_primario_idx[i].chave_primaria);

        ultimo_indice = i;
        i = t->jogador_kits_primario_idx[i].proximo_indice;
        aux++;
    }

    if (exibir_caminho) {
        printf("\n");
    }

    *indice_final = ultimo_indice;
    return aux;
}



/* Funções de busca binária */
int busca_binaria_com_reps(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int posicao_caso_repetido, int retorno_se_nao_encontrado) {
	int start = 0;
	int mid;
	int end = nmemb - 1;

	if (exibir_caminho)
		printf(REGS_PERCORRIDOS);

	while (start <= end) {
		mid = (start + end) / 2 + ((end - start + 1) % 2 == 0); // se for impar, calcula (inicio + fim) / 2, se for par acrescenta 1 ao valor
        

        if(exibir_caminho)
		   printf(" %d", mid);	

		int cmp = compar(key, ((char *)base0) + mid * size);

		if (cmp == 0) {
			if (exibir_caminho)
				printf("\n");

			if (posicao_caso_repetido == 1) {
				int last = mid;
				int aux = mid + 1;
				while (aux < nmemb && !compar(key, base0 + (aux * size))) {
					last = aux;
					aux++;
				}
				return last;
			} else if (posicao_caso_repetido == -1) { 
				int first = mid;
				int aux = mid - 1;
				while (aux >= 0 && !compar(key, base0 + (aux * size))) { 
					first = aux;
					aux--;
				}
				return first;
			} else {
				return mid;
			}
		} else if (cmp > 0) {
			start = mid + 1;
		} else {
			end = mid - 1;
		}
	}

	if (exibir_caminho)
		printf("\n");

	if (retorno_se_nao_encontrado == -1 && end >= 0) {
		return end;
	} else if (retorno_se_nao_encontrado == 0) {
		return -1;
	} else if (retorno_se_nao_encontrado == 1 && start < nmemb) {
		return start;
	} else {
		return -1;
	}
}



int busca_binaria(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int retorno_se_nao_encontrado) {
	return busca_binaria_com_reps(key, base0, nmemb, size, compar, exibir_caminho, 0, retorno_se_nao_encontrado);
}


char *strpadright(char *str, char pad, unsigned size){
	for (unsigned i = strlen(str); i < size; ++i)
		str[i] = pad;
	str[size] = '\0';
	return str;
}

char *strupr(char *str){
	for (char *p = str; *p; ++p)
		*p = toupper(*p);
	return str;
}

char *strlower(char *str){
	for (char *p = str; *p; ++p)
		*p = tolower(*p);
	return str;
}

bool verificaKit(char *id_jogador, char *id_kit) {
    jogadores_index j;
    strcpy(j.id_jogador, id_jogador);

    int found = busca_binaria((void *)&j, jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx, false, 0);
    int rrn = jogadores_idx[found].rrn;
    Jogador J = recuperar_registro_jogador(rrn);

    for(int i = 0; i < QTD_MAX_KITS; i++) {        
        if(J.kits[i][0] == '\0')
            return false;
        else if((strcmp(J.kits[i], id_kit) == 0)) { 
            return true;
        }    
    }
    return false;
}
