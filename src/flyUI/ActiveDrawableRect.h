#pragma once
#include <string>
#include "Input.h"
#include "RenderResource.h"
#include "Object.h"

/*
2014.11
*/
//抽象公有基类，可激活、可渲染的矩形
//消息传递，激活控制，渲染等等
//画满Fbo，最终缩放由fbo.draw()来控制
class ActiveDrawableRect : public WIPObject
{
public:
	WIPOBJECT(ActiveDrawableRect, WIPObject);
	WIP_MEM(ActiveDrawableRect);
	ActiveDrawableRect(void);
	virtual ~ActiveDrawableRect(void) = 0;

	virtual void update(float dt,int x,int y);
	//if not specified the position,draw with _x,_y
	virtual void draw_internal(int x=-1,int y=-1);
	virtual void draw(int x=-1,int y=-1);

	virtual void reshape(int width,int height,int x=-1,int y=-1);

	void set_id(int id);
	int get_id();
	void set_name(std::string name);
	std::string get_name();
	WIPRenderTexture2D* get_fbo();
	virtual void set_position(int,int);
	void set_activate(bool val);
	bool is_active();

	//editor
	void set_mouse_position();
	void cancel_mouse_position();
	bool is_mouse_position();
	virtual void update_editor(int x,int y);
	ActiveDrawableRect** get_all_contents();
	int get_all_num();
	bool bdraw;
protected:
	int _x,_y;
	int _old_w,_old_y;
	int _width,_height;
	WIPRenderTexture2D* _fbo;
	std::string _name;
	int _id;
	bool _bmouse_position;
	bool _last_mouse;
	//按键是否可用
	bool _bactive;

	ActiveDrawableRect *_contents[64];
	int _all_num;
};
