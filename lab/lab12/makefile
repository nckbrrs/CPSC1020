a.out: main.o vec.o vec.h
	g++ -g main.o vec.o  -lm

.cpp.o: $<  vec.h vec.cpp main.cpp
	g++ -c -Wall -g  $<  2> $(@:.o=.err)
	cat $(@:.o=.err)

clean:
	rm *.err *.o
