#!/bin/bash 

DAY=$1

mkdir "day${DAY}"
mkdir "day${DAY}/src"

cat <<-BUILD  > day${DAY}/build.lua
---@diagnostic disable: undefined-global
project "day${DAY}"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("target/" .. OutputDir .. "/%{prj.name}")
    objdir ("target/obj/" .. OutputDir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs { "src", "../common/src" }

    links { "common" }

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "RELEASE"
        runtime "Release"
        symbols "on"
        optimize "on"

    filter "configurations:Dist"
        defines "DIST"
        runtime "Release"
        symbols "off"
        optimize "on"
BUILD


cat <<-SOURCE  > day${DAY}/src/day${DAY}.cpp
#include "common/common.h"

#include <cstdio>

int main(int argc, char *argv[]) { 
    // char *data = read_file(argv[1]);

    printf("Welcome to day ${DAY}!\n");

    return 0; 
}
SOURCE


cat <<-MAIN >> build.lua 
group "day${DAY}"
    include "day${DAY}/build.lua"

MAIN

