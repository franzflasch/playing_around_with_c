#ifndef DOUBLE_BUFFERING_H
#define DOUBLE_BUFFERING_H

#include <stdint.h>

typedef struct double_buffer_struct
{
    uint32_t switch_flag;
    uint32_t buf_size;
    uint32_t buf_pos_active;
    uint32_t buf_pos_passive;
    void *base_addr_phys;
    void *buffer_a;
    void *buffer_b;
    void *active;
    void *passive;

} double_buffer_td;

void double_buffer_init(double_buffer_td *p_buffer,
                        uint32_t buf_size,
                        void *base_addr_phys,
                        void *buffer_a,
                        void *buffer_b,
                        void **p_buf_active,
                        void **p_buf_passive);
void double_buffer_switch(double_buffer_td *p_buffer, void **p_buf_active, void **p_buf_passive);

#endif /* DOUBLE_BUFFERING_H */
