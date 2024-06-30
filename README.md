# Array-List-Generation-Class
Objective: Implement a generic ArrayList class in C that can store elements of any data type

Description:

Dynamic Array: Create a dynamically resizable array that can store elements of any data type
Operations: Implement operations such as adding elements, removing elements, and accessing elements by index
Generic Implementation: Use void pointers to create a generic implementation that can handle different data type

Specifications:

Structure: Define a structure for the ArrayList that includes fields for array of elements, the current size, and function pointers for element operations
Initialization and Destruction: Implement functions to initialize and destroy the ArrayList
Add and Remove Elements: Implement functions to add elements to the end of the list (auto-resize array when necessary), remove elements by index
Access Elements: Implement functions to get and set elements by index

Auto-Resizing:

        The constructor of ArrayList can take a size argument, by default it is 10. When the ArrayList has size elements, then create a new array of old size * 2, copy the old elements to the new array, garbage collect the old array, then set the internal array element to the new array


Suggested Pre Research:

https://www.geeksforgeeks.org/internal-working-of-arraylist-in-java/
https://stackoverflow.com/questions/1403890/how-do-you-implement-a-class-in-c
https://codeforwin.org/c-programming/c-void-pointer-generic-pointer-use-arithmetic
https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/
