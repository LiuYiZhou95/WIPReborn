#include "GLFWApp.h"
#include "../AnimationClip.h"
#include "../AnimationManager.h"
#include "../FileSystem.h"
#include "../IniHelper.h"
#include "../Logger.h"
#include "../QuadTree.h"
#include "../Render.h"
#include "../ResourceManager.h"
#include "../Scene.h"
#include "../ScriptManager.h"
#include "../Sprite.h"
#include "../WIPTime.h"
#include "../InputManager.h"
#include "../Input.h"
#include "../Camera.h"
#include "../PhysicsManager.h"
#ifndef _WIN32
#include "unistd.h"
#endif

#include "UserComponent.h"
#include "AudioManager.h"

#ifdef _WIN32
#include "windows.h"
#endif // _WIN32


void open_explorer(const wchar_t* path)
{
#ifdef WIN32
	ShellExecuteW(0, L"open", 0, 0, path, SW_SHOWNORMAL);
#endif
}

std::wstring to_wstring(const std::string &str)
{
	std::wstring wstr(str.length(), L' ');
	std::copy(str.begin(), str.end(), wstr.begin());
	return wstr;
}

//只拷贝低字节至string中
std::string to_string(const std::wstring &wstr)
{
	std::string str(wstr.length(), ' ');
	std::copy(wstr.begin(), wstr.end(), str.begin());
	return str;
}

bool GLFWApp::init()
{
	scoller_y = 0;
	window_w = 1024;
	window_h = 768;
	bool ret = create_window("Demo");

	WIPFileSystem &fs = *g_filesystem;
	std::string cur_path = fs.get_current_dir();

	fs.set_current_dir("./data/");
	LOG_NOTE("cur path:%s", fs.get_current_dir().c_str());

	std::string lua_project_path;
	std::string lua_ini_path;
	std::string log_path;
	f32 fps;

	std::string apath;

	std::string path = "WIPCFG.ini";
	if (WIPIniHelper::reset_ini_file(path.data()))
	{
		WIPIniHelper::get_float("Common", "fps", fps);
		WIPIniHelper::get_string("Common", "project", lua_project_path);
		WIPIniHelper::get_string("Common", "script_init", lua_ini_path);
		WIPIniHelper::get_string("Common", "log", log_path);

		WIPIniHelper::close();
		LOG_INFO("Reading ini file...");
	}
	else
	{
		LOG_ERROR("Read ini failed!\n");
		require_exit();
	}

	LOG_INFO("Logger start up...");
	g_logger->startup(log_path.c_str());
	
	g_logger->new_log();

	LOG_INFO("Logger start up success...");


	g_script_manager->startup();
	g_script_manager->load_file(lua_project_path.c_str());
	LOG_INFO("Script start up...");


	times = new TimeSource();
	RBClock::init(times);
	clock = RBClock::Instance();

	timer = new RBTimerBase(*clock);
	clock->set_filtering(10, 1.f / fps);
	lastTime = timer->get_time();
	clock->update();
	LOG_INFO("Time start up...");


	_frame = 1.f / fps;

	g_rhi->init();
	LOG_INFO("RHI start up...");


	scene = new WIPScene();
	scene->init(1, 1, 4);
	LOG_INFO("Creating scene...");


	world_renderer = new WorldRender();
	world_renderer->init();
	world_renderer->set_world(scene);
	LOG_INFO("Renderer start up...");

	text_renderer = new TextRender(512,512);
	text_renderer->init();
	text_renderer->load_font("./font/simkai.ttf", 25, 25);

	

	g_physics_manager->startup();
	LOG_INFO("Physics start up...");


	g_input_manager->startup("");
	LOG_INFO("Input start up...");

	g_animation_manager->startup(0.15);
	LOG_INFO("Animation start up...");


	

	cameras.push_back(scene->create_camera(20.f, 20.f, window_w, window_h, window_w, window_h));
	cameras[0]->move_to(5.f, 5.f);

	ui_renderer = new UIRender();
	ui_renderer->init(cameras[0]);


	g_physics_manager->set_debug_camera(cameras[0]);


	clip = WIPAnimationClip::create_with_atlas("walk_down", "./clips/1.clip");
	
	clip1 = WIPAnimationClip::create_with_atlas("walk_left", "./clips/2.clip");
	clip2 = WIPAnimationClip::create_with_atlas("walk_right", "./clips/3.clip");
	clip3 = WIPAnimationClip::create_with_atlas("walk_up", "./clips/4.clip");
	clip_s = WIPAnimationClip::create_with_atlas("stand_down", "./clips/1s.clip");
	clip1_s = WIPAnimationClip::create_with_atlas("stand_left", "./clips/2s.clip");
	clip2_s = WIPAnimationClip::create_with_atlas("stand_right", "./clips/3s.clip");
	clip3_s = WIPAnimationClip::create_with_atlas("stand_up", "./clips/4s.clip");

	auto res_handle1 = g_res_manager->load_resource("./pic/zhaolinger_1_8.png", WIPResourceType::TEXTURE);
	int ww = ((TextureData *)(res_handle1->extra))->width;
	int hh = ((TextureData *)(res_handle1->extra))->height;
	auto res_handle2 = g_res_manager->load_resource("./pic/xianling_5.jpg", WIPResourceType::TEXTURE);
	int ww1 = ((TextureData *)(res_handle2->extra))->width;
	int hh1 = ((TextureData *)(res_handle2->extra))->height;
	auto res_handle1mask = g_res_manager->load_resource("./pic/xianling_5_2.png", WIPResourceType::TEXTURE);
	int ww1mask = ((TextureData *)(res_handle1mask->extra))->width;
	int hh1mask = ((TextureData *)(res_handle1mask->extra))->height;
	auto res_handle1fog = g_res_manager->load_resource("./pic/fog.png", WIPResourceType::TEXTURE);
	int ww1fog = ((TextureData *)(res_handle1fog->extra))->width;
	int hh1fog = ((TextureData *)(res_handle1fog->extra))->height;

	float rot = ww / (float)hh;



	auto res_lixiaoyao = g_res_manager->load_resource("./pic/lixiaoyao_orijan.png", WIPResourceType::TEXTURE);
	int wli = ((TextureData *)(res_lixiaoyao->extra))->width;
	int hli = ((TextureData *)(res_lixiaoyao->extra))->height;
	auto res_zaji1 = g_res_manager->load_resource("./pic/suzhou_people.png", WIPResourceType::TEXTURE);
	int wzaji1 = ((TextureData *)(res_zaji1->extra))->width;
	int hzaji1 = ((TextureData *)(res_zaji1->extra))->height;
	auto res_zaji2 = g_res_manager->load_resource("./pic/suzhou_people2.png", WIPResourceType::TEXTURE);
	int wzaji2 = ((TextureData *)(res_zaji2->extra))->width;
	int hzaji2 = ((TextureData *)(res_zaji2->extra))->height;
	auto res_crowd = g_res_manager->load_resource("./pic/crowd.png", WIPResourceType::TEXTURE);
	int wcrow = ((TextureData *)(res_crowd->extra))->width;
	int hcrow = ((TextureData *)(res_crowd->extra))->height;

	float rotli = wli / (float)hli;

	tex2d = g_rhi->RHICreateTexture2D(ww, hh, res_handle1->ptr);
	tex2d1 = g_rhi->RHICreateTexture2D(ww1, hh1, res_handle2->ptr);
	//issue:texture boarder
	tex2d1mask = g_rhi->RHICreateTexture2D(ww1, hh1, res_handle1mask->ptr , 0, 0, 0, 1);

	tex2d_fog = g_rhi->RHICreateTexture2D(ww1fog, hh1fog, res_handle1fog->ptr);

	tex2d_lixiaoyao = g_rhi->RHICreateTexture2D(wli, hli, res_lixiaoyao->ptr);
	tex2d_zaji1 = g_rhi->RHICreateTexture2D(wzaji1, hzaji1, res_zaji1->ptr);
	tex2d_zaji2 = g_rhi->RHICreateTexture2D(wzaji2, hzaji2, res_zaji2->ptr);
	tex2d_crowd = g_rhi->RHICreateTexture2D(wcrow, hcrow, res_crowd->ptr);

	auto res_face = g_res_manager->load_resource("./pic/face.png", WIPResourceType::TEXTURE);
	int fw = ((TextureData *)(res_face->extra))->width;
	int fh = ((TextureData *)(res_face->extra))->height;
	face = g_rhi->RHICreateTexture2D(fw, fh, res_face->ptr);

	WIPSpriteCreator ctor_man(3.6f*rot, 3.6f, WIPMaterialType::E_TRANSLUCENT);
	ctor_man.texture = tex2d;
	ctor_man.world_render = world_renderer;
	ctor_man.body_tp = WIPCollider::_CollisionTypes::E_RIGIDBODY;
	ctor_man.collider_sx = 0.5f;
	ctor_man.collider_sy = 0.2f;

	WIPSpriteCreator ctor_mask(40.f, 30.f, WIPMaterialType::E_TRANSLUCENT);
	ctor_mask.texture = tex2d1mask;
	ctor_mask.world_render = world_renderer;
	ctor_mask.body_tp = WIPCollider::_CollisionTypes::E_NO_PHYSICS;

	WIPSpriteCreator ctor_bg(40.f, 30.f, WIPMaterialType::E_TRANSLUCENT);
	ctor_bg.texture = tex2d1;
	ctor_bg.world_render = world_renderer;
	ctor_bg.body_tp = WIPCollider::_CollisionTypes::E_NO_PHYSICS;


	WIPSpriteCreator ctor_fog(20.f, 20.f, WIPMaterialType::E_TRANSLUCENT);
	ctor_fog.texture = tex2d_fog;
	ctor_fog.world_render = world_renderer;
	ctor_fog.body_tp = WIPCollider::_CollisionTypes::E_NO_PHYSICS;


	WIPSpriteCreator ctor_li(3.f*rotli, 3.5f, WIPMaterialType::E_TRANSLUCENT);
	ctor_li.texture = tex2d_lixiaoyao;
	ctor_li.world_render = world_renderer;
	ctor_li.collider_sx = 0.5f;
	ctor_li.collider_sy = 0.2f;

	WIPSpriteCreator ctor_zaji1(1.2f*2.5f*1.2f, 3.6f*1.2f, WIPMaterialType::E_TRANSLUCENT);
	ctor_zaji1.texture = tex2d_zaji1;
	ctor_zaji1.world_render = world_renderer;
	ctor_zaji1.collider_sx = 0.5f;
	ctor_zaji1.collider_sy = 0.2f;

	WIPSpriteCreator ctor_zaji2(1.8f*1.2f, 3.4f, WIPMaterialType::E_TRANSLUCENT);
	ctor_zaji2.texture = tex2d_zaji2;
	ctor_zaji2.world_render = world_renderer;
	ctor_zaji2.collider_sx = 0.5f;
	ctor_zaji2.collider_sy = 0.2f;

	WIPSpriteCreator ctor_crowd(6*1.2f, 8.f, WIPMaterialType::E_TRANSLUCENT);
	ctor_crowd.texture = tex2d_crowd;
	ctor_crowd.world_render = world_renderer;
	ctor_crowd.collider_sx = 0.85f;
	ctor_crowd.collider_sy = 0.4f;



	man_lixiaoyao = WIPSpriteFactory::create_sprite(ctor_li);
	man_lixiaoyao->_animation->add_clip(clip, clip->name);
	man_lixiaoyao->_animation->add_clip(clip1, clip1->name);
	man_lixiaoyao->_animation->add_clip(clip2, clip2->name);
	man_lixiaoyao->_animation->add_clip(clip3, clip3->name);
	man_lixiaoyao->_animation->add_clip(clip_s, clip_s->name);
	man_lixiaoyao->_animation->add_clip(clip1_s, clip1_s->name);
	man_lixiaoyao->_animation->add_clip(clip2_s, clip2_s->name);
	man_lixiaoyao->_animation->add_clip(clip3_s, clip3_s->name);
	man_lixiaoyao->_animation->play(clip1_s);
	man_lixiaoyao->set_anchor(0.5f, 0);

	zaji1 = WIPSpriteFactory::create_sprite(ctor_zaji1);
	zaji1->_animation->add_clip(clip, clip->name);
	zaji1->_animation->set_clip_instance_speed(clip->name
		, 0.2);
	zaji1->_animation->play(clip, true);
	zaji1->set_anchor(0.5f, 0);


	zaji2 = WIPSpriteFactory::create_sprite(ctor_zaji2);
	zaji2->_animation->add_clip(clip1_s, clip1_s->name);
	zaji2->_animation->play(clip1_s, true);
	zaji2->set_anchor(0.5f, 0);


	crowd = WIPSpriteFactory::create_sprite(ctor_crowd);
	crowd->_animation->add_clip(clip_s, clip_s->name);
	crowd->_animation->play(clip_s);
	crowd->set_anchor(0.4f, 0.2f);


	bg = WIPSpriteFactory::create_sprite(ctor_bg);
	MapComponent* mc = new MapComponent(bg);
	bg->add_tick_component(mc);
	mc->cam = cameras[0];
	mc->scene = scene;
	bg_mask = WIPSpriteFactory::create_sprite(ctor_mask);
	man = WIPSpriteFactory::create_sprite(ctor_man);
	man->_animation->add_clip(clip, clip->name);
	man->_animation->add_clip(clip1, clip1->name);
	man->_animation->add_clip(clip2, clip2->name);
	man->_animation->add_clip(clip3, clip3->name);
	man->_animation->add_clip(clip_s, clip_s->name);
	man->_animation->add_clip(clip1_s, clip1_s->name);
	man->_animation->add_clip(clip2_s, clip2_s->name);
	man->_animation->add_clip(clip3_s, clip3_s->name);
	mc->man = man;

	man->_animation->play(clip_s);
	man->set_anchor(0.5f, 0);

	mc->ui_renderer = ui_renderer;

	bg->set_tag("bg");
	bg_mask->set_tag("mask");
	man->set_tag("man");
	man_lixiaoyao->set_tag("lixiaoyao");
	zaji1->set_tag("zaji1");
	zaji2->set_tag("zaji2");
	crowd->set_tag("crowd");

	
	bg->set_type_tag("scene");
	bg_mask->set_type_tag("scene");

	man->set_type_tag("character");
	man_lixiaoyao->set_type_tag("character");
	zaji1->set_type_tag("character");
	zaji2->set_type_tag("character");
	crowd->set_type_tag("character");

	scene->add_sprite(bg);
	scene->add_sprite(bg_mask);
	scene->add_sprite(man);
	scene->add_sprite(man_lixiaoyao);
	scene->add_sprite(zaji1);
	scene->add_sprite(zaji2);
	scene->add_sprite(crowd);

	man_lixiaoyao->set_z_order(0.4f);
	zaji1->set_z_order(0.4f);
	zaji2->set_z_order(0.4f);
	crowd->set_z_order(0.4f);
	std::vector<const WIPSprite*> sp;
	scene->quad_tree->get_all_nodes(sp);
	sp.clear();

	man_lixiaoyao->translate_to(-3, 1);
	scene->quad_tree->get_all_nodes(sp);
	sp.clear();
	zaji1->translate_to(-5, 0);
	scene->quad_tree->get_all_nodes(sp);
	sp.clear();
	zaji2->translate_to(-4,-2);
	scene->quad_tree->get_all_nodes(sp);
	sp.clear();
	crowd->translate_to(-8, 3);
	scene->quad_tree->get_all_nodes(sp);
	sp.clear();

	
	

	fogs = WIPSpriteFactory::create_sprite(ctor_fog);
	scene->add_sprite(fogs);
	fogs->set_type_tag("scene");
	fogs->translate_to(0.f, 0.f);
	fogs->set_z_order(0.05);
	mc->fogs = fogs;



	bg->translate_to(0.f, 0.f);
	bg_mask->translate_to(0.f, 0.f);
	man->translate_to(8.f, 1.f);
	bg->set_z_order(0.9f);
	man->set_z_order(0.4f);
	bg_mask->set_z_order(0.1f);

	

	//g_res_manager->free(res_handle1, res_handle1->size);
	

	//use a big delta time to play first frame
	g_animation_manager->update(1);
	pre_clip = nullptr;

	scene->init_components();

	/*
	std::vector<std::string> res;

	g_filesystem->scan_dir(res, apath.c_str(), ".jpg", SCAN_FILES, true);
	for (int i = 0; i < res.size(); ++i)
	{
		auto res_handler = g_res_manager->load_resource((apath + res[i]).c_str());
		TextureData* d = (TextureData*)(res_handler->extra);
		textures.push_back(g_rhi->RHICreateTexture2D(d->width, d->height, res_handler->ptr));
		string ss = g_filesystem->get_path(std::string(apath + res[i]));
		paths.push_back(to_wstring(ss));
	}
	*/
	//g_res_manager->free_all();

	return ret;
}



void GLFWApp::run() 
{
	
	while (((!glfwWindowShouldClose(window))&& (!_exit_requist)))
	{
		if (_exit_requist)
			break;
		curTime = times->get_time();
		if (curTime - lastTime >= _frame)
		{
			//////////////////////////////////////////////////////////////////////////
			// only this order!!!!!
			// only to put input handle here to keep everything right
			{

				int bits = g_input_manager->get_last_key_info()->key_bit;
				int bits_c = g_input_manager->get_last_key_info()[1].key_bit;

				if (lmouse_keep_going) {
					bits |= WIP_MOUSE_LBUTTON;
				}
				if (rmouse_keep_going)
					bits |= WIP_MOUSE_RBUTTON;
				if (mmouse_keep_going)
					bits |= WIP_MOUSE_MBUTTON;
				g_input_manager->update(bits_c, bits);
			}

			glfwPollEvents();
			//////////////////////////////////////////////////////////////////////////
			
			// update physics
			g_script_manager->call("main_logic");

			//todo:move to camera::clear add rhi!
			glViewport(0, 0, window_w, window_h);
			glClearColor(0.85, 0.85, 0.85, 1);
			glClearDepth(1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			//g_rhi->set_shader(0);
			g_rhi->begin_debug_context();
			g_rhi->change_debug_color(RBColorf::red);
			//scene->quad_tree->debug_draw(cameras[0]);
			//g_rhi->debug_draw_aabb2d(RBVector2(-0.5f, -0.5f), RBVector2(0.5f, 0.5f), cameras[0]);
			g_rhi->debug_submit();
			g_rhi->end_debug_context();

			
			f32 dt = clock->get_frame_time();


			

			scene->update(dt);

			scene->fix_update(dt);


			g_animation_manager->update(clock->get_frame_time());
			//not work
			g_physics_manager->update(scene,clock->get_frame_time());

			
			for (auto i : cameras)
				world_renderer->render(i);

			ui_renderer->render_box(0, 0, 0, 0, RBColorf(0.3, 0.3, 0.5, 0.5));
			ui_renderer->render_pic(700, 50, face->get_width(), face->get_height(), face);

			/*
			scoller_y += Input::get_mouse_scroller()*100;
			int w = (cameras[0]->window_w >> 1)*0.8f;
			int h = w * textures[0]->get_height() / (f32)textures[0]->get_width();
			*/

			
			/*
			int s = -1;
			for (int i = 0; i < textures.size(); ++i)
			{
				
				int x = i % 2 * w+100;
				int y = i / 2 * h - scoller_y;
				RBAABB2D aabb(RBVector2(x, y), RBVector2(x + w, y + h));
				RBAABB2D aabbcams(RBVector2(0, 0), RBVector2(cameras[0]->window_w, cameras[0]->window_h));
				RBVector2 mpos(Input::get_mouse_x(), cameras[0]->window_h-Input::get_mouse_y());
				if (aabb.is_contain(mpos))
				{
					s = i;
				}
				if (aabbcams.intersection(aabb))
				{
					ui_renderer->render_pic(x, y, w, h, textures[i]);
				}
			}
			if (Input::get_sys_key_up(WIP_MOUSE_LBUTTON))
			{
				if (s!=-1)
					open_explorer(paths[s].c_str());
			}
			*/

			

			wchar_t words[] = L"我烦哦阿婆十一回“燕云十八飞骑奔腾如虎风烟举”。金庸，原名查良镛，1924年生于浙江海宁，后居香港，当代新派武侠小说家，代表作有《书剑恩仇录》《射雕英雄传》《神雕侠侣》《倚天屠龙记》《天龙八部》《笑傲江湖》《鹿鼎记》等。\n"
				L"但听得蹄声如雷，十余乘马疾风般卷上山来。马上乘客一色都是玄色薄毡大氅，里面玄色布衣，但见人似虎，马如龙，人既矫捷，马亦雄骏，每一匹马都是高头长腿，通体黑毛，奔到近处，群雄眼前一亮，金光闪闪，却见每匹马的蹄铁竟然是黄金打就。来者一共是一十九骑，人数虽不甚多，气势之壮，却似有如千军万马一般，前面一十八骑奔到近处，拉马向两旁一分，最后一骑从中驰出。"
				L"丐帮帮众之中，大群人猛地里高声呼叫：“乔帮主，乔帮主！”数百名帮众从人丛中疾奔出来，在那人马前躬身参见。\n"
				L"我们的游戏中需要对渲染字体做勾边处理，有种简单的方法是将字体多画几遍，向各个方向偏移一两个像素用黑色各画一遍，然后再用需要的颜色画一遍覆盖上去。这个方法的缺点是一个字就要画多次，影响渲染效\n"
				L"前几年有人发明了另一种方法，google 一下 Signed Distance Field Font Rendering 就可以找到大量的资料。大体原理是把字体数据预处理一遍，把每个像素离笔画的距离用灰度的形式记录在贴图上，然后写一个专门的 shader 来渲染字体。好处是字体可以缩放而不产生锯齿，也比较容易缺点边界做勾边处理。缺点是字模数据需要离线预处理。\n"
				L"我们的手游项目以及 3d 端游项目都大量使用了勾边字体，我希望直接利用系统字体而不用离线预处理字体把字体文件打包到客户端中。前段时间还专门实现了一个动态字体的贴图管理模块 。btw, 苹果的平台提供了高层 API 可以直接生成带勾边效果的字模。\n"
				L"但是，勾过边的字模信息中同时包含了轮廓信息和字模主体信息，看起来似乎很难用单通道记录整个字模数据了。这给染色也带来了麻烦。\n"
				L"见这张图，是一张带勾边信息的字模。轮廓是黑色的，字体是白色的。从颜色通道上看，有黑白灰的过渡。但灰色部分 alpha 通道对应量却不相等。轮廓向字体主干过渡的地方，色彩是灰色的，但是 alpha 值为 1.0 。也就是说，alpha 通道是独立的。\n"
				L"我们需要两个通道，颜色通道和 alpha 通道，来保存完整的字模信息才能在最后正确的渲染到屏幕上。很多显卡硬件并不支持两通道贴图，所以要么我们用一个 RGBA 四通道贴图来保存，要么用两张单通道贴图。\n"
				L"我想了个简单的方法只用一个通道就可以保存全部信息，那就是把 alpha 为 1.0 的像素的灰度影射到 0.5 到 1 的区间；把 alpha < 1.0 的部分像素的 alpha 值影射到 0 到 0.5 的区间。这样做可行是因为，经过勾黑边的白字，其 alpha 小于 1.0 的像素一定都是黑色的，也就是 RGBA 都相等。所以信息只损失了一个 bit 就保存了下来。";

			wchar_t words1[] = L"趙靈兒:\n好……放了他，我就跟你們走……";

			text_renderer->render_text(200, 200, words1,  wcslen(words1), window_w, cameras[0]);
			text_renderer->render(cameras[0]);
			// g_script_manager->call("debug_draw");

			g_audio_manager->Update();

			lastTime = curTime;
			clock->update();
			// g_sound_palyer->update();

			glfwSwapBuffers(window);
			g_input_manager->clear_states();
			// for glfw
			g_input_manager->clear_scroller();
		}
		else 
		{
#ifdef _WIN32
			Sleep(0);
#else
			usleep(0);
#endif
		}
	}

}

GLFWApp::~GLFWApp()
{
	
	g_physics_manager->shutdown();
	g_script_manager->shutdown();
	g_logger->shutdown();
	g_res_manager->shutdown();
	glfwDestroyWindow(window);
	glfwTerminate();
}

