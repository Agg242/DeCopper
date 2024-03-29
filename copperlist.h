#ifndef COPPERLIST_H__
#define COPPERLIST_H__

#include <exec/types.h>

// instructions macros
#define COP_MOVE(addr, data) (addr), (data)
#define COP_WAIT(VPos, HPos, VMask, HMask, BFD) (UBYTE)(VPos)<<8 | (UBYTE)(HPos) | 1, (UBYTE)((VMask & (~0x80)) | (((BFD) & 0x1) << 7))<<8 | (UBYTE)(HMask) & (UBYTE)(~0x0001)
#define COP_WAIT_END 0xffff, 0xfffe
#define COP_SKIP(VPos, HPos, VMask, HMask, BFD) (UBYTE)(VPos)<<8 | (UBYTE)(HPos) | 1, (UBYTE)((VMask & (~0x80)) | (((BFD) & 0x1) << 7))<<8 | (UBYTE)(HMask) | (UBYTE)0x0001


// registers offsets
#define BLTDDAT       0x000
#define DMACONR       0x002
#define VPOSR         0x004
#define VHPOSR        0x006

#define DIWSTRT       0x08e
#define DIWSTOP       0x090
#define DDFSTRT       0x092
#define DDFSTOP       0x094
#define DMACON        0x096
#define BPL1PTH       0x0e0
#define BPL1PTL       0x0e2
#define BPL2PTH       0x0e4
#define BPL2PTL       0x0e6
#define BPL3PTH       0x0e8
#define BPL3PTL       0x0ea
#define BPL4PTH       0x0ec
#define BPL4PTL       0x0ee
#define BPL5PTH       0x0f0
#define BPL5PTL       0x0f2
#define BPL6PTH       0x0f4
#define BPL6PTL       0x0f6

#define BPLCON0       0x100
#define BPLCON1       0x102
#define BPLCON2       0x104
#define BPLCON3       0x106
#define BPL1MOD       0x108
#define BPL2MOD       0x10a
#define SPR0PTH       0x120
#define SPR0PTL       0x122
#define SPR1PTH       0x124
#define SPR1PTL       0x126
#define SPR2PTH       0x128
#define SPR2PTL       0x12a
#define SPR3PTH       0x12c
#define SPR3PTL       0x12e
#define SPR4PTH       0x130
#define SPR4PTL       0x132
#define SPR5PTH       0x134
#define SPR5PTL       0x136
#define SPR6PTH       0x138
#define SPR6PTL       0x13a
#define SPR7PTH       0x13c
#define SPR7PTL       0x13e

#define COLOR00       0x180
#define COLOR01       0x182
#define COLOR02       0x184
#define COLOR03       0x186
#define COLOR04       0x188
#define COLOR05       0x18a
#define COLOR06       0x18c
#define COLOR07       0x18e
#define COLOR08       0x190
#define COLOR09       0x192
#define COLOR10       0x194
#define COLOR11       0x196
#define COLOR12       0x198
#define COLOR13       0x19a
#define COLOR14       0x19c
#define COLOR15       0x19e
#define COLOR16       0x1a0
#define COLOR17       0x1a2
#define COLOR18       0x1a4
#define COLOR19       0x1a6
#define COLOR20       0x1a8
#define COLOR21       0x1aa
#define COLOR22       0x1ac
#define COLOR23       0x1ae
#define COLOR24       0x1b0
#define COLOR25       0x1b2
#define COLOR26       0x1b4
#define COLOR27       0x1b6
#define COLOR28       0x1b8
#define COLOR29       0x1ba
#define COLOR30       0x1bc
#define COLOR31       0x1be

#define FMODE         0x1fc


/******* Bits *******/
// DMACON
#define B_SPREN 5

#define F_SPREN (1<<B_SPREN)

// BPLCON0
#define B_BFU0      12

#define F_HIRES     (1<<15)
#define F_HOMOD     (1<<11)
#define F_DBLPF     (1<<10)
#define F_COLOR_ON  (1<<9)
#define F_GAUD      (1<<8)
#define F_LPEN      (1<<3)
#define F_LACE      (1<<2)
#define F_ERSY      (1<<1)
#define F_BFU0      (1<<B_BFU0)

//BPLCON2
#define F_PF2PRI    (1<<6)


// various colors
#define BLACK  0x0000
#define RED    0x0f00
#define YELLOW 0X0ff0
#define WHITE  0x0fff


#define MAX_PAL_LINES 312
#define FIRST_SCREEN_LINE 0x2c
#define LAST_PAL_SCREEN_LINE ((FIRST_SCREEN_LINE + 256) & 0xff) // i'd rather add 255...
#define LAST_NTSC_SCREEN_LINE (FIRST_SCREEN_LINE + 200) // i'd rather add 199...
#define FIRST_PIXEL 0x81
#define LAST_LORES_PIXEL 0xc1
#define DIWSTRT_VALUE      ((FIRST_SCREEN_LINE << 8) | FIRST_PIXEL)
#define DIWSTOP_VALUE_PAL  ((LAST_PAL_SCREEN_LINE << 8) | LAST_LORES_PIXEL)
#define DIWSTOP_VALUE_NTSC ((LAST_NTSC_SCREEN_LINE << 8) | LAST_LORES_PIXEL)


#define STD_DDFSTRT 0x38
#define STD_DDFSTOP 0xd0

#endif
