CC = g++
CFLAGS = -Wall -DGLX_GLXEXT_PROTOTYPES -DGL_GLEXT_PROTOTYPES -DSPHERE_PARTICLE_RENDER -DPARTICLE_SCALE=0.4 -DPARTICLE_VECTOR_SCALE=0.85
RELEASE_FLAGS = -O2
DEBUG_FLAGS = -O0 -g
LFLAGS = -lm -lGL -lGLU -lGLEW `pkg-config gtkmm-2.4 --cflags --libs` `pkg-config gtkglextmm-1.2 --cflags --libs` -lpthread
SOURCE_DIRS = $(shell find src -type d)
CPP_SOURCES = $(wildcard $(addsuffix /*.cpp, $(SOURCE_DIRS)))
RELEASE_OBJECTS = $(patsubst src/%.cpp, obj/release/%.o, $(CPP_SOURCES))
DEBUG_OBJECTS = $(patsubst src/%.cpp, obj/debug/%.o, $(CPP_SOURCES))
OBJECT_DIRS = obj $(dir $(RELEASE_OBJECTS) $(DEBUG_OBJECTS))
DEPENDENCES = $(shell find -name *.d)
EXECUTABLE_SOURCES = src/main.cpp
EXECUTABLES = $(patsubst src/%.cpp, bin/%.bin, $(EXECUTABLE_SOURCES))
DEBUG_EXECUTABLES = $(patsubst src/%.cpp, bin/debug/%.bin, $(EXECUTABLE_SOURCES))

.PHONY: clean

default: release

all: $(EXECUTABLES) $(DEBUG_EXECUTABLES)

release: $(EXECUTABLES)

debug: $(DEBUG_EXECUTABLES)

clean:
	find -name *~ -delete
	rm -rf  obj/

bin $(OBJECT_DIRS):
	mkdir $@

bin/%.bin: $(RELEASE_OBJECTS) | bin
	$(CC) $(LFLAGS) $(RELEASE_OBJECTS) -o $@

bin/debug/%.bin: $(DEBUG_OBJECTS) | bin/debug
	$(CC) $(LFLAGS) $(DEBUG_OBJECTS) -o $@

$(RELEASE_OBJECTS) $(DEBUG_OBJECTS): | $(OBJECT_DIRS)

obj/release/%.o: src/%.cpp
	$(CC) -c -MD $(CFLAGS) $(LFLAGS) $(RELEASE_FLAGS) $(addprefix -I, $(SOURCE_DIRS)) $< -o $@

obj/debug/%.o: src/%.cpp
	$(CC) -c -MD $(CFLAGS) $(LFLAGS) $(DEBUG_FLAGS) $(addprefix -I, $(SOURCE_DIRS)) $< -o $@

include $(DEPENDENCES)

