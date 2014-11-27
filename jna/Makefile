ifeq ($(shell uname), Darwin)
	LIB_EXT=dylib
endif
ifeq ($(shell uname), Linux)
	LIB_EXT=so
endif

.PHONY: all
all: JavaNativeAccess.class randomjna.${LIB_EXT}

.PHONY: run
run: all
	@java -cp .:./jna-4.1.0.jar JavaNativeAccess

randomjna.${LIB_EXT}: randomjna.c
	@gcc -shared -fpic -o librandomjna.${LIB_EXT} $<

JavaNativeAccess.class: JavaNativeAccess.java
	@javac -classpath ./jna-4.1.0.jar $<

.PHONY: clean
clean:
	rm -rf JavaNativeAccess.h *.class librandomjna.${LIB_EXT} 
