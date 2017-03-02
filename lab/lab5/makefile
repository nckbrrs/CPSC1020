OBJS =    vector.o list.o  pixel.o rayfuns.o \
          material.o object.o sphere.o 

SPHOBJS = $(OBJS) sphtest.o

INCLUDE = ray.h rayhdrs.h rayfuns.h vector.h

CFLAGS = -DAA_SAMPLES=1
# -DDBG_PIX -DDBG_HIT -DDBG_DRGB
# -DDBG_PIX -DDBG_DRGB
# -DSOFT_SHADOWS

sphtest: $(SPHOBJS) 
	gcc -Wall -o sphtest -g -pg $(SPHOBJS) -lm

$(RAYOBJS): $(INCLUDE) makefile

.c.o: $<
	-gcc -c -Wall $(CFLAGS) -c -g $<  2> $(@:.o=.err)
	cat $*.err

clean:
	rm *.o  *.err

