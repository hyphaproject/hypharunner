# Hypha libraries

1) Development

The project is contained in a source directory for active development.

binaries: ./build
rpath:    absolute paths to all dependencies
datapath: ..


2) Installation (default)

The project is installed in a self-contained directory, ready for being moved or copied to another location or computer.

binaries: ./bin
rpath:    $ORIGIN/../lib
datapath: ..


3) Installation (unix system install)

The project is installed globally on a system.

binaries: /usr/[local/]bin
rpath:    empty
datapath: /usr/[local/]share/<projectname>
