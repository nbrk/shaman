# Extremely simple C89 OpenGL shader loading/management library
Shaman is a small, **C89 **, **easy to use** OpenGL shader program loading library.

## Description
Upon successful shader program assembly Shaman stores the OpenGL program object in 
an internal two-dimensional static array, thus allowing you to easily retrieve the
object later at any point in time via a pair of numbers. Shaman calls these numbers
"the table number" and "the row number" and really doesn't care about what they mean.
The only requirement is that they are a valid index into the internal static array,
which constists of 16 "tables" with 16 "rows" in each.

## Usage
Shaman has extemely simple API that constists only of handful of functions:

``` c
int shaman_just_assemble_program(GLuint* out_prog,
                                 const char* vert_path,
                                 const char* frag_path);
                                        
int shaman_store_program(int table,
                         int row,
                         const char* vert_path,
                         const char* frag_path);
                                
int shaman_access_program(int table, int row, bool useit, GLuint* prog);

int shaman_discard_program(int table, int row);

```

All functions return status/error codes with `SHAMAN_OK` meaning a success.

You can use only `shaman_just_assemble_program()` if you don't need any "table" & "row" stuff.

Function `shaman_store_program()` assembles and stores the program object at location `[table][row]`.

Function `shaman_access_program()` is used to retreive the program object from a location.

The `shaman_discard_program()` can be used to delete (as in `glDeleteProgram()`) one or more
programs, with table/row of -1 resulting in "discard all of it". 

That's it. Plaese see the source code for further details.
