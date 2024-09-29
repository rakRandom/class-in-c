default:
	gcc ../src/*.c -o main -I ../include/ -L ../lib/

test:
	gcc ../src/*.c -o test -I ../include/ -L ../lib/
	.\test.exe
	rm .\test.exe

release:
	gcc ../src/*.c -o class -O3 -I ../include/ -L ../lib/
