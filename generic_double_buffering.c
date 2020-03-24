/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>

typedef struct double_buffer_struct
{
    void *buffer_a;
    void *buffer_b;
    void *active;
    void *passive;
    
} double_buffer_td;

void double_buffer_init(double_buffer_td *p_buffer, 
                        void *buffer_a, 
                        void *buffer_b, 
                        void **p_buf_active, 
                        void **p_buf_passive)
{
    p_buffer->buffer_a = buffer_a;
    p_buffer->buffer_b = buffer_b;
    p_buffer->active = p_buffer->buffer_a;
    p_buffer->passive = p_buffer->buffer_b;
    *p_buf_active = p_buffer->active;
    *p_buf_passive = p_buffer->passive;
}

void double_buffer_switch(double_buffer_td *p_buffer, void **p_buf_active, void **p_buf_passive)
{
    void *tmp = p_buffer->active;
    *p_buf_active = p_buffer->active = p_buffer->passive;
    *p_buf_passive = p_buffer->passive = tmp;
}

int main()
{
    double_buffer_td test_buffer;
    uint8_t *p_buf_active = NULL;
    uint8_t *p_buf_passive = NULL;
    uint8_t buffer_a[3] = {1,2,3};
    uint8_t buffer_b[3] = {4,5,6};
    
    double_buffer_init(&test_buffer, buffer_a, buffer_b, (void**)&p_buf_active, (void**)&p_buf_passive);

    printf("%d %d %d\n", p_buf_active[0], p_buf_active[1], p_buf_active[2]);
    printf("%d %d %d\n", p_buf_passive[0], p_buf_passive[1], p_buf_passive[2]);

    double_buffer_switch(&test_buffer, (void**)&p_buf_active, (void**)&p_buf_passive);

    printf("%d %d %d\n", p_buf_active[0], p_buf_active[1], p_buf_active[2]);
    printf("%d %d %d\n", p_buf_passive[0], p_buf_passive[1], p_buf_passive[2]);

    return 0;
}
