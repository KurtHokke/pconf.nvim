local fnames_lib

return function()
  if fnames_lib then
    return fnames_lib
  end
  local lib_path = vim.api.nvim_get_runtime_file("lua/pconf/lib/" .. "fnames.so", false)[1]
  if not lib_path then
    error("C library not found: " .. "fnames.so")
  end
  local lib, err = package.loadlib(lib_path, 'luaopen_fnames')
  if not lib then
    error("Failed to load C library: " .. tostring(err))
  end
  fnames_lib = lib()
  return fnames_lib
end
