# Libblitter.library

AmigaOS4.1 SDK, there is struct custum, we should able point this to memory, 
and run doBlitter() function to trigger blitter. 

Blitter.c comes from UAE, so we keep the same copyrights.
Header files should be considered LGPL,
Because its GPL2 all changes so to contributed back source code, and be kept open source.
however we most like do stuff to blitter.c that makes it unwonted in UAE again, it will fork of in its own direction.

We don’t wont clock cycle bloat, we don’t need to schedule anything etc,
and do not need setters and getters for memory accesses.
