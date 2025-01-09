# Bison Interpreter

Create an interpreter for your sample programs.
See the [example lab for Python](https://gitlab.cs.wallawalla.edu/cptr354/language-interpreter-lab-python).

In this lab, you will focus on basic operations that support your sample code.

* Arithmetic operations
  * add
  * subtract
  * multiple
  * divide
* Functions (but implemented directly in the language)
  * Printing
  * Square root
* Variable for numbers
* Variable for lists (or arrays)
* Branching statements
* Looping statements

Notice you will find a new file `expr.c`.
The file is used to implement the parser rule.
Inside these functions, you will create the runtime code that is the interpreter.


## Build Process

The process is similar to prior labs.
To build the `scanner.c` run the following **flex** command.

```sh
flex -o scanner.c scanner.flex
```

The parser is built using **bison**.
Note this command also builds the `token.h`.

```sh
bison --defines=token.h --output=parser.c parser.bison
```

Then build the `main.c`, `expr.c`, `parcer.c` and `scanner.c` using **gcc**.
Note that you may get a few warnings that can be ignored.

```sh
gcc *.c -o interpreter.out
```

Then execute the test suite using `./interpreter.out` and pass in the input from your sample program.
For example here is a command for `samples/program.c`

```sh
./interpreter.out < samples/program.c
```

Single line command:

```sh
flex -o scanner.c scanner.flex && \
bison --defines=token.h --output=parser.c parser.bison && \
gcc *.c -o interpreter.out && ./interpreter.out < samples/program.c
```

## Building with Make

To simplify the process a Makefile has been supplied.

```sh
make && ./interpreter.out < samples/program.c
```

To remove the build files, use make clean.

```sh
make clean
```


## Assignment Steps

1. Start by confirming these commands work for the sample code provided. 

1. Next copy over your `scanner.flex`,  `parser.bison` and sample programs from lab 5.

1. Start working on your bison `parser.bison` and `expr.c` files to implement the interpreter part of your parser.


## Grading Rubric

The grading will be over the following categories.

Points      Description
----------- ------------------------------------
30 points   Ability to interpret — Hello world
30 points   Ability to interpret — Quadratic equation
30 points   Ability to interpret — Arithmetic operations
30 points   Ability to interpret — Integer Sort example
20 points   Ability to interpret — Looping operations
20 points   Ability to interpret — Branching operations
20 points   Ability to interpret — Array variables
10 points   Report formatting and readability


## Turn In

Please submit the URL of your GitLab project to D2L's Brightspace with your report.
On GitLab update the `lab-5` folder to have your report and code snippets before the due date.
