/*
 *获取变量在内存中的字节表示，这里以浮点数为例。
 */
#include <stdio.h>

int main() {
    double x = 9.4;//IEEE754表示:0x4022CCCCCCCCCCCD
    unsigned char* ptr1 = &x;//强制类型转换，不推荐使用signed char
    for (int i = 0;i < sizeof(x);i++) {
        printf("%X ", *(ptr1 + i)); //输出为：CD CC CC CC CC CC 22 40
    }
    printf("\n");
    return 0;
}
