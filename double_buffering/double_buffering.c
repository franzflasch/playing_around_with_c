#include <double_buffering.h>

void double_buffer_init(double_buffer_td *p_buffer,
                        uint32_t buf_size,
                        void *base_addr_phys,
                        void *buffer_a,
                        void *buffer_b,
                        void **p_buf_active,
                        void **p_buf_passive)
{
    p_buffer->switch_flag = 0;
    p_buffer->buf_size = buf_size;
    p_buffer->buf_pos_active = 0;
    p_buffer->buf_pos_passive = 0;
    p_buffer->base_addr_phys = base_addr_phys;
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
