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


#include "terminal.h"


Terminal * main_terminal_new(CSIde_app *app){
	Terminal *terminal;
	terminal->scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (terminal->scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	terminal->vte = vte_terminal_new();
	vte_terminal_set_scrollback_lines(VTE_TERMINAL (terminal->vte), -1);
	vte_terminal_fork_command(VTE_TERMINAL(terminal->vte), NULL, NULL, NULL, NULL, TRUE, TRUE,TRUE);
	vte_terminal_set_scroll_on_keystroke(VTE_TERMINAL (terminal->vte), TRUE);
	vte_terminal_set_allow_bold (VTE_TERMINAL (terminal->vte),TRUE);
	gtk_container_set_border_width(GTK_CONTAINER(terminal->scrolled_window),5);
	gtk_container_add (GTK_CONTAINER(terminal->scrolled_window),terminal->vte);

	return terminal;
}
