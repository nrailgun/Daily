MAIN = Main
JAR = a.jar
INPUT_DIR = input
OUTPUT_DIR = output

$(JAR): $(MAIN).java
	hadoop com.sun.tools.javac.Main $(MAIN).java
	jar cf $(JAR) $(MAIN)*.class

run: $(JAR) clean_output
	hadoop jar $(JAR) $(MAIN) $(INPUT_DIR) $(OUTPUT_DIR)
	cat $(OUTPUT_DIR)/*

clean_output:
	rm -rf $(OUTPUT_DIR)

clean: clean_output
	rm -rf *.class *.jar
