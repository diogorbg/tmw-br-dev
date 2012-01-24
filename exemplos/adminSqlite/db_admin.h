/**
 * Funções e SQLs de acesso à base de dados admin.sqlite3
 * @author Diogo_RBG - http://diogorbg.blogspot.com/
 * @date sábado, 21 de janeiro de 2012
 */

#ifndef DB_ADMIN_H
#define DB_ADMIN_H

extern sqlite3 *admin_db;

typedef struct DBJogador {
	struct DBJogador *next;
	int id;
	int idConta;
	int idChar;
	char *nomeConta;
	char *nomeChar;
	char status;
} DBJogador;
void delDBJogador(DBJogador **obj);

typedef struct DBJogadorCargo {
	struct DBJogadorCargo *next;
	//int jog_id;
	//int idConta;
	//int idChar;
	//char *nomeConta;
	char *nomeChar;
	char *cargo;
	//int dataInicio;
	//int dataVigencia;
} DBJogadorCargo;
void delDBJogadorCargo(DBJogadorCargo **obj);

/**
 * Retorna todos os jogadores/cargos ativos.
 * @param dados Referencia para armazenar os dados em forma de lista.
 * @param adms Conta quantidade de ADMs.
 * @param gms Conta quantidade de GMs.
 * @param devs Conta quantidade de DEVs.
 * @return quantidade de registros encontrados.
 */
int db_buscaJogadorCargo(DBJogadorCargo **dados, int *adms, int *gms, int *devs);

int db_insereJogador(DBJogador *obj, int *key);

/**
 * Retorna todos os jogadores ativos.
 * @param dados Referencia para armazenar os dados em forma de lista.
 * @return quantidade de registros encontrados.
 */
int db_buscaTodosJogadores(DBJogador **dados);

DBJogador *db_buscaJogadorPorIds(int idConta, int idChar);

const char *checkText(const char *text, int len);

#endif // DB_ADMIN_H
