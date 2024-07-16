# Coding Style

This *.md* includes the coding style of the Heleris framework.

## Names

***Always use a descriptive name!***

### '_t' typedef sufix 

The use of the '_t' suffix when using typedef is only applied to "pure" typedefs, that is, typedefs that are not followed by a definition of a structure such as struct, union or enum. Example of an use of the suffix:

```c
typedef uint8_t byte_t;
```

An example of where it cannot be used:

```c
typedef struct HRSString {
    char *_chars;
    size_t _chars_s;
} HRSString;
```

### Structures

Struct and enum use HRSPascalCase. In all, the name after the last *}* in the typedef case uses HRSPascalCase (without the prefix). Unions and Structs must have typedef, and enums must avoid typedef. Exemples:

```c
typedef struct HRSColor {
    uint8_t r; // The red of color
    uint8_t g; // The green of color
    uint8_t b; // The blue of color
    uint8_t a; // The alpha of color. 0 is transparent and 255 is opaque
} HRSColor;
```

### Variables identifiers

Variable identifiers use the camelCase pattern. Example:

```c
int foo = 25;
```

#### Suffixes and variable prefixes

Variable suffixes are intended to show what that variable has. Remembering that the suffixes here are just to help when reading and writing the code, ignoring extremely repetitive and often unnecessary things like the "prt" prefix in some styles.

- **s**:
     This suffix is normaly ussed in arrays. Exemple:

     ```c
         FILE files[20];
     ```
- **Buffer**:
     This suffix is only applied to buffers, and can also be used as "Buffers" if it is an array or list of buffers. Example:
     ```c
     int[5, 5] indexBuffers;
     ```
- **Index**:
     This suffix warns that it is an index variable; does not apply to for loops.

     ```c
         int fileIndex;
     ```
- **_c**:
     This sufix marks a variable as a count, and normaly this goes with a value variable (see next sufix). The default value for this is *size_t*, but for args of main function, the normal type is *int*. Exemple:

     ```c
         size_t file_c;
         FILE *file_v[];
     ```
- **_v**:
     This sufix marks a variable as a value, and normaly this goes with a count value (see previus sufix). Exemple:

     ```c
         size_t file_c;
         FILE *file_v[];
     ```
- **_s**:
     This sufix marks a variable as a size, and normaly this goes with a string. The default type is *size_t*. Exemple:

     ```c
         char *identifier;
         size_t identifier_s;
     ```
- **_**:
     This prefix is used just for blocking clonflits, like: types, struct, union and enum name or extension name conflicts (like the one from clangd that warns that the identifier "namespace" is defined in Objective-C++ since you are programming in C). These conflict considerations MUST not be case-sensitive and need to ignore *s* sufix. Exemple:
     
     ```c
         int isASCIIText(char *_chars) {
             //...
         }
     ```

### Pointers

The pointers two cases:

#### As a variable:

When used as a variable, use the '*' before the name, but attached. In this case is the variable, not the type, is the pointer. Example:

```c
void *stringLocation;
```

#### As a return or type:

When used as a return or type, the '*' is used after the type, but attached. Because in this case the return is the pointer. Example:

```c
HRSWindow* hrswin_create(/*...*/) {
     //...
}
```

### Function identifiers

camelCase is used for function identifiers.

When the function is "*linked*" to a structure, we use an abbreviation of it followed by an _ and the name, example:

```c
typedef struct SingleLinkedList {
     LinkedNode *head;
     LinkedNode *tail;
     size_t size;
} SingleLinkedList;

SingleLinkedList* sll_create() {
     //...
}
```

Function example:

```c
HRSColor hrsclr_create(uint8_t r, uint8_t g, uint8_t b) {
      //...
}
```

(Linked) Function exemple:

```c
void sll_free(SingleLinkedList *list) {
     //...
}
```

#### Function suffixes

Function suffixes are to indicate additional behavior on that function.

- **_op**:
     It means that this function has optional arguments, and that calling this function without this suffix will not need to specify these arguments. If there is more than one, we use a number to show the "index" of this function with optional arguments, such as "_op1", "_op2", etc. Example:

```c
double v2_getRotation(Vector2D vector) {
     //...
}

double v2_getRotation_op(Vector2D vector, Vector2D center) {
     //...
}
```
- **_np**:
     It means that this function is **non pure**, that is, it uses variables shared globally or locally. Avoid non-pure functions. Example:

```c
FILE[] filesToCompile;

void compileFiles_np() {
     //some use of the 'filesToCompile' array
}
```

### Constants

When we create a constant, SCREAMING_SNAKE_CASE is used; applies to macros, variables marked as const, or enums. Examples:

Const:

```c
const double PI = 3.141592653589793;
```

Macro:

```c
#define LINUX_EXECUTABLE_PREFIX .out
```

Enum:

```c
enum EHRSBool {
     FALSE = 0,
     TRUE = 1,
} EBool;
```

Note: **ALWAYS** after an enum value there is a ','.

In multi-line Macro definition, always use '\' in last instruction

## Syntax

These rules manage the way the code should be done!

### Separation of code blocks and instructions

When using '*{*', '*}*', mathematical operations, etc., each one must be separated; the initialization of a block of code or instruction must be on the same line. Example:

```c
int a = 3;
int b = 5;
int c = a + b;

void main() {

     int c = 2;

     printf("%d", c);
}
```

We always prefer a smaller function that does one function than a giant function that does multiple functions

### Functions

If the function has arguments, use the parentheses attached with the identifier of that function; the parameters must also be enclosed in parentheses; After the ',' a space is used. Example:

```c
HRSVector2 hrsvc2_create(float x, float y) {
     //...
}
```

If-else inversion is used when there is a lot of if nested in an function

### If-else, loops and switch-case

For all flow controllers, the '()' must be separated. Example:

```c
if (1 == 1) {
     return 10;
}
```

In the **case** of **switch**, the break always has the same indentation as the **case**, but the case code ALWAYS has to have a more advanced indentation. Example:

```c
switch (fooInt) {
     case 10:
         return "the user input is invalid";
     break;
}
```

Another notation is that the return should **NEVER** replace the break, that is, even if a return acts, the break at the end is necessary.

### White spaces

Always use whitespace to separate unrelated behaviors or blocks of instructions and code. Furthermore, it is recommended to separate the declaration of variables from the instructions. Example:

```c
int main() {

     int a = 25;

     printf("%d", a);

     return 0;
}
```

### Tabulation

Never use tabs, use 4 spaces instead.

The indentation is always 4 spaces. When we say that the indentation is larger, it means that it has a greater number of spaces; when we say that the indentation advances, it means that it increases 4 spaces; when we say that the indentation retracts or retreats, it means it decreases 4 spaces; When we say it is smaller, it means it has a smaller number of spaces

## Includes

Includes must always follow this pattern:

The first include will be that of that file, that is, if the file is called *window.c*, the first include will be of the header of that file, which whenever (again) is not an interface, will be the name of the file, replacing the extension by *.h*. Example:

```
window.c -> source code
window.h -> header
```

And in *window.c*:

```c
#include "window.h"
```

As a rule, headers are located in a '*header*' subfolder.

The next includes (separated by a blank line) are the local libs, always in alphabetical order. External libs must be located within a lib subfolder, and normally, one or more previous folders will be located if the project is separated into modules. Example:

```c
#include "headers/window.h"

#include "stb_image.h"
```

The next inclusions (separated again by a blank line) are the external libraries, i. e., libraries given at compilation time and accessed with '*<>' instead of '*""*', always in alphabetical order. Example:

```c
#include "headers/window.h"

#include "stb_image.h"

#include <GL/glew.h>
```

The next includes (separated again by a blank line) are the local files, always in alphabetical order. They are normally located in the "headers" subfolder, but if it is separated into modules, it may be necessary to use a subfolder. Example:

```c
#include "headers/window.h"

#include "stb_image.h"

#include <GL/glew.h>

#include "headers/error_codes.h"
```

The next includes (also separated by a blank line) are the standard C libs, always in alphabetical order. Example:

```c
#include "headers/window.h"

#include "../lib/stb_image.h"

#include <GL/glew.h>

#include "headers/error_codes.h"

#include <stdio.h>
```

- Generally utility files (like *bool.h*) should be located in the same location as the project initialization file (*main.c*, *window.c*), that is, in this folder there should be the utility files, the initialization file and all the project modules

### Definition of constants and structures

Structures, macros for global or multi-functions use within the file (#define) and typedef must be declared in their header (.h) file, rather than in the source code (.c) directly.

Note that we prefer to use macros rather than generic functions that never change or that change one word or another, like variable types. Example:

```c
#define BYTE_1_VERIFY_UTF_8_SEQUENCE if ((charSequence[*index + 1] & utf_8SequenceByteVerifier) != utf_8SequenceByte) { \
             perror("second byte of a rune is incorrect!"); \
             exit(4); \
         } \
```

The definition of these structures, macros and typedef generally follows the following order:

```
enums

"pure" typedef

const

union
struct

"pure" struct linked typedef 

macros

declaration of structure blocks
```

When a macro is used only within a function, that macro must be located within that block, or above, and not in the header.
