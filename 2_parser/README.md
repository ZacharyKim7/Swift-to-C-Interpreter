# Bison Parser With Tests

Create a scanner for your sample programs with tests.
The tests should include basic statements and the sample files for your language.
See the [example lab for Python](https://gitlab.cs.wallawalla.edu/cptr354/language-interpreter-lab-python).

## Build Process

To build the `scanner.c` run the following **flex** command.

```sh
flex -o scanner.c scanner.flex
```

The parser is built using **bison**.
Note this command also builds the `token.h`.

```sh
bison --defines=token.h --output=parser.c -v parser.bison
```

THe `-v` flag will create a `parser.output` which represents the grammar in text form.


### Running the Parser

Then build the `main.c`, `parcer.c` and `scanner.c` using **gcc**.
Note that you may get a few warnings that can be ignored.

```sh
gcc main.c scanner.c  parser.c -o parser.out
```

Then execute the test suite using `./parser.out` and pass in the input from your sample program.
For example here is a command for `samples/program.c`

```sh
./parser.out < samples/program.c
```


### Testing the Parser

Then build the `main_test.c`, `parcer.c` and `scanner.c` using **gcc**.
Note that you may get a few warnings that can be ignored.

```sh
gcc main_test.c scanner.c  parser.c -o parser_test.out
```

Then execute the test suite using `./parser_test.out`.

```sh
./parser_test.out
```


### Using Make

Alternatively you can use the supplied make file.

* Build main program - `make`
* Build test program - `make test`
* Clean up build files - `make clean`


## Tests

* Write test for various statements in your language 
  * assignment
  * print
  * mathmatical expressions
  * boolean expressions
  * branching
  * looping
* Write a test for each sample test file.
  * Hello World!
  * Quadratic
  * Sorting


## Grading Rubric

The grading will be over the following categories.

Points      Description
----------- ------------------------------------
60 points   Ability to parse — Six different language statements
10 points   Ability to parse — Hello world
10 points   Ability to parse — Quadratic equation
10 points   Ability to parse — Integer sorting
10 points   Report formatting and readability


## Turn In

Please submit the URL of your gitlab project to D2L's Brightspace with your report.
On gitlab update the `lab-4` folder to have your report and code snippets before the due date.
