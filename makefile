enigma: main.o enigma.o error_handler.o data_handler.o
	g++ -g main.o enigma.o error_handler.o data_handler.o -o enigma

main.o: main.cpp enigma.h error_handler.h errors.h
	g++ -Wall -g -c main.cpp

enigma.o: enigma.cpp enigma.h error_handler.h data_handler.h
	g++ -Wall -g -c enigma.cpp

error_handler.o: error_handler.cpp enigma.h error_handler.h errors.h data_handler.h
	g++ -Wall -g -c error_handler.cpp

data_handler.o: data_handler.cpp enigma.h error_handler.h errors.h
	g++ -Wall -g -c data_handler.cpp

clean:
	rm -f *.o enigma

