#pragma once
#include "RBMath/Inc/Platform/RBBasedata.h"
#include <string>

#define ATLAS			1
#define PICTURES		2

class WIPFrameBox;
class WIPSpriteFrame;
class WIPAnimation;
class WIPAnimationManager;

class WIPAnimationClip
{
public:
	bool bplaying;
	bool bloop;
	std::string name;
	//ATLAS or PICTURE
	i32 texture_type;

	~WIPAnimationClip();

	//find texture from atlas files.TODO:dtor
	static WIPAnimationClip* create_with_atlas(const char* name,const char* atlas_file);

	WIPAnimationClip(const char* name,bool loop);


public:
	friend WIPAnimation;
	friend WIPAnimationManager;
	//lt,lb,rb,rt->next::size=_tatal_frameX8
	f32* _uvs;
	i32 _total_frame;

	f32 _speed;
	//WIPFrameBox* _framebox_ref;
	f32 _cur_dt;
	//begin with 1
	i32 _cur_frame;
	
	bool _will_stop;

};

class WIPClipInstance
{
public:
	WIPClipInstance(WIPFrameBox* fb,const class WIPAnimationClip* clip)
		:frame_box_ref(fb),clip_ref(clip)
	{
		speed = clip->_speed;
		cur_dt = clip->_cur_dt;
		cur_frame = clip->_cur_frame;
		will_stop = clip->_will_stop;
		bplaying = clip->bplaying;
		bloop = clip->bloop;
		stop_now = false;
	}
	f32 speed;
	f32 cur_dt;
	i32 cur_frame;
	bool will_stop;
	bool stop_now;
	bool bplaying;
	bool bloop;
	WIPFrameBox* frame_box_ref;
	const class WIPAnimationClip* clip_ref;
};