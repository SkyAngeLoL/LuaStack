#include "LuaStack.h"

/*==========
	
==========*/

LuaStack::LuaStack() {
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
LuaStack::~LuaStack() {
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

// int 
template<>
void LuaStack::AddVariable<int>(int value, char* constantname) {
	lua_pushinteger(lua_state, value);

	lua_setglobal(lua_state, constantname);
}
// double
template<>
void LuaStack::AddVariable<double>(double value, char* constantname) {
	lua_pushnumber(lua_state, value);

	lua_setglobal(lua_state, constantname);
}
// string
template<>
void LuaStack::AddVariable<char*>(char* value, char* constantname) {
	lua_pushstring(lua_state, value);

	lua_setglobal(lua_state, constantname);
}
// bool
template<>
void LuaStack::AddVariable<bool>(bool value, char* constantname) {
	lua_pushboolean(lua_state, value);

	lua_setglobal(lua_state, constantname);
}
// functions
template<>
void LuaStack::AddVariable<lua_CFunction>(lua_CFunction value, char* constantname) {
	lua_pushcfunction(lua_state, value);

	lua_setglobal(lua_state, constantname);
}


/*=============
	Tables
=============*/

void LuaStack::Table() {
	lua_createtable(lua_state, 2, 0);
}
// int
template<>
void LuaStack::AddVarInTable<int>(int value, int index) {
	lua_pushnumber(lua_state, index);

	lua_pushinteger(lua_state, value);

	lua_settable(lua_state, -3);
}
// double
template<>
void LuaStack::AddVarInTable<double>(double value, int index) {
	lua_pushnumber(lua_state, index);

	lua_pushnumber(lua_state, value);

	lua_settable(lua_state, -3);
}
// string
template<>
void LuaStack::AddVarInTable<char*>(char* value, int index) {
	lua_pushnumber(lua_state, index);

	lua_pushstring(lua_state, value);

	lua_settable(lua_state, -3);
}
// bool
template<>
void LuaStack::AddVarInTable<bool>(bool value, int index) {
	lua_pushnumber(lua_state, index);

	lua_pushboolean(lua_state, value);

	lua_settable(lua_state, -3);
}
// functions
template<>
void LuaStack::AddVarInTable<lua_CFunction>(lua_CFunction value, int index) {
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
// int
template<>
int LuaStack::GetArgument<int>(int index) {
	return lua_tointeger(lua_state, index);
}
// double
template<>
double LuaStack::GetArgument<double>(int index) {
	return lua_tonumber(lua_state, index);
}
// string
template<>
char* LuaStack::GetArgument<char*>(int index) {
	return (char*)lua_tostring(lua_state, index);
}
// bool
template<>
bool LuaStack::GetArgument<bool>(int index) {
	return lua_toboolean(lua_state, index);
}


/*=============
	Returns
=============*/

// int
template<>
void LuaStack::Return<int>(int value) {
	lua_pushinteger(lua_state, value);
}
// double
template<>
void LuaStack::Return<double>(double value) {
	lua_pushnumber(lua_state, value);
}
// string
template<>
void LuaStack::Return<char*>(char* value) {
	lua_pushstring(lua_state, value);
}
// bool
template<>
void LuaStack::Return<bool>(bool value) {
	lua_pushboolean(lua_state, value);
}