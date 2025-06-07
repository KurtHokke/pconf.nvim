local M = {}

local fnames_lib

function M.setup(opts)
  opts = opts or {}
  fnames_lib = require'pconf.loadlib'()
end

function M.scandir(dir, opts)
  opts = opts or {}
  if fnames_lib == nil then
    print('fail')
  end
  return fnames_lib.fnames(dir, opts)
end

return M

