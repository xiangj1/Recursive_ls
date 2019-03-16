#include "lsr.c"

int main(int argc, char* argv[])
{
    if(argc > 1)
        do_ls(argv[1], 0);
    else
        do_ls(".", 0);
}
