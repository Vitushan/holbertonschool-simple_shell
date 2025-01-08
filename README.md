# Simple Shell Project

The **simple_shell** project is a custom implementation of a shell in C.
It provides basic shell functionalities, such as running commands and handling user input.
This project was developed as an educational exercise to better understand process management, forking, tokenization, and environment variables in C.

---

## Usage

### 1.  Interactive Mode:
- #### Once the shell starts, you can enter commands just like in any typical shell. For example:
```bash
#simple_shell$ ls
```
- #### You can exit the shell by typing exit:
```bash
#simple_shell$ exit
```
### 2.  Non-Interactive Mode:
- #### You can enter basic shell commands, use pipes, and specify an executable file. For example:
```bash
#zairth@LAPTOP-XXXXXXXX:/mnt/c/Users/the_User/Desktop/Holberton/holbertonschool-simple_shell$ echo "ls -l" | ./simple_shell
```

## Examples
- #### In interactive mode:  
```bash
#simple_shell$ echo "Hello, World!"
Hello, World!
#simple_shell$ exit
```

```bash
#simple_shell$ pwd"
/mnt/c/Users/the_User/Desktop/Holberton/holbertonschool-simple_shell
#simple_shell$ exit
```

```bash
#simple_shell$ ls -la"
total 40
drwxrwxrwx 1 zairth zairth   512 Dec 29 13:06 .
drwxrwxrwx 1 zairth zairth   512 Dec 24 15:57 ..
drwxrwxrwx 1 zairth zairth   512 Dec 29 13:06 .git
-rwxrwxrwx 1 zairth zairth   140 Dec 29 13:06 AUTHORS
-rwxrwxrwx 1 zairth zairth  3047 Dec 29 13:27 README.md
-rwxrwxrwx 1 zairth zairth  1901 Dec 29 13:06 function_helper.c
-rwxrwxrwx 1 zairth zairth   484 Dec 29 13:06 main.h
-rwxrwxrwx 1 zairth zairth     0 Dec 29 13:06 man_1_simple_shell
-rwxrwxrwx 1 zairth zairth 17224 Dec 29 13:06 simple_shell
-rwxrwxrwx 1 zairth zairth  4335 Dec 29 13:07 simple_shell.c
-rwxrwxrwx 1 zairth zairth  1010 Dec 29 13:06 start_forking.c
#simple_shell$ exit
```

```bash
#simple_shell$ /bin/ls -l"
total 40
-rwxrwxrwx 1 zairth zairth   140 Dec 29 13:06 AUTHORS
-rwxrwxrwx 1 zairth zairth  3847 Dec 29 13:29 README.md
-rwxrwxrwx 1 zairth zairth  1901 Dec 29 13:06 function_helper.c
-rwxrwxrwx 1 zairth zairth   484 Dec 29 13:06 main.h
-rwxrwxrwx 1 zairth zairth     0 Dec 29 13:06 man_1_simple_shell
-rwxrwxrwx 1 zairth zairth 17224 Dec 29 13:06 simple_shell
-rwxrwxrwx 1 zairth zairth  4335 Dec 29 13:07 simple_shell.c
-rwxrwxrwx 1 zairth zairth  1010 Dec 29 13:06 start_forking.c
#simple_shell$ exit
```
- #### In non-interactive mode:  
```bash
#zairth@LAPTOP-XXXXXXXX:/mnt/c/Users/the_User/Desktop/Holberton/holbertonschool-simple_shell$ echo "ls -l" | ./simple_shell
total 40
-rwxrwxrwx 1 zairth zairth   140 Dec 29 13:06 AUTHORS
-rwxrwxrwx 1 zairth zairth  3847 Dec 29 13:29 README.md
-rwxrwxrwx 1 zairth zairth  1901 Dec 29 13:06 function_helper.c
-rwxrwxrwx 1 zairth zairth   484 Dec 29 13:06 main.h
-rwxrwxrwx 1 zairth zairth     0 Dec 29 13:06 man_1_simple_shell
-rwxrwxrwx 1 zairth zairth 17224 Dec 29 13:06 simple_shell
-rwxrwxrwx 1 zairth zairth  4335 Dec 29 13:07 simple_shell.c
-rwxrwxrwx 1 zairth zairth  1010 Dec 29 13:06 start_forking.c
#simple_shell$ exit
```

## Installation
- #### Clone the repository:  
```git
git clone "https://github.com/Vitushan/holbertonschool-simple_shell.git"
```

- #### Compile the project using gcc:  
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o simple_shell
```

- #### Run the executable:  
```bash
./simple_shell
```

## Limitations

| Limitation | Description |
|------------|-------------|
| Command Substitution | The shell does not support command substitution (e.g., $(command) or `command`). |
| Redirection and Pipes | Redirection (e.g., >, >>, <) and pipes (e.g., ` |
| Background processes | Background execution (e.g., command &) is not supported. |
| Job Control | Job control features (such as stopping, resuming, or managing background processes with fg, bg, jobs, etc.) are not available. |
| Command History | The shell does not maintain a history of past commands. |
| Alias | There is no support for command aliases. |
| Limited path resolution | Path resolution is basic and does not support complex command paths (e.g., relative paths or absolute paths combined). |
| Limited Builtin CD command | This shell doesn't support the CD commands, only the option '~' and '-', and '..' (just one time for this one), and cd with no args works. |

This project is a simplified shell implementation with basic functionality, lacking some features found in more advanced shells.

## Files

| File          | Description                                            |
|---------------|--------------------------------------------------------|
| **main.h**        | Contains function prototypes and structure definitions.        |
| **simple_shell.c**     | Main implementation of the shell.                        |
| **start_forking.c**    | Functions to fork the process, handle signal and memory freeing.        |
| **function_helper.c** | Re-implemented functions from the string.h library.        |
| **man_1_simple_shell** | The Man Page content. Use man ./man_1_simple_shell.1 to view it.    |
| **get_the_pwd.c** | Functions that the actual PWD and Home directory. |
| **builtin_commands.c** | Main implementation of the command CD |

## MAN Page
![## MAN Page](https://image.noelshack.com/fichiers/2025/02/3/1736344350-man-page.png)

## Flowchart
![## Flowchart]()

# Authors  
## Vithushan Satkunanathan   &   Luca Gimenez
