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


#ifndef ACTION_H
#define ACTION_H

#include "csimpleide.h"

void new_file(CSIde_app *app);

void open_file(CSIde_app *app);

void save_file(CSIde_app *app);

void save_file_as(CSIde_app *app);

void quit_app(CSIde_app *app);

gchar* get_bin_name(gchar *filename);

void compile_file(CSIde_app *app);

void terminal_box(CSIde_app *app);


#endif /* ACTION_H */



