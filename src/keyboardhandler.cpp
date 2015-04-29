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


#include "keyboardhandler.h"
#include "utils.h"

KeyboardHandler::KeyboardHandler()
{
}

void KeyboardHandler::set(bbox::Rectangle *_rect)
{
    r = _rect;
}

void KeyboardHandler::up(cv::Mat &img)
{
    cv::Rect old = r->getRect();
    current_rect = cv::Rect(old.tl().x, old.tl().y - 1, old.width, old.height);
    cv::rectangle(img, current_rect, RED_COLOR, 2, 8, 0);
    bbox::Rectangle::drawCornerRect(current_rect.tl(), OFFSET_CORNER, img);
    bbox::Rectangle::drawCornerRect(current_rect.br(), OFFSET_CORNER, img);
    r->set(current_rect);
}

void KeyboardHandler::down(cv::Mat &img)
{
    cv::Rect old = r->getRect();
    current_rect = cv::Rect(old.tl().x, old.tl().y + 1, old.width, old.height);
    cv::rectangle(img, current_rect, RED_COLOR, 2, 8, 0);
    bbox::Rectangle::drawCornerRect(current_rect.tl(), OFFSET_CORNER, img);
    bbox::Rectangle::drawCornerRect(current_rect.br(), OFFSET_CORNER, img);
    r->set(current_rect);
}

void KeyboardHandler::left(cv::Mat &img)
{
    cv::Rect old = r->getRect();
    current_rect = cv::Rect(old.tl().x - 1, old.tl().y, old.width, old.height);
    cv::rectangle(img, current_rect, RED_COLOR, 2, 8, 0);
    bbox::Rectangle::drawCornerRect(current_rect.tl(), OFFSET_CORNER, img);
    bbox::Rectangle::drawCornerRect(current_rect.br(), OFFSET_CORNER, img);
    r->set(current_rect);
}

void KeyboardHandler::right(cv::Mat &img)
{
    cv::Rect old = r->getRect();
    current_rect = cv::Rect(old.tl().x + 1, old.tl().y, old.width, old.height);
    cv::rectangle(img, current_rect, RED_COLOR, 2, 8, 0);
    bbox::Rectangle::drawCornerRect(current_rect.tl(), OFFSET_CORNER, img);
    bbox::Rectangle::drawCornerRect(current_rect.br(), OFFSET_CORNER, img);
    r->set(current_rect);
}
