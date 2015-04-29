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
 * \file displaymanager.h
 *
 * \class DisplayManager
 *
 * \brief Class for displaying images
 *
 **/

#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <opencv2/opencv.hpp>

#include "qtcvtransform.h"
#include "mouselabel.h"

class DisplayManager
{
public:
    /**
     * \brief Create a new object DisplayManager
     *
     * \param l: mouse label
     *
     */
    DisplayManager(MouseLabel *l);
    /**
     * \brief diplay the image
     *
     * \param image: cv::Mat image to display
     *
     */
    void display(const cv::Mat &image);
private:
    int width, height;
    cv::Size size;
    QLabel *label;
};

#endif // DISPLAYMANAGER_H
