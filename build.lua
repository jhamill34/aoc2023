---@diagnostic disable: undefined-global
workspace "Advent of Code"
    configurations { "Debug", "Release", "Dist" }
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

