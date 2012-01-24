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

char *newText(const char *text);
const char *checkText(const char *text, int len);

/**
 * Retorna todos os jogadores/cargos ativos.
 * @param dados Referencia para armazenar os dados em forma de lista.
 * @param adms Conta quantidade de ADMs.
 * @param gms Conta quantidade de GMs.
 * @param devs Conta quantidade de DEVs.
 * @return quantidade de registros encontrados.
 */
int db_buscaJogadorCargo(DBJogadorCargo **dados, int *adms, int *gms, int *devs) {
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

	DBJogadorCargo *obj = NULL;
	while(1) {
		if ((ret=sqlite3_step(stmt))==SQLITE_ROW) {
			lin++;
			if (obj==NULL) {
				obj = malloc( sizeof(DBJogadorCargo) );
				*dados = obj;
			} else {
				obj->next = malloc( sizeof(DBJogadorCargo) );
				obj = obj->next;
			}
			memset(obj, 0, sizeof(DBJogadorCargo));
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

int db_insereJogador(DBJogador *obj, int *key) {
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
int db_buscaTodosJogadores(DBJogador **dados) {
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

	DBJogador *obj = NULL;
	while(1) {
		if ((ret=sqlite3_step(stmt))==SQLITE_ROW) {
			lin++;
			if (obj==NULL) {
				obj = malloc( sizeof(DBJogador) );
				*dados = obj;
			} else {
				obj->next = malloc( sizeof(DBJogador) );
				obj = obj->next;
			}
			memset(obj, 0, sizeof(DBJogador));
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

DBJogador *db_buscaJogadorPorIds(int idConta, int idChar) {
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
		throw(1, "db_buscaTodosJogadores::Falha ao executar SQL.");
		return NULL;
	}
	sqlite3_free(query);

	DBJogador *obj = NULL;
	while(1) {
		if ((ret=sqlite3_step(stmt))==SQLITE_ROW) {
			lin++;
			obj = malloc( sizeof(DBJogador) );
			memset(obj, 0, sizeof(DBJogador));
			try();
				obj->id = sqlite3_column_int(stmt, 0);
				obj->idConta = sqlite3_column_int(stmt, 1);
				obj->idChar = sqlite3_column_int(stmt, 2);
				obj->nomeConta = newText( sqlite3_column_text(stmt,3) );
				obj->nomeChar = newText( sqlite3_column_text(stmt,4) );
				obj->status = sqlite3_column_int(stmt, 5);
			catch {
				sqlite3_finalize(stmt);
				throw(2, "db_buscaTodosJogadores::Falha ao alocar memória.");
				return NULL;
			}
		} else if(ret==SQLITE_DONE) {
			break;
		} else {
			sqlite3_finalize(stmt);
			throw(3, "db_buscaTodosJogadores::Falha ao processar linhas.");
			return NULL;
		}
	}

	sqlite3_finalize(stmt);
	return obj;
}

//======================================================================
#define pObj (*obj)

void delDBJogador(DBJogador **obj) {
	if (pObj) {
		if (pObj->next) delDBJogador(&pObj->next);

		//printf("~%s\n", pObj->nomeChar);
		free(pObj->nomeConta);
		free(pObj->nomeChar);
		free (pObj);
		pObj = NULL;
	}
}

void delDBJogadorCargo(DBJogadorCargo **obj) {
	if (pObj) {
		if (pObj->next) delDBJogadorCargo(&pObj->next);

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
