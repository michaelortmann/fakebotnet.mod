# Makefile for src/mod/fakebotnet.mod/

srcdir = .
MY_NAME = fakebotnet

doofus:
	@echo ""
	@echo "Let's try this from the right directory..."
	@echo ""
	@cd ../../../ && make

static: ../${MY_NAME}.o

modules: ../../../${MY_NAME}.$(MOD_EXT)

../${MY_NAME}.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -DMAKING_MODS -c $(srcdir)/${MY_NAME}.c
	@rm -f ../${MY_NAME}.o
	mv ${MY_NAME}.o ../

../../../${MY_NAME}.$(MOD_EXT): ../${MY_NAME}.o
	$(LD) -o ../../../${MY_NAME}.$(MOD_EXT) ../${MY_NAME}.o ${XLIBS}
	$(STRIP) ../../../${MY_NAME}.$(MOD_EXT)

depend:
	$(CC) $(CFLAGS) $(CPPFLAGS) -MM $(srcdir)/${MY_NAME}.c > .depend

clean:
	@rm -f .depend *.o *.$(MOD_EXT) *~
distclean: clean

#safety hash
../${MY_NAME}.o: .././${MY_NAME}.mod/${MY_NAME}.c ../../../src/mod/module.h \
 ../../../src/main.h ../../../src/lang.h ../../../src/eggdrop.h \
 ../../../src/flags.h ../../../src/proto.h ../../../lush.h \
 ../../../src/misc_file.h ../../../src/cmdt.h ../../../src/tclegg.h \
 ../../../src/tclhash.h ../../../src/chan.h ../../../src/users.h \
 ../../../src/compat/compat.h ../../../src/compat/inet_aton.h \
 ../../../src/compat/snprintf.h ../../../src/compat/memset.h \
 ../../../src/compat/memcpy.h ../../../src/compat/strcasecmp.h \
 ../../../src/mod/modvals.h ../../../src/tandem.h
