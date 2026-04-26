main.test: main.o calc.o token.o fullbuild_collections.o
	cc main.o calc.o token.o fullbuild_collections.o -lm -o main.test
main.o: ../main.c ../token/token.h ../collections/collections.h
	cc ../main.c -c main.o
calc.o: ../calc.c ../token/token.h ../collections/collections.h
	cc ../calc.c -c calc.o


token.test: tokentest.o token.o
	cc tokentest.o token.o -lm -o token.test
tokentest.o: tokentest.c ../token/token.h
	cc tokentest.c -c tokentest.o

collections.test: collectionstest.o fullbuild_collections.o
	cc collectionstest.o fullbuild_collections.o -o collections.test
collectionstest.o: collectionstest.c ../collections/collections.h
	cc collectionstest.c -c collectionstest.o


token.o: ../token/token.c
	cc ../token/token.c -c token.o

fullbuild_collections.o: collections.o circular_list.o
	cc collections.o circular_list.o -nostdlib -r -o fullbuild_collections.o
collections.o: ../collections/collections.c ../collections/circular_list.h
	cc ../collections/collections.c -c collections.o
circular_list.o: ../collections/circular_list.c
	cc ../collections/circular_list.c -c circular_list.o


clean:
	rm *.o; rm *.test
	
