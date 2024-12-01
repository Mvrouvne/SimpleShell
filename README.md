# SimpleShell

## Overview

The **SimpleShell** project is focused on building a basic Unix shell that mimics the behavior of a real shell. The goal is to implement essential shell functionalities such as parsing user commands, executing commands, handling pipes, redirections, and environment variables. The shell should handle multiple types of commands, including built-in commands like `cd`, `exit`, and external commands.

## Features

- **Command Parsing**: Parse user input to separate commands, arguments, and operators like pipes and redirection.
- **Built-in Commands**: Implement basic built-in commands like `cd`, `exit`, `env`, and `setenv`.
- **External Commands**: Execute external programs and manage input/output redirection (`>`, `>>`, `<`).
- **Pipes**: Implement handling for pipelines (`|`), allowing the output of one command to be passed as input to another.
- **Environment Variables**: Implement handling of environment variables and the ability to set or unset them.
- **Error Handling**: Return appropriate error messages for invalid commands or arguments.
- **Fork and Exec**: Use `fork()` and `exec()` system calls to create child processes and execute external commands.

## Key Concepts

- **System Calls**: Utilize system calls like `fork()`, `exec()`, and `wait()` to handle process creation and management.
- **Input Parsing**: Implement robust input parsing to handle spaces, quotes, pipes, and redirection.
- **Process Management**: Use process control to execute commands in the background or foreground and manage their lifecycle.
- **Redirection**: Implement input/output redirection to files or other commands.
- **Environment Management**: Manage environment variables and implement custom shell-level features like `export`.

## Learning Outcomes

By completing **SimpleShell**, you will:

- Gain a deeper understanding of how Unix-based shells work under the hood.
- Learn how to manage processes and handle inter-process communication (IPC) using pipes and redirection.
- Understand the use of system calls like `fork()`, `exec()`, and `wait()` for creating and controlling processes.
- Develop the ability to parse and interpret user commands and implement error handling.
- Improve problem-solving skills and experience working with low-level C programming concepts.

---

**SimpleShell** provides a hands-on introduction to building a custom shell, offering valuable insights into process management, system-level programming, and Unix command-line interfaces.
