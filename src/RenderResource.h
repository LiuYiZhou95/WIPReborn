#pragma once
#include "./RBMath/Inc/Colorf.h"
#include <string>
#include <vector>
#include "RefCount.h"

//screen coord is lb
using std::string;

//base class
class WIPBaseTexture : public FRefCountedObject
{
public:
	WIPBaseTexture(u32 in_mips,u32 in_samples,const RBColorf& in_clear_color ):
		mips_n(in_mips),samples_n(in_samples),clear_color(in_clear_color){}
	virtual u32 get_width() const {return 0;};
	virtual u32 get_height() const {return 0;};
	virtual void* get_rhi_resource() const=0;
	//virtual void load_data(const unsigned char* const data)=0;
	//virtual void clear()=0;
	//virtual inline const void* get_data(){return nullptr;}
protected:
	RBColorf clear_color;
	u32 mips_n;
	u32 samples_n;
	std::string texture_name;
};

//interface
class WIPTexture2D : public WIPBaseTexture
{
public:
	WIPTexture2D(u32 inw,u32 inh,u32 in_mips,u32 in_samples,void* data):
		WIPBaseTexture(in_mips,in_samples,RBColorf::black),w(inw),h(inh){}
	virtual inline u32 get_width() const {return w;};
	virtual inline u32 get_height()const {return h;};

protected:
	u32 w,h;
};

//interface
class WIPRenderTexture2D : public WIPBaseTexture
{
public:
	WIPRenderTexture2D(u32 inw,u32 inh,u32 in_mips,u32 in_samples,const RBColorf& ccolor):
		WIPBaseTexture(in_mips,in_samples,ccolor),w(inw),h(inh){}
	virtual inline u32 get_width() const {return w;};
	virtual inline u32 get_height() const {return h;};

protected:
	u32 w,h;

};

//base class
class WIPShaderBase : public FRefCountedObject
{
public:
	virtual bool load_and_compile(const char* text)
	{
		shader_text = text;
		return true;
	}
	virtual void set_uniform_texture(const char* uniform_name,const WIPBaseTexture* texture)=0;
	virtual void* get_rhi_resource() const=0;
	std::string shader_text;
};

//interface
class WIPVertexShader : public WIPShaderBase
{
public:
	virtual bool load_and_compile(const char* text)=0;
	virtual void set_uniform_texture(const char* uniform_name,const WIPBaseTexture* texture)=0;

};

//interface
class WIPPixelShader : public WIPShaderBase
{
public:
	virtual bool load_and_compile(const char* text)=0;
	virtual void set_uniform_texture(const char* uniform_name,const WIPBaseTexture* texture)=0;
};


//interface
class WIPBoundShader : public FRefCountedObject
{
public:
	virtual void bind_attribute(unsigned int location, const string & name)=0;
	virtual bool compile()=0;
	virtual void* get_rhi_resource() const=0;
};


class WIPIndexBuffer : public FRefCountedObject
{
public:
	virtual void* get_rhi_resource() const=0;
};

class WIPVertexBuffer : public FRefCountedObject
{
public:
	virtual void* get_rhi_resource() const=0;
};

enum VertexType 
{
	E_FLOAT = 0,
	E_INT,
	E_TOTAL
};

class WIPVertexElement : public FRefCountedObject
{
public:
	WIPVertexElement(int cnt,VertexType tp = VertexType::E_FLOAT):type(tp),count(cnt){}
	VertexType type;
	int count;

};

class WIPVertexFormat : public FRefCountedObject
{
public:
	WIPVertexFormat():total_count(0){}
	virtual void add_float_vertex_attribute(int count)=0;
	virtual void add_int_vertex_attribute(int count) = 0;
	virtual void* get_rhi_resource() const=0;
	std::vector<WIPVertexElement> elements;
	int total_count;
};

class WIPViewPort : public FRefCountedObject
{
public:
	WIPViewPort(int ix, int iy, float iw, float ih) :
		x(ix), y(iy), w(iw), h(ih){}
	float x, y;
	float w, h;

};