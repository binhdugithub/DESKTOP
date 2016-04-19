/*
 * videoeffect.cpp
 *
 *  Created on: Jul 20, 2014
 *      Author: xyz
 */

#include "videoeffect.h"

VideoEffect::VideoEffect()
{
	// TODO Auto-generated constructor stub
}

VideoEffect::~VideoEffect()
{
	// TODO Auto-generated destructor stub
}
void VideoEffect::initFrame(int width, int height)
{
	effectImage = QImage(width, height, QImage::Format_RGB888);
	painter.begin(&effectImage);
	painter.setPen(Qt::white);
	painter.setFont(QFont("Times New Roman", 25, QFont::Bold));
	painter.setBrush(QBrush(Qt::white));
	isInitFrame = true;
	// TODO paint something here
}

