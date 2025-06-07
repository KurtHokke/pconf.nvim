local M = {}

---@class ScanDirOpts
---@field pattern string?

---@param dir string
---@param opts ScanDirOpts?
function M.scandir(dir, opts)
  opts = opts or {}
  local c = require'pconf.lua.lib.fnames'
  return c.fnames(dir, opts)
end

return M
