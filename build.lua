---@diagnostic disable: undefined-global
workspace "Advent of Code"
    configurations { "Part1", "Part2" }
    architecture "ARM64"

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "common"
    include "common/build.lua"

group "day0"
    include "day0/build.lua"

group "day1"
    include "day1/build.lua"

group "day2"
    include "day2/build.lua"

group "day3"
    include "day3/build.lua"

group "day4"
    include "day4/build.lua"

group "day5"
    include "day5/build.lua"

group "day6"
    include "day6/build.lua"

group "day7"
    include "day7/build.lua"

group "day8"
    include "day8/build.lua"

group "day9"
    include "day9/build.lua"

group "day10"
    include "day10/build.lua"

group "day11"
    include "day11/build.lua"

group "day12"
    include "day12/build.lua"

