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
    linked_list::ll_size = 0;  
}

linked_list:: ~linked_list() {
    while (head != nullptr) {
        node *temp = head;
        head = head->next;
        delete temp;
    }
}

bool linked_list::insert(size_t index, unsigned int data){
    if(index > ll_size)
        return false;

    node* new_node = new linked_list::node();
    new_node->data = data;
    new_node->next = nullptr;

    if(index == 0){
        new_node->next = head;
        head = new_node;
    } else {
        node* current = head;
        for(size_t i = 0; i < index - 1; i++)
            current = current->next;

        new_node->next = current->next;
        current->next = new_node;
    }
    ll_size++;
    return true;
}

bool linked_list:: insert_front(unsigned int data){
    return linked_list::insert(0, data);
}

bool linked_list:: insert_end(unsigned int data){
    return linked_list::insert(ll_size, data);
}

size_t linked_list::find(unsigned int data) const{
    node* current = head;
    size_t index = 0;

    while (current != nullptr)
    {
        if (current->data == data)
            return index;
        current = current->next;
        index++;
    }
    return SIZE_MAX;
}



