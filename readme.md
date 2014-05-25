# War Hog Engine
![Alt text](https://bitbucket-assetroot.s3.amazonaws.com/c/photos/2014/Mar/06/warhog-engine-logo-3151599318-1_avatar.png)

## Build engine
To build engine you will need [premake5](https://bitbucket.org/premake/premake-dev). Clone the repository and build it using documentation.

### Boost
The project depends on [boost](https://github.com/boostorg/boost) libraries. To install it clone the git repository with submodules. Then run ```boostrap``` for your target platform to compile b2 build tool. Now you can build boost running ```b2 install```. To produce proper library names use ```--layout=system``` and properties with one of the following values:

* variant (debug/release)
* threading (single/multi)
* link (static/shared)
* address-model (32/64)
* toolset (gcc/msvc/...)

Create environment viriable ```BOOST_ROOT``` to make boost visible to premake5.

### Yaml-cpp
Projects also depends on [yaml-cpp](https://code.google.com/p/yaml-cpp/). It can be installed by cloning repositary and running cmake utility. Create environment variable ```YAML_ROOT``` to make it visible to premake5.

### GLEW
Download latest release of GLEW with binaries. Define environment variable ```GLEW_ROOT``` to build project.

Name | Link
-----|------
boost | https://github.com/boostorg/boost
entityx | https://github.com/alecthomas/entityx
yaml-cpp | https://code.google.com/p/yaml-cpp/
zlib | https://github.com/madler/zlib
glew | https://github.com/nigels-com/glew
glfw | https://github.com/glfw/glfw
glm | https://github.com/g-truc/glm
lua | https://github.com/LuaDist/lua
luabind	| https://github.com/LuaDist/luabind
tinyobjloader | https://github.com/syoyo/tinyobjloader
libpng | http://sourceforge.net/projects/libpng/
libjpeg-turbo | https://github.com/jberkel/libjpeg-turbo