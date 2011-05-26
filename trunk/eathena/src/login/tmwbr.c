/**
 * funções utilitárias do login.c - TMW-BR.
 * obs.: Faz parte do código do login.c e usa a regra de compilação do mesmo.
 * Ao editar apenas este código edite tbm o login.c para que a compilação seja feita corretamente. :P
 */

#ifdef CYGWIN
typedef void* gpointer;
#else
//- Estruturas de dados complexas
//- http://developer.gnome.org/glib/unstable/glib-Hash-Tables.html
#include <glib.h>
#endif

#define DEBUG() //printf("# login linha:%d\n", __LINE__);
#define DEBUGD(d) //printf("# login linha:%d var:%d\n", __LINE__, (d));
#define DEBUGS(s) //printf("# login linha:%d var:%s\n", __LINE__, (s));

/**
 * Critica a senha caso ela seja muito simples.
 * Criticizes the password if it is very simple.
 *  0: ok.
 *  1: A senha deve ter no mínimo 8 caracteres.
 *  2: A senha deve conter números.
 *  4: A senha deve conter letras minúsculas.
 *  8: A senha deve conter letras maiúsculas.
 * 16: A senha deve conter símbolos. (não será obrigatório)
 * 15: Soma de todas as críticas.
 */
int criticalPasswd(unsigned char *str) {
	int i;
	int num = 0;

	for(i=0; str[i]; i++) {
		if( str[i]<32 )
			continue;
		else if( str[i]>='0' && str[i]<='9' )
			num = num | 2;
		else if( str[i]>='a' && str[i]<='z' )
			num = num | 4;
		else if( str[i]>='A' && str[i]<='Z' )
			num = num | 8;
		//else
		//	num = num | 16;
	}
	if(i>=8)
		num = num | 1;

	//- Retorna condições não saciadas pela crítica.
	return 15 & ~num;
}

/*
void listCriticalPasswd(int criticalPasswd){
	if( criticalPasswd&1 )
		printf("* A senha deve ter no mínimo 8 caracteres.\n");
	if( criticalPasswd&2 )
		printf("* A senha deve conter números.\n");
	if( criticalPasswd&4 )
		printf("* A senha deve conter letras minúsculas.\n");
	if( criticalPasswd&8 )
		printf("* A senha deve conter letras maiúsculas.\n");
	if( criticalPasswd&16 )
		printf("* A senha deve conter símbolos.\n");
}
*/

//======================================================================

//- Mapa de todos os ips que tentaram se autenticar.
#ifndef CYGWIN
GHashTable *mapIp = NULL;
#endif

/*
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
*/

void freeGPoniter(gpointer data) {
	free(data);
}

gpointer newInt(int i) {
	int *new = (int*) malloc(4);
    *new = i;
	return (gpointer)new;
}

/**
 * Esta função tem o objetivo de limitar a quantidade de requisições de acesso.
 * Para isso é feito um controle por IP e limite de tempo de acesso de 5s.
 *
 * @param ip IP de acesso
 * @return 1, caso o IP tenha feito um acesso em menos de 5s.
 */
int delayLoginPorIp(unsigned int ip) {
#ifndef CYGWIN

	unsigned int t = time(NULL);
	unsigned int *t2;

	if(mapIp==NULL)
		mapIp = g_hash_table_new_full(g_int_hash, g_int_equal, freeGPoniter, freeGPoniter);

	t2 = g_hash_table_lookup(mapIp, (gpointer)&ip);
	if(t2!=NULL) {
		if(*t2+5 > t) {
			//- Ainda não se passaram 5s da ultima tentativa de autenticação.
			return 1;
		}
	}
	g_hash_table_insert(mapIp, newInt(ip), newInt(t));

	// Teste de desalocação de memória...
	//int i;
	//srand(t);
	//for(i=0; i<2000; i++)
	//	g_hash_table_insert(mapIp, newInt(rand()), newInt(t));
	//unsigned char *ip3 = &ip2;
	//printf("# Requisicao de acesso - %d.%d.%d.%d - mapIp.size: %d\n", ip3[0], ip3[1], ip3[2], ip3[3], n);

	int n = g_hash_table_size(mapIp);
	if(n>10000) {
		g_hash_table_remove_all(mapIp);
	}

#endif
	return 0;
}
