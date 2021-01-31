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
fakebotnet.o: .././fakebotnet.mod/fakebotnet.c ../../../src/mod/module.h \
 ../../../src/main.h ../../../config.h ../../../eggint.h ../../../lush.h \
 ../../../src/lang.h ../../../src/eggdrop.h ../../../src/compat/in6.h \
 ../../../src/flags.h ../../../src/cmdt.h ../../../src/tclegg.h \
 ../../../src/tclhash.h ../../../src/chan.h ../../../src/users.h \
 ../../../src/compat/compat.h ../../../src/compat/base64.h \
 ../../../src/compat/inet_aton.h ../../../src/compat/snprintf.h \
 ../../../src/compat/gethostbyname2.h \
 ../../../src/compat/explicit_bzero.h ../../../src/compat/strlcpy.h \
 ../../../src/mod/modvals.h ../../../src/tandem.h
