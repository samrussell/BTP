#include <stdio.h>
#include <stdlib.h>

int test(){

    // test 1: load file
    btp_load_file("../../xen-guest.img");
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
