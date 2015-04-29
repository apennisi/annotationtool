/*
 *  AT Annotation Tool
 *  Copyright 2015 Andrea Pennisi
 *
 *  This file is part of AT and it is distributed under the terms of the
 *  GNU Lesser General Public License (Lesser GPL)
 *
 *
 *
 *  AT is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  AT is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with AT.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 *  AT has been written by Andrea Pennisi
 *
 *  Please, report suggestions/comments/bugs to
 *  andrea.pennisi@gmail.com
 *
 */


#include "rectangle.h"
#include "utils.h"

using namespace bbox;
cv::RNG rng(12345);

Rectangle::Rectangle(const cv::Rect &_rect, const int &_offset,
                     const cv::Scalar &_color, const int &_lineOffset,
                     const int &_id)
    : rect(_rect), offset(_offset), color(_color), lineOffset(_lineOffset), id(_id) {
    this->init();
}

Rectangle::Rectangle(const Rectangle *_rect)
    : rect(_rect->getRect()), offset(_rect->getOffset()),
      color(_rect->getColor()), lineOffset(LINE_WEIGHT), id(_rect->getInfo().getId()) {
    this->init();
}

Rectangle::Rectangle(const cv::Rect &_rect, const int &_id) :
    rect(_rect)
{
    tl = _rect.tl();
    br = _rect.br();
    left = new VerticalLine();
    left->set(tl, cv::Point(tl.x, br.y));
    top = new HorizontalLine();
    top->set(tl, cv::Point(br.x, tl.y));
    bottom = new HorizontalLine();
    bottom->set(cv::Point(tl.x, br.y), br);
    right = new VerticalLine();
    right->set(cv::Point(br.x, tl.y), br);
    info.set(_id, _rect);
    selected = false;
    selected_color = RED_COLOR;
    offset = 4;
    lineOffset = LINE_WEIGHT;
    color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );

}

bool Rectangle::isSelected(const cv::Point &p) const {
    if(isTopLeft(p) || isBottomRight(p))
        return false;
    return (isInside(p) || left->isBelong(p, lineOffset) || top->isBelong(p, lineOffset)
            || bottom->isBelong(p, lineOffset) || right->isBelong(p, lineOffset)) ? true : false;
}

bool Rectangle::isTopLeft(const cv::Point &p) const {
    return (p.x >= tl.x - offset && p.x <= tl.x + offset &&
            p.y >= tl.y - offset && p.y <= tl.y + offset) ? true : false;
}

bool Rectangle::isBottomRight(const cv::Point &p) const {
    return (p.x >= br.x - offset && p.x <= br.x + offset &&
            p.y >= br.y - offset && p.y <= br.y + offset) ? true : false;
}


bool Rectangle::isInside(const cv::Point &p) const
{
    return (p.x < br.x && p.x > tl.x && p.y < br.y && p.y > tl.y) ? true : false;

}

void Rectangle::init()
{
    tl = rect.tl();
    br = rect.br();
    left = new VerticalLine();
    left->set(tl, cv::Point(tl.x, br.y));
    top = new HorizontalLine();
    top->set(tl, cv::Point(br.x, tl.y));
    bottom = new HorizontalLine();
    bottom->set(cv::Point(tl.x, br.y), br);
    right = new VerticalLine();
    right->set(cv::Point(br.x, tl.y), br);
    info.set(id, rect);
    selected = false;
    selected_color = RED_COLOR;
}

void Rectangle::set(const cv::Rect &_rect)
{
    rect = _rect;
    tl = _rect.tl();
    br = _rect.br();
    left->set(tl, cv::Point(tl.x, br.y));
    top->set(tl, cv::Point(br.x, tl.y));
    bottom->set(tl, cv::Point(tl.x, br.y));
    right->set(cv::Point(br.x, tl.y), cv::Point(tl.x, br.y));
    info.set(_rect);
}

void Rectangle::draw(cv::Mat &img)
{
    (selected) ?
                cv::rectangle(img, rect, selected_color, lineOffset) :
                cv::rectangle(img, rect, color, lineOffset);
    drawCornerRect(br, offset, img);
    drawCornerRect(tl, offset, img);
    std::stringstream ss;
    ss << info.getId();
    cv::putText(img, ss.str().c_str(), info.getCenter() - cv::Point(10, 0),
                cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(120,255,0), 2);
}

void Rectangle::drawCornerRect(const cv::Point &p, const int &offset, cv::Mat &img)
{
    cv::Point tlR, brR;
    tlR.x = p.x - offset;
    tlR.y = p.y - offset;
    brR.x = p.x + offset;
    brR.y = p.y + offset;
    cv::Rect r(tlR, brR);
    cv::rectangle(img, r, BLUE_COLOR, -1);
}

Rectangle::~Rectangle()
{
    delete left;
    delete top;
    delete bottom;
    delete right;
}

Line::Line() {

}

void Line::set(const cv::Point &p1_, const cv::Point &p2_) {
    p1 = p1_;
    p2 = p2_;
}

bool HorizontalLine::isBelong(const cv::Point &p, const int &offset) {
    int range = offset / LINE_WEIGHT;
    return (p.x >= p1.x && p.x <= p2.x && p.y <= p1.y - range && p.y >= p1.y + range) ? true : false;
}

bool VerticalLine::isBelong(const cv::Point &p, const int &offset) {
    int range = offset / LINE_WEIGHT;
    return (p.x >= p1.x - range && p.x <= p1.x + range && p.y >= p1.y && p.y <= p2.y) ? true : false;
}

