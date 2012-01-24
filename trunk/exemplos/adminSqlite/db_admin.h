/**
 * Funções e SQLs de acesso à base de dados admin.sqlite3
 * @author Diogo_RBG - http://diogorbg.blogspot.com/
 * @date sábado, 21 de janeiro de 2012
 */

#ifndef DB_ADMIN_H
#define DB_ADMIN_H

extern sqlite3 *admin_db;

typedef struct ADMJogador {
	struct ADMJogador *next;
	int id;
	int idConta;
	int idChar;
	char *nomeConta;
	char *nomeChar;
	char status;
} ADMJogador;
void delADMJogador(ADMJogador **obj);

typedef struct ADMJogadorCargo {
	struct ADMJogadorCargo *next;
	//int jog_id;
	//int idConta;
	//int idChar;
	//char *nomeConta;
	char *nomeChar;
	char *cargo;
	//int dataInicio;
	//int dataVigencia;
} ADMJogadorCargo;
void delADMJogadorCargo(ADMJogadorCargo **obj);

/**
 * Retorna todos os jogadores/cargos ativos.
 * @param dados Referencia para armazenar os dados em forma de lista.
 * @param adms Conta quantidade de ADMs.
 * @param gms Conta quantidade de GMs.
 * @param devs Conta quantidade de DEVs.
 * @return quantidade de registros encontrados.
 */
int db_buscaJogadorCargo(ADMJogadorCargo **dados, int *adms, int *gms, int *devs);

int db_insereJogador(ADMJogador *obj, int *key);

/**
 * Retorna todos os jogadores ativos.
 * @param dados Referencia para armazenar os dados em forma de lista.
 * @return quantidade de registros encontrados.
 */
int db_buscaTodosJogadores(ADMJogador **dados);

ADMJogador *db_buscaJogadorPorIds(int idConta, int idChar);

const char *checkText(const char *text, int len);

#endif // DB_ADMIN_H
