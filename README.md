# Mini Linux Shell

## Overview
A minimal Unix-style shell implemented in C using POSIX system calls.

## Features
- Command execution via fork() and execvp()
- Parent-child synchronization using wait()
- Built-in cd command
- Built-in exit command

## How to Compile
gcc main.c -o shell

## How to Run
./shell
