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
 * \file keyboardhandler.h
 *
 * \class KeyboardHandler
 *
 * \brief Class for managing the keyboard keys
 *
 **/

#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include "rectangle.h"

class KeyboardHandler
{
public:
    /**
     * \brief Create a new object KeyboardHandler
     *
     */
    KeyboardHandler();
    /**
     * \brief Set the current rectangle
     *
     * \param _rect: reference of the current rectangle
     *
     */
    void set(bbox::Rectangle *_rect);
    /**
     * \brief Manage the up key
     *
     * \param img: image to modify
     *
     */
    void up(cv::Mat &img);
    /**
     * \brief Manage the down key
     *
     * \param img: image to modify
     *
     */
    void down(cv::Mat &img);
    /**
     * \brief Manage the left key
     *
     * \param img: image to modify
     *
     */
    void left(cv::Mat &img);
    /**
     * \brief Manage the right key
     *
     * \param img: image to modify
     *
     */
    void right(cv::Mat &img);
    /**
     * \brief Return the modified rectangle
     *
     * \return return the modified rectangle
     *
     */
    inline cv::Rect getCurrentRect() const
    {
        return current_rect;
    }
private:
    bbox::Rectangle *r;
    cv::Rect current_rect;
};

#endif // KEYBOARDHANDLER_H
