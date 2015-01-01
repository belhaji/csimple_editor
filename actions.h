/***************************************************************************
 *            actions.h
 *
 *  Thu January 01 12:23:13 2015
 *  Copyright  2015  adil belhaji
 *  <user@host>
 ****************************************************************************/
/*
 * actions.h
 *
 * Copyright (C) 2015 - adil belhaji
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
#ifndef ACTION_H
#define ACTION_H

#include "csimpleide.h"

void new_file(CSIde_app *app);

void open_file(CSIde_app *app);

void save_file(CSIde_app *app);

void save_file_as(CSIde_app *app);

void quit_app(CSIde_app *app);




#endif /* ACTION_H */



