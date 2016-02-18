p1.out: fewellP1.o lexicalAnalyzer.o
	g++ -o p1.out fewellP1.o lexicalAnalyzer.o

fewellP1.o: fewellP1.cpp lexicalAnalyzer.h 
	g++ -c fewellP1.cpp -g

lexicalAnalyzer.o: lexicalAnalyzer.cpp lexicalAnalyzer.h
	g++ -c lexicalAnalyzer.cpp -g

clean:	
	rm *.o p1.out

run: ./p1.out test1.in ./p1.out test2.in
	clear
	./p1.out test1.in
	./p1.out test2.in

