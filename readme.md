# WarHog Engine
![Alt text](https://bitbucket-assetroot.s3.amazonaws.com/c/photos/2014/Mar/06/warhog-engine-logo-3151599318-1_avatar.png)

## Build engine
To build engine you will need [premake5](https://bitbucket.org/premake/premake-dev) and a few third-party libraries. You can find current project dependencies below.

### Engine dependencies

Name | Link
-----|------
boost | https://github.com/boostorg/boost
entityx | https://github.com/alecthomas/entityx
lua | https://github.com/LuaDist/lua
luabind	| https://github.com/LuaDist/luabind
glm | https://github.com/g-truc/glm
yaml-cpp | https://code.google.com/p/yaml-cpp/
libpng | http://sourceforge.net/projects/libpng/
zlib | https://github.com/madler/zlib

### Editor dependencies

Name | Link
-----|------
Qt | http://qt-project.org/
assimp | http://assimp.sourceforge.net/
FreeImage | http://freeimage.sourceforge.net/
libnoise | http://libnoise.sourceforge.net/

### Build process
You can download prebuilt third-party libraries (vs2013) in download section.

To generate project files define following environment variables: DEP_ROOT and QT_ROOT. Then run ```premake5 vs2013``` in project root.

Now you are ready to build project. Just ```cd``` to "build" folder and open project files.
