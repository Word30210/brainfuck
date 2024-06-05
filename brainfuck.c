#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 32768

int tape[MAX_SIZE] = {};
int tape_index = 0;
int stack[MAX_SIZE] = {};
int stack_index = 0;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Arguments not passed.");
        return 0;
    }
    int MAX_LEN = 256;
    if (argc > 2) MAX_LEN = atoi(argv[2]);
    FILE* file;
    if ((file = fopen(argv[1], "r")) == NULL)
    {
        printf("File not found.");
        return 0;
    }
    int c;
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '+') tape[tape_index]++;
        else if (c == '-') tape[tape_index]--;
        else if (c == '>')
        {
            if (MAX_SIZE > c) tape_index++;
            else tape_index = 0;
        }
        else if (c == '<')
        {
            if (c > 1) tape_index--;
            else tape_index = MAX_SIZE - 1;
        }
        else if (c == '.') printf("%c", tape[tape_index]);
        else if (c == ',') tape[tape_index] = getchar();
        else if (c == '[')
        {
            if (tape[tape_index] == 0)
            {
                int level = 1;
                while (level > 0)
                {
                    c = fgetc(file);
                    if (c == EOF) break;
                    if (c == '[') level++;
                    else if (c == ']') level--;
                }
            }
            else
            {
                stack[stack_index] = ftell(file) - 1;
                stack_index++;
            }
        }
        else if (c == ']')
        {
            if (tape[tape_index] != 0)
            {
                stack_index--;
                fseek(file, stack[stack_index], SEEK_SET);
            }
        }
    }
    fclose(file);
    return 0;
}

