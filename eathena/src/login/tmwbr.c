/**
 * funções utilitárias do TMW-BR.
 */

#include <glib.h>

gpointer newInt(int i) {
	int *p = (int*) malloc(4);
    *p = i;
	return (gpointer)p;
}
