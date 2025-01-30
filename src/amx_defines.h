#ifndef AMX_DEFINES_H
	#define AMX_DEFINES_H

	#include "sdk/amx.h"
	#include "sdk/plugincommon.h"

	typedef cell(AMX_NATIVE_CALL* AMX_Get_String_t)(char* Dest, const cell* Source, int Use_Wide_Char, size_t Size);
	typedef int (AMX_NATIVE_CALL* AMX_Register_t)(AMX* Amx, const AMX_NATIVE_INFO* Native_List, int Number);
	typedef int (AMX_NATIVE_CALL* AMX_Set_String_t)(cell* Dest, const char* Source, int Pack, int Use_Wide_Char, size_t Size);
	typedef int (AMX_NATIVE_CALL* AMX_String_Len_t)(const cell* Cell_String, int* Length);
	typedef int (AMX_NATIVE_CALL* AMX_Get_Addr_t)(AMX* Amx, cell Amx_Addr, cell** Phys_Addr);

	extern AMX_Get_String_t AMX_Get_String_Ptr;
	extern AMX_Register_t AMX_Register_Ptr;
	extern AMX_Set_String_t AMX_Set_String_Ptr;
	extern AMX_String_Len_t AMX_String_Len_Ptr;
	extern AMX_Get_Addr_t AMX_Get_Addr_Ptr;
#endif