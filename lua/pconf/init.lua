local M = {}
-- _G.pConf = {}
-- local log = require'functions.logger'.log

function M.scandir(dir, opts)
  return require'pconf.lua.pconf.lib'.scandir(dir, opts)
end

---@param dir string
---@param opts ScanDirOpts?
function M.init(dir, opts)
  return M.scandir(dir, opts)
end

return M

