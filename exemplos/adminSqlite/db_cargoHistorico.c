/**
 * @author Diogo_RBG - http://diogorbg.blogspot.com/
 * @date sábado, 21 de janeiro de 2012
 */

#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

#include "exception.h"
#include "db_admin.h"
#include "db_cargoHistorico.h"

/**
 * Retorna um único registro cargo ativo.
 * @param idConta Id da conta para localizar jogador.
 * @param idChar Id do personagem para localizar jogador.
 * @param cargo Abreviação do cargo para localizar cargo ativo.
 * @param jogStatus Referencia para retornar o status do jogador.
 * @return Retorna um único objeto ADMCargoHist caso exista o jogador.
 * Se id for 0 é porque não existe um cargo ativo com a sigla informada.
 */
ADMCargoHist *db_getCargo_idsJogadorECargo(int idConta, int idChar, const char *cargo, int *jogStatus) {
	int ret, lin=0, col;
	sqlite3_stmt *stmt;
	char *query;

	query = sqlite3_mprintf("SELECT "
		"jog_id, "           // 0
		"jog_status, "       // 1
		"car_id, "           // 2
		//car_jog_id (será usado o valor de jog_id)
		"car_cargo, "        // 3
		"car_dataInicio, "   // 4
		"car_dataVigencia "  // 5
		//car_dataFim (sempre será 0)
		"FROM jogador "
		"LEFT JOIN cargoHistorico ON car_jog_id = jog_id AND car_cargo=%Q AND car_dataFim=0 "
		"WHERE jog_idConta=%d AND jog_idChar=%d",
		cargo, idConta, idChar);
	if (sqlite3_prepare_v2(admin_db,query,-1,&stmt,NULL) != SQLITE_OK) {
		printf("sql: '%s'\n", query);
		sqlite3_free(query);
		throw(1, "db_getCargo_idsJogadorECargo::Falha ao executar SQL.");
		return NULL;
	}
	sqlite3_free(query);

	ADMCargoHist *obj = NULL;
	while(1) {
		if ((ret=sqlite3_step(stmt))==SQLITE_ROW) {
			lin++;
			obj = malloc( sizeof(ADMCargoHist) );
			memset(obj, 0, sizeof(ADMCargoHist));
			try();
				obj->jog_id = sqlite3_column_int(stmt,0);
				if (jogStatus) (*jogStatus) = sqlite3_column_int(stmt,1);
				obj->id = sqlite3_column_int(stmt,2);
				copynText(obj->cargo, sqlite3_column_text(stmt,3), 3);
				obj->dataInicio = sqlite3_column_int(stmt,4);
				obj->dataVigencia = sqlite3_column_int(stmt,5);
			catch {
				sqlite3_finalize(stmt);
				throw(2, "db_getCargo_idsJogadorECargo::Falha ao alocar memória.");
				return NULL;
			}
		} else if(ret==SQLITE_DONE) {
			break;
		} else {
			sqlite3_finalize(stmt);
			throw(3, "db_getCargo_idsJogadorECargo::Falha ao processar linhas.");
			return NULL;
		}
	}

	sqlite3_finalize(stmt);
	return obj;
}

//======================================================================
#define pObj (*obj)

void delADMCargoHist(ADMCargoHist **obj) {
	if (pObj) {
		if (pObj->next) delADMCargoHist(&pObj->next);

		//printf("~%s\n", pObj->cargo);
		free (pObj);
		pObj = NULL;
	}
}

#undef pObj
