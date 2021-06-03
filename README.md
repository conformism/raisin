<img src="./icon/raisin.svg" align="right" width="15%" title="Raisin">

# Raisin

Raisin aims to produce aesthetic source level [control flow ~~grapes~~ graphs (CFG)](https://en.wikipedia.org/wiki/Control-flow_graph) from C++ code, just like some proprietary tools such as [SciTools Understand](https://scitools.com/feature/control-flow-graphs/) do.

Early stage project.

Forked from the [kirshanthans cfg-clang](https://github.com/kirshanthans/cfg-clang) example.

## Dev

```bash
mkdir build && cd build
conan install -b missing -s compiler.libcxx=libstdc++11 ..
cmake ..
make
ctest -V
```


Build the container :
```sh
docker build . -t raisin:0.1
```

Build Raisin:
```sh
docker run -v $PWD:/disks/ramfs -it raisin:0.1
```

And run it :
```sh
docker run -v $PWD:/disks/ramfs -it raisin:0.1 bash

	out/raisin ../test/02.noinclude.cpp --
```
