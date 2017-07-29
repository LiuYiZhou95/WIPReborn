#ifndef __ACTIVEDRAWABLE_H__
#define __ACTIVEDRAWABLE_H__
#include <string>
#include "../wip/RenderTexture.h"
//�����л��࣬�ɼ������Ⱦ�ľ���
//��Ϣ���ݣ�������ƣ���Ⱦ�ȵ�
//����Fbo������������fbo.draw()������
class ActiveDrawableRect
{
public:
	ActiveDrawableRect(void);
	~ActiveDrawableRect(void);

	virtual void update(float dt);
	//if not specified the position,draw with _x,_y
	virtual void draw_internal(int x=-1,int y=-1);
	virtual void draw(int x=-1,int y=-1);

	virtual void reshape(int width,int height,int x=-1,int y=-1);

	void set_id(int id);
	int get_id();
	void set_name(std::string name);
	std::string get_name();
	WIPRenderTexture* get_fbo();
	virtual void set_position(int,int);
	void set_activate(bool val);
	bool is_active();

	//editor
	void set_mouse_position();
	void cancel_mouse_position();
	bool is_mouse_position();
	virtual void update_editor();
	ActiveDrawableRect** get_all_contents();
	int get_all_num();
	bool bdraw;
protected:
	int _x,_y;
	int _old_w,_old_y;
	int _width,_height;
	WIPRenderTexture* _fbo;
	std::string _name;
	int _id;
	bool _bmouse_position;
	bool _last_mouse;
	//�����Ƿ����
	bool _bactive;

	ActiveDrawableRect *_contents[64];
	int _all_num;
};

#endif