// exemplo bu Antonio(Cooler)
// http://botecoUnix.com.br
#include <stdio.h>
// lib do SQLite
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

int main(int argc, char** args) {
	char *sql,nome[MAX],*end;
	int retval,i;
	int q_cnt = 5,q_size = 150,ind = 0;
	char **queries = malloc(sizeof(char) * q_cnt * q_size);

	// definindo ponteiros
	sqlite3_stmt *stmt;
	sqlite3 *handle;
	// abrindo seu banco, antes de rodar o programa crie um banco com SQLite
	retval = sqlite3_open("agenda.sqlite3",&handle);
	// caso de erro na conexão vai mostrar msg
	if(retval) {
		printf("Erro no banco\n");
		return -1;
	}
	// caso nao tenha dado erro continua
	printf("Deu certo\n");
	// pega entrada do usuário
	printf("digite um nome para adicionar no banco\n");
	getchar();
	fgets(nome, MAX, stdin);
	i = strlen(nome)-1;
	if(nome[i] == '\n') {
		nome[i] = '\0';
	}

	// vai adicionar no banco na tabela agenda no campo nome o nome digitado pelo usuario
	sql = (char *)malloc( sizeof(char) * q_size );
	strcpy(sql, "INSERT INTO users VALUES('" );
	strcat(sql,nome);
	// vai aidionar no banco o numero de tell 43432222
	strcat(sql,"', '43432222')");
	// em suma he uma query soh INSERT INTO agenda Values('STDIN(entrada do user)', 'numero_definido')

	// executa nosso comando no banco
	retval = sqlite3_exec(handle,sql,0,0,0);
	printf("retval: %d\n", retval);

	// fecha a conexão
	sqlite3_close(handle);
	return 0;
}
