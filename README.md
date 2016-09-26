# Hypha Runner

### Quick start

First install CMake, Poco, Boost

#### Build confdesc

```sh
git clone https://github.com/falsecam/confdesc.git
cd confdesc
mkdir build
cd build
cmake ..
make
```

#### Build hypha

```sh
git clone https://github.com/hyphaproject/hypha.git
cd hypha
mkdir build
cd build
cmake ..
make
```

#### Build hypharunner

```sh
git clone https://github.com/hyphaproject/hypharunner.git
cd hypharunner
mkdir build
cd build
cmake -Dhypha_DIR=../hypha -Dconfdesc_DIR=../confdesc ..
make
```

-------------------------------
![Logo](/deploy/images/logo.png) Icon made by [Freepik](http://www.freepik.com) from [www.flaticon.com](http://www.flaticon.com)
