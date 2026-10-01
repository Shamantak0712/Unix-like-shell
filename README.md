# Unix-like Shell in C

A minimal Unix-like shell written in C as a systems programming learning project.

The purpose of this project was to understand how a shell interacts with the Linux operating system to read commands, create processes, execute programs, and wait for them to finish.

## Features

- Command-line input using `getline()`
- Command tokenization using `strtok()`
- Command argument storage using `argv`
- External command execution using `execvp()`
- Process creation using `fork()`
- Parent-child synchronization using `waitpid()`
- Built-in `cd` command
- Built-in `exit` command
- Basic error handling
- Handling of empty commands

## Example

```text
echo> ls
echo> pwd
echo> cd /tmp
echo> pwd
echo> echo Hello World
echo> exit
```

## How It Works

The shell follows a basic command execution pipeline:

```text
User Input
    ↓
getline()
    ↓
Tokenization with strtok()
    ↓
argv[]
    ↓
Check Built-in Commands
    ↓
fork()
    ↓
    ├── Child → execvp()
    │
    └── Parent → waitpid()
```

### 1. Reading Input

`getline()` reads a complete line of input from the user.

```c
getline(&line, &capacity, stdin);
```

The input buffer can grow dynamically as required.

### 2. Tokenization

`strtok()` separates the command into individual tokens.

For example:

```text
echo hello world
```

becomes:

```text
argv[0] = "echo"
argv[1] = "hello"
argv[2] = "world"
argv[3] = NULL
```

The final `NULL` is required because functions such as `execvp()` expect the argument array to be NULL-terminated.

### 3. Built-in Commands

Some commands need to be handled directly by the shell instead of being executed as separate programs.

For example, `cd` changes the working directory of the shell itself, so it is handled using `chdir()`.

The `exit` command terminates the shell.

### 4. Process Creation

For external commands, the shell creates a child process using:

```c
fork();
```

This creates two processes:

- Parent process: the shell
- Child process: the process that will execute the requested command

### 5. Program Execution

The child process uses:

```c
execvp(argv[0], argv);
```

`execvp()` replaces the child process with the requested program.

For example, when the user enters:

```text
ls
```

the child process is replaced by the `ls` program.

### 6. Waiting

The parent shell waits for the child process using:

```c
waitpid(pid, NULL, 0);
```

This allows the shell to wait for a foreground command to finish before accepting the next command.

## Concepts Learned

This project helped me understand:

- C pointers
- Arrays of pointers
- Strings in C
- Dynamic memory
- Command-line argument arrays
- String tokenization
- Linux processes
- Parent and child processes
- Process creation
- Program execution
- System calls
- Process synchronization
- Basic Unix shell architecture

## Compilation

Compile the shell using GCC:

```bash
gcc shell.c -o shell
```

## Running

Run the shell with:

```bash
./shell
```

## Project Structure

```text
unix-like-shell/
├── shell.c
├── README.md
└── .gitignore
```

## Limitations

This is an educational minimal shell and is not intended to be a replacement for shells such as Bash.

It currently does not implement:

- Pipes
- Input/output redirection
- Background jobs
- Advanced signal handling
- Shell scripting
- Quoting and escaping rules
- Wildcard expansion
- Job control

## Future Extensions

Possible future extensions include:

- Pipes (`|`)
- Input/output redirection (`<`, `>`)
- Background processes (`&`)
- Signal handling
- Environment variable expansion
- Job control

These features were intentionally left out of the minimum version of the project.

## Purpose

This project was built primarily as a learning exercise to understand how command-line shells interact with Linux processes and system calls.
