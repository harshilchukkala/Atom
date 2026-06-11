app:
	g++ main.cpp Atom.cpp -lraylib -lm -o atom && ./atom

clean:
	rm -f atom