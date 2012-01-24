/**
 * Adaptação de um controle de exceções em C.
 * @author Diogo_RBG - http://diogorbg.blogspot.com/
 * @date sábado, 21 de janeiro de 2012
 */

#include <stdio.h>

#include "exception.h"

void try() {
	exception = 0;
	exceptionMsg = NULL;
	exceptionFile = NULL;
	exceptionLine = 0;
}

int _throw(int exc, const char *excMsg, const char *file, int line) {
	exception = exc;
	exceptionMsg = (char *)excMsg;
	exceptionFile = (char *)file;
	exceptionLine = line;
	return exc;
}

int printStack() {
	printf("### exception %d ### %s\n", exception, exceptionMsg);
	printf("lin: %d - %s\n", exceptionLine, exceptionFile);
	return exception;
}
