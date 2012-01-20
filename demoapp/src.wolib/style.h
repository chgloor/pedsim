#ifndef STYLE_H
#define STYLE_H

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
