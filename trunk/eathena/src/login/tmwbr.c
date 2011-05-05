/**
 * funções utilitárias do TMW-BR.
 */

#include <glib.h>

typedef struct InfoLogin {
	unsigned int time;
	unsigned int ignorados;
	unsigned int erros;
	unsigned int acertos;
}InfoLogin;

gpointer newInfoLogin(unsigned int time) {
	InfoLogin *new = (InfoLogin*) malloc(sizeof(InfoLogin));
    new->time = time;
    new->ignorados = 0;
    new->erros = 0;
    new->acertos = 0;
	return (gpointer)new;
}

void freeGPoniter(gpointer data) {
	free(data);
}

gpointer newInt(int i) {
	int *new = (int*) malloc(4);
    *new = i;
	return (gpointer)new;
}
