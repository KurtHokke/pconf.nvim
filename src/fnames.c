#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#define ERRSIZE 256

static int l_fnames(lua_State *L)
{
  const char *path = luaL_checkstring(L, 1);
  const char *pattern = NULL;
  regex_t regex;
  int regex_compiled = 0;
  int keep_ext = 1;

  if (lua_istable(L, 2)) {
    lua_getfield(L, 2, "pattern");
    pattern = luaL_optstring(L, -1, NULL);
    lua_pop(L, 1);

    lua_getfield(L, 2, "keep_ext");
    keep_ext = lua_isboolean(L, -1)? lua_toboolean(L, -1) : 1;
    lua_pop(L, 1);

    if (pattern) {
      int ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
      if (ret != 0) {
        char errbuf[ERRSIZE];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        lua_pushfstring(L, "regex compilation failed: %s", errbuf);
        return 1;
      }
      regex_compiled = 1;
    }

  }

  DIR *dir = opendir(path);
  if (dir == NULL) {
    if (regex_compiled) regfree(&regex);
    lua_pushfstring(L, "failed to open %s", path);
    return -1;
  }

  int i = 1;
  lua_newtable(L);
  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_name[0] == '.') {
      if (entry->d_name[1] == '\0') continue;
      if (entry->d_name[1] == '.' && entry->d_name[2] == '\0') continue;
    }
    if (regex_compiled && regexec(&regex, entry->d_name, 0, NULL, 0) != 0) {
      continue;
    }
    char name[strlen(entry->d_name)];
    strcpy(name, entry->d_name);
    if (!keep_ext) {
      char *dot = strrchr(name, '.');
      if (dot != NULL && dot != name && *(dot - 1) != '/') {
          // Ensure it's not a directory or hidden file like .gitignore
          *dot = '\0';
      }
    }
      lua_pushinteger(L, i);
      lua_pushfstring(L, "%s", name);
      lua_settable(L, -3);
      i++;
  }
  closedir(dir);
  if (regex_compiled) regfree(&regex);
  return 1;
}

static const struct luaL_Reg fnames[] = {
    {"fnames", l_fnames},
    {NULL, NULL} // Sentinel
};

int luaopen_fnames(lua_State *L) {
    luaL_openlib(L, "fnames", fnames, 0); // Register functions in global table 'mylib'
    return 1;                           // Return the table
}
