#include "cstack.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define UNUSED(VAR) (void)(VAR)


// Структура узла стека
struct node {
struct node* next;
void* data;
size_t size;

};

struct hand{
struct node* stack[10];
hstack_t index;
};


struct hand global_mass = {{NULL},0};

hstack_t stack_new(void)
{
hstack_t t;
struct node* new = (struct node*)malloc(sizeof(struct node));
new->size = 0;
new->next = NULL;
new->data = NULL;

for(size_t i = 0; i != 10; i++)
{
    if(global_mass.stack[i] == NULL)
    {
        t = i;
    global_mass.stack[t] = new;
    if(global_mass.stack[t] != NULL)
    {
        return t;
    }
    }
}

return -1;
}

void stack_free(const hstack_t hstack)
{
if(stack_valid_handler(hstack) == 0)
{
struct node* stack = global_mass.stack[hstack];
struct node* next;
if(stack->size == 0)
{
    free(stack);
}
else
{
    while(stack != NULL)
    {
    next = stack->next;
    if(stack->data != NULL)
        free(stack->data);
    free(stack);
    stack = next;
    }
}
global_mass.stack[hstack] = NULL;
}
}

int stack_valid_handler(const hstack_t stack)
{
    if(stack>=0 && stack<10 )
    {
        if(global_mass.stack[stack] != NULL)
            return 0;
    }
return 1;
}

unsigned int stack_size(const hstack_t stack)
{
    if(stack_valid_handler(stack) == 0)
    {
        struct node* i = global_mass.stack[stack];
        return i->size;
    }
    return 0;
}

void stack_push(const hstack_t hstack, const void* data_in, const unsigned int size)
{
if(stack_valid_handler(hstack) == 0)
{
    struct node** old = &global_mass.stack[hstack];
    struct node* siz = *old;

    if(siz->size == 0)
    {
        if(data_in != NULL && size != 0)
        {
        siz->size++;
        siz->data = malloc(size);

            memcpy(siz->data, data_in, size);
        }

    }else
    {
    if(stack_valid_handler(hstack) == 0)
        {
        if(data_in != NULL && size != 0)
        {
            struct node* new = (struct node*)malloc(sizeof(struct node));
            new->data = malloc(size);
            if(data_in != NULL)
                memcpy(new->data, data_in, size);
            new->size = siz->size + 1;
            new->next = *old;
            *old = new;

            global_mass.stack[hstack] = *old;
        }
        }
    }
}
}


unsigned int stack_pop(const hstack_t hstack, void* data_out, const unsigned int size)
{

if (stack_valid_handler(hstack) == 0)
{
struct node* data_pop = global_mass.stack[hstack];

if(data_pop->data != NULL)
{
    memcpy(data_out, data_pop->data, size);
    free(data_pop->data);


global_mass.stack[hstack] = data_pop->next;
free(data_pop);
return size;
}
}
return 0;
}

