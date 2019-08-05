PROG = majora

CXXFLAGS += `sdl2-config --cflags`
CXXFLAGS += -g -lefence

LDFLAGS += `sdl2-config --libs` -lSDL2_mixer -lSDL2_image -lm

OUT = bin
SEARCHPATH += src
vpath %.c $(SEARCHPATH)
vpath %.h $(SEARCHPATH)

DEPS += defs.h structs.h

_OBJS += draw.o
_OBJS += init.o input.o
_OBJS += main.o

OBJS = $(patsubst %,$(OUT)/%,$(_OBJS))

all: $(PROG)

$(OUT)/%.o: %.c %.c $(DEPS)
	@mkdir -p $(OUT)
	gcc $(CFLAGS) $(CXXFLAGS) -c -o $@ $<

$(PROG): $(OBJS)
	gcc -o $@ $(OBJS) $(LDFLAGS)

clean:
	$(RM) -rf $(OUT) $(PROG)
