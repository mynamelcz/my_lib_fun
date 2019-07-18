

/*
**作用是将 size 提升为 align 定义的整数的倍数，
**例如： RT_ALIGN(13,4) 将返回 16。
*/
#define RT_ALIGN(size, align)           (((size) + (align) - 1) & ~((align) - 1))

/*
**作用是将 size 下降为 align 定义的整数的倍数，
**例如： RT_ALIGN(13,4) 将返回 12。
*/
#define RT_ALIGN_DOWN(size, align)      ((size) & ~((align) - 1))