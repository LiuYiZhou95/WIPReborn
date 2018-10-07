#pragma once
#include "QuadTree.h"
#include <string>
#include <queue>
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

#if 1

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
	WIPScene1() :initilized(false)
	{
	}
	~WIPScene1();
	void create_sprite();
	void create_camera();
	

	void init(float world_sizex, float world_sizey, int max_depth);
	void add_sprite(WIPSprite* sprite);
	//delete related_scene may detroy iterator.
	void remove_sprite(WIPSprite* sptrite, bool op_related_scene = true);
	WIPCamera* create_camera(f32 w, f32 h, f32 sw, f32 sh, int iww, int iwh);
	void update_sprite(WIPSprite*  sprite);
	void sort_by_y(std::vector<WIPSprite* > v);
	void update_zorder_by_type_tag(std::string type_tag, f32 min_z = 0.2f, f32 max_z = 0.8f);
	void update_zorder_by_type_tag(const WIPSprite*  s, std::string type_tag, f32 min_z = 0.2f, f32 max_z = 0.8f);
	void update(f32 dt);
	void fix_update(f32 dt);
	void init_components();
	void destroy_components();
	
	WIPSprite* get_sprite_by_tag(const std::string& name) const;
	void clear();

private:
	

	std::vector<WIPCamera*> cameras;

	std::vector<TRefCountPtr<WIPSprite>> objects;

	bool initilized;

	float world_size_x, world_size_y;
	WIPQuadTree* quad_tree;
};



#endif

class WIPLevelLoader : public FRefCountedObject
{
public:
	virtual void load_level(int id, const RBVector2& pos) = 0;
	virtual void init_game() = 0;
};
class WIPScene : public FRefCountedObject
{
public:
	static WIPScene* instance();
protected:
	WIPScene() :initilized(false)
	{
	}
	~WIPScene();
public:
	void init(float world_sizex, float world_sizey, int max_depth);
	void add_sprite(WIPSprite* sprite);
	void add_camera(WIPCamera* camera);
	void load_sprite(WIPSprite* sprite);
	void load_camera(WIPCamera* camera);
	//may detroy iterator.
	void remove_sprite(WIPSprite*  sptrite, bool op_related_scene = true);
	static WIPCamera* create_camera(f32 w, f32 h, f32 sx,f32 sy, f32 sw, f32 sh, int iww, int iwh);
	void update_sprite(WIPSprite*  sprite);
	void sort_by_y(std::vector<WIPSprite* > v);
	void update_zorder_by_type_tag(std::string type_tag, f32 min_z = 0.2f, f32 max_z = 0.8f);
	void update_zorder_by_type_tag(const WIPSprite*  s, std::string type_tag, f32 min_z = 0.2f, f32 max_z = 0.8f);
	void update(f32 dt);
	void fix_update(f32 dt);
	void render_world();
	void render_ui();
	void init_components();
	void destroy_components();
	WIPSprite* get_sprite_by_tag(const std::string& name) const;
	WIPCamera* get_camera(const std::string& name) const;
	void clear(bool destroy_persistent=false);

	void cancel_object_change();
	void submit_object_change();
	//creating or deleting objects will happened at the end of a frame!
	void pending_objects(WIPSprite* s);
	//add object to scene in case of destory iterator.
	void creating_object(WIPSprite* s);
	std::vector< WIPSprite*> _deleting_objects;
	std::vector< WIPSprite*> _creating_objects;

	//00-nothing 10-unload 01-load 11-reload
	FORCEINLINE void reset_level_load_state(){ level_change_state = 0; }
	FORCEINLINE void set_level_load(){ level_change_state |= 1; }
	FORCEINLINE void set_level_unload(){ level_change_state |= 2; }
	//sumbit loading and unloading
	void submit_level_change();


	bool initilized;
	uint level_change_state = 0;
	float world_size_x,world_size_y,world_depth;
	WIPQuadTree* quad_tree;
	//the only strong ref
	std::vector<TRefCountPtr<WIPSprite>> objects;
	std::vector<TRefCountPtr<WIPCamera>> cameras;
	//std::vector<WIPSprite* > persistent_objects;
	//std::vector<TRefCountPtr<WIPCamera>> persistent_cameras;
	class WorldRender* world_renderer=nullptr;
	WIPLevelLoader* loader = nullptr;
	void load_level(int id=0,const RBVector2& pos=RBVector2::zero_vector);
	
private:
	friend class WIPLevelLoader;
	std::vector<TRefCountPtr<WIPSprite>> loaded_objects;
	std::vector<TRefCountPtr<WIPCamera>> loaded_cameras;
	//todo:check->if donnot use auto_ptr, a problem about vector iter incompletion will occur when call object::init_component().
	std::vector<TRefCountPtr<WIPSprite> > _objects_cache;

	

};

extern WIPScene* g_scene;