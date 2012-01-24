/**
 * @author Diogo_RBG - http://diogorbg.blogspot.com/
 * @date sábado, 21 de janeiro de 2012
 */

#ifndef DB_CARGO_HISTORICO_H
#define DB_CARGO_HISTORICO_H

extern sqlite3 *admin_db;

typedef struct ADMCargoHist {
	struct ADMCargoHist *next;
	int id;
	int jog_id;
	char cargo[4]; //- 3 dígitos + \0
	int dataInicio;
	int dataVigencia;
	int dataFim;
} ADMCargoHist;
void delADMCargoHist(ADMCargoHist **obj);

/**
 * Retorna um único registro cargo ativo.
 * @param idConta Id da conta para localizar jogador.
 * @param idChar Id do personagem para localizar jogador.
 * @param cargo Abreviação do cargo para localizar cargo ativo.
 * @param jogStatus Referencia para retornar o status do jogador.
 * @return Retorna um único objeto ADMCargoHist caso exista o jogador.
 * Se id for 0 é porque não existe um cargo ativo com a sigla informada.
 */
ADMCargoHist *db_getCargo_idsJogadorECargo(int idConta, int idChar, const char *cargo, int *jogStatus);

//int db_insereCargo(ADMCargoHist *obj, int *key);

//int db_buscaTodosJogadores(ADMCargoHist **dados);

#endif // DB_CARGO_HISTORICO_H
