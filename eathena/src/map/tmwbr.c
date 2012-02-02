//

#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#include "tmwbr.h"

#include "socket.h"
#include "timer.h"
#include "malloc.h"
#include "version.h"
#include "nullpo.h"

#include "atcommand.h"
#include "battle.h"
#include "chat.h"
#include "chrif.h"
#include "clif.h"
#include "guild.h"
#include "intif.h"
#include "itemdb.h"
#include "magic.h"
#include "map.h"
#include "mob.h"
#include "npc.h"
#include "party.h"
#include "pc.h"
#include "script.h"
#include "skill.h"
#include "storage.h"
#include "trade.h"

int op_spyLog = 0;

void setOpSpyLog(int op) {
	op_spyLog = op;
}

/**
 * Envia uma mensagem que será exibida na tela de chat do jogador.
 */
void displayMessage (const int fd, char *format, ...) {
	char buffer[256];
	va_list args;

	va_start(args, format);
	vsprintf(buffer, format, args);
	clif_displaymessage(fd, buffer);
	va_end(args);
}

/**
 * Retorna o valor corrigido do item para a cotação do item 'mercadoria de troca' ou valor definido no NPC.
 */
int getValueTrade (struct npc_data *nd, int nameid, int val) {
	int i;

    if (nd->idItemTrade>0) {
    	val /= nd->valueTrade;
    }
    for (i=0; nd->u.shop_item[i].nameid || nd->u.shop_item[i].nameidpaid; i++) {
    	if (nd->u.shop_item[i].nameidpaid != nameid)
    		continue;
    	//printf("item: %d %d$\n", nd->u.shop_item[i].nameidpaid, nd->u.shop_item[i].value);
    	val = nd->u.shop_item[i].value;
    	break;
    }
	return val;
}

/**
 * Adiciona item no inventário por id e quantidade.
 * @return Retorn 0 em caso de sucesso.
 */
int addItem(struct map_session_data *sd, int idItem, int count) {
	struct item item_tmp;
	int flag;

	memset(&item_tmp, 0, sizeof(item_tmp));
	item_tmp.nameid = idItem;
	item_tmp.identify = 1;
	if ( (flag = pc_additem((struct map_session_data *) sd, &item_tmp, count)) )
		clif_additem((struct map_session_data *) sd, 0, 0, flag);
	return flag;
}

/**
 * Remove item do inventário por id e quantidade.
 * @return Retorn 0 em caso de sucesso.
 */
int delitem(struct map_session_data *sd, int idItem, int count) {
	return pc_delitem(sd, pc_search_inventory(sd, idItem), count, 0);
}

/**
 * Conta quantidade de um item no inventário.
 */
int countItem(struct map_session_data *sd, int idItem) {
	return pc_count_all_items(sd, idItem);
}

void checkUrl(struct map_session_data *sd, char *wis, unsigned char *buf) {
	if (op_spyLog==0) return;

	char detected[512];
	int i=0, p=0, pp=0, b=0;

	for(i=0; p<512; i++,p++) {
		if (buf[i]<=' ') {
			if (b>=2) {
				b = 0;
				detected[p] = ' ';
				pp = p+1;
				if (buf[i]==0) break;
				continue;
			} else {
				b = 0;
				p = pp-1;
				if (buf[i]==0) break;
				continue;
			}
		}
		if (buf[i]=='.') {
			if (pp-p==0);                   //- inicia com 'ponto'
			else if (i>0 && buf[i-1]=='.'); //- repete o 'ponto'
			else if (buf[i+1]<=' ');        //- termina com 'ponto'
			else b++;
		}
		detected[p] = buf[i];
	}
	if (p>0) {
		detected[p] = 0;
		if (wis)
			log_spy("url", sd, "\t%s\t%s", detected, wis);
		else
			log_spy("url", sd, "\t%s", detected);
	}
}

void log_storage(const char *func, struct map_session_data *sd, const char *fmt, ...) {
	char buff[512];

	//- cálculo de tempo...
	time_t time_v;
	struct tm t;
	time(&time_v);
	localtime_r(&time_v, &t);

	//- criação do arquivo log_storage...
    static int timeLogFile = 0;
	static FILE *logFile = NULL;
	int time = t.tm_year*12*31 + t.tm_mon*31;
	if( timeLogFile!=time ) {
		if(logFile)
			fclose(logFile);
		logFile = NULL;
	}
	if(!logFile) {
		timeLogFile = time;
		sprintf(buff, "log/storage.%04d-%02d.log", t.tm_year+1900, t.tm_mon+1);
		logFile = fopen(buff, "a");
	}

	//- recuperando parâmetros...
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buff, 511, fmt, ap);
	va_end(ap);

	fprintf(logFile,"%s,%ld,%d,%d,%s,%s\n", func, time_v, sd->status.account_id, sd->status.char_id,
			map[sd->bl.m].name, buff);
	fflush(logFile);
}

void log_map(const char *func, struct map_session_data *sd, const char *fmt, ...) {
	char buff[512];

	//- cálculo de tempo...
	time_t time_v;
	struct tm t;
	time(&time_v);
	localtime_r(&time_v, &t);

	//- criação do arquivo log_map...
    static int timeLogFile = 0;
	static FILE *logFile = NULL;
	int time = t.tm_year*12*31 + t.tm_mon*31;
	if( timeLogFile!=time ) {
		if(logFile)
			fclose(logFile);
		logFile = NULL;
	}
	if(!logFile) {
		timeLogFile = time;
		sprintf(buff, "log/map.%04d-%02d.log", t.tm_year+1900, t.tm_mon+1);
		logFile = fopen(buff, "a");
	}

	//- recuperando parâmetros...
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buff, 511, fmt, ap);
	va_end(ap);

	fprintf(logFile,"%s,%ld,%d,%d,%s,%d,%d,%s\n", func, time_v, sd->status.account_id, sd->status.char_id,
			map[sd->bl.m].name, sd->bl.x, sd->bl.y, buff);
	fflush(logFile);
}

void log_trade(const char *func, struct map_session_data *sd, const char *fmt, ...) {
	char buff[512];

	//- cálculo de tempo...
	time_t time_v;
	time(&time_v);

	//- recuperando parâmetros...
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buff, 511, fmt, ap);
	va_end(ap);

	log_tradeln(func, "%ld,%d,%d,%s,%d,%d,%s", time_v, sd->status.account_id, sd->status.char_id,
			map[sd->bl.m].name, sd->bl.x, sd->bl.y, buff);
}

void log_tradeln(const char *func, const char *fmt, ...) {
	char buff[512];

	//- cálculo de tempo...
	time_t time_v;
	struct tm t;
	time(&time_v);
	localtime_r(&time_v, &t);

	//- criação do arquivo log_trade...
    static int timeLogFile = 0;
	static FILE *logFile = NULL;
	int time = t.tm_year*12*31 + t.tm_mon*31;
	if( timeLogFile!=time ) {
		if(logFile)
			fclose(logFile);
		logFile = NULL;
	}
	if(!logFile) {
		timeLogFile = time;
		sprintf(buff, "log/trade.%04d-%02d.log", t.tm_year+1900, t.tm_mon+1);
		logFile = fopen(buff, "a");
	}

	//- recuperando parâmetros...
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buff, 511, fmt, ap);
	va_end(ap);

	fprintf(logFile,"%s,%s\n", func, buff);
	fflush(logFile);
}

void log_spy(const char *func, struct map_session_data *sd, const char *fmt, ...) {
	char buff[512];

	//- cálculo de tempo...
	time_t time_v;
	struct tm t;
	time(&time_v);
	localtime_r(&time_v, &t);

	//- criação do arquivo log_map...
    static int timeLogFile = 0;
	static FILE *logFile = NULL;
	int time = t.tm_year*12*31 + t.tm_mon*31;
	if( timeLogFile!=time ) {
		if(logFile)
			fclose(logFile);
		logFile = NULL;
	}
	if(!logFile) {
		timeLogFile = time;
		sprintf(buff, "log/spy.%04d-%02d.log", t.tm_year+1900, t.tm_mon+1);
		logFile = fopen(buff, "a");
	}

	//- recuperando parâmetros...
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buff, 511, fmt, ap);
	va_end(ap);

	fprintf(logFile,"%s,%ld,%d,%d,%s\n", func, time_v, sd->status.account_id, sd->status.char_id, buff);
	fflush(logFile);
}

char *trocaAspa(char *name) {
	int i, j=0;
	static char buf[64];

	for(i=0;name[i];i++) {
		if(name[i]=='\'') {
			buf[j] = '\\'; j++;
			buf[j] = '\''; j++;
		} else {
			buf[j] = name[i]; j++;
		}
	}
	buf[j] = 0;

	return (char*)&buf;
}
