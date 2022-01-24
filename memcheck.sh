# Script for running a memory leak check on ./uchat 8080 (change the .exe if desired)

valgrind --leak-check=full --show-leak-kinds=all --log-file=server_utils/valgrind.log  --suppressions=/usr/share/gtk-3.0/valgrind/gtk.supp --suppressions=/usr/share/glib-2.0/valgrind/glib.supp ./uchat 8080
