/**
 * Adaptação de um controle de exceções em C.
 * @author Diogo_RBG - http://diogorbg.blogspot.com/
 * @date sábado, 21 de janeiro de 2012
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdio.h>
#define debug printf("lin: %d - %s\n", __LINE__, __FILE__)

int exception;
char *exceptionMsg;
char *exceptionFile;
int exceptionLine;

void try();

#define catch if(exception>0)
#define throw(exc, excMsg) _throw((exc), (excMsg), __FILE__, __LINE__)

int _throw(int exc, const char *excMsg, const char *file, int line);

int printStack();

#endif // EXCEPTION_H
