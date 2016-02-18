P1.out: Project1.o lexicalAnalyzer.o SetLimits.o
	g++ -o P1.out Project1.o lexicalAnalyzer.o SetLimits.o

Project1.o: Project1.cpp lexicalAnalyzer.h 
	g++ -c Project1.cpp -g

lexicalAnalyzer.o: lexicalAnalyzer.cpp lexicalAnalyzer.h
	g++ -c lexicalAnalyzer.cpp -g

SetLimits.o: SetLimits.cpp SetLimits.h
	g++ -c SetLimits.cpp -g

clean:	
	rm *.o P1.out




