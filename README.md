# Junebug-2

## Standards
 - Curly brackets on same line
 - Do not use `using namespace`
 - Try not to use arrays unless necessary
 - Always annotate functions, structs, and classes that you create or modify with the `/**...*/` annotation type
 - Destructors should only be used when necessary

##Variable Prefixes
| Prefix | Name          | Description                  | Used in |
|--------|---------------|------------------------------|---------|
| m      | Member        | Member variable of a class   | Classes |
| s      | Struct member | Member variable of a struct  | Structs |
| u      | Union member  | Member variable of a union   | Unions  |
| p      | Pointer       | Variable is a pointer        | Any     |
| r      | Reference     | | Any     |
| C      | Const         | | Classes, structs amd unions  |
| M      | Mutable       | | Classes, structs amd unions  |
| g      | Global        | This should not be used ever | Never   |
