#ifndef DECOP_H__
#define DECOP_H__

#include <exec/types.h>

#define COPPER_INST_SIZE 4

typedef struct _CopperMove {
    UWORD custom_reg;
    UWORD value;
} CopperMove;


typedef struct _CopperWait {
    UBYTE vert_pos;
    UBYTE horz_pos;
    UBYTE vert_mask;
    UBYTE horz_mask;
} CopperWait;


typedef union _CopperInst {
    UWORD words[2];
    ULONG longword;
    CopperMove move;
    CopperWait wait;
} CopperInst;


extern int DeCopInst(CopperInst *inst, char *output, int max_len);
extern BOOL DeCopList(APTR list, int list_len, char *out, int out_len);

#endif //DECOP_H__
