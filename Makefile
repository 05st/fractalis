CFLAGS = -std=c++20 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

Fractalis: main.cpp
	g++ $(CFLAGS) -o Fractalis main.cpp $(LDFLAGS)

test: Fractalis
	./Fractalis

clean:
	rm -f Fractalis
