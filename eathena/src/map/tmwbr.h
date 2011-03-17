//
#ifndef _TMWBR_H_
#define _TMWBR_H_

#include "map.h"

void log_storage(const char *func, struct map_session_data *sd, const char *fmt, ...);
void log_map(const char *func, struct map_session_data *sd, const char *fmt, ...);
void log_trade(const char *func, struct map_session_data *sd, const char *fmt, ...);
void log_tradeln(const char *func, const char *fmt, ...);

char *trocaAspa(char *name);

#endif /* _TMWBR_H_ */
