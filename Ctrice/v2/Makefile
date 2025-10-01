# === Cible par défaut : tout compiler ===
all : bin/Ctrice.exe

# === Options de compilation ===
# -Wall     => active tous les warnings importants
# -Wextra   => active encore plus de warnings utiles
# -Ilib     => permet d’inclure les fichiers .h dans le dossier "lib"
CFLAGS = -Wall -Wextra -Ilib

# === Créer le dossier bin si nécessaire ===
bin:
	cmd /C "if not exist bin mkdir bin"

# === Compilation de Ctrice.exe ===
bin/Ctrice.exe : bin/Ctrice.c lib/Tools.c game/Display.c game/Engine.c | bin
	gcc $(CFLAGS) -o bin/Ctrice.exe bin/Ctrice.c lib/Tools.c game/Display.c game/Engine.c

