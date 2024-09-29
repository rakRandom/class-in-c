default:
	gcc ../src/*.c -o main -I ../include/ -L ../lib/

test:
	gcc ../src/*.c -o main -I ../include/ -L ../lib/
	.\main
	rm main.exe

release:
	gcc ../src/*.c -o class -O3 -I ../include/ -L ../lib/
