#include <stdio.h>
#include <stdlib.h> 

// defining structure of array 
typedef struct ArrayList { 
    //(ptr (*) is a variable that holds memory address of another variable) 
    void **elements; // storing the memory address to an array of ptrs
    size_t size, capacity, element_size; // current size index, size of whole array, size of each element
    void (*copy_element)(void *dest, const void *src); //copying element from src location to destination
    void (*free_element)(void *element); // freeing space in memory 

} ArrayList;

// Initialization & Desctruction 

void initialize_array_list(ArrayList *list1, size_t size, size_t element_size, size_t capacity,
                     void (*copy_element)(void *dest, void *src),
                     void (*free_element)(void *element)) {


    list1->size = 0; // initializing to empty 
    list1->element_size = element_size; //setting to what is passed into init
    list1->capacity = 10; //setting size to 10 
    list1->elements = malloc(list1->capacity * sizeof(void *)); // holds elemnts of size capacity * void ptr size
    list1->copy_element = copy_element; // copying elements to the list 
    list1->free_element = free_element; // destruction 
}

//Destruction & Freeing 
void destroy_array_list(ArrayList *list1){
    if (list1->free_element != NULL) {
        //freeing individual elements in array 
        for (size_t i = 0; i < list1->size; i++) {
        list1->free_element(list1->elements[i]);
        }
        // freeing memeory allocated for pointers (malloc)
        free(list1->elements); 

        //resetting values 
        list1->elements = NULL;
        list1->size = 0;
        list1->capacity = 0;
    }
}

//Autoresizing 
void resize_array(ArrayList *list1){
    list1->capacity = list1->capacity * 2; // doubles capacity of array 

    //resizes list->elements to list1->capacity * sizeof(void *)
    // temporary ptr to hold realloc: void **ptr_to_new_void_array
    void **ptr_to_new_void_array = realloc(list1->elements, list1->capacity * sizeof(void *));

    if (!ptr_to_new_void_array) { //if realloc returned NULL
        fprintf(stderr, "Failed to reallocate memory for ArrayList.\n");
        exit(EXIT_FAILURE);
    }

    //updates elements of void list to new memory block 
    list1->elements = ptr_to_new_void_array;
}

// Adding an element, const means not modifying element 
void add(ArrayList *list1, const void *element){
    // check if there is capactiy 
    if (list1->size == list1->capacity) {
        resize_array(list1);
    }

    // allocate memory for the element add onto current element array 
    // mallocing only size of 1 element to the index of the current size i.e end of array 
    list1->elements[list1->size] = malloc(list1->element_size); 

    //error checking after allocation
    if (!list1->elements[list1->size]){
        fprintf(stderr, "Failed to allocate memory for new element.\n");
        exit(EXIT_FAILURE);
    }

    // copy the element into allocated memory 
    // copying element from source location (element) --> 
    // to destination (list1->elements[list1->size])- new index created 
    list1->copy_element(list1->elements[list1->size], element); 

    //increase size of list 
    list1->size = list1->size + 1; 
}

// removing an element at a specific index 
void remove(ArrayList *list1, size_t index){
// validating the index 
if (index >= list1->size){ 
    fprintf(stderr, "Index out of bounds.\n");
    return;
}

// freeing memory associated with the element
if(list1->free_element != NULL){
    //freeing the element at the specific index
    list1->free_element(list1->elements[index]);
}

// shifting elements in the array to fill the gap 
// i is the index value passed in, size-1 because 1 element removed  
for (size_t i = index; i < list1->size -1; i++){
    //list->elements[i] is NULL currenlty, setting it the value next to it
    //next i becomes NULL
    list1->elements[i] = list1->elements[i+1];
}

// updating size of the list 
list1->size = list1->size - 1; 
}


// returns a pointer to element at passed in index, void type  
// elements array is an array of void ptrs
// getting a ptr, hence *get 
void *get (ArrayList *list1, size_t index){

// validating the index 
if (index >= list1->size){ 
    fprintf(stderr, "Index out of bounds.\n");
    return;
}
return list1->elements[index];
}


// set elements by index 
void set(ArrayList *list1, size_t index, void *element){
// validating the index 
if (index >= list1->size){ 
    fprintf(stderr, "Index out of bounds.\n");
    return;
}

//copy to set the new index 
list1->copy_element(list1->elements[index], element); 
}


void copy_integer(void *dest, void *src) {
    *(int *)dest = *(int *)src;
}

void free_integer(void *element) {
    // No-op for integers
}


int main(){

    ArrayList list1;
    initialize_array_list(&list1, 10, sizeof(int), 10, copy_integer, free_integer);

    int value = 23;
    add(&list1, &value);

    int val = 24;
    add(&list1, &val);

    for (size_t i = 0; i < list1.size; i++) {
        int *elem = (int *)get(&list1, i);
        printf("%d\n", *elem);
    }

    remove(&list1, 0);

    for (size_t i = 0; i < list1.size; i++) {
        int *elem = (int *)get(&list1, i);
        printf("%d\n", *elem);
    }

    destroy_array_list(&list1);
    return 0;
}













