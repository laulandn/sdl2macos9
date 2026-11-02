
all:
#	make -C dummy_dir -f Makefile
#	make -C macos8addons -f Makefile
	make -C SDL-main -f Makefile
	
clean:
#	make -C __debugbreak -f Makefile clean
#	make -C dummy_atomic -f Makefile clean
#	make -C dummy_dir -f Makefile clean
#	make -C dummy_image -f Makefile clean
#	make -C dummy_pthreads -f Makefile clean
#	make -C mytests -f Makefile clean
#	make -C macos8addons -f Makefile clean
	make -C SDL-main -f Makefile clean
	rm -f */*.o */*.a
