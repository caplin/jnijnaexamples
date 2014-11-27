ifeq ($(shell uname), Darwin)
	LIB_EXT=dylib
endif
ifeq ($(shell uname), Linux)
	LIB_EXT=so
endif

.PHONY: all
all: JavaNativeInterface.class randomjni.${LIB_EXT}

.PHONY: run
run: all
	@java -Djava.library.path=. JavaNativeInterface

randomjni.${LIB_EXT}: randomjni.c JavaNativeInterface.h
	@gcc -shared -fpic -o librandomjni.${LIB_EXT} -I/usr/lib/jvm/java/include -I/usr/lib/jvm/java/include/linux -I${JAVA_HOME}/include -I${JAVA_HOME}/include/darwin $<

JavaNativeInterface.class: JavaNativeInterface.java
	@javac $<

JavaNativeInterface.h: JavaNativeInterface.class
	@javah -jni JavaNativeInterface

.PHONY: clean
clean:
	rm -rf *.h *.class librandomjni.${LIB_EXT}
