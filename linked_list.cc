#include "linked_list.h"

// Initial declaration of the static member function
// pointers in the linked_list class.
//
void * (*linked_list::malloc_fptr)(size_t) = nullptr;
void (*linked_list::free_fptr)(void*)      = nullptr;

// These static member functions are provided for you. 
// You still need to implement the new() and delete()
// operators.
//

void* linked_list::operator new(size_t size){
    if (linked_list::malloc_fptr)
        return linked_list::malloc_fptr(size);

    return ::operator new(size);    
}

void* linked_list::node::operator new(size_t size){
    if (linked_list::malloc_fptr)
        return linked_list::malloc_fptr(size);

    return ::operator new(size);    
}

void linked_list::operator delete(void *ptr){
    if (linked_list::free_fptr)
        linked_list::free_fptr(ptr);
    else
        ::operator delete(ptr);  
}

void linked_list::node::operator delete(void *ptr){
    if (linked_list::free_fptr)
        linked_list::free_fptr(ptr);
    else
        ::operator delete(ptr);  
}

void linked_list::register_malloc(void *(*malloc)(size_t)) {
    linked_list::malloc_fptr = malloc;
}

void linked_list::register_free(void (*free)(void*)) {
    linked_list::free_fptr = free;
}

linked_list:: linked_list(){
    linked_list::head = nullptr;    
}

linked_list:: ~linked_list() {
    while (head != nullptr) {
        node *temp = head;
        head = head->next;
        delete temp;
    }
}

