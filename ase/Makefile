%.pml.run: %.pml
	~/Downloads/spin -T $?

verify: p4.pml
	spin -a $<
	gcc -DSAFETY -o pan pan.c
	./pan

.PHONY: all clean

clean:
	rm pan* *.trail pan
