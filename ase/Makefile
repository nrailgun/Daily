%.pml.run: %.pml
	spin -T $?

verify: dining-3.pml
	spin -a $<
	gcc -DSAFETY -o pan pan.c
	./pan

.PHONY: all clean

clean:
	rm pan* *.trail *.tmp pan
