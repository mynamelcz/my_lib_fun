#include "cbuf.h"

#define NULL 0


static void my_memcpy(unsigned char *tar, const unsigned char *src, unsigned int len)
{
  ASSERT(tar);
	ASSERT(src);
	if(len==0)
		return;
	while(len--)
		*tar++ = *src++;
}

static unsigned int min(unsigned int data1, unsigned int data2)
{
    return (data1<data2)?(data1):(data2);
}

static unsigned int mutex_wait(struct cbuf_t *cbuf)
{
	return 0;
}
static unsigned int mutex_release(struct cbuf_t *cbuf)
{
	return 0;
}
static unsigned int mutex_create(struct cbuf_t *cbuf)
{
	return 0;
}

/*
** 向 缓冲区 写入数据
** 返回值：实际写入数据
*/
unsigned int put_fifo(struct cbuf_t *cbuf, const unsigned char *data_in, unsigned int len)
{
    if((cbuf == NULL)||(data_in == NULL)||(len==0)){
        return 0;
    }
	mutex_wait(cbuf);
    
	len = min(len, cbuf->size - (cbuf->in-cbuf->out));     			//保证写入长度 <= 空闲空间大小
    unsigned int L = min(len, cbuf->size - (cbuf->in & (cbuf->size - 1)));       // size - in&(sie-1)in到缓冲区尾部的距离
    my_memcpy(cbuf->buffer + (cbuf->in&(cbuf->size-1)) , data_in, L);
    my_memcpy(cbuf->buffer, data_in+L, len-L);
    cbuf->in += len;
	
	mutex_release(cbuf);
    return len;
}
/*
** 读数据
*/
unsigned int get_fifo(struct cbuf_t *cbuf,  unsigned char *data_out, unsigned int len)
{
    if((cbuf == NULL)||(data_out == NULL)||(len==0)){
        return 0;
    }
	mutex_wait(cbuf);
	
    len = min(len , cbuf->in - cbuf->out);
    unsigned int L = min(len,cbuf->size - (cbuf->out &(cbuf->size - 1) ));
    my_memcpy(data_out , cbuf->buffer + (cbuf->out &(cbuf->size - 1)), L );
    my_memcpy(data_out+L , cbuf->buffer , len -L);
    cbuf->out += len;

    mutex_release(cbuf);
    return len;
}


/**
** 循环提取buf中的数据  不删除数据
*/
unsigned int get_fifo_roll(struct cbuf_t *cbuf,  unsigned char *data_out, unsigned int len)
{
    if((cbuf == NULL)||(data_out == NULL)||(len==0)){
        return 0;
    }
	mutex_wait(cbuf);
	
    unsigned int L = min(len,cbuf->size - cbuf->out);
    if((cbuf->out+1) >=  cbuf->size)
        cbuf->out = 0;
    my_memcpy(data_out , cbuf->buffer + cbuf->out, L );
    my_memcpy(data_out+L , cbuf->buffer , len -L);
    cbuf->out ++;
	
	mutex_release(cbuf);
	return 0;
}


/*
 * size:只能是2的几次幂
 */
unsigned int cbuffer_init(struct cbuf_t *cbuf,unsigned char *buf, unsigned int size)
{
    if((size&(size-1)) != 0){
			return 1;
    }
    cbuf->buffer = buf;
    cbuf->in = 0;
    cbuf->out = 0;
    cbuf->size = size;
	
	mutex_create(cbuf);
	return 0;
}
