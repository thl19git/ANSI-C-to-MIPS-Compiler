Deliverable 3: A compiler for the C language
============================================

Your program should read C source code from a file, and write MIPS assembly to another file.

Program build and execution
---------------------------

Your program should be built by running the following command in the top-level directory of your repo:

    make bin/c_compiler

The compilation function is invoked using the flag `-S`, with the source file and output file specified on the command line:

    bin/c_compiler -S [source-file.c] -o [dest-file.s]
    
You can assume that the command-line arguments will always be in this order, and that there will be no spaces in source or destination paths.

Input 
-----

The input file will be pre-processed [ANSI C](https://en.wikipedia.org/wiki/ANSI_C), also called C90 or C89. It's what's generally thought of as "classic" or "normal" C, but not the _really_ old one without function prototypes (you may never have come across that). C90 is still often used in embedded systems, and pretty much the entire Linux kernel is in C90.

You've mainly been taught C++, but you're probably aware of C as a subset of C++ without classes, which is a good mental model. Your programs (lexer, parser and compiler) will never be given code that has different parsing or execution semantics under C and C++ (so, for example, I won't give you code that uses `class` as an identifier).

The source code will not contain any compiler-specific or platform-specific extensions. If you pre-process a typical program (see later), you'll see many things such as `__attribute__` or `__declspec` coming from the system headers. You will not need to deal with any of these.

The test inputs will be a set of files of increasing complexity and variety. The test inputs will not have syntax errors or other programming errors, so your code does not need to handle these gracefully.

Here is a list of basic features that you might like to implement first.

1. a file containing just a single function with no arguments - done
2. variables of `int` type - done
3. local variables - done
4. arithmetic and logical expressions - nearly finished
5. if-then-else statements - done
6. while loops - done

Here is a list of intermediate features that you might like to implement once the basic features are working.

7. files containing multiple functions that call each other - done
8. functions that take up to four parameters - done
9. for loops - done
10. arrays declared globally (i.e. outside of any function in your file) - maybe try this if we have time? probably not
11. arrays declared locally (i.e. inside a function) - done
12. reading and writing elements of an array - done
13. recursive function calls - done
14. the `enum` keyword - TODO
15. `switch` statements - TODO
16. the `break` and `continue` keywords - done

Here is a list of more advanced features like you might like to implement once the basic and intermediate features are working.

17. variables of `double`, `float`, `char`, `unsigned`, structs, and pointer types - probably avoid
18. calling externally-defined functions (i.e. the file being compiled declares a function, but its definition is provided in a different file that is linked in later on) - done
19. functions that take more than four parameters - done
20. mutually recursive function calls - done
21. locally scoped variable declarations (e.g. a variable that is declared inside the body of a while loop, such as `while(...) { int x = ...; ... }`. - done except repeated names both in scope
22. the `typedef` keyword - maybe do?
23. the `sizeof(...)` function (which takes either a type or a variable) - maybe do?
24. taking the address of a variable using the `&` operator - probably not
25. dereferencing a pointer-variable using the `*` operator - probably not
26. pointer arithmetic - probably not
27. character literals, including escape sequences like `\n` - probably not
28. strings (as NULL-terminated character arrays) - probably not
29. declaration and use of structs - probably not

Your compiler will be assessed using test inputs that exercise the above features. No feature not listed above will be tested. 
Here is a (partial) list of features that will not be tested.

* multithreading
* the `goto` keyword
* macros and other preprocessing directives
* the comma operator (for sequencing within expressions)
* the [old K&R style of declaring functions](https://stackoverflow.com/a/18820829)
* union types
* variable-length arrays
* the `const` keyword

All test inputs will be valid; that is, you can assume the absence of programmer errors like syntax faults, type mismatches, and array out-of-bounds errors. The entire compilation and testing process (including compilation, assembly, linking, and MIPS simulation) is expected to complete within ten seconds per program (which should be plenty of time!), and is expected not to use an inordinate amount of memory or disk space. There is no requirement for the generated assembly to be optimised in any way -- the only requirement is that it produces the correct answer.

The [compiler_tests](compiler_tests) contains a large number of example inputs, divided into various categories, that you might like to use as testcases. Your compiler will be assessed on these "seen" inputs together with a further set of "unseen" inputs that are of a similar form. It is worth emphasising that it is not expected that many compilers will correctly compile all of the "seen" inputs (let alone the "unseen" ones!). You are encouraged to focus on compiling the "basic" features (as listed above) first, before moving on to more advanced features if you have time.

Output Format
-------------

The output format should be MIPS1 assembly code.

It should be possible to assemble and link this code against a C run-time, and have it execute correctly on a MIPS processor as emulated by `qemu-mips`.

For instance, suppose I have a file called `test_program.c` that contains:

    int f() { return 10; }
    
and another file called `test_program_driver.c` that contains:

    int f();
    int main() { return !( 10 == f() ); }
    
I run the compiler on the test program, like so:

    bin/c_compiler -S test_program.c -o test_program.s
    
I then use GCC to assemble the generated assembly program (`test_program.s`), like so:

    mips-linux-gnu-gcc -mfp32 -o test_program.o -c test_program.s
    
I then use GCC to link the generated object file (`test_program.o`) with the driver program (`test_program_driver.c`), to produce an executable (`test_program`), like so:

    mips-linux-gnu-gcc -mfp32 -static -o test_program test_program.o test_program_driver.c

I then use QEMU to simulate the executable on MIPS, like so:

    qemu-mips test_program
    
This command should produce the exit code `0`.
