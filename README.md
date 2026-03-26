*This project has been created as part of the 42 curriculum by seramaro*

<div style="text-align: center;">
    <img src="https://media4.giphy.com/media/v1.Y2lkPTc5MGI3NjExdmZpbjY1dnIxZXhyaG9kYnhnenpvaTRieXUwazJ2cnUzM2x6eDRwdiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/lptIayuGHV9Utu3iTv/giphy.gif" alt="Description" width="" height="300">
    <br>
    <b style="font-size: 100px;">ft_printf</b>
    <p style="font-size: 20px;">Because ft_putnbr() and ft_putstr() aren’t enough</p>
</div>

## Description

`ft_printf` is a custom re-implementation of the standard C library function `printf`, built from scratch without using `<stdio.h>`. The goal of this project is to deeply understand how variadic functions work in C, how format strings are parsed, and how different data types can be formatted and written to standard output using only low-level system calls.

This implementation supports the following conversion specifiers:

| Specifier | Description |
|-----------|-------------|
| `%c` | Prints a single character |
| `%s` | Prints a null-terminated string |
| `%d` | Prints a signed decimal integer |
| `%i` | Prints a signed decimal integer |
| `%u` | Prints an unsigned decimal integer |
| `%x` | Prints an unsigned integer in lowercase hexadecimal |
| `%X` | Prints an unsigned integer in uppercase hexadecimal |
| `%p` | Prints a pointer address in hexadecimal (prefixed with `0x`) |
| `%%` | Prints a literal percent sign |

The function returns the total number of characters printed, mirroring the behavior of the original `printf`.

---

## Algorithm

### Overview

The core of `ft_printf` is a **linear format-string parser** combined with a **recursive base-conversion algorithm** for numeric output. Here is a breakdown of each component and the reasoning behind the design choices:

### 1. Format String Parsing (Linear Scan)

The main `ft_printf` function iterates through the format string character by character using a simple `while` loop with an index `i`. This approach is:

- **Simple and predictable**: There are no complex state machines or look-ahead buffers needed for the mandatory part of the subject.
- **Efficient**: Each character is visited exactly once, giving O(n) time complexity relative to the length of the format string.

When a `%` is encountered, `i` is incremented to peek at the next character (the specifier). The specifier is then matched using a chain of `if/else if` conditions, each dispatching to the appropriate helper function.

### 2. Variadic Argument Handling (`stdarg.h`)

The C standard library macros `va_list`, `va_start`, `va_arg`, and `va_end` are used to access the variable-length argument list. Each time a format specifier is matched, the corresponding argument is consumed from the list via `va_arg`. This is the standard and portable way to implement variadic functions in C.

### 3. Number-to-String Conversion (Recursive Base Conversion — `ft_putnbr`)

Numeric output (`%d`, `%i`, `%u`, `%x`, `%X`, `%p`) is handled by a single, unified recursive function:

```c
size_t ft_putnbr(long long int n, long long int base, char *bbbase);
```

This function converts a number to any base (10 for decimal, 16 for hexadecimal) by:

1. Handling the sign for negative numbers.
2. Recursively dividing the number by the base until the remainder is a single digit.
3. Writing digits in the correct (most-significant first) order as the call stack unwinds.

**Why recursion?**
Recursive base conversion is an elegant and concise solution for a mandatory project where the emphasis is on correctness and code clarity. The digits of a number naturally appear in reverse order when computed with modulo, and recursion reverses this without needing an intermediate buffer or a reverse loop. The call depth is bounded by `log_base(n)`, which is at most ~20 levels for a 64-bit integer in base 10, making stack overflow a non-issue in practice.

**Why a unified function with a `base` parameter?**
Using one function for all numeric types (signed/unsigned decimal and hexadecimal) avoids code duplication. The `bbbase` character array (`"0123456789abcdef"` or `"0123456789ABCDEF"`) also handles the lowercase/uppercase distinction for hex output without branching.

### 4. Output via `write(2)`

All output is produced using the POSIX `write` system call rather than `putchar` or `fwrite`. This avoids any dependency on `<stdio.h>` buffering and keeps the implementation fully self-contained, as required by the 42 norm.

### 5. Character Count Tracking

Every helper function returns the number of characters it writes. The main loop accumulates these values into a `count` variable, which is returned at the end, faithfully mirroring the `printf` contract.

---

## Instructions

### Prerequisites

- A Unix-based system (Linux or macOS)
- A C compiler (`cc` / `gcc` / `clang`)
- `make`

### Compilation

Navigate to the `ft_printf` folder and run:

```bash
make
```

This will compile all source files and produce a static library archive:

```
libprintf.a
```

### Linking with Your Project

To use `ft_printf` in your own project, include the header and link against the archive:

```bash
cc your_file.c -L. -lprintf -I. -o your_program
```

In your C source file:

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello, %s! You are %d years old.\n", "world", 42);
    return (0);
}
```

### Makefile Targets

| Target | Action |
|--------|--------|
| `make` / `make all` | Compile and build `libprintf.a` |
| `make clean` | Remove object files (`.o`) |
| `make fclean` | Remove object files and `libprintf.a` |
| `make re` | Full recompilation (`fclean` + `all`) |

---

## Usage Examples

```c
ft_printf("Char: %c\n", 'A');
// Output: Char: A

ft_printf("String: %s\n", "hello");
// Output: String: hello

ft_printf("Integer: %d\n", -42);
// Output: Integer: -42

ft_printf("Unsigned: %u\n", 4294967295u);
// Output: Unsigned: 4294967295

ft_printf("Hex lower: %x\n", 255);
// Output: Hex lower: ff

ft_printf("Hex upper: %X\n", 255);
// Output: Hex upper: FF

ft_printf("Pointer: %p\n", (void *)0x1234);
// Output: Pointer: 0x1234

ft_printf("Percent: 100%%\n");
// Output: Percent: 100%
```

---

## File Structure

```
ft_printf/
├── ft_printf.h     # Header file — function prototypes and includes
├── ft_printf.c     # Core parsing loop and specifier dispatch
├── ft_putnbr.c     # Recursive base-conversion for numeric output
├── ft_putstr.c     # String and character output helpers
└── Makefile        # Build rules
```

---

## Resources

### Documentation & References

- [C Standard — `printf` specification (cppreference.com)](https://en.cppreference.com/w/c/io/fprintf)
- [Linux `man` page — `printf(3)`](https://man7.org/linux/man-pages/man3/printf.3.html)
- [Linux `man` page — `stdarg(3)` (variadic functions)](https://man7.org/linux/man-pages/man3/stdarg.3.html)
- [Linux `man` page — `write(2)`](https://man7.org/linux/man-pages/man2/write.2.html)
- [GNU C Library documentation — Formatted Output](https://www.gnu.org/software/libc/manual/html_node/Formatted-Output.html)

### Tutorials & Articles

- [Variadic Functions in C — GeeksforGeeks](https://www.geeksforgeeks.org/variadic-functions-in-c/)
- [How `printf` works internally — CS:APP blog](https://www.cs.cmu.edu/afs/cs/academic/class/15213-f19/www/recitations/)
- [Base conversion explained — Khan Academy](https://www.khanacademy.org/math/algebra-home/alg-intro-to-algebra/algebra-alternate-number-bases/a/hexadecimal-to-decimal)

### AI Usage

Claude AI was used in the following ways during this project:

- **README generation**: Copilot assisted in drafting the structure and content of this README file, including section layout, algorithm explanations, and usage examples.
- **No code was generated by AI**: All `.c` and `.h` files were written manually, and AIs were not used to produce or complete any source code.

&nbsp;

<div style="text-align: center;">
    <img src="https://media4.giphy.com/media/v1.Y2lkPTc5MGI3NjExY2U2ajI5ZTNhdmc5M2RleTVmZjMyNzY1M2Vlc3BidnNsd21zdHBoeSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/TKL99l61UBNnnQSx4o/giphy.gif" alt="Description" width="" height="300">
</div>

<div style="text-align: center;">
  <b style="font-size: 120px;">Thank You!</b>
</div>
