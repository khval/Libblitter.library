VERSION		EQU	1
REVISION	EQU	1

DATE	MACRO
		dc.b '11.8.2021'
		ENDM

VERS	MACRO
		dc.b 'libblitter.library 1.1'
		ENDM

VSTRING	MACRO
		dc.b 'libblitter.library 1.1 (11.8.2021)',13,10,0
		ENDM

VERSTAG	MACRO
		dc.b 0,'$VER: libblitter.library 1.1 (11.8.2021)',0
		ENDM
