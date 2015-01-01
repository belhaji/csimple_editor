/*
 * Copyright (C) 2014 adil belhaji <belhaji.dev@gmail.com>
 * 
 * CSimpleIDE is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * CSimpleIDE is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "csimpleide.h"
#include "main_window.h"
#include "main_menu.h"
#include "main_tool_bar.h"
#include "editor.h"
#include "callback.h"

int main(int argc,char **argv){
	gtk_init (&argc,&argv);
	CSIde_app *app;
	GtkWidget *main_vbox;
	GtkAccelGroup *accelGroup;

	accelGroup = gtk_accel_group_new ();
	
	app = cside_app_new();
	app->main_window	= main_window_new ();
	app->main_menu		= createMenuBar(app,accelGroup);
	app->main_toolbar   = createToolBar (app);
	app->editor		= editor_create(app);
	main_vbox		= gtk_box_new (GTK_ORIENTATION_VERTICAL,0);
	
	gtk_window_add_accel_group (GTK_WINDOW(app->main_window),accelGroup);
	g_signal_connect(G_OBJECT(app->main_window),"delete-event",G_CALLBACK(mainWindowDeleteEvent),(gpointer)app);
	
	gtk_container_add (GTK_CONTAINER(app->main_window),main_vbox);
	gtk_box_pack_start (GTK_BOX(main_vbox),app->main_menu,FALSE,FALSE,0);
	gtk_box_pack_start (GTK_BOX(main_vbox),app->main_toolbar,FALSE,FALSE,0);
	gtk_box_pack_start (GTK_BOX(main_vbox),app->editor->scrolled_window,TRUE,TRUE,0);
	gtk_widget_show_all (app->main_window);
	gtk_main ();
	return 0;
}






























