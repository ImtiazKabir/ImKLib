# Imtiaz Kabir's ANSI C Codebase (ImKLib)

Imklib is the improved version of imlib, an OOP based take on ANSI C. It works by creating fat pointers which contain important methods of object like constructor, destructor, equality, clone, hash etc. Inheritance is supported by having parent the first member of the structure and interface implementation works with creating a structure with function pointers that is passed to the object to fill up.

## How does ImKLib differ from [imlib](https://github.com/ImtiazKabir/imlib)?

imlib was my first try on this approach. Like any first, it is very dear to me but it is not as organized as I want it to be. In some places, the dependency spaghetti is beyond description. ImKLib aims to fix that. It is mostly imlib but it brings some new ideto the table like stack based allocation and smart pointers.

## Is it production ready?

**Not really.** It is a hobby project. But a mini express like http server has been created with imlib before (check out [Fordo](https://github.com/ImtiazKabir/Fordo)).

## How to build

```bash
cd build
cmake ..
make
```

This will build the library with the examples. The library builds as a static library inside `build/lib` folder. Copy the include and lib directory to your project. Have fun!

## Run examples

After building, you can just

```bash
cd build/examples
./assert
```
