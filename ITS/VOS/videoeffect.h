/*
 * videoeffect.h
 *
 *  Created on: Jul 20, 2014
 *      Author: xyz
 */

#ifndef VIDEOEFFECT_H_
#define VIDEOEFFECT_H_

#include "mycommon.h"
#include <QtGui/qimage.h>
#include <QtGui/qpainter.h>

class VideoEffect
{
public:
	VideoEffect();
	virtual ~VideoEffect();
	virtual void initFrame(int width, int height);
	virtual void addFrameEffect(const QImage& src) = 0;
	virtual void getFrameEffect(QImage& dst) { dst = effectImage;};

protected:
	QImage effectImage;
	QPainter painter;
	bool isInitFrame;
	string mUrl;
};

#endif /* VIDEOEFFECT_H_ */
