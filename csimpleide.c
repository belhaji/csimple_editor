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

/* define app functions for initialization */

CSIde_app *cside_app_new(void){
	CSIde_app *app  = (CSIde_app*)  g_slice_new(CSIde_app);
	Editor *editor  = (Editor*) g_slice_new(Editor);
	Document *doc  = (Document*) g_slice_new(Document);
	app->editor = editor;
	doc->name   = NULL;
	doc->isSaved	= FALSE;
	doc->isOnDisk   = FALSE;
	app->doc	= doc;
	return app;
}