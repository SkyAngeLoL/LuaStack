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
	
	/*=============================
		Constructor/Destructor
	=============================*/

	LuaStack() {
		lua_state = luaL_newstate();

		static const luaL_Reg lualibs[] = {
				{"base", luaopen_base},
				{"io", luaopen_io},
				{NULL, NULL}
		};

		for(const luaL_Reg *lib = lualibs; lib->func != NULL; lib++) {
			luaL_requiref(lua_state, lib->name, lib->func, 1);

			lua_settop(lua_state, 0);
		}

	}
	~LuaStack() {
		lua_close(lua_state);
	}

	/*==================
		Run lua file
	==================*/

	int LuaStack::RunFile(char* ScriptFileName) {
		luaL_dofile(lua_state, ScriptFileName);

		return lua_tointeger(lua_state, lua_gettop(lua_state));
	}

	/*==============
		Def vars
	==============*/

	void AddVariable(int value, char* constantname) {
		lua_pushinteger(lua_state, value);

		lua_setglobal(lua_state, constantname);
	}

	void AddVariable(double value, char* constantname) {
		lua_pushnumber(lua_state, value);

		lua_setglobal(lua_state, constantname);
	}

	void AddVariable(char* value, char* constantname) {
		lua_pushstring(lua_state, value);

		lua_setglobal(lua_state, constantname);
	}

	void AddVariable(bool value, char* constantname) {
		lua_pushboolean(lua_state, value);

		lua_setglobal(lua_state, constantname);
	}

	void AddVariable(lua_CFunction value, char* constantname) {
		lua_pushcfunction(lua_state, value);

		lua_setglobal(lua_state, constantname);
	}

	/*=============
		Tables
	=============*/

	void Table() {
		lua_createtable(lua_state, 2, 0);
	}

	void AddVarInTable(int value, int index) {
		lua_pushnumber(lua_state, index);

		lua_pushinteger(lua_state, value);

		lua_settable(lua_state, -3);
	}

	void AddVarInTable(double value, int index) {
		lua_pushnumber(lua_state, index);

		lua_pushnumber(lua_state, value);

		lua_settable(lua_state, -3);
	}

	void AddVarInTable(char* value, int index) {
		lua_pushnumber(lua_state, index);

		lua_pushstring(lua_state, value);

		lua_settable(lua_state, -3);
	}

	void AddVarInTable(bool value, int index) {
		lua_pushnumber(lua_state, index);

		lua_pushboolean(lua_state, value);

		lua_settable(lua_state, -3);
	}

	void AddVarInTable(lua_CFunction value, int index) {
		lua_pushnumber(lua_state, index);

		lua_pushcfunction(lua_state, value);

		lua_settable(lua_state, -3);
	}

	/*====================
		Get arguments
	====================*/

	int LuaStack::GetArgumentCount() {
		return lua_gettop(lua_state);
	}

	template<class type>
	type GetArgument(int index);

	template<>
	int GetArgument<int>(int index) {
		return lua_tointeger(lua_state, index);
	}
	
	template<>
	double GetArgument<double>(int index) {
		return lua_tonumber(lua_state, index);
	}
	
	template<>
	char* GetArgument<char*>(int index) {
		return (char*)lua_tostring(lua_state, index);
	}
	
	template<>
	bool LuaStack::GetArgument<bool>(int index) {
		return lua_toboolean(lua_state, index);
	}

	/*=============
		Returns
	=============*/

	void Return(int value) {
		lua_pushinteger(lua_state, value);
	}

	void Return(double value) {
		lua_pushnumber(lua_state, value);
	}

	void Return(char* value) {
		lua_pushstring(lua_state, value);
	}

	void Return(bool value) {
		lua_pushboolean(lua_state, value);
	}
};

