# JKOS

JK operating system.

![jkos](https://user-images.githubusercontent.com/97398293/229361498-ca4ba2ee-f97f-4c31-a596-c8beb075d5a6.png)

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
