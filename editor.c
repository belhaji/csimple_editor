/***************************************************************************
 *            editor.c
 *
 *  Sun December 28 17:57:02 2014
 *  Copyright  2014  adil belhaji
 *  <user@host>
 ****************************************************************************/
/*
 * editor.c
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

#include "editor.h"
#include <gtksourceview/gtksourceview.h>


Editor * editor_create(CSIde_app *app){
	GtkSourceBuffer *buffer;
	GtkSourceLanguage	*lang;
	GtkSourceLanguageManager *langm;

	Editor *editor  = (Editor*) g_slice_new(Editor);

	editor->scrolled_window = gtk_scrolled_window_new (NULL,NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(editor->scrolled_window ),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

	buffer  = gtk_source_buffer_new (NULL);
	langm   = gtk_source_language_manager_new ();
	lang	= gtk_source_language_manager_get_language (langm,"csimple");

	editor->buffer = buffer;
	editor->source_view = gtk_source_view_new_with_buffer (buffer);
	gtk_source_view_set_auto_indent (GTK_SOURCE_VIEW(editor->source_view),TRUE);
	gtk_source_view_set_show_line_numbers (GTK_SOURCE_VIEW(editor->source_view),TRUE);
	gtk_source_buffer_set_language (buffer,lang);
	gtk_source_buffer_set_highlight_syntax (buffer,TRUE);
	gtk_source_view_set_highlight_current_line (GTK_SOURCE_VIEW(editor->source_view),TRUE);
	gtk_container_add (GTK_CONTAINER(editor->scrolled_window),editor->source_view);

	return editor;
}




















