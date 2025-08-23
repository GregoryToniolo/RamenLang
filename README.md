
# RamenLang

A very shitty and probably not memory safe transpiler menat for sceintific and mathematical applications that translates my custom syntax to c++

## FAQ

#### Why do my arrays and templates have weird spacing?
They just do. be happy that your code even manages to compile

#### Why do my multiplications have weird spacing
Same as before if it works it works. if you have an issue shoot me an email.


## Dependencies

make, a c++ compiler

## Installation
Linux / wsl

clang
```bash
  git clone https://github.com/GregoryToniolo/RamenLang && cd RamenLang && clang++ main.cpp -std=c++20 -o ramen && make build && sudo cp ramen /usr/bin 
```
(if using gcc go into Makefile and change build to use gcc instead of clang++ after cloning)
gcc
```bash
  git clone https://github.com/GregoryToniolo/RamenLang && cd RamenLang && gcc main.cpp -std=c++20 -o ramen && make build && sudo cp ramen /usr/bin 
```
## Usage

clang
```bash
    ramen filename 
    clang++ output.cpp -std=c++20 -o output
```
gcc
```bash
    ramen filename
    gcc output.cpp -std=c++20 -o output
```
## Modifying the language

add your modifications to parser.hpp and tokenizer.hpp

The order of the keywords is very important!

## Language syntax

ramen language syntax can be found in ramenKeywords in parser.hpp with c++ equivalents in cppKeywords
i have also provided an example in test.ramen
