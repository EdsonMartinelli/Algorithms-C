# Algorithms in C

Some algorithms built with C standard library, without assistance of third-party libraries.

## ⚔️ What I need to run?

You gonna need a C/C++ compiler and CMake installed to compile and link the entire project. 

## 🚀 How to run it?
To build this project just go to the root of application and run:

```bash
./build.sh
```

A output folder will be created in root with folders below:

- **bin** : Executable files directory;
- **lib** : Static libraries directory; 
- **external** : Third-party static libraries (just for tests);
- **test** : Executable files of tests;

To test the project use:

```bash
./test.sh
```

To run examples presents in the *src/executables* folder, after build, execute:

```bash
./output/bin/<example_name>.out
```

## 💻 Algorithms

- **Linked List** : Doubly Linked List with methods to get, pop and push items.
- **HeapSort** : Sort algorithm using heap structure.
- **Priority Queue** : Ensures the first item of array have the higher weight/importance. It have methods to add and extract.
- **HashMap** : Simple hashmap implemented with linked list to add a tuple with key and value and get the value based on key.
- **Vector** : Array with dynamic size, based in C++ class *Vector*.
- **Infinity Array**: Javascript like array.
