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
#include "callback.h"
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
		
	if (app->doc->name != NULL )
	{
		g_free(app->doc->name);
	}
	if (app->doc->bin_name != NULL)
	{
		g_free(app->doc->bin_name);	
	}
	app->doc->isSaved	= FALSE;
	app->doc->name		= NULL;
	app->doc->bin_name	= NULL;
	app->doc->isOnDisk	= FALSE;
	g_free(text);
	//wgtk_source_buffer_end_not_undoable_action (app->editor->buffer);
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
	gchar *fileName = NULL;
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
			if (app->doc->name != NULL )
			{
				g_free(app->doc->name);
			}
			if (app->doc->bin_name != NULL)
			{
				g_free(app->doc->bin_name);	
			}
			app->doc->name	= fileName;
			app->doc->bin_name = get_bin_name(fileName);
			g_file_get_contents(fileName,&text,&lenText,&error);
			if(text == NULL)
			{
				g_print("Error: %s ",error->message);
				g_free (error);
			}
			gtk_text_buffer_set_text (buffer,text,(gint)lenText);

			app->doc->isSaved	= TRUE;
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
			app->doc->bin_name = get_bin_name(app->doc->name);
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
		g_free(text);
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

gchar* get_bin_name(gchar *filename){
	
	gchar *bin_name  = (gchar*) g_malloc(sizeof(gchar) * (strlen(filename)+5));
	if (bin_name != NULL)
	{
		g_sprintf (bin_name,"%s.bin",filename);
	}
	return bin_name;
}

void compile_file(CSIde_app *app){
	gchar *cmd_args[] = {"gcc","-o",app->doc->bin_name,app->doc->name,"-lcsimple",NULL};
	vte_terminal_fork_command(VTE_TERMINAL(app->terminal->vte), "gcc", cmd_args, NULL, NULL, TRUE, TRUE,TRUE);
}


void terminal_box(CSIde_app *app){
	TerminalBox *tb = (TerminalBox*) g_slice_new(TerminalBox);
	tb->terminal_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(tb->terminal_window),app->doc->bin_name);
	gtk_window_set_default_size (GTK_WINDOW(tb->terminal_window),600,400);

	tb->scrolled_window = gtk_scrolled_window_new (NULL,NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(tb->scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	gtk_container_add (GTK_CONTAINER(tb->terminal_window),tb->scrolled_window);

	tb->vte = vte_terminal_new();
	vte_terminal_set_scrollback_lines(VTE_TERMINAL (tb->vte), -1);
	vte_terminal_fork_command(VTE_TERMINAL(tb->vte),app->doc->bin_name,NULL, NULL, NULL, TRUE, TRUE,TRUE);	
	vte_terminal_set_scroll_on_keystroke(VTE_TERMINAL (tb->vte), TRUE);
	vte_terminal_set_allow_bold (VTE_TERMINAL (tb->vte),TRUE);
	g_signal_connect(G_OBJECT(tb->terminal_window),"destroy",G_CALLBACK(terminal_window_distroy),(gpointer) tb);
 
	gtk_container_add (GTK_CONTAINER(tb->scrolled_window),tb->vte);
	gtk_widget_show_all(tb->terminal_window);

}



void update_title(CSIde_app *app){
	gchar *title = (gchar*) g_malloc(sizeof(gchar) * 100);
	if (title != NULL)
	{
		if(app->doc->isSaved)
			g_sprintf(title,"%s(%s)",APP_NAME,g_path_get_basename(app->doc->name));
		else{
			if (app->doc->isOnDisk)
				g_sprintf(title,"%s(%s*)",APP_NAME,g_path_get_basename(app->doc->name));
			else
				g_sprintf(title,"%s(%s*)",APP_NAME,"Untitled");
		}
		gtk_window_set_title (GTK_WINDOW(app->main_window),title);
		g_free(title);
	}

}





