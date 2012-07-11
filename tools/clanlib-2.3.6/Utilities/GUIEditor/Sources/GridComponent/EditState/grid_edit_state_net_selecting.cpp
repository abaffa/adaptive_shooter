/*
**  ClanLib SDK
**  Copyright (c) 1997-2011 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
*/

#include "precomp.h"
#include "grid_edit_state_net_selecting.h"
#include "GridComponent/grid_component.h"
#include "MainWindow/gui_editor_window.h"
#include "Selection/selection.h"

GridEditStateNetSelecting::GridEditStateNetSelecting()
{
}

bool GridEditStateNetSelecting::on_input_pressed(const CL_InputEvent &e)
{
	if (e.id == CL_MOUSE_LEFT)
	{
		grid->main_window->get_selection()->clear();
		grid->capture_mouse(true);
		grid->request_repaint();
		start = e.mouse_pos;
		return true;
	}
	else
	{
		return false;
	}
}

bool GridEditStateNetSelecting::on_input_released(const CL_InputEvent &e)
{
	if (e.id == CL_MOUSE_LEFT)
	{
		grid->capture_mouse(false);
		grid->edit_state.set_state(GridEditState::state_none);
		grid->set_netselect_box(CL_Rect());
		grid->select_objects(get_rect(e.mouse_pos));
		return true;
	}
	else
	{
		return false;
	}
}

bool GridEditStateNetSelecting::on_input_doubleclick(const CL_InputEvent &e)
{
	return false;
}

bool GridEditStateNetSelecting::on_input_pointer_moved(const CL_InputEvent &e)
{
	grid->set_netselect_box(get_rect(e.mouse_pos));
	return true;
}

CL_Rect GridEditStateNetSelecting::get_rect(const CL_Point &end) const
{
	CL_Point p1 = start;
	CL_Point p2 = end;
	if (p1.x > p2.x)
		swap(p1.x, p2.x);
	if (p1.y > p2.y)
		swap(p1.y, p2.y);
	return CL_Rect(p1.x, p1.y, p2.x, p2.y);
}

void GridEditStateNetSelecting::swap(int &v1, int &v2)
{
	int temp = v1;
	v1 = v2;
	v2 = temp;
}
