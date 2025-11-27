# Notes

This document is a notepad.

## Resources

- [Bare Bones Tutorial](https://wiki.osdev.org/Bare_Bones)
- [Meaty Skeleton](https://wiki.osdev.org/Meaty_Skeleton)

## GCC Cross-Compiler

The assignment requires the following options:

- `-fno-builtin`: Disables built-ins. Don’t recognize built-in functions that do not begin with `__builtin_` as prefix
- `-fno-exceptions`: Disables exception handling ([reading for later](https://mmomtchev.medium.com/the-true-cost-of-c-exceptions-7be7614b5d84)).
- `-fno-stack-protector`: Disables the [Stack Smashing Protector](https://wiki.osdev.org/Stack_Smashing_Protector).
- `-fno-rtti`: Disables [RTTI (RunTime Type Identification)](https://pvs-studio.com/en/blog/posts/cpp/0998/), a mechanism that allows to determine the data type of a variable at runtime (used with the identification features `dynamic_cast` and `typeid`).
- `-nostdlib`: Do not use the standard system startup files or libraries when linking.
- `-nodefaultlibs`: Do not use the standard system libraries when linking.

Resources:

- [Why do I need a Cross Compiler?](https://wiki.osdev.org/Why_do_I_need_a_Cross_Compiler%3F)
- [GCC Cross-Compiler Tutorial](https://wiki.osdev.org/GCC_Cross-Compiler)
