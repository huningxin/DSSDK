PREFIX = $(DESTDIR)/opt/depthsense
BINDIR = $(PREFIX)/bin
LIBDIR = $(PREFIX)/lib

all: ConsoleDemo
 
ConsoleDemo:
	gcc -o ConsoleDemo samples/ConsoleDemo/ConsoleDemo.cxx -Iinclude -Llib -lDepthSense -lDepthSensePlugins -lturbojpeg

install: ConsoleDemo
	mkdir -p $(BINDIR)
	mkdir -p $(LIBDIR)
	install -D ConsoleDemo $(BINDIR)/ConsoleDemo
	cp -r bin/* $(BINDIR)
	cp -r lib/* $(LIBDIR)
  
uninstall:
	rm -rf $(PREFIX)
 
 
clean:
	rm -f ConsoleDemo samples/ConsoleDemo/ConsoleDemo.o
 
distclean: clean
 

.PHONY : all install uninstall clean distclean
