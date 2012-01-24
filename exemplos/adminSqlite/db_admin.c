/**
 * Funções e SQLs de acesso à base de dados admin.sqlite3
 * @author Diogo_RBG - http://diogorbg.blogspot.com/
 * @date sábado, 21 de janeiro de 2012
 */

#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

#include "exception.h"
#include "db_admin.h"

const char *checkText(const char *text, int len);

/**
 * Retorna todos os jogadores/cargos ativos.
 * @param dados Referencia para armazenar os dados em forma de lista.
 * @param adms Conta quantidade de ADMs.
 * @param gms Conta quantidade de GMs.
 * @param devs Conta quantidade de DEVs.
 * @return quantidade de registros encontrados.
 */
int db_buscaJogadorCargo(ADMJogadorCargo **dados, int *adms, int *gms, int *devs) {
	int ret, lin=0, col;
	sqlite3_stmt *stmt;
	char *query;

	query = sqlite3_mprintf("SELECT "
		"jog_nomeChar, " //0
		"car_cargo "     //1
		"FROM view_jogadorCargo");
	if (sqlite3_prepare_v2(admin_db,query,-1,&stmt,NULL) != SQLITE_OK) {
		printf("sql: '%s'\n", query);
		sqlite3_free(query);
		return -throw(1, "db_buscaJogadorCargo::Falha ao executar SQL.");
	}
	sqlite3_free(query);

	ADMJogadorCargo *obj = NULL;
	while(1) {
		if ((ret=sqlite3_step(stmt))==SQLITE_ROW) {
			lin++;
			if (obj==NULL) {
				obj = malloc( sizeof(ADMJogadorCargo) );
				*dados = obj;
			} else {
				obj->next = malloc( sizeof(ADMJogadorCargo) );
				obj = obj->next;
			}
			memset(obj, 0, sizeof(ADMJogadorCargo));
			try();
				obj->nomeChar = newText( sqlite3_column_text(stmt,0) );
				obj->cargo = newText( sqlite3_column_text(stmt,1) );
				if (adms && obj->cargo && strcmp(obj->cargo,"adm") ) (*adms)++;
				if (devs && obj->cargo && strcmp(obj->cargo,"dev") ) (*devs)++;
				if (gms && obj->cargo && strcmp(obj->cargo,"gm") ) (*gms)++;
			catch {
				sqlite3_finalize(stmt);
				return -throw(2, "db_buscaJogadorCargo::Falha ao alocar memória.");
			}
		} else if(ret==SQLITE_DONE) {
			break;
		} else {
			sqlite3_finalize(stmt);
			return -throw(3, "db_buscaJogadorCargo::Falha ao processar linhas.");
		}
	}

	sqlite3_finalize(stmt);
	return lin;
}

int db_insereJogador(ADMJogador *obj, int *key) {
	int ret;
	sqlite3_stmt *stmt;
	char *query;

	query = sqlite3_mprintf("INSERT INTO jogador "
		"(jog_idConta,jog_idChar,jog_nomeConta,jog_nomeChar) VALUES(%d,%d,%Q,%Q);",
		obj->idConta,
		obj->idChar,
		checkText(obj->nomeConta, 32),
		checkText(obj->nomeChar, 32));
	if ((ret = sqlite3_exec(admin_db,query,NULL,NULL,NULL)) != SQLITE_OK) {
		printf("ret: %d sql: '%s'\n", ret, query);
		printf("erro: %s\n", sqlite3_errmsg(admin_db));
		sqlite3_free(query);
		return -throw(1, "db_insereJogador::Falha ao executar SQL.");
	}
	sqlite3_free(query);
}

/**
 * Retorna todos os jogadores ativos.
 * @param dados Referencia para armazenar os dados em forma de lista.
 * @return quantidade de registros encontrados.
 */
int db_buscaTodosJogadores(ADMJogador **dados) {
	int ret, lin=0, col;
	sqlite3_stmt *stmt;
	char *query;

	query = sqlite3_mprintf("SELECT "
		"jog_id, "        // 0
		"jog_idConta, "   // 1
		"jog_idChar, "    // 2
		"jog_nomeConta, " // 3
		"jog_nomeChar "   // 4
		//"jog_status "
		"FROM jogador WHERE jog_status=1");
	if (sqlite3_prepare_v2(admin_db,query,-1,&stmt,NULL) != SQLITE_OK) {
		printf("sql: '%s'\n", query);
		sqlite3_free(query);
		return -throw(1, "db_buscaTodosJogadores::Falha ao executar SQL.");
	}
	sqlite3_free(query);

	ADMJogador *obj = NULL;
	while(1) {
		if ((ret=sqlite3_step(stmt))==SQLITE_ROW) {
			lin++;
			if (obj==NULL) {
				obj = malloc( sizeof(ADMJogador) );
				*dados = obj;
			} else {
				obj->next = malloc( sizeof(ADMJogador) );
				obj = obj->next;
			}
			memset(obj, 0, sizeof(ADMJogador));
			try();
				obj->id = sqlite3_column_int(stmt, 0);
				obj->idConta = sqlite3_column_int(stmt, 1);
				obj->idChar = sqlite3_column_int(stmt, 2);
				obj->nomeConta = newText( sqlite3_column_text(stmt,3) );
				obj->nomeChar = newText( sqlite3_column_text(stmt,4) );
				obj->status = 1;
			catch {
				sqlite3_finalize(stmt);
				return -throw(2, "db_buscaTodosJogadores::Falha ao alocar memória.");
			}
		} else if(ret==SQLITE_DONE) {
			break;
		} else {
			sqlite3_finalize(stmt);
			return -throw(3, "db_buscaTodosJogadores::Falha ao processar linhas.");
		}
	}

	sqlite3_finalize(stmt);
	return lin;
}

/**
 * Obtem todos os dados de um ADMJogador.
 * @param idConta Id da conta.
 * @param idChar Id do char.
 * @return Retorna um único objeto caso o localize na base de dados.
 */
ADMJogador *db_getJogador_idsJogador(int idConta, int idChar) {
	int ret, lin=0, col;
	sqlite3_stmt *stmt;
	char *query;

	query = sqlite3_mprintf("SELECT "
		"jog_id, "        // 0
		"jog_idConta, "   // 1
		"jog_idChar, "    // 2
		"jog_nomeConta, " // 3
		"jog_nomeChar, "  // 4
		"jog_status "     // 5
		"FROM jogador WHERE jog_idConta=%d AND jog_idChar=%d",
		idConta, idChar);
	if (sqlite3_prepare_v2(admin_db,query,-1,&stmt,NULL) != SQLITE_OK) {
		printf("sql: '%s'\n", query);
		sqlite3_free(query);
		throw(1, "db_getJogador_idsJogador::Falha ao executar SQL.");
		return NULL;
	}
	sqlite3_free(query);

	ADMJogador *obj = NULL;
	while(1) {
		if ((ret=sqlite3_step(stmt))==SQLITE_ROW) {
			lin++;
			obj = malloc( sizeof(ADMJogador) );
			memset(obj, 0, sizeof(ADMJogador));
			try();
				obj->id = sqlite3_column_int(stmt, 0);
				obj->idConta = sqlite3_column_int(stmt, 1);
				obj->idChar = sqlite3_column_int(stmt, 2);
				obj->nomeConta = newText( sqlite3_column_text(stmt,3) );
				obj->nomeChar = newText( sqlite3_column_text(stmt,4) );
				obj->status = sqlite3_column_int(stmt, 5);
			catch {
				sqlite3_finalize(stmt);
				throw(2, "db_getJogador_idsJogador::Falha ao alocar memória.");
				return NULL;
			}
		} else if(ret==SQLITE_DONE) {
			break;
		} else {
			sqlite3_finalize(stmt);
			throw(3, "db_getJogador_idsJogador::Falha ao processar linhas.");
			return NULL;
		}
	}

	sqlite3_finalize(stmt);
	return obj;
}

//======================================================================
#define pObj (*obj)

void delADMJogador(ADMJogador **obj) {
	if (pObj) {
		if (pObj->next) delADMJogador(&pObj->next);

		//printf("~%s\n", pObj->nomeChar);
		free(pObj->nomeConta);
		free(pObj->nomeChar);
		free (pObj);
		pObj = NULL;
	}
}

void delADMJogadorCargo(ADMJogadorCargo **obj) {
	if (pObj) {
		if (pObj->next) delADMJogadorCargo(&pObj->next);

		//printf("~%s\n", pObj->nomeChar);
		free(pObj->nomeChar);
		free(pObj->cargo);
		free (pObj);
		pObj = NULL;
	}
}

#undef pObj
//======================================================================

char *newText(const char *text) {
	if(text==NULL) return NULL;

	char *ret = malloc( strlen(text)+1 );
	if (ret==NULL) {
		throw(1, "Falha ao alocar memória.");
		return NULL;
	}
	strcpy(ret, text);
	return ret;
}

void copynText(char *dest, const char *orig, int n) {
	if(orig==NULL) {
		dest[0] = 0;
		return;
	}
	strncpy(dest, orig, n);
}

const char *checkText(const char *text, int len) {
	if(text==NULL)
		return NULL;
	int i;
	for (i=0; text[i]; i++);
	if (i>len) {
		throw(1, "Tamanho do texto foi excedido.");
		return NULL;
	}
	return text;
}
