OBJ_FILES=csimpleide.o main_window.o main.o callback.o main_menu.o main_tool_bar.o editor.o actions.o search_box.o terminal.o

CC=gcc

CFLAGS= `pkg-config --cflags gtk+-3.0 gtksourceview-3.0 vte-2.90`

CLIBS=`pkg-config --libs gtk+-3.0 gtksourceview-3.0 vte-2.90`

csimple_editor  :   $(OBJ_FILES)
	$(CC) -o csimple_editor $(OBJ_FILES) $(CFLAGS) $(CLIBS)

main.o		:   main.c
	   $(CC) -c main.c $(CFLAGS) $(CLIBS)

csimpleide.o :   csimpleide.c
	   $(CC) -c csimpleide.c $(CFLAGS) $(CLIBS)

main_window.o		:   main_window.c
	   $(CC) -c main_window.c $(CFLAGS) $(CLIBS)

callback.o		:   callback.c
	   $(CC) -c callback.c $(CFLAGS) $(CLIBS)

main_menu.o		:   main_menu.c
	   $(CC) -c main_menu.c $(CFLAGS) $(CLIBS)

main_tool_bar.o		:   main_tool_bar.c
	   $(CC) -c main_tool_bar.c $(CFLAGS) $(CLIBS)

editor.o		:   editor.c
	   $(CC) -c editor.c $(CFLAGS) $(CLIBS)

actions.o		:   actions.c
	   $(CC) -c actions.c $(CFLAGS) $(CLIBS)

search_box.o	:   search_box.c
	   $(CC) -c search_box.c $(CFLAGS) $(CLIBS)

terminal.o	:   terminal.c
	   $(CC) -c terminal.c $(CFLAGS) $(CLIBS)

clean : 
	rm -rf *.o
