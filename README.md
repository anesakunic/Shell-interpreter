Shell Interpreter (my_shell)
Overview
This is a simple shell interpreter written in C that allows users to enter and execute basic commands.
The shell supports commands such as ls, pwd, grep, and cd. It creates a child process to execute the entered command and waits for the child process to finish before prompting for the next command.

Features
Basic command-line interface.
Supports commands: ls, pwd, grep, and cd.
Child processes are created to execute commands.
Error handling for command execution and directory change.

Commands
ls: List files in the current directory.
pwd: Print the current working directory.
grep: Search for a pattern in a file.
cd: Change the current directory.

Notes
The code uses fork() to create a child process for command execution.
It utilizes execvp() to execute supported commands.
Error messages are displayed for failed command execution or directory change.
Feel free to explore.
