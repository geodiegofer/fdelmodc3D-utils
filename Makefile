#master makefile for OpenSource MYUTILS
#adapted from Thorbecke's OpenSource main Makefile

MAKE=make

all: mkdirs install chmods

install:
	cd bin2su		; $(MAKE)
	cd twoD_to_twoHalfD	; $(MAKE) 
	cd vel2rho		; $(MAKE) 
	cd mysurange	; $(MAKE)
	cd plot3dSliceSnaps; $(MAKE)
	cd rmserr; $(MAKE)
	sh put_bashrc.sh $@

mkdirs:
	-mkdir -p bin

chmods:
	cd bin; chmod +x *.sh

clean:
	sh put_bashrc.sh uninstall
	cd bin2su		; make clean
	cd twoD_to_twoHalfD	; make clean
	cd vel2rho		; make clean
	cd mysurange		; make clean
	cd plot3dSliceSnaps; make clean
	cd rmserr; make clean
	rm -f bin/*.exe
