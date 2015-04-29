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
 * \file rectanglemanager.h
 *
 * \class RectangleManager
 *
 * \brief Class for managing rectangles
 *
 **/

#ifndef RECTANGLEMANAGER_H
#define RECTANGLEMANAGER_H

#include <qcombobox.h>
#include <map>

#include "associatedialog.h"
#include "rectangle.h"
#include "utils.h"

namespace bbox {
    class RectangleManager
    {
    public:
        /**
         * \brief Create a new object RectangleManager
         *
         * \param _combobox: GUI combobox 
         *
         */
        RectangleManager(QComboBox *_comboBox);
        /**
         * \brief RectangleManager Destructor
         *
         */
        ~RectangleManager();
        /**
         * \brief Associate rectangles
         *
         * \param frame_clone: image to modify
         *
         */
        bool associate(cv::Mat &frame_clone);
        /**
         * \brief Deselect Rectangle
         *
         */
        void deselect();
        /**
         * \brief Release Rectangle
         *
         */
        void release();
        /**
         * \brief Select Rectangle by Id
         *
         * \param _id: id to select
         * \param img: image to modify
         *
         */
        void selectById(const int &_id, cv::Mat &img);
        /**
         * \brief Add rectangle
         *
         * \param _color: rectagle color
         *
         */
        void add(const cv::Scalar &_color);
        /**
         * \brief Select Rectangle
         *
         * \param img: image to modify
         *
         */
        void select(cv::Mat &img);
        /**
         * \brief Verify if the rectangle has been selected
         *
         * \param img: image to modify
         *
         */
        void selected(cv::Mat &img);
        /**
         * \brief Return the current id of the rectangle
         *
         * \return return the current id of the rectangle
         *
         */
        int getCurrentIdx() const
        {
            return currentIdx;
        }
        /**
         * \brief Return the previous id of the rectangle
         *
         * \return return the previous id of the rectangle
         *
         */
        int getPrevIdx() const
        {
            return previousIdx;
        }
        /**
         * \brief Add rectangles to history
         *
         */
        void addRectangles()
        {
            rectangles.push_back(currentRectangles);
        }
        /**
         * \brief Find a point
         *
         * \param x: x coordinate
         * \param y: y coordinate
         *
         */
        int findPoint(const int &x, const int &y);
        /**
         * \brief Copy a vector of bbox::Rectangle in the currentRectangles vector
         *
         * \param _rect: vector of rectangles
         *
         */
        void copyRectVector(const std::vector<bbox::Rectangle *> &_rect);
        /**
         * \brief Move a rectangle
         *
         * \param p1: top left corner
         * \param p2: bottom right corner
         * \param img: image to modify
         * \param color: rectangle color
         *
         */
        void moving(const cv::Point &p1, const cv::Point &p2,
                    cv::Mat &img, const cv::Scalar &color);
        /**
         * \brief If the bottom right corner has been selected, resize the rectangle
         *
         * \param img: image to modify
         * \param xGap: gap between the previous x-coordinate and the current x-coordinate
         * \param yGap: gap between the previous y-coordinate and the current y-coordinate
         *
         */
        void selectBR(cv::Mat &img, const int &xGap,
                      const int &yGap);
        /**
         * \brief If the top left corner has been selected, resize the rectangle
         *
         * \param img: image to modify
         * \param xGap: gap between the previous x-coordinate and the current x-coordinate
         * \param yGap: gap between the previous y-coordinate and the current y-coordinate
         *
         */
        void selectTL(cv::Mat &img, const int &xGap,
                      const int &yGap);
        /**
         * \brief If the rectangle has been selected, move the rectangle
         *
         * \param img: image to modify
         * \param xGap: gap between the previous x-coordinate and the current x-coordinate
         * \param yGap: gap between the previous y-coordinate and the current y-coordinate
         *
         */
        void moveRect(cv::Mat &img, const int &xGap,
                      const int &yGap);
        /**
         * \brief Return the history of the annotated rectangles
         *
         * \return return the history of the annotated rectangles
         *
         */
        inline std::vector< std::vector<bbox::Rectangle*> > getRectangles() const
        {
            return rectangles;
        }
        /**
         * \brief Return the current id of the selected rectangle
         *
         * \return return the current id of the selected rectangle
         *
         */
        inline int getIdx() const
        {
            return currentIdx;
        }
        /**
         * \brief Return the current selected rectangle
         *
         * \return return the current selected rectangle
         *
         */
        inline bbox::Rectangle* getRectangle() const
        {
            return currentRectangles[currentIdx];
        }
        /**
         * \brief Set the current rectangle
         *
         * \param _rect: rectangle to set
         *
         */
        void setCurrentRect(const cv::Rect &_rect)
        {
            current_rect = _rect;
        }
        /**
         * \brief Copy the history of the annotated rectangle
         *
         * \param _rectangles: history of the annotated rectangle
         *
         */
        void copyRect(const std::vector< std::vector<bbox::Rectangle*> > &_rectangles);
        /**
         * \brief Draw rectangles
         *
         * \param img: image to draw
         *
         */
        void drawRectangles(cv::Mat &img);
        /**
         * \brief Draw the rectangle into the next frame
         *
         * \param img: image to draw
         * \param end: end of frames
         *
         */
        void nextFrame(cv::Mat &img, const int &end);
        /**
         * \brief Draw the rectangle into the previous frame
         *
         * \param img: image to draw
         * \param end: end of frames
         *
         */
        void prevFrame(cv::Mat &img, const int &end);
        /**
         * \brief Hide the current rectangle
         *
         * \param img: image to draw
         *
         */
        void hide(cv::Mat &img);
        /**
         * \brief Delete the current rectangle
         *
         * \param img: image to draw
         *
         */
        void delete_rect(cv::Mat &img);
    private:
        std::vector< std::vector<bbox::Rectangle*> > rectangles;
        std::vector<bbox::Rectangle*> currentRectangles;
        bbox::Rectangle selectedRectangle;
        cv::Rect current_rect;
        QComboBox *comboBox;
        int frameCount, idCounter, idComboBoxCounter;
        int currentIdx, previousIdx;
        bool selectedById;
        std::map<int, cv::Scalar> rectangleList;
        std::map<int, int> idList;
        void copyRectVector();
        void updateRectangles();
        void drawSelectedRectangle(const cv::Point &tl,
                                   const cv::Point &br, cv::Mat &img);
        bool findTLPoint(const int &x, const int &y);
        bool findBRPoint(const int &x, const int &y);
        bool findRectangle(const int &x, const int &y);
    };
}

#endif // RECTANGLEMANAGER_H
