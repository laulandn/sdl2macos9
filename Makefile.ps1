
all:
	make -C psxaddons -fMakefile.ps1 lib
	make -C Baselibc -fMakefile.ps1 lib
	make -C SDL-main -fMakefile.ps1
	cp -rf */*.a SDL-main/include .
	
clean:
	make -C SDL-main -fMakefile.ps1 clean
	rm -rf */*.o */*.a *.a include