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

