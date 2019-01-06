#include "ActiveDrawableRect.h"
#include "Render.h"
#include <iostream>


ActiveDrawableRect::ActiveDrawableRect(void)
{
	_bmouse_position = false;
	_last_mouse = false;
	_all_num = 0;
	bdraw = true;
	_fbo = nullptr;
	_bactive = true;
}


ActiveDrawableRect::~ActiveDrawableRect(void)
{
	delete _fbo;
}

void ActiveDrawableRect::set_position(int x,int y)
{
	_x = x;
	_y = y;
}

void ActiveDrawableRect::update(float dt, int x, int y)
{
	if(!_bactive) 
		return;

}

void ActiveDrawableRect::draw(int x,int y)
{
	if(x<0||y<0)
		g_temp_uisys->draw_picture(_x, _y, _width, _height, _fbo);
	else
		g_temp_uisys->draw_picture(x, y, _width, _height, _fbo);
}

void ActiveDrawableRect::draw_internal(int x,int y)
{

}

void ActiveDrawableRect::set_id(int id)
{
	_id = id;
}

int ActiveDrawableRect::get_id()
{
	return _id;
}

void ActiveDrawableRect::set_name(std::string name)
{
	_name = name;
}

std::string ActiveDrawableRect::get_name()
{
	return _name;
}

void ActiveDrawableRect::reshape(int width,int height,int x,int y)
{
	
	if(x>=0&&y>=0)
	{
		_x = x;
		_y = y;
	}
	
	_width = width;
	_height = height;
}

WIPRenderTexture2D* ActiveDrawableRect::get_fbo()
{
	return _fbo;
}


//editor
void ActiveDrawableRect::set_mouse_position()
{
	_bmouse_position = true;
}

void ActiveDrawableRect::cancel_mouse_position()
{
	_bmouse_position = false;
}

bool ActiveDrawableRect::is_mouse_position()
{
	return _bmouse_position;
}

void ActiveDrawableRect::update_editor(int x, int y)
{
	if (!_bactive)
		return;
	int _mx = Input::get_mouse_x();
	int _my = Input::get_mouse_y();

	
	if (_last_mouse)
	{
		_x = _mx - x - _width/2;
		_y = _my - y - _height/2;
		LOG_INFO("%d,%d", _x, _y);
		if (Input::get_sys_key_up(WIP_MOUSE_RBUTTON))
		{
			_last_mouse = false;
		}
	}
	else
	{
		bool m = Input::get_sys_key_up(WIP_MOUSE_RBUTTON);
		if (m)
		{
			if (_mx >= _x + x && _mx <= _x + x + _width && _my >= _y + y && _my <= _y + y + _height)
				_last_mouse = true;
		}
	}

}

ActiveDrawableRect** ActiveDrawableRect::get_all_contents()
{
	return _contents;
}

int ActiveDrawableRect::get_all_num()
{
	return _all_num;
}

void ActiveDrawableRect::set_activate(bool val)
{
	_bactive = val;
}

bool ActiveDrawableRect::is_active()
{
	return _bactive;
}