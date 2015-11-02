%.pml.run: %.pml
	spin -T $?

%.pml.verify: %.pml
	spin -a $<
	gcc -DMEMLIM=1024 -O2 -DXUSAFE -w -o pan pan.c
	./pan -m10000 -a

.PHONY: all clean

clean:
	rm pan* *.trail *.tmp pan
