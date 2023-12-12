---@diagnostic disable: undefined-global
project "day11"
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
