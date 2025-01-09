# Flex Scanner

Create a scanner for your sample programs.
See the [example lab for Python](https://gitlab.cs.wallawalla.edu/cptr354/language-interpreter-lab-python).

## Language Scanner

Add the tokens needed to scan your sample code files.

In addition include the following:

* All the math operations (+,-,/,* etc.)
* All boolean expression (==,>,< etc.)
* All relational operators (not,and,or)
* ...

## Testing the Language Scanner

Write unit test for your sample code.
The sample program uses `utest.h` which is a simple c unit test framework.
The documentation can be found at <https://github.com/sheredom/utest.h>.

The `main.c` has been replaced with unit test code.
Your task is to create one unit test for each sample file.

When you submit the code to GitLab, the CI should automatically compile and run your test code.
To recieve full credit, the tests must pass when run through GitLab CI.

## Build Process

To build the `scanner.c` run the following **flex** command.

```sh
flex -o scanner.c scanner.flex
```

Then build the `main.c` and `scanner.c` using **gcc**.

```sh
gcc main_test.c scanner.c -o scanner_test.out
```

Then execute the test suite using `./scanner_test.out`.

```sh
./scanner_test.out
```

## Scanner Only

```sh
flex -o scanner.c scanner.flex
gcc main.c scanner.c -o scanner.out
./scanner.out
```


## Grading Rubric

The grading will be over the following categories.

Points      Description
----------- ------------------------------------
30 points   Tests for individual language tokens
10 points   Ability to scan — Hello world
20 points   Ability to scan — Quadratic equation
20 points   Ability to scan — Integer sorting
20 points   Passes continuous integration

## Turn In

Please submit the URL of your gitlab project to D2L's Brightspace with your report.
On gitlab update the `lab-3` folder to have your report and code snippets before the due date.
