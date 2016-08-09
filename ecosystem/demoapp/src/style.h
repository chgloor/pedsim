//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#ifndef _style_h_
#define _style_h_

#include <QPlastiqueStyle>
#include <QPalette>

class Style : public QPlastiqueStyle {
	Q_OBJECT

	public: 
		Style();
		~Style() {};

		void polish(QPalette &palette);
		void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
		QPainter *painter, const QWidget *widget) const;
};

#endif
