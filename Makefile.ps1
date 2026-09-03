
all:
	make -C psxaddons -fMakefile.ps1 lib
	make -C Baselibc -fMakefile.ps1 lib
	make -C SDL-main -fMakefile.ps1
	
clean:
	make -C SDL-main -fMakefile.ps1 clean
	rm -f */*.o */*/*.o */*.a
