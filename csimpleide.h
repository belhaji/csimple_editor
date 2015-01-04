/*
 * Copyright (C) 2014 adil belhaji <belhaji.dev@gmail.com>
 * 
 * csimple_editor is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * csimple_editor is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef CSIMPLEIDE_H
#define CSIMPLEIDE_H

#include <gtk/gtk.h>
#include <gtksourceview/gtksourceview.h>
#include <vte/vte.h>



/* define the application infos */

#define APP_NAME	 "csimple_editor"

#define APP_VERSION	 "0.1"

#define AUTHOR_NAME	 "Belhaji Adil"

#define AUTHOR_EMAIL "belhaji.dev@gmail.com"

#define CONFIG_DIR	 "/.scide/"

#define CONFIG_FILE	 ".csimple.rc"

#define APP_DIR		 "/usr/share/scide/"


/* define app data structure */
typedef struct {
	GtkWidget *scrolled_window;
	GtkWidget *source_view;
	GtkSourceBuffer *buffer;
}Editor;

typedef struct {
	gchar *name;
	gboolean isSaved;
	gboolean isOnDisk;
}Document;

typedef struct {
	GtkWidget *vte;
	GtkWidget *scrolled_window;
}Terminal;

typedef struct {
	GtkWidget *main_window;
	GtkWidget *main_menu;
	GtkWidget *main_toolbar;
	Terminal *terminal;
	Editor *editor;
	Document *doc;
} CSIde_app ;



/* define app functions for initialization */

CSIde_app *cside_app_new(void);

























#endif // CSIMPLEIDE_H 