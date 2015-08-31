MAIN = WordCount
JAR = wc.jar
INPUT_DIR = input
OUTPUT_DIR = output

all:
	hadoop com.sun.tools.javac.Main WordCount.java
	jar cf wc.jar WordCount*.class

run: clean_output
	hadoop jar $(JAR) $(MAIN) $(INPUT_DIR) $(OUTPUT_DIR)
	cat $(OUTPUT_DIR)/*

clean_output:
	rm -rf $(OUTPUT_DIR)

clean: clean_output
	rm -rf *.class *.jar
