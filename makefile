CC=gcc

CFLAGS= -DDEBUG -Wall -Wno-missing-braces -Wextra -Wno-missing-field-initializers -Wformat=2 -Wswitch-default -Wswitch-enum -Wcast-align -Wpointer-arith -Wbad-function-cast -Wstrict-overflow=5 -Wstrict-prototypes -Winline -Wundef -Wnested-externs -Wcast-qual -Wshadow -Wunreachable-code -Wlogical-op -Wfloat-equal -Wstrict-aliasing=2 -Wredundant-decls -Wold-style-definition -Werror -ggdb3 -O0 -fno-omit-frame-pointer -ffloat-store -fno-common -fstrict-aliasing -lm

CFLAGS_BUILD=-O3 -Wall -Wextra

LDFLAGS=
EXEC=monohttpd

SRC= $(wildcard *.c)

#on construis la liste des .o à partir des .c
OBJ= $(SRC:.c=.o)

##	$@ Le nom de la cible
##      $< Le nom de la première dépendance
##      $^ La liste des dépendances
##      $?  La liste des dépendances plus récentes que la cible $* Le nom
##	du fichier sans suffixe

#la directive all doit lister tous les executables à produire


all: build

FUZZ_CC=afl-gcc
FUZZ_CFLAGS=-static
FUZZ_LDFLAGS=-static

fuzzbuild: CC=$(FUZZ_CC)
fuzzbuild: CFLAGS=$(FUZZ_CFLAGS)
fuzzbuild: LDFLAGS=$(FUZZ_LDFLAGS)
fuzzbuild: clean all

fuzz: fuzzbuild
	AFL_SKIP_CPUFREQ=1 afl-fuzz -i in -o out $(EXEC) @@

build: CFLAGS=$(CFLAGS_BUILD)
build: $(EXEC)

debug: $(EXEC)


$(EXEC): $(OBJ)
	@echo "Building the main binary file..."
	@$(CC) -o $@ $^ $(LDFLAGS)


args.o: args.h error.h
args_parser.o: args_parser.h args.o error.h strconv.o rand.o
client.o: client.h http.o tcp.o args_parser.o netinit.h error.h
file_tools.o: file_tools.h error.h
http.o: http.h netinit.h tcp.o error.h file_tools.o
tcp.o: netinit.h error.h args_parser.o
iptools.o: iptools.h netinit.h error.h

main.o: args_parser.o tcp.o http.o rand.o client.o iptools.o

# règle générique pour tous les dépendances en .o, avec un pipe pour les arguments de comp.
%.o: %.c
	@echo "Building $@..."
	@$(CC) -o $@ -c $< $(CFLAGS)
#.phony reconstruit toujours ses dépendances
.PHONY: clean mrproper
#vire tous les fichiers intermédiaires
clean:
#	rm -rf *.o  ne marche pas récursivement
	find ./ -type f -name '*.o' -delete
mrproper: clean
	rm -rf $(EXEC)

install:
	install -t /usr/bin/ $(EXEC)

uninstall:
	rm --interactive=never /usr/bin/$(EXEC)

ARGS?=-t test -l 42 $(EXEC)

valgrind: debug
	valgrind --show-reachable=yes --dsymutil=yes --tool=memcheck --leak-check=full --track-origins=yes ./$(EXEC) $(ARGS)
