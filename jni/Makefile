.PHONY: all
all: JavaNativeInterface.class randomjni.so

.PHONY: run
run: all
	@java -Djava.library.path=. JavaNativeInterface

randomjni.so: randomjni.c JavaNativeInterface.h
	@gcc -shared -fpic -o librandomjni.so -I/usr/lib/jvm/java/include -I/usr/lib/jvm/java/include/linux $<

JavaNativeInterface.class: JavaNativeInterface.java
	@javac $<

JavaNativeInterface.h: JavaNativeInterface.class
	@javah -jni JavaNativeInterface

.PHONY: clean
clean:
	rm -rf *.h *.class librandomjni.so
