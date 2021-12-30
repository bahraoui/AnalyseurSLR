#include <stdio.h>
#include <stdlib.h>

void implement(int *par){
    (*par)++;
    printf("xfunction:%d\n",(*par));
}

int main(int argc, char const *argv[])
{
    int x = 1;
    printf("x:%d\n",x);
    implement(&x);
    printf("x:%d\n",x);

    return 0;
}