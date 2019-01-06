#include "ButtonWidget.h"
#include "Input.h"
#include "Render.h"

ButtonWidget::ButtonWidget()
{
	_draw = false;
	call = false;
	_mouse_state = 0;//normal
	_button_state = 0;//normal
	_last_button_state = 0;
	_mx = _my = 0;
	_x = _y = 0;
	_last_mouse_state = 0;
}

ButtonWidget::~ButtonWidget()
{
	delete _image_down;
	delete _image_normal;
	delete _image_move;
}

void ButtonWidget::init_button(std::string pic_path_down, std::string pic_path_move, std::string pic_path_normal, void(*button_event)(ButtonWidget*))
{
	_button_event = button_event;

	_image_down = TempUISys::load_texture(pic_path_down.c_str());
	_image_move = TempUISys::load_texture(pic_path_move.c_str());
	_image_normal = TempUISys::load_texture(pic_path_normal.c_str());



	_gh = _image_normal->get_height();
	_gw = _image_normal->get_width();
	_draw = true;
	_width = _gw;
	_height = _gh;



}

void ButtonWidget::set_size(int width, int height)
{
	_width = _gw = width;
	_height = _gh = height;
}

void ButtonWidget::update_button(int __x, int __y, int x, int y)
{
	_mx = __x;
	_my = __y;
	//static bool _bpressed = false;

	if (_mx >= _x + x && _mx <= _x + x + _width && _my >= _y + y && _my <= _y + y + _height)
	{
		/*鼠标状态 _mouse_state:
		 *0：已经弹起；
		 *1：正在按下；
		 *2：正在弹起
		 *3：已经按下
		 ------------
		 *按钮状态 _button_state:
		 *0:Nomal
		 *1:Move
		 *2:Down
		 */
		if (_mouse_state == 1)//pressing
		{
			_button_state = 2;//down
			_mouse_state = 3;//pressed
		}
		else if (_mouse_state == 2)
		{
			send_event(get_string_hash("button pressed"), this);
			if (_button_event)
				_button_event(this);
			call = true;
			_button_state = 1;//move

			_mouse_state = 0;
		}
		else
			if (_mouse_state != 3)
			{
				_button_state = 1;
				if (_last_button_state != 1)
					send_event(get_string_hash("button enter hover"), this);
			}
	}
	else
	{
		_button_state = 0;
		_mouse_state = 0;

	}
	_last_button_state = _button_state;
}

void ButtonWidget::draw(int x, int y)
{
	if (!_bactive) return;
	//未初始化返回
	if (!_draw)
		return;

	draw_internal(x, y);
}

void ButtonWidget::set_position(int __x, int __y)
{
	_x = __x;
	_y = __y;
}

void ButtonWidget::update(float dt, int x, int y)
{
	if (!_bactive) return;
	ActiveDrawableRect::update(dt, x, y);
	int mouse_x = Input::get_mouse_x();
	int mouse_y = Input::get_mouse_y();
	//if left button is pressed state.Ture for pressed.
	bool bpressed = Input::get_sys_key_pressed(WIP_MOUSE_LBUTTON);
	if (_last_mouse_state == 0 && bpressed == 1)
		set_mouse_state(mouse_x, mouse_y, 1);
	else if (_last_mouse_state == 1 && bpressed == 0)
		set_mouse_state(mouse_x, mouse_y, 2);
	update_button(mouse_x, mouse_y, x, y);
	//set_mouse_state(mouse_x,mouse_y,bpressed? 1 : 2 );


	_last_mouse_state = bpressed;
}

void ButtonWidget::draw_internal(int x, int y)
{
	//未初始化返回
	if (!_draw)
		return;
	int w = _width;
	int h = _height;

	switch (_button_state)
	{
	case 0:
		g_temp_uisys->draw_picture(_x + x, _y + y, w, h, _image_normal);
		break;
	case 1:
		g_temp_uisys->draw_picture(_x + x, _y + y, w, h, _image_move, RBColorf(1.f, 1.f, 1.f, 0.8f));
		break;
	case 2:
		g_temp_uisys->draw_picture(_x + x, _y + y, w, h, _image_down, RBColorf(.8f, .8f, .8f, 1.f));
		break;
	}

}

TextWidget::TextWidget(int x, int y, int width, int height)
{
	_x = (x); _y = (y); _width = (width); _height = (height);
	//_background = TempUISys::load_texture();
}

TextWidget::~TextWidget()
{
}

void TextWidget::update(float dt, int x, int y)
{
	if (!_bactive) return;
	ActiveDrawableRect::update(dt, x, y);
}

void TextWidget::draw_internal(int x, int y)
{
}

void TextWidget::draw(int x, int y)
{
	if (!_bactive) return;
	g_temp_uisys->draw_box(x + _x, y + _y, _width, _height, RBColorf::blue);
	int sz = wcslen(_text.data());
	g_temp_uisys->draw_text(x + _x + padding.x, y + _y + padding.y, _text.data(), sz, _width - padding.x, padding.x);
}

void TextWidget::set_text_padding(int x_padding, int y_padding)
{
	padding.x = x_padding;
	padding.y = y_padding;
}
