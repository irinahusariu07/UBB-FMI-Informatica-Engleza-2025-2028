#pragma once
#include<QWidget>
#include<QPainter>
#include<vector>
#include"Star.h"

class GraphicStars : public QWidget
{
	std::vector<Star> stars;
	std::string selected;
public:
    GraphicStars(const std::vector<Star>& s, const std::string& name, QWidget* parent = nullptr)
        : QWidget(parent), stars(s), selected(name) {
        setFixedSize(600, 600);
    }

protected:
    void paintEvent(QPaintEvent*) override
    {
        QPainter p(this);
        for (const auto& s : stars) {
            if (s.getName() == selected) p.setBrush(Qt::red);
            else p.setBrush(Qt::black);

            p.drawEllipse(s.getRA() % 550, s.getDec() % 550, s.getDiam(), s.getDiam());
        }
    }
};