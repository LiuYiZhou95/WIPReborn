#pragma once
#include "RenderResource.h"
#include "define.h"
#include "ActiveDrawableRect.h"
//#include <vector>

class BaseWidget;

class BasePanel : public ActiveDrawableRect
{
public:
	WIPOBJECT(BasePanel, ActiveDrawableRect);
	WIP_MEM(BasePanel);
	BasePanel(int x,int y,int width,int height);
	~BasePanel();

	void set_color();
	void set_background(const char* path);

	void add_panel(BasePanel* panel);
	void add_widget(BaseWidget* widget);

	void update(float dt,int x, int y);

	virtual void draw_internal(int x=-1,int y=-1);
	//if not specified the position,draw with _x,_y
	void draw(int x=-1,int y=-1,int width=0,int height=0);

protected:
	WIPTexture2D* _background;
	//ofTrueTypeFont _font;

	//ofFbo _fbo;

	std::vector<BasePanel*> _sub_panels;
	std::vector<BaseWidget*> _widgets;
private:
	/*
	int _x,_y;
	int _width,_height;
	*/


};


class TiledPanel :public BasePanel
{
public:

};

#include "Vector2.h"
#include "BaseWidget.h"
#include <map>

class TableTextPanel : public BaseWidget
{
public:
	WIPOBJECT(TableTextPanel, BaseWidget);
	WIP_MEM(TableTextPanel);
	TableTextPanel(int x, int y, int width, int height);
	~TableTextPanel();

	void set_color();
	void set_background(const char* path);

	void add_item(const wstring& name, const wstring& disc,const WIPTexture2D* t=nullptr,int cnt=1);
	void remove_item(const wstring& name, int cnt = 1);
	void remove_item(int idx, int cnt = 1);


	void update(float dt, int x, int y);

	virtual void draw_internal(int x = -1, int y = -1) {}

	void draw(int x = -1, int y = -1);
	
private:

	const WIPTexture2D* bachground = nullptr;

	std::vector<wstring> _discriptions;
	std::vector<wstring> _item_names;
	std::vector<const WIPTexture2D*> _icons;
	std::vector<int> _count;

	std::vector<class TextWidget*> _texts;
	class TextWidget* _readme_text;
	RBVector2I _table_relative_pos = RBVector2I(10,0);
	RBVector2I _table_size = RBVector2I(650, 400);
	int _content_y = 0;
	RBVector2I _table_cell_size = RBVector2I(200,40);
};