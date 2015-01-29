solution 'warhog'
	platforms { 'x32', 'x64' }
	configurations { 'Release', 'Debug' }
	location 'build'
	startproject 'editor'
	
	filter 'platforms:x32'
		architecture 'x32'
		
	filter 'platforms:x64'
		architecture 'x64'
	
	-- Get dep libs location
	local dep = os.getenv('DEP_ROOT')
	
	project 'engine'
		targetname 'engine'
		language 'C++'
		kind 'SharedLib'
		
		defines { 'ENGINE_LIB', 'UMOF_LIBRARY' }
		includedirs { dep..'/include' }
		vectorextensions 'AVX'
		
		links
		{ 
			'opengl32',
			'entityx',
			'lua'
		}
		
		files
		{
			'src/engine/**.h',
			'src/engine/**.cpp'
		}
		
		-- Exclude extra platforms from build
		if os.is('windows') then
			excludes
			{ 
				'src/engine/platforms/null/**',
				'src/engine/render/opengl/platforms/null/**'
			}
		else
			excludes
			{
				'src/engine/platforms/win32/**',
				'src/engine/render/opengl/platforms/null/**'
			}
		end
		
		filter { 'platforms:x32', 'Debug' }
			libdirs { dep..'/lib/x86/Debug'}
		filter { 'platforms:x32', 'Release' }
			libdirs { dep..'/lib/x86/Release'}
		filter { 'platforms:x64', 'Debug' }
			libdirs { dep..'/lib/x64/Debug'}
		filter { 'platforms:x64', 'Release' }
			libdirs { dep..'/lib/x64/Release'}
		
		filter 'Debug'
			targetdir 'bin/debug'
			defines '_DEBUG'
			flags { 'Symbols' }
			
			links 
			{
				'zlibd',
				'libpngd',
				'libyaml-cppmdd',
				'luabind09-d'
			}
			
		filter 'Release'
			targetdir 'bin/release'
			defines 'NDEBUG'
			optimize 'On'
			
			links 
			{
				'zlib',
				'libpng',
				'libyaml-cppmd',
				'luabind09'
			}
			
	project 'launcher'
		targetname 'launcher'
		language 'C++'
		kind 'WindowedApp'
		
		includedirs
		{ 
			'src/engine',
			dep..'/include'
		}
		
		links
		{
			'engine',
			'entityx'
		}
		
		files
		{
			'src/launcher/**'
		}
		
		filter { 'platforms:x32', 'Debug' }
			libdirs { dep..'/lib/x86/Debug'}
		filter { 'platforms:x32', 'Release' }
			libdirs { dep..'/lib/x86/Release'}
		filter { 'platforms:x64', 'Debug' }
			libdirs { dep..'/lib/x64/Debug'}
		filter { 'platforms:x64', 'Release' }
			libdirs { dep..'/lib/x64/Release'}
		
		filter 'Debug'
			targetdir 'bin/debug'
			defines '_DEBUG'
			flags { 'Symbols' }
			
		filter 'Release'
			targetdir 'bin/release'
			defines 'NDEBUG'
			optimize 'On'
			
	project 'editor'
		targetname 'editor'
		language 'C++'
		kind 'WindowedApp'
		
		defines { 'Q_COMPILER_INITIALIZER_LISTS' }
		
		includedirs
		{ 
			'src/engine',
			dep..'/include'
		}
		
		links 
		{ 
			'engine',
			'entityx',
			'libnoise'
		}
		
		files
		{
			'src/editor/**.h',
			'src/editor/**.cpp',
			'src/editor/**.ui',
			'src/editor/**.qrc',
			'src/editor/**.qss'
		}
		
		include 'qt.lua'
		local qt = premake.extensions.qt
		local qtDir = os.getenv('QT_ROOT')
		qt.enable()
		qtpath(qtDir)
		qtmodules { 'core', 'gui', 'widgets', 'opengl', 'concurrent' }
		qtprefix 'Qt5'
		
		filter { 'platforms:x32', 'Debug' }
			libdirs { dep..'/lib/x86/Debug'}
		filter { 'platforms:x32', 'Release' }
			libdirs { dep..'/lib/x86/Release'}
		filter { 'platforms:x64', 'Debug' }
			libdirs { dep..'/lib/x64/Debug'}
		filter { 'platforms:x64', 'Release' }
			libdirs { dep..'/lib/x64/Release'}
		
		filter 'Debug'
			targetdir 'bin/debug'
			defines '_DEBUG'
			flags { 'Symbols' }
			qtsuffix 'd'
			
			links 
			{
				'libyaml-cppmdd',
				'FreeImaged',
				'assimpd'
			}
			
		filter 'Release'
			targetdir 'bin/release'
			defines 'NDEBUG'
			optimize 'On'
			
			links 
			{
				'libyaml-cppmd',
				'FreeImage',
				'assimp'
			}