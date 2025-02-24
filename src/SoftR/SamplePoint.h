#pragma once

#include "SamplerBase.h"
#include "Texture2D.h"
#include "..\\RBMath\\Inc\\Colorf.h"
#include "..\\RBMath\\Inc\\Vector4.h"

class SrSamplerPoint : public SrSamplerBase
{
public:
	enum SWARPS
	{

		E_TOTAL,
	};
	RBColorf sample(const SrTexture2D* tex, float u, float v)
	{

		int x = (int)(u*(tex->get_width() -1))% (tex->get_width() - 1);
		int y = (int)(v*(tex->get_height() -1))% (tex->get_height() - 1);

		return tex->get_color(x,y);
	}
	RBColorf sample_l(const SrTexture2D* tex, float u, float v)
	{
		//双线性采样，有奇怪的白点

		int ox = (int)(u*(tex->get_width() - 1)) / (tex->get_width() - 1)*(tex->get_width() - 1);
		int oy = (int)(v*(tex->get_height() - 1)) / (tex->get_height() - 1)*(tex->get_height() - 1);



		float x = u*(tex->get_width()-1)-ox;
		float y = v*(tex->get_height()-1)-oy;

		float x0, x1;
		x0 = floor(x);
		x1 = ceil(x);
		float y0, y1;
		y0 = floor(y);
		y1 = ceil(y);

		
		RBVector4 c00 = tex->get_color(x0,y0);
		RBVector4 c01 = tex->get_color(x0, y1);
		RBVector4 c10 = tex->get_color(x1, y0);
		RBVector4 c11 = tex->get_color(x1, y1);

		RBVector4 oc(0),occ(0);
		if (x0 == x1)
		{
			oc = c10;
			occ = c11;
		}
		else
		{
			oc = (x - x0)*c10 + (x1 - x)*c00;
			occ = (x - x0)*c11 + (x1 - x)*c01;
		}
		if(y0!=y1)
			oc = (y - y0)*occ + (y1 - y)*oc;

		return oc;
	}
};