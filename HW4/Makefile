# Java compiler and flags
JAVAC = javac
JFLAGS = -g

# Source files
SOURCES = BoundedBuffer.java Consumer.java Producer.java ProducerConsumer.java

# Output class files
CLASSES = $(SOURCES:.java=.class)

# Zip file name
ZIP_FILE = Travis-Barkley-HW4.zip

# Default target: Build all classes
all: $(CLASSES)

# Compile .java files to .class files
%.class: %.java
	$(JAVAC) $(JFLAGS) $<

# Clean all generated files
clean:
	rm -f $(CLASSES) $(ZIP_FILE)

# Package all required files into a .zip archive
package:
	zip -r Travis-Barkley-HW4.zip Producer.java Consumer.java BoundedBuffer.java ProducerConsumer.java Makefile README.txt

.PHONY: all clean package
