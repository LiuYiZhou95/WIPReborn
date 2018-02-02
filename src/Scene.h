#pragma once
#include "QuadTree.h"
#include <string>
#include "RefCount.h"

class WIPSprite;
class WIPCamera;
class WIPScene;

//1.we dont surpport mulitple world
//2.world is a container of so many objects
//3.scene is just a stage of worlds
class WIPWorld
{
public:
	WIPWorld();
	~WIPWorld();

private:
	std::vector<WIPSprite*> _objects;
	std::vector<WIPCamera*> _cameras;
};



//����ȫ��ֻ��һ������ֻ������һ���£�����һ��level����������object��run����object
//�������������,�������Ϊ�����������������ͼ�������������������ͨ��active������
//�����г�����Ϸ�е�����object��һ��list�����ºͲ�ѯ����ͬ�࣬active�����Ƿ���£��ر�ģ�
//��������һ���־�list�����ڴ����Щ�������ڿ�Խ�ؿ���objects����ЩobjectsҲ������ºͲ�ѯ��
//���ǲ������Ÿı�ؿ��������٣�����object��������object�ǲ��Ƽ��ģ�
//����ÿ�ιؿ�load��ɵ�ʱ�򣬶������object��start��������ʱ������һЩ��ʼ��������
//ͬ���ؿ�����ʱҲ�����end����
//һ���ؿ�����һ�����ݣ�����͸��������Щ���ݣ�Ȼ��ִ����Щ������������������
//�����û��Զ���Ľű������C++��������Ϊһ��ScriptComponent
//Ϊ�˱�֤����ԣ�SceneӦ��������ϸС�Ľӿڣ�load_levelӦ�ñ�һ��Loader������
class WIPScene1 :public FRefCountedObject
{
public:
	void create_sprite();
	void create_camera();


private:
	

	typedef HashLink<WIPSprite> object_list_t;
	std::list<WIPCamera*> _cameras;

	object_list_t _objects;
	u32 _object_num = 0;
	object_list_t _persistent_objects;
	u32 _persistent_object_num = 0;
};

class WIPScene : public FRefCountedObject
{
public:
	WIPScene():initilized(false)
	{
	}
	~WIPScene();

	void init(float world_sizex, float world_sizey, int max_depth);
	void add_sprite(TRefCountPtr<WIPSprite> sprite);
	//delete related_scene may detroy iterator.
	void remove_sprite(TRefCountPtr<WIPSprite> sptrite,bool op_related_scene=true);
	WIPCamera* create_camera(f32 w, f32 h, f32 sw, f32 sh, int iww, int iwh);
	void update_sprite(TRefCountPtr<WIPSprite> sprite);
	void sort_by_y(std::vector<TRefCountPtr<WIPSprite>> v);
	void update_zorder_by_type_tag(std::string type_tag,f32 min_z=0.2f,f32 max_z=0.8f);
	void update_zorder_by_type_tag(TRefCountPtr<const WIPSprite> s, std::string type_tag, f32 min_z = 0.2f, f32 max_z = 0.8f);
	void update(f32 dt);
	void fix_update(f32 dt);
	void init_components();
	void destroy_components();
	WIPSprite* get_sprite_by_tag(const std::string& name) const;
	void clear();
	//todo
	void change_level(){}
	bool initilized;
	float world_size_x,world_size_y;
	WIPQuadTree* quad_tree;
	std::vector<TRefCountPtr<WIPSprite>> objects;
	std::vector<WIPCamera*> cameras;
};