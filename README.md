# minishell

This is a group project, made with [@leevyh](https://github.com/leevyh)

## Overview

The `minishell` project is a complex endeavor that involves creating a minimal Unix shell. A shell is a command-line interface that allows users to interact with the operating system by running commands and managing processes. In this project, students are tasked with building a basic shell from scratch, capable of executing various commands, managing environment variables, and handling input/output redirection.

The `minishell` project is a fundamental stepping stone to understanding the inner workings of shells and how they process user commands. It requires implementing core features such as command execution, handling built-in shell commands, managing environment variables, and handling signals.

## Key Components

1. **Command Execution**: The shell should be capable of launching external commands (e.g., `/bin/ls`) and managing their execution.

2. **Built-In Commands**: Implementing built-in commands like `cd`, `echo`, `pwd`, and `env`, which are executed directly by the shell without invoking external processes.

3. **Environment Variables**: Managing environment variables, including adding, modifying, and deleting them.

4. **Input/Output Redirection**: Allowing users to redirect command input and output using `<`, `>`, `<<` and `>>`.

5. **Pipes**: Handling the execution of commands connected by pipes (`|`) and effectively redirecting the output of one command as the input of another.

6. **Signals**: Properly handling signals like `Ctrl+C`, `Ctrl+D` and `Ctrl+\`.

7. **Command Line Editing**: Providing basic command line editing features such as line editing and command history.

8. **Error Handling**: Ensuring that the shell handles errors correctly and provides meaningful error messages.

9. **Quoting and Escaping**: Implementing proper parsing and handling of special characters, quoting, and escaping.

## Key Skills Developed

1. **System Programming**: Understanding system calls, processes, and file management is crucial in building a functional shell.

2. **Command Execution**: Learning how to spawn and manage external processes, including error handling and communication with them.

3. **Shell Concepts**: Gaining a deep understanding of shell concepts such as environment variables, input/output redirection, and pipes.

4. **Signal Handling**: Managing Unix signals and ensuring the shell responds appropriately to user interruptions.

5. **Command Line Editing**: Developing user-friendly command line editing and history functionality to enhance the user experience.

6. **Parsing and Tokenization**: Implementing parsing and tokenization of user input, considering quoting, escaping, and special characters.

7. **Problem Solving**: Addressing complex issues in process management, input/output redirection, and error handling.

8. **Debugging Skills**: Learning how to debug complex programs and trace issues in system calls and processes.

<!-- 
### Mandatory

- **Prompt** : OK
- **Historique** : OK
- **Stock PATH/env** : OK
- **Variable Globale** : OK
- **Guillemets** : 
	- Pas interpreter guillemets non fermes en \ ou ;
	- Gerer '
	- Gerer "
- **Redirections** : OK
- **|** : OK
- **Stocker variables environment** : OK
- **$?** : OK
- **Signaux d'arret** Gérer ctrl-C, ctrl-D et ctrl-\ 
	- Ctrl-C
		- (while typing, before hiting enter) : newline OK
		- (in the middle of cmd) : closes cmd + newline OK
	- Ctrl-D 
		- (while typing, before hiting enter) : nothing happens OK
		- (in the middle of cmd) : closes cmd + newline OK
	- Ctrl-\ 
		- (while typing, before hiting enter) : nothing happens OK
		- (in the middle of cmd) : OK
	
- **BUILTINS** :
	- echo et l’option -n
	- cd uniquement avec un chemin relatif ou absolu
	- pwd sans aucune option
	- export sans aucune option
	- unset sans aucune option
	- env sans aucune option ni argument
	- exit sans aucune option -->
