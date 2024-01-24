#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define BLOCK_SIZE 512
#define IMGNAME_SIZE 8

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usafe: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("cannot open the file");
        return 1;
    }

    int img_num = 0;
    char img_name[IMGNAME_SIZE];

    uint8_t buffer[BLOCK_SIZE];

    FILE *img = NULL;

    while (fread(buffer, 1, BLOCK_SIZE, card))
    {
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (img_num > 0)
            {
                fclose(img);
            }
            sprintf(img_name, "%03i.jpg", img_num);
            img_num++;
            img = fopen(img_name, "w");
            if (img == NULL)
            {
                printf("cannot open the file");
                return 1;
            }
        }
        // for the first buffer, could start with random numbers
        if (img != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }

    fclose(card);
}
