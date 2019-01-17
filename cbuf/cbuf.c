
typedef unsigned int    u32;
typedef unsigned char   u8;
typedef struct kfifo
{
 unsigned char *buffer;			  //循环buffer指针
 unsigned int   size;            //循环buffer空间大小
 unsigned int   in;              //输入数据偏移索引
 unsigned int   out;             //输出数据偏移索引
}cbuft;
u32 min(u32 data1, u32 data2)
{
    return (data1<data2)?(data1):(data2);
}
/*
** 向 缓冲区 写入数据
** 返回值：实际写入数据
*/
u32 put_fifo(cbuft *cbuf, const u8* data_in, u32 len)
{
    len = min(len, cbuf->size - (cbuf->in-cbuf->out));     			//保证写入长度 <= 空闲空间大小
    u32 L = min(len, cbuf->size - (cbuf->in & (cbuf->size - 1)));       // size - in&(sie-1)in到缓冲区尾部的距离
    memcpy(cbuf->buffer + (cbuf->in&(cbuf->size-1)) , data_in, L);
    memcpy(cbuf->buffer, data_in+L, len-L);
    cbuf->in += len;
    return len;
}
/*
** 读数据
*/
u32 get_fifo(cbuft *cbuf, const u8* data_out, u32 len)
{

     len = min(len , cbuf->in - cbuf->out);
     u32 L = min(len,cbuf->size - (cbuf->out &(cbuf->size - 1) ));

     memcpy(data_out , cbuf->buffer + (cbuf->out &(cbuf->size - 1)), L );
     memcpy(data_out+L , cbuf->buffer , len -L);
     cbuf->out += len;

     return len;
}


/**
** 循环提取buf中的数据  不删除数据
*/
void get_lcd_data_roll(cbuft *cbuf, const u8* data_out, u32 len)
{

    u32 L = min(len,cbuf->size - cbuf->out);
    if((cbuf->out+1) >=  cbuf->size)
        cbuf->out = 0;
    memcpy(data_out , cbuf->buffer + cbuf->out, L );
    memcpy(data_out+L , cbuf->buffer , len -L);
    cbuf->out ++;

}



void cbuffer_init(cbuft *cbuf,u8 *buf, u32 size)
{
    cbuf->buffer = buf;
    cbuf->in = 0;
    cbuf->out = 0;
    cbuf->size = size;
}
