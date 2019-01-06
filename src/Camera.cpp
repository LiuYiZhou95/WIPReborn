#if 1
#include "Camera.h"
#include "Sprite.h"
#include "Logger.h"
#include "RBMath/Inc/RBMath.h"
#include "Scene.h"
#include <algorithm>
#include "Render.h"



WIPCamera::WIPCamera(f32 w, f32 h, f32 px, f32 py, f32 sw, f32 sh, int iww, int iwh)
{
	world_x = world_y = 0.f;
	world_h = h;
	world_w = w;
	_active = true;
	_zoom = 1.f;
	window_h = iwh;
	window_w = iww;
	viewport = g_rhi->RHICreateViewPort(px, py, sw, sh);
	
}

WIPCamera::~WIPCamera()
{
}

void WIPCamera::reset_ratio(f32 ratio)
{
	f32 new_height = world_w * ratio;
	i32 height = static_cast<i32>(new_height);
	world_h = height;
}

RBVector2 WIPCamera::camera_to_world(const RBVector2& camera_pos) const 
{
	return RBVector2(world_x+camera_pos.x,world_y+camera_pos.y);
}

RBVector2 WIPCamera::world_to_camera(const RBVector2& world_pos) const
{
	return RBVector2(world_pos.x-world_x,world_pos.y-world_y);
}

RBVector2 WIPCamera::screen_to_world(const RBVector2I& screen_pos) const
{
	return camera_to_world(ndc_to_camera(screen_to_ndc(screen_pos)));
	int x = screen_pos.x;
	int y = window_h - screen_pos.y;
	f32 ndcx = (x - viewport->x)*2.f/viewport->w-1.f;
	f32 ndcy = (y - viewport->y)*2.f/viewport->h-1.f;
	f32 w1 = world_w*0.5f*_zoom;
	f32 w2 = world_h*0.5f*_zoom;
	return RBVector2(ndcx*w1+world_x,ndcy*w2 + world_y);
}

RBVector2I WIPCamera::world_to_screen(const RBVector2 & world_pos) const
{
	return ndc_to_screen(camera_to_ndc(world_to_camera(world_pos)));
	RBVector2 newp = world_pos - RBVector2(world_x, world_y);
	f32 w1 = world_w*0.5f*_zoom;
	f32 w2 = world_h*0.5f*_zoom;
	newp.x = (newp.x/w1+1.f)*viewport->w*0.5f+viewport->x;
	newp.y = (newp.y/w2+1.f)*viewport->h*0.5f+viewport->y;

	return RBVector2I(newp.x+0.5f,newp.y+0.5f);
}

RBVector2 WIPCamera::screen_to_camera(const RBVector2I& screen_pos) const
{
	return ndc_to_camera(screen_to_ndc(screen_pos));
	int x = screen_pos.x;
	int y = window_h - screen_pos.y;
	f32 ndcx = (x - viewport->x)*2.f / viewport->w - 1.f;
	f32 ndcy = (y - viewport->y)*2.f / viewport->h - 1.f;
	f32 w1 = world_w*0.5f*_zoom;
	f32 w2 = world_h*0.5f*_zoom;
	return RBVector2(ndcx*w1, ndcy*w2);
}

RBVector2 WIPCamera::camera_to_ndc(const RBVector2 & cam_pos) const
{
	f32 w1 = world_w * 0.5f*_zoom;
	f32 w2 = world_h * 0.5f*_zoom;
	return RBVector2(cam_pos.x / w1, cam_pos.y / w2);
}

RBVector2 WIPCamera::ndc_to_camera(const RBVector2 & ndc_pos) const
{
	f32 w1 = world_w * 0.5f*_zoom;
	f32 w2 = world_h * 0.5f*_zoom;
	return ndc_pos*RBVector2(w1,w2);
}

RBVector2 WIPCamera::screen_to_ndc(const RBVector2I& screen_pos) const
{
#ifndef USE_D3D
	//auto* viewport = g_rhi->get_active_viewport();
	int x = screen_pos.x ;
	//ndc ori is on the left down
	//viewport ori left down
	int y = window_h -  screen_pos.y;
	f32 ndcx = (x)*2.f / window_w - 1.f;
	f32 ndcy = (y)*2.f / window_h - 1.f;
	return RBVector2(ndcx, ndcy);
#endif
}

RBVector2I WIPCamera::ndc_to_screen(const RBVector2 & ndc_pos) const
{
#ifndef USE_D3D
	f32 x = (ndc_pos.x+1.f)*window_w*0.5f;
	f32 y = (ndc_pos.y+1.f)*window_h*0.5f;
	y = window_h - y;
	return RBVector2I(x+0.5f,y+0.5f);
#endif
}

void WIPCamera::set_background_color(const WIPColorf& color)
{

}

void WIPCamera::move(f32 dx,f32 dy)
{
	world_x += dx;
	world_y += dy;
}

void WIPCamera::move_to(f32 x,f32 y)
{
	world_x = x;
	world_y = y;
}


void WIPCamera::set_active(bool val)
{
	_active = val;
}

bool WIPCamera::get_active()
{
	return _active;
}

#endif