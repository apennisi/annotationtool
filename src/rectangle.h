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
 * \file rectangle.h
 *
 * \class Line, VerticalLine, HorizontalLine, Rectangle
 *
 * \brief Class for describing the bounding box
 *
 **/


#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <opencv2/opencv.hpp>
#include "rectangleinformation.h"

namespace bbox {

    class Line {
    public:
        /**
         * \brief Create a new object Line
         *
         */
        Line();
        /**
         * \brief Line Destructor
         *
         */
        virtual ~Line() {}
        /**
         * \brief Set line
         *
         * \param p1: starting point
         * \param p2: ending point
         *
         */
        void set(const cv::Point &, const cv::Point &);
        /**
         * \brief Decide if a point belong to a line
         *
         * \param p: point
         *
         */
        virtual bool isBelong(const cv::Point &, const int &) = 0;
    protected:
        cv::Point p1, p2;
    };

    class HorizontalLine : public Line {
    public:
        /**
         * \brief Create a new object HorizontalLine
         *
         */
        HorizontalLine() {}
        /**
         * \brief Decide if a point belong to a line
         *
         * \param p: point
         *
         */
        bool isBelong(const cv::Point &, const int &);
    };

    class VerticalLine : public Line {
    public:
        /**
         * \brief Create a new object VerticalLine
         *
         */
        VerticalLine() {}
        /**
         * \brief Decide if a point belong to a line
         *
         * \param p: point
         *
         */
        bool isBelong(const cv::Point &, const int &);
    };


    class Rectangle {
    public:
        /**
         * \brief Create a new object Rectangle
         *
         * \param rect: input rect
         * \param offset: rectangle offset
         * \param color: rectangle color
         * \param lineOffset: line offset
         * \param id: rectangle id
         *
         */
        Rectangle(const cv::Rect &, const int &,
                  const cv::Scalar &, const int &,
                  const int &);
        /**
         * \brief Create a new object Rectangle
         *
         * \param _rect: rectangle
         *
         */
        Rectangle(const Rectangle *);
        /**
         * \brief Create a new object Rectangle
         *
         * \param _rect: rectangle
         * \param _id: rectangle id
         *
         */
        Rectangle(const cv::Rect &, const int &);
        /**
         * \brief Create a new object Rectangle
         *
         */
        Rectangle() {}
        /**
         * \brief Rectangle Destructor
         *
         */
        virtual ~Rectangle();
        /**
         * \brief Set rectangle
         *
         * \param _rect: rectangle
         *
         */
        void set(const cv::Rect &);
        /**
         * \brief Enstablish if a point belongs to a rectangle
         *
         * \param p: point
         *
         */
        bool isSelected(const cv::Point &) const;
        /**
         * \brief Enstablish if a point is Top Left
         *
         * \param p: point
         *
         */
        bool isTopLeft(const cv::Point &) const;
        /**
         * \brief Enstablish if a point is Bottom Right
         *
         * \param p: point
         *
         */
        bool isBottomRight(const cv::Point &) const;
        /**
         * \brief Draw rectangle corners
         *
         * \param p: point
         * \param offset: point offset
         * \param img: image to modify
         *
         */
        static void drawCornerRect(const cv::Point &,  const int &, cv::Mat &);
        /**
         * \brief Draw rectangle
         *
         * \param img: image to modify
         *
         */
        void draw(cv::Mat &);
        /**
         * \brief Set rectangle id
         *
         * \param _id: id to set
         *
         */
        inline void setId(const int &_id)
        {
            info.setId(_id);
        }
        /**
         * \brief Set rectangle color
         *
         * \param _color: color to set
         *
         */
        inline void setColor(const cv::Scalar &_color)
        {
            color = _color;
        }
        /**
         * \brief Get rectangle
         *
         */
        inline cv::Rect getRect() const
        {
            return rect;
        }
        /**
         * \brief Return true if the rectangle has been selected
         *
         * \return return true if the rectangle has been selected
         *
         */
        inline bool isRectSelected() const
        {
            return selected;
        }
        /**
         * \brief Select the rectangle
         *
         */
        inline void select()
        {
            selected = true;
        }
        /**
         * \brief Deselect the rectangle
         *
         */
        inline void deselect()
        {
            selected = false;
        }
        /**
         * \brief Get the rectangle color
         *
         */
        inline cv::Scalar getColor() const
        {
            return color;
        }
        /**
         * \brief Get the point offset
         *
         */
        inline int getOffset() const
        {
            return offset;
        }
        /**
         * \brief Get rectangle information
         *
         */
        inline RectangleInformation getInfo() const
        {
            return info;
        }
    private:
        /**
         * \brief Return true if a point is inside a rectangle
         *
         * \return return true if a point is inside a rectangle
         *
         */
        bool isInside(const cv::Point &) const;
        cv::Rect rect;
        RectangleInformation info;
        int offset, lineOffset;
        cv::Scalar color, selected_color;
        Line *left, *right, *top, *bottom;
        cv::Point tl, br;
        bool selected;
        cv::Mat image;
        void init();
        int id;
    };


}

#endif
