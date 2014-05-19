include "qt.lua"
local qt = premake.extensions.qt

solution "warhog"
	configurations { "Release", "Debug" }
	location ( "build" )
	
	project "engine"
		targetname "engine"
		language "C++"
		kind "SharedLib"
		defines { "GLEW_STATIC", "ENGINE_LIB" }
		includedirs { "dep/include/*" }
		links { 
			"opengl32", 
			"glew32s", 
			"glfw3", 
			"libpng16", 
			"zlib", 
			"entityx", 
			"tinyobjloader",
			"libyaml-cppmd",
			"lua52",
			"libluabind"
		}
		
		files
		{
			"src/engine/**.h",
			"src/engine/**.cpp",
			"src/engine/**.lua",
			"src/engine/**.yaml",
			"src/engine/shaders/*"
		}
		
		configuration "Debug"
			targetdir "bin/debug"
			defines "_DEBUG"
			flags { "Symbols" }
			libdirs { "dep/lib/debug" }
			
		configuration "Release"
			targetdir "bin/release"
			defines "NDEBUG"
			optimize "On"
			libdirs { "dep/lib/release" }
			
	project "editor"
		targetname "editor"
		language "C++"
		kind "WindowedApp"
		includedirs { "" }
		
		files
		{
			"src/editor/**.h",
			"src/editor/**.cpp",
			"src/editor/**.ui",
			"src/editor/**.qrc"
		}
		
		qt.enable()
		qtpath "C:/third-party/qt-5.2.1/qtbase"
		qtmodules { "core", "gui", "widgets", "opengl" }
		qtprefix "Qt5"
		
		configuration "Debug"
			targetdir "bin/debug"
			defines "_DEBUG"
			flags { "Symbols" }
			
		configuration "Release"
			targetdir "bin/release"
			defines "NDEBUG"
			optimize "On"