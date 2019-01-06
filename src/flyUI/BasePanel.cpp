#include "BaseWidget.h"
#include "BasePanel.h"
#include "Render.h"

BasePanel::BasePanel(int x,int y,int width,int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_background = NULL;
	
	//wrong with global construct
	//_fbo.allocate(width,height);
	_fbo = g_rhi->RHICreateRenderTexture2D(width, height, RBColorf::black);
}

BasePanel::~BasePanel()
{
	delete _background;
}

void BasePanel::set_background(const char *path)
{
	if (!_background)
	{
		_background = TempUISys::load_texture(path);
	}
}

void BasePanel::add_panel(BasePanel* panel)
{

	_sub_panels.push_back(panel);
}

void BasePanel::add_widget(BaseWidget* widget)
{

	_widgets.push_back(widget);
}

void BasePanel::update(float dt, int x, int y)
{
	if (!_bactive) return;
	int tempnum = 0;

	ActiveDrawableRect::update(dt,x,y);
	int lenp = _sub_panels.size();
	int lenw = _widgets.size();

	//update_editor(x, y);

	

	for(int i=0;i<lenp;++i)
	{
		_sub_panels[i]->update(dt,x+_x,y+_y);
		_sub_panels[i]->update_editor(x + _x, y + _y);

		//editor
		_contents[tempnum] = _sub_panels[i];
		tempnum++;
	}
	
	for(int i=0;i<lenw;++i)
	{
		_widgets[i]->update(dt, x + _x, y + _y);
		_widgets[i]->update_editor( x + _x, y + _y);

		//editor
		_contents[tempnum] = _widgets[i];
		tempnum++;
	}
	
	_all_num = tempnum;
	//std::cout<<"updating BasePanel "<<_name<<" ...\n";
	

	//g_rhi->set_main_back_buffer();
}

void BasePanel::draw(int x,int y,int width,int height)
{
	if (!_bactive) return;
	if(_background)
	if(x<0||y<0)
		g_temp_uisys->draw_picture(_x, _y, _width, _height, _background);
	else
		g_temp_uisys->draw_picture(_x+x, _y+y, _width, _height, _background);
	int lenp = _sub_panels.size();
	int lenw = _widgets.size();
	for (int i = 0; i < lenp; ++i)
	{
		_sub_panels[i]->draw(_x + x, _y + y);
	}

	for (int i = 0; i < lenw; ++i)
	{
		_widgets[i]->draw(_x + x, _y + y);
	}
	
}

void BasePanel::draw_internal(int x,int y)
{

}

#include "ButtonWidget.h"

void TableTextPanel::set_background(const char * path)
{
	bachground = TempUISys::load_texture(path);
}

void TableTextPanel::add_item(const wstring& name, const wstring& disc, const WIPTexture2D* t,int cnt)
{
	int i = 0;
	for (; i < _item_names.size(); ++i)
	{
		if (_item_names[i] == name/*&&_discriptions[i]==disc*/)
		{
			_count[i]++;
			return;
		}
	}
	_count.push_back(cnt);
	_item_names.push_back(name);
	_discriptions.push_back(disc);
	_icons.push_back(t);

}

void TableTextPanel::remove_item(const wstring & name, int cnt)
{
	bool remove = false;
	auto it1 = _discriptions.begin();
	auto it2 = _item_names.begin();
	auto it3 = _icons.begin();
	auto it4 = _count.begin();

	int i = 0;
	for (; i < _item_names.size(); ++i)
	{
		if (_item_names[i] == name)
		{
			_count[i]-=cnt;
			if (_count[i] <= 0)
				break;
			return;
		}
		it1++; it2++; it3++; it4++;
	}
	_discriptions.erase(it1);
	_item_names.erase(it2);
	_icons.erase(it3);
	_count.erase(it4);

}

void TableTextPanel::remove_item(int idx, int cnt)
{
	if (idx >= _item_names.size()) return;
	_count[idx] -= cnt;
	if (_count[idx] > 0)
		return;
	auto it1 = _discriptions.begin();
	auto it2 = _item_names.begin();
	auto it3 = _icons.begin();
	auto it4 = _count.begin();
	int i = 0;
	for (; i < _item_names.size(); ++i)
	{
		if (idx == i) break;
		it1++; it2++; it3++; it4++;
	}
	_discriptions.erase(it1);
	_item_names.erase(it2);
	_icons.erase(it3);
	_count.erase(it4);
}

void TableTextPanel::update(float dt, int x, int y)
{
	if (!is_active()) return;
}

#include "AudioManager.h"

void TableTextPanel::draw(int x, int y)
{
	if (!is_active()) return;
	//g_rhi->enable_depth_test();
	//g_rhi->enable_stencil_test();
	//g_rhi->set_stebcil_function();
	int mx = Input::get_mouse_x();
	int my = Input::get_mouse_y();
	int ox = _x + x,oy = y + _y;
	int rel_x = mx - ox - _table_relative_pos.x, rel_y = my - oy-_table_relative_pos.y;
	int j = rel_x / _table_cell_size.x;
	int k = (rel_y - _content_y) / _table_cell_size.y;
	int dx = j * _table_cell_size.x;
	int dy = k * _table_cell_size.y;
	if (!bachground)
		g_temp_uisys->draw_box(x + _x, y + _y, _width, _height, RBColorf::green);
	else
		g_temp_uisys->draw_picture(x + _x, y + _y, _width, _height, bachground);
	//g_rhi->set_stencil_write(true);
	g_temp_uisys->draw_box(x + _x + _table_relative_pos.x, y + _y+_table_relative_pos.y, _table_size.x, _table_size.y, RBColorf::grey);
	//g_rhi->set_stencil_write(false);
	g_temp_uisys->draw_box(x + _x, y + _y+ _table_relative_pos.y + _content_y, _width, 2, RBColorf::cyan);

	//draw contents
	for (int i = 0; i<_item_names.size(); ++i)
	{
		
			int kx = i % 3;
			int ky = i / 3;
			int icon_drawx = ox + _table_relative_pos.x + kx * _table_cell_size.x;
			int icon_drawy = oy + _table_relative_pos.y + ky * _table_cell_size.y + _content_y;
		if (ky * _table_cell_size.y + _content_y >-2 && (ky+1) * _table_cell_size.y + _content_y < _table_size.y+1)
		{
			int paddingy = (_table_cell_size.y - _icons[i]->get_height()) / 2;
			g_temp_uisys->draw_picture(icon_drawx, icon_drawy + paddingy, _icons[i]->get_width(), _icons[i]->get_height(), _icons[i]);
			int paddingx_between = 10;
			//int _table_cell_size.x - _icons[i]->get_width() - paddingx_between + wcslen(_item_names[i].data())
			g_temp_uisys->draw_text(icon_drawx + paddingx_between + _icons[i]->get_width(), icon_drawy + paddingy, _item_names[i].data(), wcslen(_item_names[i].data()), _table_cell_size.x);

			wchar_t cnt[32];
			swprintf(cnt, L"%d", _count[i]);
			g_temp_uisys->draw_text(icon_drawx + _table_cell_size.x - 30, icon_drawy + paddingy, cnt, wcslen(cnt), _table_cell_size.x);
		}
	}

	//g_rhi->disable_stencil_test();
	if(rel_x>0&&rel_x< _table_size.x&&dx+_table_cell_size.x<_table_size.x&&rel_y>0&&rel_y< _table_size.y)
	{
		_content_y += Input::get_mouse_scroller() * 50;
		
		
		int tl = (_item_names.size() +2)/ 3*_table_cell_size.y;
		if (_content_y<_table_size.y-tl)
		{
			_content_y = _table_size.y - tl;
		}
		if (_content_y > 0)_content_y = 0;
		_content_y = _content_y / _table_cell_size.y*_table_cell_size.y;
		int idx = k * 3 + j;
		if (idx < _discriptions.size())
		{
			_readme_text->set_text(_discriptions[idx].data());


			
			int ddy = dy + oy + _table_relative_pos.y + _content_y;
			int fdy = RBMath::get_max(ddy, oy);
			int fdh = _table_cell_size.y;
			if (ddy < oy)
			{
				fdh -= (oy - ddy);
			}

			if (ddy + _table_cell_size.y > oy + _table_size.y + _table_relative_pos.y)
			{
				fdh -= (fdy + _table_cell_size.y - oy - _table_size.y - _table_relative_pos.y);
			}
			if (Input::get_sys_key_up(WIP_MOUSE_LBUTTON))
			{
				g_audio_manager->Play("event:/talk_se");
				remove_item(idx);
			}
			if(Input::get_sys_key_pressed(WIP_MOUSE_LBUTTON))
				g_temp_uisys->draw_box(dx + ox + _table_relative_pos.x, fdy+2, _table_cell_size.x-2, fdh-4, RBColorf(0.7, 0.7, 0.7, 0.5));
			else
				g_temp_uisys->draw_box(dx + ox + _table_relative_pos.x, fdy, _table_cell_size.x, fdh, RBColorf(0.7, 0, 0, 0.5));
		}
	}

	_readme_text->draw(ox, oy);
	_readme_text->set_text(L"");
}




TableTextPanel::TableTextPanel(int x, int y, int width, int height)
{
	_x = x; _y = y;
	_width = width;
	_height = height;
	_readme_text = new TextWidget(10, 410, 650, 180);
	_readme_text->set_text(L"");
}

TableTextPanel::~TableTextPanel()
{
}
