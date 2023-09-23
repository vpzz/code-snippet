/*
 *数值在内存中的十六进制表示和数值之间的相互转换。同时支持大小端。
 */
#include <stdio.h>
enum Endian {
    BigEndian = -1,  //大端
    LittleEndian = 1 //小端
};
//读写内存中字节推荐使用unsigned char类型
int FromHex(char* str, void* x, size_t size, enum Endian endian) {
    unsigned char* ptr1 = (unsigned char*)x;//不强制类型转换的会报warning
    for (int i = 0;i < size; i++) {
        sscanf(str + (1 - endian) * (size - 1) + i * 2 * endian, "%2hhX", ptr1 + i);//每次读取2个字符，当作1个字节整数的16进制表示
    }
    return 0;
}
int ToHex(char* str, void* x, size_t size, enum Endian endian) {
    unsigned char* ptr1 = (unsigned char*)x;
    for (int i = 0;i < size;i++) {
        sprintf(str + i * 2, "%.2X", *(ptr1 + (1 - endian) * (size - 1) / 2 + i * endian));//将一个字节输出为2位16进制数字。
    }
    return 0;
}
int main() {
    //double x = 0x4022CCCCCCCCCCCD;//不能这样直接赋值，等号右侧会被当作整数
    char str[16] = { 0 };//输出用，最长类型位64位，占用64/4=16个字符。
    //double测试
    double x = 0;
    char strx[] = "CDCCCCCCCCCC2240";
    FromHex(strx, &x, sizeof(x), LittleEndian);
    printf("x = %f\n", x);//9.400000
    ToHex(str, &x, sizeof(x), LittleEndian);
    printf("x in memory: %s\n", str);//CDCCCCCCCCCC2240
    //float测试
    float y = 0;
    char stry[] = "66661641";
    FromHex(stry, &y, sizeof(y), LittleEndian);
    printf("y = %f\n", y);//9.400000
    ToHex(str, &y, sizeof(y), LittleEndian);
    printf("y in memory: %s\n", str);//66661641
    //int测试
    int z = 0;
    char strz[] = "02000100";//
    FromHex(strz, &z, sizeof(z), LittleEndian);
    printf("z = %d\n", z);//65538
    ToHex(str, &z, sizeof(z), LittleEndian);
    printf("z in memory: %s\n", str);//02000100
    //大端测试
    char strxx[] = "4022CCCCCCCCCCCD";
    FromHex(strxx, &x, sizeof(x), BigEndian);
    printf("x = %f\n", x);//9.400000
    ToHex(str, &x, sizeof(x), BigEndian);
    printf("x in memory: %s\n", str);//4022CCCCCCCCCCCD
    return 0;
}
