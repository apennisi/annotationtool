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
 * \file mouselabel.h
 *
 * \class MouseLabel
 *
 * \brief Class for creating a Label, which is able to detect the mouse movements
 *
 **/

#ifndef MOUSELABEL_H
#define MOUSELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>

class MouseLabel : public QLabel

{
    Q_OBJECT
public:
    /**
     * \brief Create a new object MouseLabel
     *
     */
    explicit MouseLabel(QWidget *parent = 0);
    /**
     * \brief Mouse move event
     *
     */
    void mouseMoveEvent(QMouseEvent *event);
    /**
     * \brief Mouse press event
     *
     */
    void mousePressEvent(QMouseEvent *event);
    /**
     * \brief Mouse release event
     *
     */
    void mouseReleaseEvent(QMouseEvent *event);
    /**
     * \brief Mouse leave event
     *
     */
    void leaveEvent(QEvent *event);
    int x, y;

signals:
    void Mouse_Pressed();
    void Mouse_Position();
    void Mouse_Right();
    void Mouse_Left();
    void Mouse_Release();
    void Mouse_Leave();
};

#endif // MOUSELABEL_H
