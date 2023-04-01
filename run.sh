#!/bin/bash
set -xe
make && qemu-system-x86_64 build/boot.bin