# Libblitter.library

AmigaOS4.1 SDK, there is struct custum, we should able point this to memory, 
and run doBlitter() function to trigger blitter. 

Blitter.c comes from UAE, so we keep the same copyright (GPL2).

Auto generated header files should be considered LGPL. 
(Keeping same license is only meant for "programs" as stated in the GPL2 License, not libraries, we don’t won’t limit the libraries use by enforcing strict GPL2 policy,
Scope the GPL2 license is the library, it does apply to other program that might wont to use it, or the OS it runs on :-) )

Because it GPL2 you have right change/modify as you like, you have right distributed, and sell it, provided include licensee, and keep any changed open source.

this code will fork of in its own direction.

We don’t wont clock cycle bloat, we don’t need to schedule anything etc,
and do not need setters and getters for memory accesses.

Who is this for, well it is for developers, its not for users, it won’t make your 25-year-old game or
program work without change automagically, changes will need to be made to your old programs/games and demos, in order for it to work?

First of all there is no chipset on 0xDFF000, you need allocate memory as large as the chipset,
because its memory, nothing will auto magically happen, you now need to Tigger code manually.

