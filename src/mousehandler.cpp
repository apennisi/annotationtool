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

#include "mousehandler.h"

MouseHandler::MouseHandler()
{
    state = NONE;
    rng = cv::RNG(12345);
    setColor = true;
}

MouseHandler::MouseHandler(bbox::RectangleManager *_rectManager)
{
    state = NONE;
    rectManager = _rectManager;
    rng = cv::RNG(12345);
    setColor = true;
}

void MouseHandler::selected(const int &x, const int &y, cv::Mat &img)
{
    if(rectManager->getCurrentIdx() != -1)
    {
        point1 = cv::Point(x, y);
        rectManager->selected(img);
        state = RECTANGLE_SELECTED;
    }
}

void MouseHandler::pressed(const int &x, const int &y)
{
    point1 = cv::Point(x, y);
    bool f = true;
    switch (rectManager->findPoint(x, y)) {
    case 0:
        state = BR_POINT_SELECTED;
        break;
    case 1:
        state = TL_POINT_SELECTED;
        break;
    case 2:
        if(state == NONE)
            state = RECTANGLE_FOUND;
        break;
    default:
        f = false;
        break;
    }
    if(!f && state == RECTANGLE_SELECTED)
    {
        rectManager->deselect();
        state = NONE;
    }
    else if(!f && state == RECTANGLE_MOVED)
    {
        state = NONE;
    }

    last_x = x;
    last_y = y;
}


void MouseHandler::moved(const int &x, const int &y, cv::Mat &img)
{
    last_x = x;
    last_y = y;
    point2 = cv::Point(x, y);
    int xGap = point2.x - point1.x,
            yGap = point2.y - point1.y;

    if(state == NONE)
        state = MOVING;

    switch (state) {
        case BR_POINT_SELECTED:
        {
            rectManager->selectBR(img, xGap, yGap);
            break;
        }
        case TL_POINT_SELECTED:
        {
            rectManager->selectTL(img, xGap, yGap);
            break;
        }
        case RECTANGLE_SELECTED:
        {
            this->deselected(img);
            this->pressed(x, y);
            break;
        }
        case RECTANGLE_MOVED:
        case RECTANGLE_FOUND:
        {
            state = RECTANGLE_MOVED;
            rectManager->moveRect(img, xGap, yGap);
            break;
        }
        case MOVING:
        {
            if(setColor)
            {
                _color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
                setColor = false;
            }
            rectManager->moving(point1, point2, img, _color);
            break;
        }
        default:
            break;
    }

}

void MouseHandler::released(const int &x, const int &y, cv::Mat &img)
{

    switch (state) {
        case BR_POINT_SELECTED:
        case TL_POINT_SELECTED:
        case RECTANGLE_MOVED:
        {
            rectManager->deselect();
            state = NONE;
            break;
        }
        case MOVING:
        {
            rectManager->add(_color);
            setColor = true;
            state = NONE;
            break;
        }
        case RECTANGLE_SELECTED:
        {
            if(rectManager->getCurrentIdx() != rectManager->getPrevIdx())
            {
                rectManager->release();
                this->selected(x, y, img);
            }
            else
            {
                this->deselected(img);
            }
            break;
        }
        case RECTANGLE_FOUND:
        {
            this->selected(x, y, img);
            break;
        }
        default:
        {
            break;
        }
    }
    rectManager->drawRectangles(img);
}

void MouseHandler::deselected(cv::Mat &img)
{
    rectManager->deselect();
    rectManager->drawRectangles(img);
    state = (state == RECTANGLE_SELECTED) ?
         RECTANGLE_MOVED :
                NONE;
}

void MouseHandler::setNoneState()
{
    if(state == RECTANGLE_SELECTED)
    {
        rectManager->deselect();
        state = NONE;
    }
}
