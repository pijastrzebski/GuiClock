#include "mainwindow.h"
#include <QTimer>
#include <QPoint>
#include <QPainter>

AnalogClock::AnalogClock(QWidget *parent)
    : QWidget(parent)
{
    QTimer* timer = new QTimer(this);

    connect(timer, &QTimer::timeout, [this](){update();});

    timer->start(1000);

    setWindowTitle("Ana Clock");
    resize(400, 400);

    m_clockParts.push_back(HourHand({{7, 3}, {-7, 8}, {0, -40}}));
    m_clockParts.push_back(MinuteHand({{1, 1}, {-6, 8}, {0, -70}}));
    m_clockParts.push_back(SecondHand({{1, 1}, {-1, 1}, {0, -90}}));
}

void AnalogClock::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    m_side = qMin(width(), height());
    m_time = QTime::currentTime();

    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(m_side / 200.0, m_side / 200.0);

    // draw clock face


//    painter.setPen(m_clockParts[2].m_color);

//    for(auto i = 0; i < 180; ++i)
//    {
//        if(i%5)
//        {
//            painter.drawLine(97, 0, 95, 0);
//        }
//        painter.rotate(2.0);
//    }

    // draw hour hand
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_clockParts[0].m_color);

    painter.save();
    painter.rotate(30.0 * ((m_time.hour() + m_time.minute() / 60.0)));
    painter.drawConvexPolygon(&m_clockParts[0].m_points[0], 3);
    painter.restore();

    // draw hour clock face
    painter.setPen(QPen(m_clockParts[0].m_color, 3));

    for(auto i = 0; i < 12; ++i)
    {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }

    // draw minute hand
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_clockParts[1].m_color);

    painter.save();
    painter.rotate(6.0 * (m_time.minute() + m_time.second() / 60.0));
    painter.drawConvexPolygon(&m_clockParts[1].m_points[0], 3);
    painter.restore();

    // draw minute clock face (1 line/5 minute)
    painter.setPen(m_clockParts[1].m_color);

    for(auto j = 0; j < 60; ++j)
    {
        if((j%5) != 0)
        {
            painter.drawLine(92, 0, 96, 0);
        }
        painter.rotate(6.0);
    }

    // draw second hand
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_clockParts[2].m_color);

    painter.save();
    painter.rotate(6.0 * m_time.second());
    painter.drawConvexPolygon(&m_clockParts[2].m_points[0], 3);
    painter.restore();

}
