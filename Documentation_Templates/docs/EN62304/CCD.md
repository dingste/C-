# Coding Conventions

Code, like written language, may be very expressive and diverse. While this enriches cultural aspects in human society, in the formal context of this project it is an obstacle if the code does not follow predefined conventions. Surprises while reading the code have to be avoided at all costs as it may cause misunderstandings which themselves may cause hazards in the later product. Therefore, in the following we define the coding conventions for this project.

## Basic principles
Overall we agree with [Google's C++ Style Guide](https://google.github.io/styleguide/cppguide.html) and [Clean Code by Robert C. Martin ](https://gist.github.com/wojteklu/73c6914cc446146b8b533c0988cf8d29). The items which still need to be defined or deviate from the aforementioned sources are listed in the following.


## Naming
Naming items in the code properly is one of the biggest challenges in writing good code. In the following the conventions used in this project are listed.

{%
   include-markdown "../Description/ComponentNaming.md"
%}

{%
   include-markdown "../Description/FunctionNaming.md"
%}

{%
   include-markdown "../Description/VariableAndTypeNaming.md"
%}

## Preprocessor
Preprocessor defines (i.e. "#define" command) shall be avoided. Constant values shall be collected in the aforementioned global constant structs, if necessary. Also the use of the "#warning" command is prohibited. All warnings are treated as errors.

