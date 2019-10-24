//
// Created by tao on 18-10-5.
//

#ifndef UNIXSTUDY_IOTEST_H
#define UNIXSTUDY_IOTEST_H

#include <stdio.h>
#define INPUT_SIZE 100

void iotest(){
    printf("Hello, World!\n");
    char buff[INPUT_SIZE];

//    scanf("%s",buff);
    printf("%s\n",buff);
    printf("f:%.5f\td:%1d\n",1.454545454,5464646);
    printf("i f:%.*f\n",3,1.454545);
    printf("%-10s\n","hello");
    printf("%zd\n", sizeof(int));

    int ch;
    while ((ch=getchar())!=EOF){
        putchar(ch);
    }
    printf("\nget char end!\n");

    //scanf 貌似存在越界的问题，但是gcc没有_s 系的函数？？？
    char smallBuff[5];
    scanf("%s",smallBuff);
    printf("%s\n",smallBuff);

}


void iotest_main(){
    iotest();
}
#endif //UNIXSTUDY_IOTEST_H
