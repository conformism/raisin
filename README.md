# Poireau

![poireau](./poireau.jpg)

Control flow graph

from [kirshanthans cfg-clang](https://github.com/kirshanthans/cfg-clang)

## Dev

Build the container :
```sh
docker build . -t cfg:10
```

Build Poireau :
```sh
docker run -v $PWD:/disks/ramfs -it cfg:10
```

And run it :
```sh
docker run -v $PWD:/disks/ramfs -it cfg:10 bash

	out/poireau ../test/02.noinclude.cpp --
```
