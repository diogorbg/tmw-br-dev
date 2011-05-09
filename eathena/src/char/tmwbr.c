/**
 * funções utilitárias do char.c - TMW-BR.
 * obs.: Faz parte do código do char.c e usa a regra de compilação do mesmo.
 * Ao editar apenas este código edite tbm o char.c para que a compilação seja feita corretamente. :P
 */

#define DEBUG() //printf("# char linha:%d\n", __LINE__);
#define DEBUGD(d) //printf("# char linha:%d var:%d\n", __LINE__, (d));
#define DEBUGS(s) //printf("# char linha:%d var:%s\n", __LINE__, (s));

// FIXME TMW-BR log_char()
void log_char(const char *func, struct mmo_charstatus *cs, const char *fmt, ...) {
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
		sprintf(buff, "log/char.%04d-%02d.log", t.tm_year+1900, t.tm_mon+1);
		logFile = fopen(buff, "a");
	}

	//- recuperando parâmetros...
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buff, 511, fmt, ap);
	va_end(ap);

	fprintf(logFile,"%s,%ld,%d,%d,%s,%d,%d,%s\n", func, time_v, cs->account_id, cs->char_id,
			cs->last_point.map, cs->last_point.x, cs->last_point.y, buff);
	fflush(logFile);
}

// FIXME TMW-BR backup_char()
void backup_char(struct mmo_charstatus *cs) {
	char buff[65000];

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
		sprintf(buff, "log/char.%04d-%02d.backup", t.tm_year+1900, t.tm_mon+1);
		logFile = fopen(buff, "a");
	}

	mmo_char_tostr(buff, cs);
	fprintf (logFile, "%ld,%s\n", time_v, buff);
	fflush(logFile);
}
