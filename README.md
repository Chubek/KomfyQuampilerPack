# KQP: The Komfy Quampiler Pack
#### Compiler Design and Implementation in Terms of Micro-DSLs


## Mission Statement

The 'Komfy Quampiler Pack' is a general toolchain, similar to GCC. It approaches compiler design in terms of extremely targeted 'micro-DSL' languages.

The idea for using Domain-Specific Languages as a meta-language for compiler design is nothing new. Most Compiler-Compilers of the old, Lex/Flex, YACC/BISON, ANTRL, PEG/LEG, these are all Compiler-Compilers that rely on DSLs, be it regular expressions, Context-Free Grammar representations such as EBNF, Parser Expression Grammars, etc. Also, let's not forget that tools like LLVM rely on DSLs for tasks such as Intermediate Representation.

I (and if you so desire, *you*, therefore, *us*) plan on taking this concept on step further. KQP will first define highly-specialized micro-meta languages for each task, or groups of tasks, and then use these DSLs to implement the toolchain. This toolchain shall include:

* A compiler frontend (lexing, parsing, IR generation)
* A compiler backend (optimization, assembly generation)
* An assembler (for as many targets that we can)
* A linker (for both ELF and PE, maybe freestanding)

The aim is to be versatile. In many ways, KQP is more similar to LLVM that GCC, except in KQP, you can define your own IR.

## The Plan

I am early in development. I have so far managed to implement several data structures that are needed in plain-old ISO CPP, as header files. You can find them in `komfyBasicIncludes`. This folder, and the `komfySMX` (The Komfy Super Macro 10 DSL) are going to be the only directories which will be in pure ISO C. The aim is, to compile KSMX and then KSMX will be the 'base DSL' for all the other DSLs, and from then on, the toolchain.

## Further Reading and Influential Books

KQP is highly influenced by this book:

* `Ralf Lämmel, Software Languages: Syntax, Semantics,
and Metaprogramming, Springer, 2018`

All the algorithms are taken from:

* `Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein, Introduction to Algorithms, 4th ed, MIT Press, 2022`

I will add all the other books very soon.


## Contact Me

Email: chubakbidpaa@gmail.com
Discord: .chubak

## KQP Elsewhere:

* Reddit: `reddit.com/r/KomfyQuampilerPack`

## Patrons

I owe an incredible debt to Dr. Kevin Moran for funding KQP. If you wish to bankroll KQP (when it's viable that is, I'm writing this as some sort of 'The Secret' self-assertion) please visit my profile, or contact me.