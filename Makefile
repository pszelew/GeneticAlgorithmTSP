IDIR=include
FLAGS=-O2

solution: tests/Test program

program : obj/main.o obj/DataLoader.o obj/Population.o obj/Task.o obj/Greedy.o obj/GA.o
	g++ -g $(FLAGS) -o program obj/main.o obj/DataLoader.o obj/Population.o obj/Task.o obj/Greedy.o obj/GA.o

tests/Test : obj/Test.o obj/Greedy.o obj/DataLoader.o obj/Task.o obj/Population.o obj/GA.o 
	g++ $(FLAGS) -o tests/Test obj/Test.o obj/Greedy.o obj/DataLoader.o obj/Task.o obj/Population.o obj/GA.o -I $(IDIR) -lboost_unit_test_framework

obj/Test.o : tests/Test.cpp include/Greedy.hh include/DataLoader.hh include/Population.hh include/GA.hh
	g++ $(FLAGS) -o obj/Test.o -c tests/Test.cpp -I $(IDIR)

obj/main.o : src/main.cpp include/DataLoader.hh include/Population.hh include/Greedy.hh
	g++ $(FLAGS) -o obj/main.o -c src/main.cpp -I $(IDIR)

obj/GA.o : src/GA.cpp include/GA.hh include/Population.hh include/Task.hh
	g++ $(FLAGS) -o obj/GA.o -c src/GA.cpp -I $(IDIR)

obj/Greedy.o : src/Greedy.cpp include/Greedy.hh include/Task.hh
	g++ $(FLAGS) -o obj/Greedy.o -c src/Greedy.cpp -I $(IDIR)

obj/Population.o : src/Population.cpp include/Population.hh
	g++ $(FLAGS) -o obj/Population.o -c src/Population.cpp -I $(IDIR)

obj/DataLoader.o : src/DataLoader.cpp include/DataLoader.hh include/Task.hh
	g++ $(FLAGS) -o obj/DataLoader.o -c src/DataLoader.cpp -I $(IDIR)

obj/Task.o : src/Task.cpp include/Task.hh
	g++ $(FLAGS) -o obj/Task.o -c src/Task.cpp -I $(IDIR)

clean :
	rm program obj/main.o obj/DataLoader.o obj/Population.o obj/Task.o obj/Greedy.o tests/Test obj/Test.o obj/GA.o
