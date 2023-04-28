# CIS330: Lab4

Structures, linking, libraries.

# Description

In this lab you will make your own error-reporting library.
While a quick `fprintf(stderr, "...");` may be fine for debugging your own code,
most larger projects define their own error-reporting systems which allow
flexible display and / or logging of errors encounter while the code runs.
Type `$ dmesg` on your linux box for an example of how the linux operating system
reports and logs various errors and other runtime messages.

In this lab we will:
  1. implement a simple error reporting library which dumps errors to an arbitrary `FILE *` with custom formatting;
  2. package our error system in static and dynamic libraries;
  3. maintain a Makefile which automates the commands needed to compile the libraries and link a test executable.

A main function to test your library is already implemented in the file `src/lab4.c`.

# Instructions

1. Type `make` and run the resulting `lab4' executable to make sure everything works on your development system.
The initial implementation contains empty shells for all error-reporting functions so only the main output from lab4.c is displayed.

2. Explore `Makefile`, `src/`, `include/`, and the generated directories `obj/` and `lib/` to see what's going on.

3. Finish implementation of the error reporting system in `src/ohno.c`.
The formatting of how errors are presented is up to you but you must print your messages on the FILE * passed into `ohno_init()` (hint: use `fprintf`).
See the comments in `src/ohno.c` for more details.

4. Remake and test `lab4` with your error reporting implementation.
Try things like having no arguments (e.g. `$ ./lab4`),
single arguments (e.g. `$ ./lab4 100`),
or a list of the same number as the argument (e.g. `$ ./lab4 100 100 100 100`).
You should get errors reported through your custom error functions
(e.g. ``Oh No! A fatal error occured: there's no arguments!``).

5. Edit `Makefile` to generate a dynamically-linked executable called `lab4_dyn`.
Note that you will also need to make a dynamic library `liblab4.so` from the object files
and to modify the runtime environment variable `LD_LIBRARY_PATH` before running `lab4_dyn`.

Note:
You can make a shared library with gcc by adding the `-shared` flag and setting the output to be a `.so` file.
Also, object files included in a shared library must be compiled as `position independent code` which you can generate by adding `-fPIC` to your
CFLAGS.

For example `$ gcc -shared -o libfoo.so foo.o bar.o` will create a shared library called `libfoo.so` with definitions from `foo.o` and `bar.o`.
Read a full example here: https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/create-libraries/index

Note also that gcc links executables to shared libraries by default if a shared library is found (unless the -static flag is given).
Use `readelf -d <your executable name>` to get a summary of what shared libraries a particular executable requires.

