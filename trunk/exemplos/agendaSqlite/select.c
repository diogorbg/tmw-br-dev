// Antonio (Cooler)
// http://botecoUnix.com.br
#include<stdio.h>
#include<sqlite3.h>
#include<stdlib.h>

int main(int argc, char** args) {
	//definindo vars e mem
	int retval;
	int q_cnt = 5,q_size = 150,ind = 0;
	char **queries = malloc(sizeof(char) * q_cnt * q_size);
	// preparando
	sqlite3_stmt *stmt;

	// criando o ponteiro para conectar
	sqlite3 *handle;

	// definindo nome do banco para conectar
	retval = sqlite3_open("agenda.sqlite3",&handle);
	// condição caso de erro
	if(retval) {
		printf("erro na conexao com banco agenda.sqlite3\n");
		return -1;
	}
	printf("Coexao com banco ok\n");
	// definimos a query SQL para uma busca simples enquanto tiver resultado ira nos mostrar as saidas
	queries[ind++] = "SELECT * from users";
	retval = sqlite3_prepare_v2(handle,queries[ind-1],-1,&stmt,0);
	// caso de erro
	if(retval) {
		printf("db selecionado com erro\n");
		return -1;
	}

	// le numero de colunas
	int cols = sqlite3_column_count(stmt);
	while(1) {
		// retorna os statos
		retval = sqlite3_step(stmt);

		if(retval == SQLITE_ROW) {

			// nos retornando os resultados
			for(int col=0 ; col<cols;col++) {
				const char *val = (const char*)sqlite3_column_text(stmt,col);
				// definimos como vai ser a saida das colunas
				printf("%s = %s\t",sqlite3_column_name(stmt,col),val);
			}
			printf("\n");
		}
		else if(retval == SQLITE_DONE) {
			// termina
			printf("pronto\n");
			break;
		} else {
			// caso ocorra algum erro
			printf("algum erro\n");
			return -1;
		}
	}

	// fecha conexão
	sqlite3_close(handle);
	return 0;
}