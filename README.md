# Libblitter.library

AmigaOS4.1 SDK, there is struct custum, we should able point this to memory, 
and run doBlitter() function to trigger blitter. 

Blitter.c comes from UAE, so we keep the same copyrights.
Header files should be considered LGPL,
Because its GPL2 all changes so to contributed back source code, and be kept open source.
however we most like do stuff to blitter.c that makes it unwonted in UAE again, it will fork of in its own direction.

We don’t wont clock cycle bloat, we don’t need to schedule anything etc,
and do not need setters and getters for memory accesses.

Who is this for, well it is for developers, its not for users, it won’t make your 25-year-old game or
program work without change automagically, changes will need to be made to your old programs/games and demos, in order for it to work?

first of all there is no chipset on 0xDFF000, you need allocate memory as large as the chipset,
because its memory, nothing will auto magically happen, you now need to Tigger code manually.

