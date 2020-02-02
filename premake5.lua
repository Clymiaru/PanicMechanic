-- Sandbox Premake5 File

SolutionName = "PanicMechanic"

ProjectName = "PanicMechanic"

workspace (SolutionName)
    configurations 
    {
        "Debug",
        "Release"
    }

    platforms
    {
        "Win64",
        "Win32"
    }

    flags
    {
        "MultiProcessorCompile"
    }

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

-- File path of the "dependencies" folder 
DependencyDir = "%{ProjectName}/dependencies"

-- File path of the "source" folder
SourceDir = "%{ProjectName}/source"

-- File path of the "include" folder
IncludeDir = "%{ProjectName}/source"

-- Dependency Directiories --
Dependencies = {}
Dependencies["Log"] = "spdlog"
Dependencies["SFML32"] = "SFML32"
Dependencies["SFML64"] = "SFML64"


project (ProjectName)
    location (ProjectName)
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
    targetdir ("bin/"..OutputDir.."/%{prj.name}")
    objdir ("bin-int/"..OutputDir.."/%{prj.name}")
    
    --pchheader "pch.h"
    --pchsource "%{SourceDir}/pch.cpp"

    files
    {
        "%{IncludeDir}/**.h",
        "%{SourceDir}/**.cpp"
    }

    includedirs
    {
        "%{IncludeDir}",
        "%{DependencyDir}/%{Dependencies.Log}/include"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "SFML_STATIC"
    }

    filter "platforms:Win32"
        architecture "x32"
        system "windows"

        includedirs
        {
            "%{DependencyDir}/%{Dependencies.SFML32}/include"
        }

        libdirs
        {
            "%{DependencyDir}/%{Dependencies.SFML32}/lib"
        }

        defines
        {
            "WIN32"
        }
        
    filter "platforms:Win64"
        architecture "x64"
        system "windows"

        includedirs
        {
            "%{DependencyDir}/%{Dependencies.SFML64}/include"
        }

        libdirs
        {
            "%{DependencyDir}/%{Dependencies.SFML64}/lib"
        }

        defines
        {
            "WIN64"
        }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "DEBUG" 
        buildoptions "/MDd"
        runtime "Debug"
        symbols "on"

        links
        {
            "opengl32.lib",
            "freetype.lib",
            "winmm.lib",
            "gdi32.lib",
            "openal32.lib",
            "flac.lib",
            "vorbisenc.lib",
            "vorbisfile.lib",
            "vorbis.lib",
            "ogg.lib",
            "sfml-audio-s-d.lib",
            "sfml-graphics-s-d.lib",
            "sfml-window-s-d.lib",
            "sfml-system-s-d.lib",
        }
        
    filter "configurations:Release"
        defines "RELEASE" 
        buildoptions "/MD"
        runtime "Release"
        optimize "on"

        links
        {
            "opengl32.lib",
            "freetype.lib",
            "winmm.lib",
            "gdi32.lib",
            "openal32.lib",
            "flac.lib",
            "vorbisenc.lib",
            "vorbisfile.lib",
            "vorbis.lib",
            "ogg.lib",
            "sfml-audio-s.lib",
            "sfml-graphics-s.lib",
            "sfml-window-s.lib",
            "sfml-system-s.lib",
        }
