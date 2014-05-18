#include "agent.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include <math.h>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;


static qreal normalizeAngle(qreal angle) {
    while (angle < 0) angle += TwoPi;
    while (angle > TwoPi) angle -= TwoPi;
    return angle;
}


Agent::Agent() : angle(0), speed(0), agentEyeDirection(0), color(qrand() % 256, qrand() % 256, qrand() % 256) {
    setRotation(qrand() % (360 * 16));
}


QRectF Agent::boundingRect() const {
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust, 36 + adjust, 60 + adjust);
}


QPainterPath Agent::shape() const {
    QPainterPath path;
    path.addRect(-10, -20, 20, 20);
    return path;
}


void Agent::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    // Body
    painter->setBrush(color);
    painter->drawEllipse(-10, -20, 20, 20);

    // Eyes
    painter->setBrush(Qt::white);
    painter->drawEllipse(-10, -17, 8, 8);
    painter->drawEllipse(2, -17, 8, 8);

    // Nose
    painter->setBrush(Qt::black);
    painter->drawEllipse(QRectF(-2, -22, 4, 4));

    // Pupils
    painter->drawEllipse(QRectF(-8.0 + agentEyeDirection, -17, 4, 4));
    painter->drawEllipse(QRectF(4.0 + agentEyeDirection, -17, 4, 4));
}


void Agent::advance(int step) {
    if (!step)
        return;
    // Don't move too far away
    QLineF lineToCenter(QPointF(0, 0), mapFromScene(0, 0));
    if (lineToCenter.length() > 150) {
        qreal angleToCenter = ::acos(lineToCenter.dx() / lineToCenter.length());
        if (lineToCenter.dy() < 0)
            angleToCenter = TwoPi - angleToCenter;
        angleToCenter = normalizeAngle((Pi - angleToCenter) + Pi / 2);

        if (angleToCenter < Pi && angleToCenter > Pi / 4) {
            // Rotate left
            angle += (angle < -Pi / 2) ? 0.25 : -0.25;
        } else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4)) {
            // Rotate right
            angle += (angle < Pi / 2) ? 0.25 : -0.25;
        }
    } else if (::sin(angle) < 0) {
        angle += 0.25;
    } else if (::sin(angle) > 0) {
        angle -= 0.25;
    }

    // Try not to crash with any other mice
    QList<QGraphicsItem *> dangerMice = scene()->items(QPolygonF() 
        << mapToScene(0, 0) << mapToScene(-30, -50) << mapToScene(30, -50));

    foreach (QGraphicsItem *item, dangerMice) {
        if (item == this) continue;

        QLineF lineToAgent(QPointF(0, 0), mapFromItem(item, 0, 0));
        qreal angleToAgent = ::acos(lineToAgent.dx() / lineToAgent.length());

        if (lineToAgent.dy() < 0) angleToAgent = TwoPi - angleToAgent;

        angleToAgent = normalizeAngle((Pi - angleToAgent) + Pi / 2);

        if (angleToAgent >= 0 && angleToAgent < Pi / 2) {
            // Rotate right
            angle += 0.5;
        } else if (angleToAgent <= TwoPi && angleToAgent > (TwoPi - Pi / 2)) {
            // Rotate left
            angle -= 0.5;
        }
    }

    // Add some random movement
    if (dangerMice.size() > 1 && (qrand() % 10) == 0) {
        if (qrand() % 1) angle += (qrand() % 100) / 500.0;
        else angle -= (qrand() % 100) / 500.0;
    }

    speed += (-50 + qrand() % 100) / 100.0;

    qreal dx = ::sin(angle) * 10;
    agentEyeDirection = (qAbs(dx / 5) < 1) ? 0 : dx / 5;

    setRotation(rotation() + dx);
    setPos(mapToParent(0, -(3 + sin(speed) * 3)));
}
