#include <stdio.h>
#include <stdlib.h>

int test(){

    // test 1: load file
    if(btp_load_file("../../test8g.img")) return 1;
    return 0;
}

int main()
{
    printf("Hello world!\n");
    if(!test()){
        printf("Failed to open file\n");
    }
    return 0;
}
