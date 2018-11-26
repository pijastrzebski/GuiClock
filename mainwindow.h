#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVector>
#include <QTime>

// TODO: clock parts -> move to a new file
struct Parts
{
    Parts(const QColor& color = QColor(255, 255, 255, 255)) :
        m_color(color)
    {}
    QVector<QPoint> m_points;
    QColor m_color;
};

class MinuteHand : public Parts
{
public:
    MinuteHand() : Parts(QColor(0, 127, 127, 150)){}
    MinuteHand(const std::initializer_list<QPoint>& list)  :
        MinuteHand()
    {
        for(const auto& el : list)
        {
            m_points.push_back(el);
        }
    }
};

class HourHand : public Parts
{
public:
    HourHand() : Parts(QColor(127, 0, 150, 180)){}
    HourHand(const std::initializer_list<QPoint>& list) :
        HourHand()
    {
        for(const auto& el : list)
        {
            m_points.push_back(el);
        }
    }
};

class SecondHand : public Parts
{
public:
    SecondHand() : Parts(QColor(60, 0, 127, 120)){}
    SecondHand(const std::initializer_list<QPoint>& list) :
        SecondHand()
    {
        for(const auto& el : list)
        {
            m_points.push_back(el);
        }
    }
};

class QPoint;

class AnalogClock : public QWidget
{
    Q_OBJECT

public:
    AnalogClock(QWidget *parent = nullptr);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

private:
    QVector<Parts> m_clockParts;

    QTime m_time;
    int m_side;
};

#endif // MAINWINDOW_H
