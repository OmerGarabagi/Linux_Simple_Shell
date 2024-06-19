# MyShell

## Overview

MyShell is a custom Linux shell implemented in C. It supports basic shell functionalities, including executing commands, handling input/output redirection, and managing background processes.

## Features

- Execute standard shell commands
- Input and output redirection
- Background process management
- Simple error handling

## Functions

### main

The entry point for the shell, responsible for the main loop and handling user input.

### execute_command

Executes the given command by forking a new process.

### redirect_input

Handles input redirection.

### redirect_output

Handles output redirection.

### parse_command

Parses the user input into a command and its arguments.

### is_background

Checks if a command should be run in the background.

## Contributors

- Omer Garabagi
