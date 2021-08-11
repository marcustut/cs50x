#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // get_string takes an string input from STDIN
    string name = get_string("What is your name?\n>");

    // printf prints the output to STDOUT
    printf("\nHello, %s!\n", name);
}