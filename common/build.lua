---@diagnostic disable: undefined-global
project "common"
	kind "StaticLib"
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

	includedirs { "src" }

	filter "configurations:Part1"
		defines "PART1"
		runtime "Debug"
		symbols "on"

	filter "configurations:Part2"
		defines "PART2"
		runtime "Debug"
		symbols "on"

