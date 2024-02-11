#include <exec/types.h>
#include "decop.h"
#include "copperlist.h"
#include <dbg/dbg.h>

typedef void (*RegInfoDisplayer)(UWORD value, char *vinfo);

typedef struct _RegisterInfo {
    int offset;
    char *label;
    RegInfoDisplayer displayer;
} RegisterInfo;

void bplcon0_display(UWORD value, char *vinfo)
{
    int depth = (value & 0x7000) >> 12;

    if(depth > 0)
        vinfo += sprintf(vinfo, "DEPTH=%d ", depth);

    if(F_HIRES & value)
        vinfo += sprintf(vinfo, "HIRES ");

    if(F_HOMOD & value)
        vinfo += sprintf(vinfo, "HOMOD ");

    if(F_DBLPF & value)
        vinfo += sprintf(vinfo, "DBLPF ");

    if(F_COLOR_ON & value)
        vinfo += sprintf(vinfo, "COLOR ");

    if(F_GAUD & value)
        vinfo += sprintf(vinfo, "GAUD ");

    if(F_LPEN & value)
        vinfo += sprintf(vinfo, "LPEN ");

    if(F_LACE & value)
        vinfo += sprintf(vinfo, "LACE ");

    if(F_ERSY & value)
        vinfo += sprintf(vinfo, "ERSY ");
}

void bplcon1_display(UWORD value, char *vinfo)
{
    vinfo += sprintf(vinfo, "PF1H=%d ", value & 0xf);
    vinfo += sprintf(vinfo, "PF2H=%d ", value >> 4);
}

void bplcon2_display(UWORD value, char *vinfo)
{
    if(F_PF2PRI & value)
        vinfo += sprintf(vinfo, "PF2PRI ");

    vinfo += sprintf(vinfo, "PF1P=%d ", value & 0x7);
    vinfo += sprintf(vinfo, "PF2P=%d ", (value >> 3) & 0x7);
}

void diwstrt_display(UWORD value, char *vinfo)
{
    vinfo += sprintf(vinfo, "H=$%02x V=$%02x ", value & 0xff, value >> 8);
}

void diwstop_display(UWORD value, char *vinfo)
{
    vinfo += sprintf(vinfo, "H=$%02x V=$%02x ", (value | 0x100) & 0x1ff, (value >> 8) | ((value & 0x80)?0:0x100));
}

void color_display(UWORD value, char *vinfo)
{
    vinfo += sprintf(vinfo, "R=%d G=%d B=%d ", value >> 8, (value >> 4) & 0xf, value & 0xf);
}


static RegisterInfo custom_regs[] = {
    {0x08E, "DIWSTRT", diwstrt_display},
    {0x090, "DIWSTOP", diwstop_display},
    {0x092, "DDFSTRT", NULL},
    {0x094, "DDFSTOP", NULL},
    {0x0E0, "BPL1PTH", NULL},
    {0x0E2, "BPL1PTL", NULL},
    {0x0E4, "BPL2PTH", NULL},
    {0x0E6, "BPL2PTL", NULL},
    {0x0E8, "BPL3PTH", NULL},
    {0x0EA, "BPL3PTL", NULL},
    {0x0EC, "BPL4PTH", NULL},
    {0x0EE, "BPL4PTL", NULL},
    {0x0F0, "BPL5PTH", NULL},
    {0x0F2, "BPL5PTL", NULL},
    {0x0F4, "BPL6PTH", NULL},
    {0x0F6, "BPL6PTL", NULL},
    {0x100, "BPLCON0", bplcon0_display},
    {0x102, "BPLCON1", bplcon1_display},
    {0x104, "BPLCON2", bplcon2_display},
    {0x108, "BPL1MOD", NULL},
    {0x10A, "BPL2MOD", NULL},
    {0x120, "SPR0PTH", NULL},
    {0x122, "SPR0PTL", NULL},
    {0x124, "SPR1PTH", NULL},
    {0x126, "SPR1PTL", NULL},
    {0x128, "SPR2PTH", NULL},
    {0x12A, "SPR2PTL", NULL},
    {0x12C, "SPR3PTH", NULL},
    {0x12E, "SPR3PTL", NULL},
    {0x130, "SPR4PTH", NULL},
    {0x132, "SPR4PTL", NULL},
    {0x134, "SPR5PTH", NULL},
    {0x136, "SPR5PTL", NULL},
    {0x138, "SPR6PTH", NULL},
    {0x13A, "SPR6PTL", NULL},
    {0x13C, "SPR7PTH", NULL},
    {0x13E, "SPR7PTL", NULL},
    {0x180, "COLOR00", color_display},
    {0x182, "COLOR01", color_display},
    {0x184, "COLOR02", color_display},
    {0x186, "COLOR03", color_display},
    {0x188, "COLOR04", color_display},
    {0x18A, "COLOR05", color_display},
    {0x18C, "COLOR06", color_display},
    {0x18E, "COLOR07", color_display},
    {0x190, "COLOR08", color_display},
    {0x192, "COLOR09", color_display},
    {0x194, "COLOR10", color_display},
    {0x196, "COLOR11", color_display},
    {0x198, "COLOR12", color_display},
    {0x19A, "COLOR13", color_display},
    {0x19C, "COLOR14", color_display},
    {0x19E, "COLOR15", color_display},
    {0x1A0, "COLOR16", color_display},
    {0x1A2, "COLOR17", color_display},
    {0x1A4, "COLOR18", color_display},
    {0x1A6, "COLOR19", color_display},
    {0x1A8, "COLOR20", color_display},
    {0x1AA, "COLOR21", color_display},
    {0x1AC, "COLOR22", color_display},
    {0x1AE, "COLOR23", color_display},
    {0x1B0, "COLOR24", color_display},
    {0x1B2, "COLOR25", color_display},
    {0x1B4, "COLOR26", color_display},
    {0x1B6, "COLOR27", color_display},
    {0x1B8, "COLOR28", color_display},
    {0x1BA, "COLOR29", color_display},
    {0x1BC, "COLOR30", color_display},
    {0x1BE, "COLOR31", color_display},
};


#define LABEL_LEN 8 + 1
#define INFO_LEN 128
#define SAFE_LEN 50

void GetRegLabelAndInfo(UWORD ofs, UWORD value, char *vlabel, char *vinfo)
{
    int len = sizeof(custom_regs) / sizeof(RegisterInfo);
    BOOL found = FALSE;
    RegisterInfo *reg = custom_regs;

    while(len > 0)
    {
        if(ofs == (UWORD)reg->offset)
        {
            found = TRUE;
            strncpy(vlabel, reg->label, LABEL_LEN - 1);
            if(ASSIGNED(reg->displayer))
            {
                reg->displayer(value, vinfo);
            }
            else
            {
                snprintf(vinfo, INFO_LEN, "%04hx", value);
            }
            break;
        }
        if(ofs < (UWORD)reg->offset)
            break;

        reg++;
        len--;
    }

    if(found == FALSE)
    {
        snprintf(vlabel, LABEL_LEN, "%04hx", ofs);
        snprintf(vinfo, INFO_LEN, "%04hx", value);
    }
}

#define F_BFD 1<<7
static int display_wait(CopperInst *inst, char *buf, int len)
{
    int res = 0;
    int written;
    BOOL blit_finished = FALSE;

    if(0xfffffffe == inst->longword)
    {
        res = snprintf(buf, len, "WAIT FOREVER");
    }
    else
    {
        written = snprintf(buf, len, "WAIT ");
        buf += written ;
        res = written;

        if(0x00 != inst->wait.vert_mask)
        {
            written = snprintf(buf, len - res, "Vert:$%02hhX mask:$%02hhX  ",
                            inst->wait.vert_pos,
                            inst->wait.vert_mask);
            buf += written;
            res += written;

            if(!(F_BFD & inst->wait.vert_mask))
            {
                blit_finished = TRUE;
            }
        }

        if(0x00 != inst->wait.horz_mask)
        {
            written = snprintf(buf, len - res, "Horz:$%02hhX mask:$%02hhX  ",
                            inst->wait.horz_pos & 0xfe,
                            inst->wait.horz_mask);
            buf += written;
            res += written;
        }

        if(blit_finished)
        {
            res += snprintf(buf, len - res, "BLT Finished");
        }
    }

    return res;
}


static int display_skip(CopperInst *inst, char *buf, int len)
{
    int res = 0;
    int written;
    BOOL blit_finished = FALSE;

    written = snprintf(buf, len, "SKIP next if ");
    buf += written ;
    res = written;

    if(0x00 != inst->wait.vert_mask)
    {
        written = snprintf(buf, len - res, "Vert>=$%02hhX mask:$%02hhX  ",
                        inst->wait.vert_pos,
                        inst->wait.vert_mask);
        buf += written;
        res += written;
    }

    if(0x01 != inst->wait.horz_mask)
    {
        written = snprintf(buf, len - res, "Horz>=$%02hhX mask:$%02hhX  ",
                        inst->wait.horz_pos & 0xfe,
                        inst->wait.horz_mask);
        buf += written;
        res += written;
    }

    return res;
}


int DeCopInst(CopperInst *inst, char *output, int max_len)
{
    int written = 0;
    char reg_label[LABEL_LEN];
    char value_info[INFO_LEN];
    reg_label[LABEL_LEN - 1] = '\0';
    check(ASSIGNED(inst), "NULL instruction pointer");
    check(ASSIGNED(output), "NULL output buffer");

    /*
        MOVE: 0 x
        WAIT: 1 0
        SKIP: 1 1
    */

    if((inst->words[0] & 1) == 0) // move
    {
        GetRegLabelAndInfo(inst->move.custom_reg, inst->move.value, reg_label, value_info);
        written = snprintf(output, max_len, "%s = %s",
                           reg_label, value_info);
    }
    else if((inst->words[1] & 1) == 0) // wait
    {
        written += display_wait(inst, output, max_len);
    }
    else // skip
    {
        written += display_skip(inst, output, max_len);
    }

on_error:
    return written;
}


BOOL DeCopList(APTR list, int list_len, char *out, int out_len)
{
    BOOL res = FALSE;
    CopperInst *inst;
    char *cur_buf = out;
    int written;
    int remaining = out_len;

    check(ASSIGNED(list), "NULL copperlist pointer");
    inst = (CopperInst *)list;

    while((list_len >= COPPER_INST_SIZE) && (SAFE_LEN <= remaining))
    {
        written = DeCopInst(inst, cur_buf, remaining - 1);
        cur_buf += written;
        *cur_buf++ = '\n';
        remaining -= written + 1;
        if(inst->longword == 0xfffffffe)
            break;
        inst++;
        list_len -= COPPER_INST_SIZE;
    }
    *cur_buf = '\0';

    res = TRUE;

on_error:
    return res;
}

