#include "BaseWidget.h"
#include "Render.h"

BaseWidget::BaseWidget()
{

}

void BaseWidget::update(float dt, int x, int y)
{
	ActiveDrawableRect::update(dt,x,y);
	//std::cout<<"updating BaseWidget "<<_name<<" ...\n";
}

void BaseWidget::draw(int x,int y)
{
	
}

void BaseWidget::draw_internal(int x,int y)
{

}