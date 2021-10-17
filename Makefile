SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard src/*.h)
INCLUDES = $(wildcard /usr/share/include/)

INCLUDE_PARAMS = $(foreach d, $(INCLUDES), -I$d)

CFLAGS = -std=c++20
LDFLAGS = -lglfw -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

Fractalis:
	g++ $(CFLAGS) -o Fractalis glad.c $(SOURCES) $(HEADERS) $(LDFLAGS) $(INCLUDE_PARAMS)

run: Fractalis
	./Fractalis

clean:
	rm -f Fractalis
