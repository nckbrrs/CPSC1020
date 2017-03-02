RAYOBJS = camera.o image.o list.o main.o material.o model.o object.o pixel.o \
			plane.o rayfuns.o sphere.o vector.o raytrace.o tplane.o
		
INCLUDE =  list.h pixel.h rayfuns.h ray.h rayhdrs.h vector.h

ray: $(RAYOBJS)
	gcc -Wall -g -o ray $(RAYOBJS) -lm

$(RAYOBJS): $( INCLUDE) makefile

.c.o: $<
	-gcc -c -Wall -c -g $<  2> $(@:.o=.err)
	cat $*.err

clean:
	rm *.o  *.err

