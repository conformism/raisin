<img src="./icon/raisin.svg" align="right" width="15%" title="Raisin">

# Raisin

Raisin aims to produce aesthetic source level [control flow ~~grapes~~ graphs (CFG)](https://en.wikipedia.org/wiki/Control-flow_graph) from C++ code, just like some proprietary tools such as [SciTools Understand](https://scitools.com/feature/control-flow-graphs/) do.

Early stage project and by the way it became our playground to experiment architectural design, development tools and modern C++ features. Don't expect it to become a thing soon.

Forked from the [kirshanthans cfg-clang](https://github.com/kirshanthans/cfg-clang) example.

## Dev

Enter the dev env :
```sh
nix develop
```

Basic build commands :
```sh
mkdir build && cd build
cmake .. -DCMAKE_CXX_COMPILER=<clang++|g++> -DCMAKE_BUILD_TYPE=<Debug|Coverage|Release>
make
```

The dev env relies on the tools provided by the [cmake-utils](https://github.com/conformism/cmake-utils) CMake library, take a look for usage informations.
