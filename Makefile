all:
	msp430-gcc -Os -mmcu=msp430g2553 radioAm.c -o radioAm.elf -w
	sudo mspdebug rf2500 "prog radioAm.elf"
comp:
	msp430-gcc -Os -mmcu=msp430g2553 radioAm.c -o radioAm.elf -w
prog:
	sudo mspdebug rf2500 "prog radioAm.elf"
debug:
	sudo mspdebug rf2500