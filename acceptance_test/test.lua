#!/usr/bin/env lua
local e = ... or 'macosx/bin/Debug/ris'

os.execute(e .. " acceptance_test/test.json")
