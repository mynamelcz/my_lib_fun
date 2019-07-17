#ifndef __CBUF_H
#define __CBUF_H


struct cbuf_t
{
 unsigned char *buffer;			  //ѭ��bufferָ��
 unsigned int   size;            //ѭ��buffer�ռ��С
 unsigned int   in;              //��������ƫ������
 unsigned int   out;             //�������ƫ������
 unsigned int   mutex;
};


unsigned int put_fifo(struct cbuf_t *cbuf, const unsigned char *data_in, unsigned int len);
unsigned int get_fifo(struct cbuf_t *cbuf,       unsigned char *data_out,unsigned int len);
unsigned int get_fifo_roll(struct cbuf_t *cbuf,  unsigned char *data_out,unsigned int len);
unsigned int cbuffer_init (struct cbuf_t *cbuf,  unsigned char *buf,     unsigned int size);




#endif





