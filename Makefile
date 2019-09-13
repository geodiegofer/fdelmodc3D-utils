#master makefile for OpenSource MYUTILS
#adapted from Thorbecke's OpenSource main Makefile

MAKE="make"

all: mkdirs chmods
	cd bin2su		; $(MAKE)
	cd twoD_to_twoHalfD	; $(MAKE) 
	cd vel2rho		; $(MAKE) 
	cd mysurange	; $(MAKE)

mkdirs:
	-mkdir -p bin

chmods:
	cd bin; chmod +x *.sh

clean:
	cd bin2su		; $(MAKE) $@
	cd twoD_to_twoHalfD	; $(MAKE) $@
	cd vel2rho		; $(MAKE) $@
	cd mysurange		; $(MAKE) $@
	rm -f bin/*.exe
