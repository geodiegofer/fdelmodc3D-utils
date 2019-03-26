#master makefile for OpenSource MYUTILS
#adapted from Thorbecke's OpenSource main Makefile

MAKE="make"

all: mkdirs 
	cd bin2su		; $(MAKE)
	cd twoD_to_twoHalfD	; $(MAKE) 
	cd vel2rho		; $(MAKE) 

mkdirs:
	-mkdir -p bin

clean:
	cd bin2su		; $(MAKE) $@
	cd twoD_to_twoHalfD	; $(MAKE) $@
	cd vel2rho		; $(MAKE) $@

