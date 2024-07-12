# Programming Project: Implementing the List Abstract Data Type

**Subject: Programação I (DIM0176)**

**Students**

* Igor Marques de Lima
* Vitor Emanuel Rodrigues de Alencar


## 1. About Project
The project consists of implementing our own version of a Vector container to address the List ADT storing the elements in a dynamic array.
A random access iterator was also fully implemented to make sure some iterator-dependant operations can be achieved.

## 2. Compile and Run
Check README.md
## 3. Errors and Limitations
The only limitation we could find and can lead to errors is that some functions doesn't have unit_tests already implemented, and we weren't able to make them by our own.
## 4. Difficulties
The insert functions were by far the most difficult ones to implement, specially when a const iterator to the insert position have been provided, because reserve makes them obsolete.
Another difficulty was to think the correct types for every situation, because in this project we managed value_type, raw pointers, references, all in a template class T. 