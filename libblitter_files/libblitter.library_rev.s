VERSION = 53
REVISION = 1

.macro DATE
.ascii "11.8.2021"
.endm

.macro VERS
.ascii "libblitter.library 53.1"
.endm

.macro VSTRING
.ascii "libblitter.library 53.1 (11.8.2021)"
.byte 13,10,0
.endm

.macro VERSTAG
.byte 0
.ascii "$VER: libblitter.library 53.1 (11.8.2021)"
.byte 0
.endm
