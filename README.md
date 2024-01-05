# Algorithms in C

Some algorithms built with C standard library, without assistance of third-party libraries.

## What is needed to run?

You gonna need a C/C++ compiler and CMake installed to compile and link the entire project. 

## How to run?
To build this project just go to the root of application and run:

```bash
./build.sh
```

A output folder will be created in root with folders below:

- **bin** : Executables files directory;
- **lib** : Static libraries directory; 
- **external** : Third-party static libraries (just for tests);

To test the project use:

```bash
./test.sh
```
<!---
To run:

```bash
./run.sh <algorithm_name>
```

The name of all algorithms are mentioned in the next section.
-->



## Algorithms

- **LinkedList** : Doubly Linked List with methods to get, pop and push items.
- **HeapSort** : Sort algorithm using heap structure.
- **PriorityQueue** : Ensures the first item of array have the higher weight/importance. It have methods to add and extract.
- **HashMap** : Simple hashmap implemented with linked list to add a tuple with key and value and get the value based on key.
- **Vector** : Array with dynamic size, based in C++ class *Vector*.
- **InfinityArray**: Javascript like array.
