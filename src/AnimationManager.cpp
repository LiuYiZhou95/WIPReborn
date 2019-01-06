#include "AnimationManager.h"
#include "AnimationClip.h"
#include "FrameBox.h"
#include "RBMath/Inc/RBMath.h"

#include "Render.h"


//WIPAnimationManager* WIPAnimationManager::_instance = 0;

WIPAnimationManager* WIPAnimationManager::instance()
{
	static WIPAnimationManager* _instance;
	if(!_instance)
		_instance = new WIPAnimationManager();
	return _instance;
}

bool WIPAnimationManager::startup(f32 delta/* = 1/24*/)
{
	_delta_t = delta;
	return true;
}

void WIPAnimationManager::shutdown()
{

}

void WIPAnimationManager::update(f32 dt)
{
	/*
	_cur_dt+=dt;
	if(dt<_delta_t)
		return;
		*/
	WIPClipInstance* clip;
	i32 step = 1;
	WIPFrameBox* frame;
	i32 index = 0;
	i32 n = 0;
	int i = 0;
	if (_clip_queue.empty())
		return;
	//clip = _clip_queue.front();
	//while(i<_clip_queue.size())

	list<WIPClipInstance*>::iterator it = _clip_queue.begin();

	for (; it!=_clip_queue.end();++it)
	{
		clip = *it;
		if (clip->will_stop)
		{
			//be sure finish
			clip->bplaying = false;
			_remove_list.push_back(clip);
			clip->will_stop = false;
		}
		if (clip->stop_now)
		{
			clip->bplaying = false;
			_remove_list.push_back(clip);
			clip->stop_now = false;
			continue;
		}
		clip->cur_dt += dt * clip->speed;
		//printf("\n\n%d",clip);
		if (RBMath::abs(clip->cur_dt) >= _delta_t + 0.001)
		{

			step = clip->cur_dt>0 ? 1 : -1;

			//printf("\n\n%d\n%f\n%f",clip,clip->_cur_dt-dt,clip->_cur_dt);
			frame = clip->frame_box_ref;
			index = (clip->cur_frame - 1) * 8;
			frame->lt.x = clip->clip_ref->_uvs[index];
			frame->lt.y = clip->clip_ref->_uvs[index + 1];
			frame->lb.x = clip->clip_ref->_uvs[index + 2];
			frame->lb.y = clip->clip_ref->_uvs[index + 3];
			frame->rb.x = clip->clip_ref->_uvs[index + 4];
			frame->rb.y = clip->clip_ref->_uvs[index + 5];
			frame->rt.x = clip->clip_ref->_uvs[index + 6];
			frame->rt.y = clip->clip_ref->_uvs[index + 7];
			clip->cur_frame += step;

			if (clip->cur_frame>clip->clip_ref->_total_frame)
			{

				clip->cur_frame = 1;
				if (!clip->bloop)
				{
					clip->bplaying = false;
					//finish callback
					if (clip->cb)
						clip->cb(clip->obj_ref);
					_remove_list.push_back(clip);
				}

			}
			else if (clip->cur_frame<1)
			{
				//once set the speed to negtive be sure to set the frame to the last
				//and be sure that set the speed only when the clip is stop
				clip->cur_frame = clip->clip_ref->_total_frame;
				if (!clip->bloop)
				{
					clip->bplaying = false;
					//finish callback
					if (clip->cb)
						clip->cb(clip->obj_ref);
					_remove_list.push_back(clip);
				}

			}
			clip->cur_dt = 0;
		}

		
	}

	for (int i = 0; i < _remove_list.size(); ++i)
	{
		_clip_queue.remove(_remove_list[i]);
	}
	_remove_list.clear();


}

void WIPAnimationManager::remove_clip(WIPClipInstance* clip)
{
	clip->bplaying = false;
	list<WIPClipInstance*>::iterator it = _clip_queue.begin();
	for (; it != _clip_queue.end(); ++it)
	{
		if (*it == clip)
		{
			break;
		}
	}
	if (it != _clip_queue.end())
	{
		_clip_queue.erase(it);
	}
}

void WIPAnimationManager::add_clip(WIPClipInstance* clip)
{
	/*
	if(!clip)
		return;
	*/
	clip->bplaying = true;
	//clip->cur_dt = _delta_t + 0.001;
	//_clip_queue.push_back(clip);
	///++_queue_szie;
	_clip_queue.push_back(clip);

}

void WIPAnimationManager::add_clip_back(WIPClipInstance* clip)
{
	clip->bplaying = true;
	//clip->cur_dt = _delta_t + 0.001;
	_clip_queue.push_back(clip);
}

void WIPAnimationManager::add_clip_front(WIPClipInstance* clip)
{
	clip->bplaying = true;
	//clip->cur_dt = _delta_t + 0.001;
	_clip_queue.push_front(clip);
}

WIPAnimationManager::WIPAnimationManager()
{
	_delta_t = 1/24;
}

WIPAnimationManager::~WIPAnimationManager()
{
	_clip_queue.clear();
	_remove_list.clear();
}


//WIPAnimationManager* g_animation_manager = WIPAnimationManager::instance();

WIPFrameAnimationPlayer * WIPFrameAnimationPlayer::instance()
{
	static WIPFrameAnimationPlayer* _instance;
	if (!_instance)
		_instance = new WIPFrameAnimationPlayer();
	return _instance;
}


bool WIPFrameAnimationPlayer::startup(int dis_x,int dis_y,int displayw, int displayh)
{
	_dis_x = dis_x; _dis_y = dis_y;
	_displayw = displayw; _displayh = displayh;
	_used = true;

	return true;
}

void WIPFrameAnimationPlayer::shutdown()
{
}

//add-hoc
#include "GLFWApp.h"

bool WIPFrameAnimationPlayer::update(f32 dt)
{
	if (!_playing_clip) return true;
	_playing_clip->_cur_dt += dt * _playing_clip->_speed;
	//LOG_INFO("%f\n", _playing_clip->_cur_dt);
	if (RBMath::abs(_playing_clip->_cur_dt) >= _delta_t + 0.001)
	{
		_playing_clip->_cur_dt = 0.f;
		//from 0 begin
		if (++_playing_clip->_cur_frame>=_playing_clip->_total_frame)
		{
			_playing_clip->_cur_frame = 0;
			_playing_clip->bplaying = false;
			return true;
		}
	}
	g_temp_uisys->begin();
	g_temp_uisys->clear();
	g_temp_uisys->draw_picture(0, 0, _displayw, _displayh, _playing_clip->_textures[_playing_clip->_cur_frame]);
	g_temp_uisys->end();
	//g_rhi->clear_back_buffer();
	

	//g_app->swap();
	return false;
}

#include "WIPTime.h"

void WIPFrameAnimationPlayer::play_clip(WIPFrameAnimationClip * clip)
{
	if (!_used)
	{
		LOG_ERROR("Not init!");
		return;
	}
	if (_playing_clip&& _playing_clip->bplaying) return;
	_playing_clip = clip;
}
