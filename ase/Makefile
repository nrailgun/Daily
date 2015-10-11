%.pml.run: %.pml
	spin -T $?

verify: ns-2.pml
	spin -a $<
	#gcc -DSAFETY -o pan pan.c
	gcc -o pan pan.c
	./pan

.PHONY: all clean

clean:
	rm pan* *.trail *.tmp pan
