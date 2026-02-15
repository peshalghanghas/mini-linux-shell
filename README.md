# Mini Linux Shell

## Overview
A custom Unix-style shell implemented in C using POSIX system calls.  
Supports built-in commands, background execution, and command history. Designed to demonstrate core systems programming skills including process management and inter-process synchronization.

## Architecture
- Parent shell runs an infinite loop, reading user input
- Forked child process created per command
- `execvp()` executes programs in child process
- `waitpid()` ensures foreground commands complete before continuing
- Background processes run concurrently without blocking the shell
- Command history stored in a circular buffer (last 10 commands)

## Key Features
- Built-in commands: `cd`, `exit`
- Background execution using `&`
- Command history (last 10 commands, in-memory)
- Robust error handling for invalid commands or paths

## Process Lifecycle
1. Read user input using `fgets()`
2. Remove trailing newline
3. Store command in history
4. Parse input into arguments using `strtok()`
5. Check for built-in commands (`cd`, `exit`, `history`)
6. Detect background execution (`&`)
7. Fork a child process
8. Execute command in child process using `execvp()`
9. Parent waits if foreground; continues immediately if background

## How to Compile
```bash
gcc main.c -o shell

## How to Run
./shell


## Example Usage 
mini-shell> ls
mini-shell> sleep 5 &
Started background process with PID: 12345
mini-shell> cd ..
mini-shell> history
1 ls
2 sleep 5 &
3 cd ..

