#pragma once

#ifndef _LUA_SCRIPT_H_
#define _LUA_SCRIPT_H_

#pragma comment(lib, "lua.lib")

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}
#endif
/*===================
	Create class
===================*/
class LuaStack {

private:
	lua_State *lua_state;

public:
	LuaStack();
	~LuaStack();

	int RunFile(char* ScriptFileName);

/* Def vars */

	template<class type>
	void AddVariable(type value, char* constantname);

/* Tables */

	void Table();

	template<class type>
	void AddVarInTable(type value, int index);

	void RegTable(char* arrayname);

/* Get arguments */

	int GetArgumentCount();

	template<class type>
	type GetArgument(int index);

/* Returns */

	template<class type>
	void Return(type value);
	
};

