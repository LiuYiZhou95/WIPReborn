#ifndef __BUTTON_H__
#define __BUTTON_H__
#include "BaseWidget.h"
#include <string>
#include "RenderResource.h"

class ButtonWidget : public BaseWidget
{
public:
	WIPOBJECT(ButtonWidget, BaseWidget);
	WIP_MEM(ButtonWidget);
	ButtonWidget();
	~ButtonWidget();
	void init_button(std::string pic_path_down,std::string pic_path_move,std::string pic_path_normal,void (*button_event)(ButtonWidget*));
	virtual void update_button(int,int,int,int);
	//void draw();
	void set_position(int __x,int __y);
	inline void set_mouse_state(int mx,int my,int _state)
	{
		_mouse_state = _state;
		_mx = mx;
		_my = my;
	}


	void update(float dt, int x, int y);

	virtual void draw_internal(int x=-1,int y=-1);

	virtual void draw(int x=-1,int y=-1);

	void set_size(int width,int height);


	bool call;
protected:
	bool _draw;
	WIPTexture2D* _image_down;
	WIPTexture2D* _image_move;
	WIPTexture2D* _image_normal;
	void (*_button_event)(ButtonWidget*);
	int _gw;
	int _gh;
	int _mouse_state;
	int _button_state;
	int _last_button_state;
	int _mx;
	int _my;
	int _last_mouse_state;

private:
	
};

#include "Vector2.h"

class TextWidget : public BaseWidget
{
public:
	WIPOBJECT(TextWidget, BaseWidget);
	WIP_MEM(TextWidget);
	TextWidget(int x, int y, int width, int height);
	~TextWidget();

	void set_text(const wchar_t* chs) { _text = chs; }

	void update(float dt, int x, int y);

	virtual void draw_internal(int x = -1, int y = -1);
	//if not specified the position,draw with _x,_y
	void draw(int x = -1, int y = -1);
	void set_text_padding(int x_padding,int y_padding=0);
private:
	wstring _text;
	RBVector2I padding = RBVector2I(20,8);
	//WIPTexture2D* _background;
};
#endif