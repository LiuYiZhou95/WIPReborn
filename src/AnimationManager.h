#pragma once
#include "RBMath/Inc/Platform/RBBasedata.h"
#include <list>
#include "LinkList.h"
#include <list>
#include <vector>
#include "RefCount.h"

using std::list;
using std::vector;

#define WIP_ANIMATION_DELTA_T 1/24.f

class WIPAnimationClip;
class WIPClipInstance;

class WIPAnimationManager : public FRefCountedObject
{
public:
	static WIPAnimationManager* instance();

	bool startup(f32 delta = 1/24);
	void shutdown();
	void update(f32 dt);

	void add_clip(WIPClipInstance* clip);
	void add_clip_back(WIPClipInstance* clip);
	void add_clip_front(WIPClipInstance* clip);

	//remove clip now !
	void remove_clip(WIPClipInstance* clip);

protected:
	WIPAnimationManager();
	~WIPAnimationManager();

private:

	

	//typedef LinkList<WIPClipInstance*> _ClipQueue;
	//_ClipQueue _clip_queue;
	//i32 _queue_szie;

	//f32 _cur_dt;
	f32 _delta_t;

	list<WIPClipInstance*> _clip_queue;
	vector<WIPClipInstance*> _remove_list;
};




extern WIPAnimationManager* g_animation_manager;


//this is just a game related system should not be here or to redesign!!!
class WIPFrameAnimationPlayer : public FRefCountedObject
{
public:
	static WIPFrameAnimationPlayer* instance();

	bool startup(int dis_x, int dis_y,int displayw,int displayh);
	void shutdown();
	

	void play_clip(class WIPFrameAnimationClip* clip);
	bool update(f32 dt);
protected:
	WIPFrameAnimationPlayer()
	{}
	~WIPFrameAnimationPlayer() {}


	
private:
	bool _used=false;
	//f32 _cur_dt;
	f32 _delta_t= WIP_ANIMATION_DELTA_T;
	int _dis_x, _dis_y;
	int _displayw, _displayh;
	class WIPFrameAnimationClip* _playing_clip = nullptr;
};

extern WIPFrameAnimationPlayer* g_frame_player;