#include <stdio.h>

#define LAMBDA(c_) ({ c_ _;})

void func(int nb, void (*f)(int)) {
    int i;
    for (i = 0; i < nb; i++) f(i);
}

int main()
{
    
    /* C variant of https://www.w3schools.com/python/python_lambda.asp */
    int (*x)(int a) = LAMBDA(int _(int a) { return a + 10; } );
    printf("%d\n", x(5));
    
    x = LAMBDA(int _(int a) { return a + 15; } );
    printf("%d\n", x(5));
    
    /* taken from https://blog.noctua-software.com/c-lambda.html */
    func(4, LAMBDA(void _(int v) { printf("%d\n", v); }) );
    
    return 0;
}
