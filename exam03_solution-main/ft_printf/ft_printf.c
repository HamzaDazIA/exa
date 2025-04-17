#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

int c_conv(char c)
{
    write(1, &c, 1);
    return (1);
}

int s_conv(char *str)
{
    int i = 0;
    int counter = 0;

    if (str == NULL)
    {
        return (s_conv("(null)"));
    }
    while(str[i])
    {
        counter += c_conv(str[i]);
        i++;
    }
    return (counter);
}

int d_conv(int x)
{
    int count = 0;
    if (x == INT_MIN)
    {
        s_conv("-2147483648");
        return (11);
    }
    if (x < 0)
    {
        count += c_conv('-');
        x *= -1;
    }
    if (x > 9)
    {
        count += d_conv(x / 10);
        count += d_conv(x % 10);
    }
    if (x <= 9)
        count += c_conv(x + 48);

    return count;
}

int x_conv(unsigned int x)
{
    char *str = "0123456789abcdef";
    int count = 0;

    if (x >= 16)
        count += x_conv(x / 16);
    c_conv(str[x % 16]);
    count++;
    return count;
}

int ft_printf(const char *str, ...)
{
    va_list arg;
    int counter = 0;
    size_t i = 0;

    va_start(arg, str);
    while(str[i])
    {
        if (str[i] == '%')
        {
            i++;
            if (str[i] == 's')
                counter += s_conv(va_arg(arg, char *));
            else if (str[i] == 'd')
                counter += d_conv(va_arg(arg, int));
            else if (str[i] == 'x')
                counter += x_conv(va_arg(arg, int));
        }
        else
            counter += c_conv(str[i]);
        i++;
    }
    va_end(arg);
    return counter;
}

// #include <stdio.h>
// int main()
// {
//     ft_printf("[%d]\n",ft_printf("%x", -2147483648));
//     printf("[%d]\n",printf("%x", -2147483648));

//     ft_printf("%s\n", NULL);
//     ft_printf("Magic %s is %d", "number", 42);
//     ft_printf("Hexadecimal for %d is %x\n", 42, 42);
// }
