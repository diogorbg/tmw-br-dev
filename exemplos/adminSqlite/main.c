/**
 * Testes com o biblioteca SQLite3
 * @author Diogo_RBG - http://diogorbg.blogspot.com/
 * @date sábado, 21 de janeiro de 2012
 */

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

// Ponteiro manupulador do banco de dados.
sqlite3 *admin_db = NULL;

#include "exception.h"
#include "db_admin.h"

void listarCargos() {
	int adms=0, gms=0, devs=0;
	ADMJogadorCargo *obj, *it;
	if (db_buscaJogadorCargo(&obj, &adms, &gms, &devs)>=0) {
		if (adms) {
			printf(".:: Lista de ADMs ::.\n");
			for (it=obj; it; it=it->next) {
				if( !it->cargo || strcmp(it->cargo, "adm")!=0 ) continue;
				printf("* %s\n", it->nomeChar);
			}
		}
		if (gms) {
			printf(".:: Lista de GMs ::.\n");
			for (it=obj; it; it=it->next) {
				if( !it->cargo || strcmp(it->cargo, "gm")!=0 ) continue;
				printf("* %s\n", it->nomeChar);
			}
		}
		if (devs) {
			printf(".:: Lista de DEVs ::.\n");
			for (it=obj; it; it=it->next) {
				if( !it->cargo || strcmp(it->cargo, "dev")!=0 ) continue;
				printf("* %s\n", it->nomeChar);
			}
		}
	} else {
		printStack();
	}
	delADMJogadorCargo(&obj);
}

void inserirJogador() {
	ADMJogador obj;
	char nomeConta[32], nomeChar[32];
	printf("idConta: "); scanf("%d", &obj.idConta);
	printf("idChar: "); scanf("%d", &obj.idChar);
	printf("nomeConta: "); scanf("%s", nomeConta);
	obj.nomeConta = nomeConta;
	printf("nomeChar: "); scanf("%s", nomeChar);
	obj.nomeChar = nomeChar;
	try();
		db_insereJogador(&obj, NULL);
	catch {
		printStack();
	}
}

void listarTodosJogadores() {
	ADMJogador *obj, *it;
	if (db_buscaTodosJogadores(&obj)>=0) {
		printf(".:: Lista de Jogadores ::.\n");
		for (it=obj; it; it=it->next) {
			printf("* %02d|%d|%s|%d|%s\n", it->id, it->idConta, it->nomeConta, it->idChar, it->nomeChar);
		}
	} else {
		printStack();
	}
	delADMJogador(&obj);
}

void buscarJogadorPoIds() {
	int idConta, idChar;
	ADMJogador *obj;
	printf("idConta: "); scanf("%d", &idConta);
	printf("idChar: "); scanf("%d", &idChar);
	try();
	if (obj=db_buscaJogadorPorIds(idConta, idChar)) {
		printf(".:: Jogador Localizado ::.\n");
		printf("* %02d|%d|%s|%d|%s\n", obj->id, obj->idConta, obj->nomeConta, obj->idChar, obj->nomeChar);
	}
	catch {
		printStack();
	}
	delADMJogador(&obj);
}

//======================================================================

int main() {
	// definindo nome do banco para conectar
	if (sqlite3_open("admin.sqlite3", &admin_db)!=SQLITE_OK) {
		printf("### erro ### Falha ao abrir base de dados: admin.sqlite3.\n");
		return 1;
	}

	char op, x;
	while(1) {
		printf("\n");
		printf(".:: Menu ::...............\n");
		printf("* Listar Jogador Cargo [c]\n");
		printf("* Listar Jogador...... [j]\n");
		printf("* Burcar Jogador...... [b]\n");
		printf("* Inserir Jogador..... [1]\n");
		scanf("%c", &op);
		scanf("%c", &x);

		printf("\n");
		if (op=='c') {
			listarCargos();
		} else if (op=='j') {
			listarTodosJogadores();
		} else if (op=='b') {
			buscarJogadorPoIds();
			scanf("%c", &x);
		} else if (op=='1') {
			inserirJogador();
			scanf("%c", &x);
		} else {
			break;
		}
	}

	// fecha conexão
	sqlite3_close(admin_db);
	return 0;
}
