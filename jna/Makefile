.PHONY: all
all: JavaNativeAccess.class randomjna.so

.PHONY: run
run: all
	@java -cp .:./jna-4.1.0.jar JavaNativeAccess

randomjna.so: randomjna.c
	@gcc -shared -fpic -o librandomjna.so $<

JavaNativeAccess.class: JavaNativeAccess.java
	@javac -classpath ./jna-4.1.0.jar $<

.PHONY: clean
clean:
	rm -rf JavaNativeAccess.h *.class librandomjna.so 
