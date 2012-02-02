//
#ifndef _TMWBR_H_
#define _TMWBR_H_

#include "map.h"

void displayMessage (const int fd, char *format, ...);
int getValueTrade (struct npc_data *nd, int nameid, int val);
int addItem(struct map_session_data *sd, int idItem, int count);
int delitem(struct map_session_data *sd, int id, int count);
int countItem(struct map_session_data *sd, int idItem);
void checkUrl(struct map_session_data *sd, const char *buf);

void log_storage(const char *func, struct map_session_data *sd, const char *fmt, ...);
void log_map(const char *func, struct map_session_data *sd, const char *fmt, ...);
void log_trade(const char *func, struct map_session_data *sd, const char *fmt, ...);
void log_tradeln(const char *func, const char *fmt, ...);
void log_spy(const char *func, struct map_session_data *sd, const char *fmt, ...);

char *trocaAspa(char *name);

#endif /* _TMWBR_H_ */
