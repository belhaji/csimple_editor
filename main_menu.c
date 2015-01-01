/***************************************************************************
 *            main_menu.c
 *
 *  Sun December 21 14:13:54 2014
 *  Copyright  2014  adil belhaji
 *  <user@host>
 ****************************************************************************/
/*
 * main_menu.c
 *
 * Copyright (C) 2014 - adil belhaji
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "main_menu.h"
#include "callback.h"
#include <gdk/gdkkeysyms.h>

GtkWidget * createMenuBar(CSIde_app *app,GtkAccelGroup *accel_group)
{
	GtkWidget *menuItem;
	GtkWidget *menuFile;
	GtkWidget *menuEdit;
	GtkWidget *menuChangeCase;
	GtkWidget *menuHelp;
	GtkWidget *menuBar;


	menuBar			= gtk_menu_bar_new ();
	menuFile		= gtk_menu_new ();
	menuEdit		= gtk_menu_new ();
	menuHelp		= gtk_menu_new ();
	menuChangeCase	= gtk_menu_new ();

	

	
	menuItem	= gtk_menu_item_new_with_label ("New");
	gtk_widget_add_accelerator (menuItem,"activate",accel_group,GDK_KEY_N,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuFile),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_new_clicked),(gpointer) app);

	menuItem	= gtk_menu_item_new_with_label ("Open");
	gtk_widget_add_accelerator (menuItem,"activate",accel_group,GDK_KEY_O,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuFile),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_open_clicked ),(gpointer) app);

	menuItem	= gtk_menu_item_new_with_label ("save");
	gtk_widget_add_accelerator (menuItem,"activate",accel_group,GDK_KEY_S,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuFile),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_save_clicked ),(gpointer) app);

	menuItem	= gtk_menu_item_new_with_label ("Save as");
	gtk_widget_add_accelerator (menuItem,"activate",accel_group,GDK_KEY_S,GDK_SHIFT_MASK | GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuFile),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_save_as_clicked ),(gpointer) app);

	menuItem	= gtk_separator_menu_item_new ();
	gtk_menu_shell_append (GTK_MENU_SHELL(menuFile),menuItem);
	
	menuItem	= gtk_menu_item_new_with_label ("Quit");
	gtk_widget_add_accelerator (menuItem,"activate",accel_group,GDK_KEY_Q,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuFile),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_quit_clicked),(gpointer) app);

	menuItem	= gtk_menu_item_new_with_label ("File");
	gtk_menu_item_set_submenu (GTK_MENU_ITEM(menuItem),menuFile);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuBar),menuItem);


	menuItem	= gtk_menu_item_new_with_label ("Undo");
	gtk_widget_add_accelerator (menuItem,"activate",accel_group,GDK_KEY_Z,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuEdit),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_undo_clicked ),(gpointer) app);

	menuItem	= gtk_menu_item_new_with_label ("Redo");
	gtk_widget_add_accelerator (menuItem,"activate",accel_group,GDK_KEY_C,GDK_CONTROL_MASK | GDK_SHIFT_MASK,GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuEdit),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_redo_clicked ),(gpointer) app);

	menuItem	= gtk_separator_menu_item_new ();
	gtk_menu_shell_append (GTK_MENU_SHELL(menuEdit),menuItem);
	
	menuItem	= gtk_menu_item_new_with_label ("Copy");
	gtk_widget_add_accelerator (menuItem,"activate",accel_group,GDK_KEY_C,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuEdit),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_copy_clicked ),(gpointer) app);

	menuItem	= gtk_menu_item_new_with_label ("Cut");
	gtk_widget_add_accelerator (menuItem,"activate",accel_group,GDK_KEY_X,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuEdit),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_cut_clicked ),(gpointer) app);

	menuItem	= gtk_menu_item_new_with_label ("Paste");
	gtk_widget_add_accelerator (menuItem,"activate",accel_group,GDK_KEY_V,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuEdit),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_paste_clicked ),(gpointer) app);

	menuItem	= gtk_menu_item_new_with_label ("Delete");
	gtk_widget_add_accelerator (menuItem,"activate",accel_group,GDK_KEY_D,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuEdit),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_delete_clicked ),(gpointer) app);

	menuItem	= gtk_menu_item_new_with_label ("Select all");
	gtk_widget_add_accelerator (menuItem,"activate",accel_group,GDK_KEY_A,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuEdit),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_select_all_clicked ),(gpointer) app);

	menuItem	= gtk_menu_item_new_with_label ("Deselect");
	gtk_widget_add_accelerator (menuItem,"activate",accel_group,GDK_KEY_D,GDK_CONTROL_MASK | GDK_SHIFT_MASK,GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuEdit),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_deselect_clicked ),(gpointer) app);

	menuItem	= gtk_separator_menu_item_new ();
	gtk_menu_shell_append (GTK_MENU_SHELL(menuEdit),menuItem);

	menuItem	= gtk_menu_item_new_with_label ("To UpperCase");
	gtk_widget_add_accelerator (menuItem,"activate",accel_group,GDK_KEY_U,GDK_CONTROL_MASK | GDK_SHIFT_MASK,GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuChangeCase),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_to_upper_clicked ),(gpointer) app);

	menuItem	= gtk_menu_item_new_with_label ("To LowerCase");
	gtk_widget_add_accelerator (menuItem,"activate",accel_group,GDK_KEY_L,GDK_CONTROL_MASK | GDK_SHIFT_MASK,GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuChangeCase),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_to_lower_clicked ),(gpointer) app);

	
	menuItem	= gtk_menu_item_new_with_label ("Change Case");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem),menuChangeCase);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuEdit),menuItem);
	
	menuItem	= gtk_menu_item_new_with_label ("Edit");
	gtk_menu_item_set_submenu (GTK_MENU_ITEM(menuItem),menuEdit);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuBar),menuItem);


	

	menuItem	= gtk_menu_item_new_with_label ("About");
	gtk_menu_shell_append (GTK_MENU_SHELL(menuHelp),menuItem);
	g_signal_connect(G_OBJECT(menuItem),"activate",G_CALLBACK(menu_item_about_clicked  ),(gpointer) app);

	menuItem	= gtk_menu_item_new_with_label ("help");
	gtk_menu_item_set_submenu (GTK_MENU_ITEM(menuItem),menuHelp);
	gtk_menu_shell_append (GTK_MENU_SHELL(menuBar),menuItem);


	
	return menuBar;

}


