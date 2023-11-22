#!/bin/bash 

premake5 gmake2 --file=build.lua
premake5 export-compile-commands --file=build.lua

if [ ! -L "./compile_commands.json" ]; then
	ln -s compile_commands/debug.json compile_commands.json
fi
