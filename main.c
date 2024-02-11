/** DeCopper
    Copperlist disassembler
*/

#include <stdio.h>
#include <stdlib.h>
#include <dbg/dbg.h>

#define VERSTAG "\0$VER: DeCopper 1.0 (09/02/2024) Brewed for you by Pepito\0"

#include "decop.h"


static void Usage(char *progname)
{
    fprintf(stderr, "USAGE: %s <clist file>\n", progname);
}

static long GetFileSize(FILE *f)
{
    long size = 0;

    check(NULL != f, "Null file pointer");
    check(0 == fseek(f, 0, SEEK_END), "Error while getting to end of file");
    size = ftell(f);
    rewind(f);

on_error:
    return size;
}

// estimated average sufficient line len
#define LINE_LEN 30
static BOOL DisassembleCopFile(FILE *f)
{
    BOOL res = FALSE;
    long file_size;
    char *buf = NULL;
    int buf_len;
    APTR clist = NULL;

    check(NULL != f, "Null file pointer");
    file_size = GetFileSize(f);
    check(0 != file_size, "Can't process file");

    clist = malloc(file_size);
    check_mem(clist);
    check(1 == fread(clist, file_size, 1, f), "Error reading file content");

    buf_len = (file_size / COPPER_INST_SIZE) * LINE_LEN;
    buf = malloc(buf_len);
    check_mem(buf);
    buf[0] = '\n';

    res = DeCopList(clist, file_size, buf, buf_len);

    if(TRUE == res)
    {
        printf("Disassembled copperlist:\n%s\n", buf);
    }

on_error:
    if(ASSIGNED(buf))
    {
        free(buf);
    }
    if(ASSIGNED(clist))
    {
        free(clist);
    }
    return res;
}


int main(int argc, char *argv[])
{
    UBYTE versiontag[] = VERSTAG;
    int res = EXIT_FAILURE;
    int opt;
    FILE *binary = NULL;

    if(1 >= argc)
    {
        Usage(argv[0]);
        goto on_error;
    }

    binary = fopen(argv[1], "rb");
    check(NULL != binary, "Unable to open clist binary file \"%s\"", argv[1]);

    res = DisassembleCopFile(binary);

on_error:
    if(NULL != binary)
    {
        fclose(binary);
    }
    return res;
}
