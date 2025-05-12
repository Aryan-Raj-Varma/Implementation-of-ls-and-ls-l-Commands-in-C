# Implementation-of-ls-and-ls-l-Commands-in-C

# Simple `ls` and `ls -l` Implementation in C

This project provides a basic implementation of the Unix `ls` and `ls -l` commands using C and command-line arguments. It uses POSIX system calls to read directory contents and display information similar to the native `ls` utility.

---

##  Features

- Lists files in a specified directory (defaults to current directory)
- Supports the `-l` option for long listing format
- Displays file permissions, number of links, owner, group, size, and modification time
- Skips hidden files (those starting with `.`)
- Simple command-line argument parsing

---

##  Build Instructions

### Prerequisites

- GCC or any C compiler
- Linux or Unix-based system

### Compilation

```bash
gcc ls_clone.c -o ls_clone
