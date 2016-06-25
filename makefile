CC=gcc

CFLAGS= -DDEBUG -Wall -Wno-missing-braces -Wextra -Wno-missing-field-initializers -Wformat=2 -Wswitch-default -Wswitch-enum -Wcast-align -Wpointer-arith -Wbad-function-cast -Wstrict-overflow=5 -Wstrict-prototypes -Winline -Wundef -Wnested-externs -Wcast-qual -Wshadow -Wunreachable-code -Wlogical-op -Wfloat-equal -Wstrict-aliasing=2 -Wredundant-decls -Wold-style-definition -Werror -ggdb3 -O0 -fno-omit-frame-pointer -ffloat-store -fno-common -fstrict-aliasing -lm

CFLAGS_BUILD=-O3 -Wall -Wextra

#pthread pour le threading, et ld pour les modules
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
all: $(EXEC)


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
build: clean all


$(EXEC): $(OBJ)
	@echo "Building the main binary file..."
	@$(CC) -o $@ $^ $(LDFLAGS)

main.o: error.h args.h
args_parser.o: error.h


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
