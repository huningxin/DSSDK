all: ConsoleDemo
 
ConsoleDemo:
	gcc -o ConsoleDemo samples/ConsoleDemo/ConsoleDemo.cxx -Iinclude -Llib -lDepthSense -lDepthSensePlugins -lturbojpeg

install: ConsoleDemo
	mkdir -p /opt/depthsense/bin/
	install -D ConsoleDemo /opt/depthsense/bin/ConsoleDemo
	cp -r bin/* /opt/depthsense/bin/
	mkdir -p /opt/depthsense/lib/
	cp -r lib/* /opt/depthsense/lib/
  
uninstall:
	rm -rf /opt/depthsense
 
 
clean:
	rm -f ConsoleDemo samples/ConsoleDemo/ConsoleDemo.o
 
distclean: clean
 

.PHONY : all install uninstall clean distclean