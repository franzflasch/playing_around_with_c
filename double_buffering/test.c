#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <double_buffering.h>

#define BUF_SIZE 64

void *reader_thread(void *vargp)
{
    volatile double_buffer_td *test_buffer = vargp;
    uint8_t *p_buf_passive = test_buffer->passive;
    uint32_t i = 0;
    while(1)
    {
        printf("\n=============\n");
        printf("reader thread\n");
        if(test_buffer->switch_flag == 0)
        {
            p_buf_passive = test_buffer->passive;
            for(i=0;i<test_buffer->buf_pos_passive;i++)
            {
                printf("%d ", p_buf_passive[i]);
            }
            test_buffer->buf_pos_passive = 0;
            test_buffer->switch_flag = 1;
        }
        else
        {
            printf(".");
        }
        usleep(200000);
        printf("\n=============\n\n");
    }
    return NULL;
}

void *writer_thread(void *vargp)
{
    volatile double_buffer_td *test_buffer = vargp;
    uint8_t *p_buf_active = test_buffer->active;
    uint8_t *p_buf_passive = test_buffer->passive;
    uint8_t counter = 0;
    printf("Writer thread!\n");
    while(1)
    {
        // printf("\n=============\n");
        // printf("writer thread\n");
        if(test_buffer->switch_flag == 1)
        {
            printf("Switch!\n");
            // printf("=============\n");
            // printf("writer thread\n");
            // printf("%d %d %d\n", p_buf_active[0], p_buf_active[1], p_buf_active[2]);
            // printf("=============\n\n");
            test_buffer->buf_pos_passive = test_buffer->buf_pos_active;
            double_buffer_switch((double_buffer_td *)test_buffer, (void**)&p_buf_active, (void**)&p_buf_passive);
            test_buffer->switch_flag = 0;
            test_buffer->buf_pos_active = 0;
        }
        else
        {
            if(test_buffer->buf_pos_active>=test_buffer->buf_size)
            {
                printf("%d ", counter);
            }
            else
            {
                printf("+");
                p_buf_active[test_buffer->buf_pos_active++] = counter;
            }
            counter++;
        }

        // printf("\n=============\n\n");
        usleep(10000);
    }
    return NULL;
}


int main()
{
    volatile double_buffer_td test_buffer;
    uint8_t *p_buf_active = NULL;
    uint8_t *p_buf_passive = NULL;
    uint8_t buffer_a[BUF_SIZE] = {0};
    uint8_t buffer_b[BUF_SIZE] = {0};

    pthread_t reader_thread_id;
    pthread_t writer_thread_id;

    double_buffer_init((double_buffer_td *)&test_buffer, BUF_SIZE, 0, buffer_a, buffer_b, (void**)&p_buf_active, (void**)&p_buf_passive);

    // printf("%d %d %d\n", p_buf_active[0], p_buf_active[1], p_buf_active[2]);
    // printf("%d %d %d\n", p_buf_passive[0], p_buf_passive[1], p_buf_passive[2]);

    // double_buffer_switch(&test_buffer, (void**)&p_buf_active, (void**)&p_buf_passive);

    // printf("%d %d %d\n", p_buf_active[0], p_buf_active[1], p_buf_active[2]);
    // printf("%d %d %d\n", p_buf_passive[0], p_buf_passive[1], p_buf_passive[2]);

    pthread_create(&reader_thread_id, NULL, reader_thread, (void *)&test_buffer);
    pthread_create(&writer_thread_id, NULL, writer_thread, (void *)&test_buffer);
    pthread_join(writer_thread_id, NULL);
    pthread_join(reader_thread_id, NULL);

    return 0;
}
