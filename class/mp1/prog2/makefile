PLNOBJS = plntest.o plane.o list.o object.o material.o\
          vector.o pixel.o rayfuns.o image.o camera.o 

SPHOBJS = sphtest.o sphere.o list.o object.o material.o\
          vector.o pixel.o rayfuns.o image.o camera.o 

INCLUDE = ray.h rayhdrs.h pixel.h vector.h rayfuns.h
CFLAGS  =

plntest: $(PLNOBJS)
	gcc -Wall -o plntest -g $(PLNOBJS) -lm
sphtest: $(SPHOBJS)
	gcc -Wall -o sphtest -g $(SPHOBJS) -lm

.c.o: $<
	-gcc -c -Wall $(CFLAGS) -c -g $<  2> $(@:.o=.err)
	cat $*.err

clean:
	rm *.o  *.err

