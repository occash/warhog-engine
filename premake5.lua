solution "warhog"
	platforms { "x64" }
	configurations { "Release", "Debug" }
	location ( "build" )
	
	project "engine"
		targetname "engine"
		language "C++"
		kind "SharedLib"
		defines { "GLEW_STATIC", "ENGINE_LIB" }
		includedirs {
			"D:/third-party/boost",
			"D:/third-party/entityx",
			"D:/third-party/glew-1.10.0/include",
			"D:/third-party/glfw/include",
			"D:/third-party/glm",
			"D:/third-party/lua/include/lua",
			"D:/third-party/luabind",
			"D:/third-party/yaml-cpp/include",
			"D:/third-party/zlib",
			"D:/third-party/libpng"
		}
		libdirs {
			"D:/third-party/glew-1.10.0/lib/Release/x64"
		}
		links { 
			"opengl32",
			"glew32s",
			"glfw3",
			"entityx",
			"lua"
		}
		
		files
		{
			"src/engine/*.h",
			"src/engine/*.cpp",
			"src/engine/components/**.h",
			"src/engine/components/**.cpp",
			"src/engine/render/**.h",
			"src/engine/render/**.cpp",
			"src/engine/resource/**.h",
			"src/engine/resource/**.cpp",
			"src/engine/systems/**.h",
			"src/engine/systems/**.cpp",
		}
		
		if os.is('windows') then
			files 
			{ 
				"src/engine/platforms/win32/**.h",
				"src/engine/platforms/win32/**.cpp"
			}
		else
			files 
			{ 
				"src/engine/platforms/null/**.h",
				"src/engine/platforms/null/**.cpp"
			}
		end
		
		configuration "Debug"
			targetdir "bin/debug"
			defines "_DEBUG"
			flags { "Symbols" }
			libdirs { 
				"D:/third-party/glfw/x64/Debug",
				"D:/third-party/libpng/projects/visualc71/x64/LIB Debug",
				"D:/third-party/entityx/Debug",
				"D:/third-party/yaml-cpp/x64/Debug",
				"D:/third-party/lua/Debug",
				"D:/third-party/luabind/src/Debug"
			}
			links {
				"zlibd",
				"libpngd",
				"libyaml-cppmdd",
				"luabind09-d"
			}
			
		configuration "Release"
			targetdir "bin/release"
			defines "NDEBUG"
			optimize "On"
			libdirs { 
				"D:/third-party/glfw/x64/Release",
				"D:/third-party/libpng/projects/visualc71/x64/LIB Release",
				"D:/third-party/entityx/Release",
				"D:/third-party/yaml-cpp/x64/Release",
				"D:/third-party/lua/Release",
				"D:/third-party/luabind/src/Release"
			}
			links {
				"zlib",
				"libpng",
				"libyaml-cppmd",
				"luabind09"
			}
			
	project "editor"
		targetname "editor"
		language "C++"
		kind "WindowedApp"
		defines { "FREEIMAGE_LIB" }
		includedirs {
			"D:/third-party/boost/include",
			"D:/third-party/entityx",
			"D:/third-party/libnoise/noise/include",
			"D:/projects/warhog-engine/src/engine",
			"D:/third-party/FreeImage/Dist",
			"D:/third-party/glm",
			"D:/third-party/yaml-cpp/include",
			"D:/third-party/tinyobjloader"
		}
		libdirs {
			"D:/projects/warhog-engine/bin",
			"D:/third-party/FreeImage/Dist",
			"D:/third-party/tinyobjloader"
		}
		links { 
			"engine",
			"entityx",
			"libnoise"
		}
		
		files
		{
			"src/editor/**.h",
			"src/editor/**.cpp",
			"src/editor/**.ui",
			"src/editor/**.qrc",
			"src/editor/**.qss"
		}
		
		include "qt.lua"
		local qt = premake.extensions.qt
		qt.enable()
		qtpath "D:/third-party/qt-everywhere-opensource-src-5.3.0/qtbase"
		qtmodules { "core", "gui", "widgets", "opengl", "concurrent" }
		qtprefix "Qt5"
		
		configuration "Debug"
			targetdir "bin/debug"
			defines "_DEBUG"
			flags { "Symbols" }
			libdirs {
				"D:/third-party/entityx/Debug",
				"D:/third-party/yaml-cpp/x64/Debug",
				"D:/third-party/libnoise/noise/x64/Debug"
			}
			links {
				"libyaml-cppmdd",
				"FreeImaged",
				"tinyobjloaderd"
			}
			
		configuration "Release"
			targetdir "bin/release"
			defines "NDEBUG"
			optimize "On"
			libdirs {
				"D:/third-party/entityx/Release",
				"D:/third-party/yaml-cpp/x64/Release",
				"D:/third-party/libnoise/noise/x64/Release"
			}
			links {
				"libyaml-cppmd",
				"FreeImage",
				"tinyobjloader"
			}