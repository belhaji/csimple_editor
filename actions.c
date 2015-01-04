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

#include "actions.h"
#include <string.h>

void new_file(CSIde_app *app){
	GtkTextIter iStart,iEnd;
	GtkTextBuffer *buffer = GTK_TEXT_BUFFER(app->editor->buffer);
	gtk_text_buffer_get_bounds(buffer,&iStart,&iEnd);
	gchar * text = gtk_text_buffer_get_text(buffer,&iStart,&iEnd,FALSE);
	if(app->doc->isSaved == FALSE && strcmp("",text)) 
	{	
		GtkWidget * msgDialog;
		msgDialog = gtk_message_dialog_new(GTK_WINDOW(app->main_window),
		                                   GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
		                                   GTK_MESSAGE_WARNING,
		                                   GTK_BUTTONS_YES_NO,
	                          			   "Do you want save your file ?",
		                                   NULL);
		switch (gtk_dialog_run (GTK_DIALOG(msgDialog))) 
		{   
			
			case GTK_RESPONSE_YES:
				if(app->doc->name == NULL)
				{   
					save_file_as(app);
					gtk_text_buffer_delete(buffer,&iStart,&iEnd);
				}	
				else
				{
					save_file(app);
					gtk_text_buffer_delete(buffer,&iStart,&iEnd);
					
				}
				break;
				
			case GTK_RESPONSE_NO:
				gtk_text_buffer_delete(buffer,&iStart,&iEnd);
				break;

		}
		
		gtk_widget_destroy (msgDialog);
	}else{
		
		gtk_text_buffer_delete(buffer,&iStart,&iEnd);
	}
		
	app->doc->isSaved	= FALSE;
	app->doc->name		= NULL;
	app->doc->isOnDisk	= FALSE;

}

void open_file(CSIde_app *app){
	
	if(app->doc->isSaved == FALSE && app->doc->isOnDisk == TRUE ) 
	{	
		GtkWidget * msgDialog;
		msgDialog = gtk_message_dialog_new(GTK_WINDOW(app->main_window),
		                                   GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
		                                   GTK_MESSAGE_WARNING,
		                                   GTK_BUTTONS_YES_NO,
	                          			   "Do you want save your file ?",
		                                   NULL);
		switch (gtk_dialog_run (GTK_DIALOG(msgDialog))) 
		{   
			
			case GTK_RESPONSE_YES:
				if(app->doc->name == NULL)
				{   
					save_file_as(app);
				}	
				else
				{
					save_file(app);
				}
		}
		
		gtk_widget_destroy (msgDialog);
	}
	gchar *fileName;
	gchar *text = NULL;
	GError *error;
	gsize  lenText;
	GtkWidget *dialog;
	GtkFileFilter *filter;
	GtkTextBuffer *buffer = GTK_TEXT_BUFFER(app->editor->buffer);
	filter = gtk_file_filter_new ();
	gtk_file_filter_set_name (filter,"Text Files");
	gtk_file_filter_add_pattern (filter,"*.*");
	dialog = gtk_file_chooser_dialog_new("Open a file ..",
	                                     GTK_WINDOW(app->main_window),
	                                     GTK_FILE_CHOOSER_ACTION_OPEN,
	                                      "_OPEN",GTK_RESPONSE_OK, "_Cancel",GTK_RESPONSE_CANCEL,
	                                     NULL);
	gtk_file_chooser_set_create_folders(GTK_FILE_CHOOSER(dialog),TRUE);
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER(dialog),g_get_home_dir ());
	gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER(dialog),TRUE);
	switch (gtk_dialog_run (GTK_DIALOG(dialog)))
	{
		case GTK_RESPONSE_OK:
			fileName		= gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(dialog));
			app->doc->name	= fileName;
			g_file_get_contents(fileName,&text,&lenText,&error);
			if(text == NULL)
			{
				g_print("Error: %s ",error->message);
				g_free (error);
			}
			gtk_text_buffer_set_text (buffer,text,(gint)lenText);

			app->doc->isSaved		= TRUE;
			app->doc->isOnDisk	= TRUE;
			g_free (text);
		default:
			gtk_widget_destroy (dialog);

	}
		

}


void save_file(CSIde_app *app)
{
	GtkTextIter iStart,iEnd;
	gchar *text = NULL;
	gsize  lenText;
	gtk_text_buffer_get_start_iter (GTK_TEXT_BUFFER(app->editor->buffer),&iStart);
	gtk_text_buffer_get_end_iter (GTK_TEXT_BUFFER(app->editor->buffer),&iEnd);
	text		= gtk_text_buffer_get_text (GTK_TEXT_BUFFER(app->editor->buffer),&iStart,&iEnd,TRUE);
	lenText		= (gsize) strlen(text);
	if(!g_file_set_contents (app->doc->name,text,(gssize) lenText,NULL))
	{
		g_print("Error: cannot save the file\n");

	}
	g_free (text);
	app->doc->isSaved	 = TRUE;
	app->doc->isOnDisk = TRUE;	
}


void save_file_as(CSIde_app *app){
	GtkWidget *dialog;
	GtkFileFilter *filter;
	filter = gtk_file_filter_new ();
	gtk_file_filter_set_name (filter,"Text Files");
	gtk_file_filter_add_pattern (filter,"*.*");
	dialog = gtk_file_chooser_dialog_new("Save the file ..",
	                                     GTK_WINDOW(app->main_window),
	                                     GTK_FILE_CHOOSER_ACTION_SAVE,
	                                      "_SAVE",GTK_RESPONSE_OK, "_Cancel",GTK_RESPONSE_CANCEL,
	                                     NULL);

	gtk_file_chooser_set_create_folders(GTK_FILE_CHOOSER(dialog),TRUE);
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER(dialog),g_get_home_dir ());
	gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER(dialog),"Untitled.txt");
	gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER(dialog),TRUE);
	switch (gtk_dialog_run (GTK_DIALOG(dialog)))
	{
		case GTK_RESPONSE_OK:
			app->doc->name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
			save_file(app);
			app->doc->isSaved  = TRUE;
			app->doc->isOnDisk = TRUE;
			break;
			
	}
	gtk_widget_destroy (dialog);

}


void quit_app(CSIde_app *app){
	GtkTextIter iStart,iEnd;
	gchar *text = NULL;
	GtkTextBuffer *buffer = GTK_TEXT_BUFFER(app->editor->buffer);
	gtk_text_buffer_get_start_iter (buffer,&iStart);
	gtk_text_buffer_get_end_iter (buffer,&iEnd);
	text		= gtk_text_buffer_get_text (buffer,&iStart,&iEnd,TRUE);

	if(app->doc->isSaved == FALSE && strlen(text) != 0 )  
	{
		GtkWidget * msgDialog;
		msgDialog = gtk_message_dialog_new(GTK_WINDOW(app->main_window),
		                                   GTK_DIALOG_DESTROY_WITH_PARENT | GTK_DIALOG_MODAL | GTK_DIALOG_USE_HEADER_BAR,
		                                   GTK_MESSAGE_WARNING,
		                                   GTK_BUTTONS_YES_NO,
		                                   "Do you want save your file ?",
		                                   NULL);
		gtk_dialog_add_button (GTK_DIALOG(msgDialog),"Cancel",GTK_RESPONSE_CANCEL);

		switch (gtk_dialog_run (GTK_DIALOG(msgDialog)))
		{
			case GTK_RESPONSE_YES:
				if(app->doc->name == NULL)
				{
					save_file_as(app);
					gtk_widget_destroy(msgDialog);
					gtk_main_quit ();
				}
				else
				{   
					save_file(app);
					gtk_widget_destroy(msgDialog);
					gtk_main_quit ();
				}
				break;
			case GTK_RESPONSE_NO:
				gtk_widget_destroy(msgDialog);
				gtk_main_quit ();
				break;
			default :
				gtk_widget_destroy(msgDialog);
				break;
		}
	}else{
		gtk_main_quit();
	}

}
