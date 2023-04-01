# JKOS

JK operating system.

## About

Wanted to improve my bare-metal skills, so why not make a whole operating system?

## Building and running

### Requirements

- nasm
- qemu-system-x86
- make

After installing the prerequisites, use the following command to build for Debian:

``` bash
sudo make debian
```

Then use the following command to run the iso using qemu:

``` bash
./run.sh
```

## License

JKOS is under an Apache 2.0 license.