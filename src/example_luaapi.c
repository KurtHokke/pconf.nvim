#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int l_add(lua_State *L) {
    double a = luaL_checknumber(L, 1); // Get first argument
    double b = luaL_checknumber(L, 2); // Get second argument
    lua_pushnumber(L, a + b);          // Push result
    return 1;                          // Number of return values
}

// Register functions in a table
static const struct luaL_Reg fnames[] = {
    {"add", l_add},
    {NULL, NULL} // Sentinel
};

// Module initialization function
int luaopen_fnames(lua_State *L) {
    luaL_openlib(L, "fnames", fnames, 0); // Register functions in global table 'mylib'
    return 1;                           // Return the table
}
