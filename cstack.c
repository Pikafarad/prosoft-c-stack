#include "cstack.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define NUMBER_SIZE 10


// Структура узла стека
struct node
{
    struct node* next;
    void* data;
    size_t size;
};

// Структура для хранения стека
// hstack_t index - нигде не используется
struct hand
{
    struct node* stack[NUMBER_SIZE];
    hstack_t index;
};

struct hand global_mass = {{NULL},0};

// Функция для инициализации стека
hstack_t stack_new(void)
{
    hstack_t t = 0;
    struct node* new = (struct node*)malloc(sizeof(struct node));
    new->size = 0;
    new->next = NULL;
    new->data = NULL;

    for(size_t i = 0; i != NUMBER_SIZE; i++)
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

// Функция для освобождения памяти стека
void stack_free(const hstack_t hstack)
{
    if(stack_valid_handler(hstack) == 0)
    {
        struct node* stack = global_mass.stack[hstack];
        struct node* next;
        while(stack != NULL)
        {
            next = stack->next;
            if(stack->data != NULL)
                free(stack->data);
            free(stack);
            stack = next;
        }
        global_mass.stack[hstack] = NULL;
    }
}

// Функция провекри на влидность хэндлера стека
int stack_valid_handler(const hstack_t stack)
{
    if(stack>=0 && stack<10 && global_mass.stack[stack] != NULL)
    {
        return 0;
    }
    return 1;
}

// Функция возвращающая размер стека
unsigned int stack_size(const hstack_t stack)
{
    if(stack_valid_handler(stack) == 0)
    {
        struct node* i = global_mass.stack[stack];
        return i->size;
    }
    return 0;
}

// Функция, добавляющая данные в стек
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

// Функция, вытаксиващие данные из стека и записыващая их в буфер
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

