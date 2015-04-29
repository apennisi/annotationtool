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

#ifndef UTILS_H
#define UTILS_H

#define RED_COLOR cv::Scalar(0,0,255)
#define BLUE_COLOR cv::Scalar(255, 0, 0)
#define GREEN_COLOR cv::Scalar(255, 0, 0)
#define OFFSET_CORNER 4
#define LINE_WEIGHT 2

enum status {NONE, MOVING, TL_POINT_SELECTED, BR_POINT_SELECTED, RECTANGLE_MOVED,
             RECTANGLE_SELECTED, RECTANGLE_FOUND};

#endif // UTILS_H
