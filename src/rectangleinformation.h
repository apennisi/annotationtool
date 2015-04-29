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
 * \file rectangleinformation.h
 *
 * \class RectangleInformation
 *
 * \brief Class containing the rectangle information
 *
 **/

#ifndef RECTANGLEINFORMATION_H
#define RECTANGLEINFORMATION_H
#include <opencv2/opencv.hpp>

class RectangleInformation
{
public:
    /**
     * \brief Create a new object RectangleInformation
     *
     */
    RectangleInformation();
    /**
     * \brief Set information
     *
     * \param _id: rectangle id
     * \param _rect: rectangle
     *
     */
    void set(const int &_id, const cv::Rect &_rect);
    /**
     * \brief Set information
     *
     * \param _rect: rectangle
     *
     */
    void set(const cv::Rect &_rect);
    /**
     * \brief Return the id
     *
     * \return return the id
     *
     */
    inline int getId() const
    {
        return id;
    }
    /**
     * \brief Return the rectangle center
     *
     * \return return the rectangle center
     *
     */
    inline cv::Point getCenter() const
    {
        return center;
    }
    /**
     * \brief Return the rectangle width
     *
     * \return return the rectangle width
     *
     */
    inline int getWidth() const
    {
        return width;
    }
    /**
     * \brief Return the rectangle height
     *
     * \return return the rectangle height
     *
     */
    inline int getHeight() const
    {
        return height;
    }
    /**
     * \brief Return the rectangle top left corner
     *
     * \return return the rectangle top left corner
     *
     */
    inline cv::Point getTL() const
    {
        return tl;
    }
    /**
     * \brief Return the rectangle bottom right corner
     *
     * \return return the rectangle bottom right corner
     *
     */
    inline cv::Point getBR() const
    {
        return br;
    }
    /**
     * \brief Set rectangle id
     *
     * \param _id: id to set
     *
     */
    inline void setId(const int &_id)
    {
        id = _id;
    }
private:
    int id;
    cv::Point center, tl, br;
    int width;
    int height;
};

#endif // RECTANGLEINFORMATION_H
