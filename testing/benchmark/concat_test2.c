#include <stdio.h>
#include <string.h>
#include "../../smart_string.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        return 0;
    }

    smart_string buf = new_string("The Following is being concatinated:\n");
    smart_string buf2 = new_string("x");

    // printf("Before concat:\n");
    // printf("buf = %s, size = %lu\n", buf, getlen_string(buf));
    // printf("buf2 = %s, size = %lu\n", buf2, getlen_string(buf2));

    for (int i = 0; i < atoi(argv[1]); i++)
    {
        buf = concat_string(buf, buf2);
    }

    // printf("buf = %s, size = %lu\n", buf, getlen_string(buf));
    // printf("buf2 = %s, size = %lu\n", buf2, getlen_string(buf2));

    delete_string(buf);
    delete_string(buf2);
    return 0;
}
