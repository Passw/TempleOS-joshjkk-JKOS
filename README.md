# JKOS

JK operating system.

![Screenshot from 2023-04-02 19-23-57](https://user-images.githubusercontent.com/97398293/229371560-f58da1b1-3907-4362-9f63-ee843ef5a1f7.png)

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
