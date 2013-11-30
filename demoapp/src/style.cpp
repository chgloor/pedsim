//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2012 by Christian Gloor
//                              

#include "style.h"

using namespace std;

Style::Style() {}

void Style::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
		QPlastiqueStyle::drawPrimitive(element, option, painter, widget);
}


void Style::polish (QPalette &palette) {

	// A general background color.
	palette.setColor( QPalette::Background, QColor( 44, 44, 44 ) ); // orange

	// A general foreground color.
	palette.setColor( QPalette::Foreground, QColor( 255, 255, 255 ) );

	// Used as the background color for text entry widgets; usually white or another light color.
	palette.setColor( QPalette::Base, QColor(44, 44, 44) );

	// Used as the alternate background color in views with alternating row colors
	palette.setColor( QPalette::AlternateBase, QColor( 138, 138, 138 ) );

	// The foreground color used with Base. This is usually the same as the Foreground, in which case it must provide good contrast with Background and Base.
	palette.setColor( QPalette::Text, QColor( 255, 130, 0 ) ); // orange

	// The general button background color. This background can be different from Background as some styles require a different background color for buttons.
	palette.setColor( QPalette::Button, QColor( 66, 66, 66 ) );

	// A foreground color used with the Button color.
	palette.setColor( QPalette::ButtonText, QColor( 255, 255, 255 ) ); // orange

	// Lighter than Button color. --> used for the dock window resize bars *AND* for inacive text shadows
	palette.setColor( QPalette::Light, QColor( 180, 70, 0 ) );

	// Between Button and Light. --> not used?
	palette.setColor( QPalette::Midlight, QColor( 134, 134, 134 ) );

	// Darker than Button. --> not used
	palette.setColor( QPalette::Dark, QColor( 55, 55, 55 ) );

	// Between Button and Dark. --> not used
	palette.setColor( QPalette::Mid, QColor( 60, 60, 60 ) );

	// A very dark color. By default, the shadow color is Qt::black. --> e.g. group box borders
	palette.setColor( QPalette::Shadow, QColor( 180, 70, 0 ) );

	// A color to indicate a selected item or the current item.
	//	palette.setColor( QPalette::Highlight, QColor( 138, 0, 0 ) );
	palette.setColor( QPalette::Highlight, QColor( 255, 170, 0 ) );

	// A text color that contrasts with Highlight.
	palette.setColor( QPalette::HighlightedText, QColor( 255, 255, 255 ) );
}
