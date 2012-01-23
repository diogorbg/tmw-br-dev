#include<stdio.h>
#include<sqlite3.h>
#include<stdlib.h>

int main(int argc, char** args) {
	int retval;
	int q_cnt = 5,q_size = 150,ind = 0;
	char **queries = malloc(sizeof(char) * q_cnt * q_size);
	// preparando estados com ponteiro
	sqlite3_stmt *stmt;

	// criando ponteiro leitor do banco
	sqlite3 *handle;

	// definimos local do banco sqlite
	retval = sqlite3_open("agenda.sqlite3",&handle);
	// condição caso de certo
	if(retval) { printf("erro no banco\n"); return -1; }
	printf("OK\n");
	// nossa query para executar no banco
	char create_table[100] = "CREATE TABLE users (nome varchar(30), senha varchar(12))";
	// Executando a qury no banco
	retval = sqlite3_exec(handle,create_table,0,0,0);
	printf("retval: %d\n", retval);
	// fechando conexão
	sqlite3_close(handle);
	return 0;
}
