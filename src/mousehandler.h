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

/**
 * \file mousehandler.h
 *
 * \class MouseHandler
 *
 * \brief Class for handling the mouse
 *
 **/

#ifndef MOUSEHANDLER_H
#define MOUSEHANDLER_H

#include <opencv2/opencv.hpp>
#include <iostream>

#include "rectanglemanager.h"
#include "utils.h"


class MouseHandler
{
public:
    /**
     * \brief Create a new object MouseHandler
     *
     */
    MouseHandler();
    /**
     * \brief Create a new object MouseHandler
     *
     * \param _rectManager: the rect manager object, which is modyfied accordint to the mouse position
     *
     */
    MouseHandler(bbox::RectangleManager *_rectManager);
    /**
     * \brief MouseHandler Destructor
     *
     */
    ~MouseHandler() {}
    /**
     * \brief Select State
     *
     * \param x: x coordinate
     * \param y: y coordinate
     * \param img: image to modify
     *
     */
    void selected(const int &x, const int &y, cv::Mat &img);
    /**
     * \brief Pressed State
     *
     * \param x: x coordinate
     * \param y: y coordinate
     *
     */
    void pressed(const int &x, const int &y);
    /**
     * \brief Move Rectangle
     *
     * \param x: x coordinate
     * \param y: y coordinate
     * \param img: image to modify
     *
     */
    void moved(const int &x, const int &y, cv::Mat &img);
    /**
     * \brief Release State
     *
     * \param x: x coordinate
     * \param y: y coordinate
     * \param img: image to modify
     *
     */
    void released(const int &x, const int &y, cv::Mat &img);
    /**
     * \brief Deselect Rectangle
     *
     * \param img: image to modify
     *
     */
    void deselected(cv::Mat &img);
    /**
     * \brief Set none state
     *
     */
    void setNoneState();
    /**
     * \brief Set Status
     *
     * \param _state: new status to set
     *
     */
    inline void setStatus(const status &_state)
    {
        state = _state;
    }
    /**
     * \brief Set selected status
     *
     */
    inline void setSelectedStatus()
    {
        state = RECTANGLE_SELECTED;
    }
    /**
     * \brief Get current status
     *
     */
    inline status getStatus() const
    {
        return state;
    }

private:
    cv::Point point1, point2;
    cv::Scalar _color;
    status state;
    int last_x, last_y;
    bbox::RectangleManager *rectManager;
    cv::RNG rng;
    bool setColor;
};

#endif // MOUSEHANDLER_H
