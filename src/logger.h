#ifndef LOGGER_H
	#define LOGGER_H

	typedef void (*Log_Printf_t)(const char* Format, ...);
	extern Log_Printf_t Log_Printf;
#endif