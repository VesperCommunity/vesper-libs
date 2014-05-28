
# Coding style

## Naming conventions

C code in `vesper-libs` should use `snake_case` names for variables and
functions.
C++ code should use upper-case `CamelCase` names for classes and
structs and lower-case `camelCase` for variables and functions.
C and C++ code should use upper-case `SNAKE_CASE` for constants and macros.

## Filenames

C code files should have a `snake_case` filename with `*.h` or `*.c` extension.
C++ code files should have an upper-case `CamelCase` filename with `*.hpp` or
`*.cpp` extension.

## Indent style

Code in `vesper-libs` should use [One True Brace Style (1TBS)][1TBS_link].

[1TBS_link]:
http://en.wikipedia.org/wiki/Indent_style#Variant:_1TBS

## Miscellaneous

Code in `vesper-libs` should furthermore conform to the following rules:

* Lines should not be longer than 80 characters.
* Pointer variables have the asterisk `*` symbol attached to their name.
* Keywords like `if`, `for`, `while`, `switch` are followed by a space.
* Binary operators excluding `>>` and `<<` are framed by spaces.
* Unary operators and increment or decrement operators are not framed by spaces.
* Inner elements in round brackets are not framed by spaces.
* Nested preprocessor commands (starting with hash `#` sign) use current code
  indentation and are indented by 2 spaces per level.
* Code inside preprocessor commands is indented by 4 spaces.
* `#endif` lines should include matching `#if` condition as a comment.
* Curly brackets closing a namespace should include namespace as a comment.
* Namespace do not affect indentation at all.
* `switch` statements: `case` is indented by 4 spaces, the code is indented by 8
  spaces, `break` is indented by 6 spaces.
* Keywords like `public`, `protected`, `private` are indented by 2 spaces.
* All code should use `/* C-style */` comments.
* Multi-line comments begin and end with an empty line and are prefixed by `*`.
* Header files should be guarded by `HEADER_H_INCLUDED` or `HEADER_HPP_INCLUDED`
  preprocessor commands, which do not affect indentation at all.

## Example

### C code

`output_string.c`:

```C
#if defined _WIN32
  #include <windows.h>
#endif /* defined _WIN32 */

/**
 * Output information about input number.
 * Returns 0 if input number is even, else 1.
 */
int output_string(int *interesting_number)
{
    if (*interesting_number > 100) {
        puts("Big number.");
    } else {
        puts("Small number.");
    }

    int x = *interesting_number % 2;
    switch (x) {
        case 0:
            puts("Even number.");
          break;

        case 1:
            puts("Odd number.");
          break;
    }

    #if defined PRINT_GREETING
        puts("Hello, world.");
    #endif /* defined PRINT_GREETING */

    return x;
}
```

### C++ code

`NumberOperator.hpp`:

```C++
#if !defined NUMBEROPERATOR_HPP_INCLUDED
#define NUMBEROPERATOR_HPP_INCLUDED

#include <iostream>

namespace NumberWorks {

class NumberOperator {
  private:
    int anyNumber;

  public:
    NumberOperator(int anyNumber) : anyNumber(anyNumber)
    {
        /* do nothing */
    }

    /**
     * Print the number and return.
     */
    void printInformation()
    {
        std::cout<<"Number: "<<anyNumber<<std::endl;
    }

};

} /* namespace NumberWorks */

#endif /* !defined NUMBEROPERATOR_HPP_INCLUDED */
```
