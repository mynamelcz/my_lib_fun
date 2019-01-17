
typedef unsigned int    u32;
typedef unsigned char   u8;
typedef struct kfifo
{
 unsigned char *buffer;			  //ѭ��bufferָ��
 unsigned int   size;            //ѭ��buffer�ռ��С
 unsigned int   in;              //��������ƫ������
 unsigned int   out;             //�������ƫ������
}cbuft;
u32 min(u32 data1, u32 data2)
{
    return (data1<data2)?(data1):(data2);
}
/*
** �� ������ д������
** ����ֵ��ʵ��д������
*/
u32 put_fifo(cbuft *cbuf, const u8* data_in, u32 len)
{
    len = min(len, cbuf->size - (cbuf->in-cbuf->out));     			//��֤д�볤�� <= ���пռ��С
    u32 L = min(len, cbuf->size - (cbuf->in & (cbuf->size - 1)));       // size - in&(sie-1)in��������β���ľ���
    memcpy(cbuf->buffer + (cbuf->in&(cbuf->size-1)) , data_in, L);
    memcpy(cbuf->buffer, data_in+L, len-L);
    cbuf->in += len;
    return len;
}
/*
** ������
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
** ѭ����ȡbuf�е�����  ��ɾ������
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
