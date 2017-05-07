# Hypha Runner

### Quick start

First install CMake, Poco, Boost

#### Build confdesc

```bash
git clone https://github.com/falsecam/confdesc.git
cd confdesc
mkdir build
cd build
cmake ..
make
```

#### Build hypha

```bash
git clone https://github.com/hyphaproject/hypha.git
cd hypha
mkdir build
cd build
cmake ..
make
```

#### Build hypharunner

```bash
git clone https://github.com/hyphaproject/hypharunner.git
cd hypharunner
mkdir build
cd build
cmake -Dhypha_DIR=../hypha -Dconfdesc_DIR=../confdesc ..
make
```

#### Run hypharunner

```bash
hypharunner -pd/path/to/plugins -f/path/to/hypha.xml
```

#### Debug hypharunner

Open Runner in browser: [localhost:47965](http://localhost:47965).

Send message to plugin espeak: [http://localhost:47965/send/espeak?message={\"say\":\"hello%20world!\"}](http://localhost:47965/send/espeak?message={\"say\":\"hello%20world!\"})


-------------------------------
![Logo](/deploy/images/logo.png) Icon made by [Freepik](http://www.freepik.com) from [www.flaticon.com](http://www.flaticon.com)
