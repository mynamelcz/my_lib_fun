#ifndef __CBUF_H
#define __CBUF_H


struct cbuf_t
{
 unsigned char *buffer;			  //循环buffer指针
 unsigned int   size;            //循环buffer空间大小
 unsigned int   in;              //输入数据偏移索引
 unsigned int   out;             //输出数据偏移索引
 unsigned int   mutex;
};


unsigned int put_fifo(struct cbuf_t *cbuf, const unsigned char *data_in, unsigned int len);
unsigned int get_fifo(struct cbuf_t *cbuf,       unsigned char *data_out,unsigned int len);
unsigned int get_fifo_roll(struct cbuf_t *cbuf,  unsigned char *data_out,unsigned int len);
unsigned int cbuffer_init (struct cbuf_t *cbuf,  unsigned char *buf,     unsigned int size);




#endif





