# DeCopper
Amiga CopperList reversing tool

Built with VBCC 0.9h and NDK3.2R4

## what's the point ?

When reversing Amiga demo or game, it displays copper instructions from binary block.


## usage
```
1.Files:Dev/C/Projets/DeCopper
> decopper                             
USAGE: decopper <clist file>
```

```
1.Files:Dev/C/Projets/DeCopper
> decopper tst.clist                             
Disassembled copperlist:
WAIT Vert:$96 mask:$FF  
WAIT Vert:$97 mask:$7F  BLT Finished
WAIT Vert:$97 mask:$FF  Horz:$20 mask:$0E  
WAIT Vert:$98 mask:$7F  Horz:$40 mask:$FE  BLT Finished
SKIP next if Vert>=$64 mask:$FF  
WAIT FOREVER
```

tst.clist:
```
Offset(d) 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
00000000  96 01 FF 00 97 01 7F 00 97 21 FF 0E 98 41 7F FE  –.ÿ.—...—!ÿ.˜A.þ
00000016  64 01 FF 01 FF FF FF FE 69 74 74 65 6E 3B 0A 20  d.ÿ.ÿÿÿþitten;. 
00000032  20 20 20 20 20 20 20 20 20 20 20 72 65 73 20 2B             res +
00000048  3D 20 77 72 69 74 74 65 6E 3B 0A                 = written;.
```

## use case

Disassemble an old Amiga game as a learning hobby.

### starting from the floppy
* use my read_track tool to extract the floppy bootblock
* use IRA (http://aminet.net/package/dev/asm/ira) to disassemble the code
* when you catch a copperlist,
  * locate it on the disk
  * extract the track
  * crop it with FileX (http://aminet.net/package/disk/moni/filex-2.4-amigaos)
  * analyze the resulting file with DeCropper

 ### starting from WinUAE debugger
 * start your game with WinUAE
 * go to the point you'd like to analyze
 * summon the debugger
 * locate and dump the current copperlist to a file
 * analyze with DeCropper


## ToDo
* Implement dedicated displayer for more registers
* Add verbose mode to give more precise information
* Improve after some practice with real games/demos copperlists
* Use of DeCopInst function as a comment generator for Amiga reversing tool project

## Example
```
1.Files:Dev/C/Projets/DeCopper
> decopper cracktro_clist_41846                             
Disassembled copperlist:
BPL1PTH = 0005
BPL1PTL = 6d78
BPL2PTH = 0005
BPL2PTL = 0000
BPL3PTH = 0005
BPL3PTL = 9c58
BPL4PTH = 0005
BPL4PTL = 1f40
BPL5PTH = 0005
BPL5PTL = cb38
BPL6PTH = 0005
BPL6PTL = 3e80
BPLCON0 = DEPTH=6 DBLPF 
BPLCON1 = PF1H=0 PF2H=0 
BPL1MOD = 0000
BPL2MOD = 0000
DDFSTRT = 0038
DDFSTOP = 00d0
BPLCON2 = PF1P=0 PF2P=0 
DIWSTRT = H=$81 V=$46 
DIWSTOP = H=$1c1 V=$ff 
SPR0PTH = 0000
SPR0PTL = 0000
SPR5PTH = 0006
SPR5PTL = 53f0
SPR6PTH = 0006
SPR6PTL = 5000
COLOR27 = R=5 G=5 B=5 
COLOR29 = R=9 G=9 B=9 
COLOR30 = R=12 G=12 B=12 
COLOR31 = R=7 G=7 B=7 
COLOR00 = R=0 G=0 B=0 
COLOR03 = R=15 G=0 B=0 
COLOR02 = R=12 G=0 B=0 
COLOR01 = R=10 G=0 B=0 
COLOR11 = R=14 G=0 B=0 
COLOR10 = R=11 G=0 B=0 
COLOR09 = R=9 G=0 B=0 
COLOR04 = R=15 G=0 B=15 
COLOR14 = R=15 G=0 B=0 
COLOR06 = R=10 G=0 B=0 
COLOR12 = R=5 G=8 B=15 
COLOR04 = R=0 G=0 B=15 
WAIT Vert:$46 mask:$FF  
COLOR04 = R=0 G=0 B=14 
WAIT Vert:$47 mask:$FF  
COLOR04 = R=0 G=0 B=13 
WAIT Vert:$48 mask:$FF  
COLOR04 = R=0 G=0 B=12 
WAIT Vert:$49 mask:$FF  
COLOR04 = R=0 G=0 B=11 
WAIT Vert:$4A mask:$FF  
COLOR04 = R=0 G=0 B=10 
WAIT Vert:$4B mask:$FF  
COLOR04 = R=0 G=0 B=9 
WAIT Vert:$4C mask:$FF  
COLOR04 = R=0 G=0 B=8 
WAIT Vert:$4D mask:$FF  
COLOR04 = R=0 G=0 B=7 
WAIT Vert:$4E mask:$FF  
COLOR04 = R=0 G=0 B=6 
WAIT Vert:$4F mask:$FF  
COLOR04 = R=0 G=0 B=5 
WAIT Vert:$50 mask:$FF  
COLOR04 = R=0 G=0 B=6 
WAIT Vert:$51 mask:$FF  
COLOR04 = R=0 G=0 B=7 
WAIT Vert:$52 mask:$FF  
COLOR04 = R=0 G=0 B=8 
WAIT Vert:$53 mask:$FF  
COLOR04 = R=0 G=0 B=9 
WAIT Vert:$54 mask:$FF  
COLOR04 = R=0 G=0 B=10 
WAIT Vert:$55 mask:$FF  
COLOR04 = R=0 G=0 B=11 
WAIT Vert:$56 mask:$FF  
COLOR04 = R=0 G=0 B=12 
WAIT Vert:$57 mask:$FF  
COLOR04 = R=0 G=0 B=13 
WAIT Vert:$58 mask:$FF  
COLOR04 = R=0 G=0 B=14 
WAIT Vert:$59 mask:$FF  
COLOR12 = R=0 G=0 B=15 
WAIT Vert:$EA mask:$FF  
COLOR12 = R=0 G=0 B=14 
WAIT Vert:$EB mask:$FF  
COLOR12 = R=0 G=0 B=13 
WAIT Vert:$EC mask:$FF  
COLOR12 = R=0 G=0 B=12 
WAIT Vert:$ED mask:$FF  
COLOR12 = R=0 G=0 B=11 
WAIT Vert:$EE mask:$FF  
COLOR12 = R=0 G=0 B=10 
WAIT Vert:$EF mask:$FF  
COLOR12 = R=0 G=0 B=9 
WAIT Vert:$F0 mask:$FF  
COLOR12 = R=0 G=0 B=8 
WAIT Vert:$F1 mask:$FF  
COLOR12 = R=0 G=0 B=7 
WAIT Vert:$F2 mask:$FF  
COLOR12 = R=0 G=0 B=6 
WAIT Vert:$F3 mask:$FF  
COLOR12 = R=0 G=0 B=5 
WAIT Vert:$F4 mask:$FF  
COLOR12 = R=0 G=0 B=6 
WAIT Vert:$F5 mask:$FF  
COLOR12 = R=0 G=0 B=7 
WAIT Vert:$F6 mask:$FF  
COLOR12 = R=0 G=0 B=8 
WAIT Vert:$F7 mask:$FF  
COLOR12 = R=0 G=0 B=9 
WAIT Vert:$F8 mask:$FF  
COLOR12 = R=0 G=0 B=10 
WAIT Vert:$F9 mask:$FF  
COLOR12 = R=0 G=0 B=11 
WAIT Vert:$FA mask:$FF  
COLOR12 = R=0 G=0 B=12 
WAIT Vert:$FB mask:$FF  
COLOR12 = R=0 G=0 B=13 
WAIT Vert:$FC mask:$FF  
COLOR12 = R=0 G=0 B=14 
WAIT Vert:$FD mask:$FF  
WAIT FOREVER
```
