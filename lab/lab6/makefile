hittest: main.o model.o plane.o raytrace.o material.o object.o\
         vector.o list.o pixel.o
	gcc -Wall -g -o hittest *.o -lm

.c.o: $<
	-gcc -c -Wall -c -g $<  2> $(@:.o=.err)
	cat $*.err

clean:
	rm *.err *.o
