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

	filter "configurations:Part1"
		defines "PART1"
		runtime "Debug"
		symbols "on"

	filter "configurations:Part2"
		defines "PART2"
		runtime "Debug"
		symbols "on"
BUILD


cat <<-SOURCE  > day${DAY}/src/day${DAY}.cpp
#include "common/common.h"

#include <iostream>

void Parse(const std::vector<char>& data) {
    int current = 0, line = 1;

    while (current < data.size()) {
        current++;
    }
}

void part1() {
    std::cout << "not implemented\n";
    exit(1);
}

void part2() {
    std::cout << "not implemented\n";
    exit(1);
}

int main(int argc, char *argv[]) { 
    std::cout << "Welcome to day ${DAY}!\n";
    std::vector<char> data = Common::ReadFile(argv[1]);

    Parse(data);

#ifdef PART1 
    part1();
#endif

#ifdef PART2
    part2();
#endif

    return 0; 
}
SOURCE


cat <<-MAIN >> build.lua 
group "day${DAY}"
    include "day${DAY}/build.lua"

MAIN

