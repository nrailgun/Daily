MAIN = src/Main
JAR = a.jar
INPUT_DIR = input
OUTPUT_DIR = output

# Using `hadoop com.sun.tools.javac.Main $(MAIN).java', but I prefer keep it simple.
# Not a good idea set CLASSPATH env variable, but, works now.
$(JAR): $(MAIN).java
	javac -d build/classes $(MAIN).java
	#jar cf $(JAR) $(MAIN)*.class

run: $(JAR) clean_output
	hadoop jar $(JAR) $(MAIN) $(INPUT_DIR) $(OUTPUT_DIR)
	cat $(OUTPUT_DIR)/*

clean_output:
	rm -rf $(OUTPUT_DIR)

clean: clean_output
	rm -rf build/classes/*
