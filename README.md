# Libblitter.library

AmigaOS4.1 SDK, there is struct custum, declare it a local variable. 
and run doBlitter() function to trigger blitter, as the last thing you do.

This project is based on Peter Gordon, blitzen v0.3, 
during test, it has proven to work pretty well.

This project is now Freeware, as defined by Peter Gordon.

(first this project tried to use UAE code, but it was 
over complicated for this library, and I did not get it to work correct.)

I also speculated about wring my own from ground up, but it probably be west of time.
I hope to be forgiven :-)

this how you use it.

Exsample.

  ;insted of A6 pointing to $DFF0000, 
  ;you point it some memory, you have allocated.

move.l #$09F0000,BLTCON0(a6)
move.l #$FFFFFFFF,BLTAFWM(a6)
move.l #Font,BLTAPTH(a6)
move.l #screen,BLTDPTH(a6)
move.w #FontBpl-4,BLTAMOD(a6)
move.w #ScrBpl-4,BLTDMOD(a6)
move.w #20*64+4+2,BLTSIZE(a6)

  ;Setting BLTSIZE should start blitter, but nothing happens, because no chipset is used,
  ;so we call doBlitter, do blitter takes A6 as first and only argument.
  
lea libBlitter(pc),a1
jsr doBlitter(a1)

