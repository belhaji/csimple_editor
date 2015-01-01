/***************************************************************************
 *            main_tool_bar.c
 *
 *  Sun December 21 14:51:59 2014
 *  Copyright  2014  adil belhaji
 *  <user@host>
 ****************************************************************************/
/*
 * main_tool_bar.c
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

#include "main_tool_bar.h"
#include "callback.h"


GtkWidget * createToolBar(CSIde_app *app)
{
	GtkWidget *toolBar;
	GtkToolItem *btnNew,
				*btnOpen,
				*btnSave,
				*btnSaveAs,
				*btnCopy,
				*btnPaste,
				*btnCut,
				*btnDelete,
				*btnSelectAll,
				*separator;

	toolBar			= gtk_toolbar_new ();
	gtk_toolbar_set_style(GTK_TOOLBAR(toolBar),GTK_TOOLBAR_ICONS);
	gtk_toolbar_set_icon_size(GTK_TOOLBAR(toolBar),GTK_ICON_SIZE_SMALL_TOOLBAR);
	
	btnNew			= gtk_tool_button_new_from_stock (GTK_STOCK_NEW);
	btnOpen			= gtk_tool_button_new_from_stock (GTK_STOCK_OPEN);
	btnSave			= gtk_tool_button_new_from_stock (GTK_STOCK_SAVE);
	btnSaveAs		= gtk_tool_button_new_from_stock (GTK_STOCK_SAVE_AS);
	btnCopy			= gtk_tool_button_new_from_stock (GTK_STOCK_COPY);
	btnPaste		= gtk_tool_button_new_from_stock (GTK_STOCK_PASTE);
	btnCut			= gtk_tool_button_new_from_stock (GTK_STOCK_CUT);
	btnDelete		= gtk_tool_button_new_from_stock (GTK_STOCK_DELETE);
	btnSelectAll	= gtk_tool_button_new_from_stock (GTK_STOCK_SELECT_ALL);

	separator = gtk_separator_tool_item_new ();
	
	g_signal_connect(G_OBJECT(btnNew),"clicked",G_CALLBACK(menu_item_new_clicked),(gpointer) app);
	g_signal_connect(G_OBJECT(btnOpen),"clicked",G_CALLBACK(menu_item_open_clicked),(gpointer) app);
	g_signal_connect(G_OBJECT(btnSave),"clicked",G_CALLBACK(menu_item_save_clicked),(gpointer) app);
	g_signal_connect(G_OBJECT(btnSaveAs),"clicked",G_CALLBACK(menu_item_save_as_clicked),(gpointer) app);
	g_signal_connect(G_OBJECT(btnCopy),"clicked",G_CALLBACK(menu_item_copy_clicked),(gpointer) app);
	g_signal_connect(G_OBJECT(btnPaste),"clicked",G_CALLBACK(menu_item_paste_clicked),(gpointer) app);
	g_signal_connect(G_OBJECT(btnCut),"clicked",G_CALLBACK(menu_item_cut_clicked),(gpointer) app);
	g_signal_connect(G_OBJECT(btnDelete),"clicked",G_CALLBACK(menu_item_delete_clicked),(gpointer) app);
	g_signal_connect(G_OBJECT(btnSelectAll),"clicked",G_CALLBACK(menu_item_select_all_clicked),(gpointer) app);

	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnNew,0);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnOpen,1);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnSave,2);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnSaveAs,3);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),separator,4);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnCut,5);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnCopy,6);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnPaste,7);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnDelete,8);
	gtk_toolbar_insert (GTK_TOOLBAR(toolBar),btnSelectAll,9);
	

	                 
	return toolBar;
}


