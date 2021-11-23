#include <stdio.h>

#define compose(arr_name, arr_size, ...) void (*arr_name[arr_size])(void*) = { __VA_ARGS__ };

#define calc(arr_name, arr_size, var_name) \
    for (int i = 0; i < arr_size; i++)     \
        arr_name[i](var_name);

#define lambda(name, type, param, ...) \
    void name(void* xx)                \
    {                                  \
        type* param = (type*)xx;       \
        __VA_ARGS__;                   \
    }

lambda(sum, int, a, int sum = 0; for (int i = 0; i < 10; i++) sum += a[i]; a[0] = sum);
lambda(add_one, int, a, (*a)++);
lambda(time_two, int, a, (*a) *= 2);
lambda(arr_time_two, int, a, for (int i = 0; i < 10; i++) a[i] *= 2);

int main()
{
    /*int a = 34;*/
    int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    compose(fn, 3, &arr_time_two, &arr_time_two, &sum);
    calc(fn, 3, arr);
    printf("a: %d\n", *arr);
    return 0;
}
