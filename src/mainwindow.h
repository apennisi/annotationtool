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
 * \file mainwindow.h
 *
 * \class MainWindow
 *
 * \brief Class for managing the GUI
 *
 **/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

#include "displaymanager.h"
#include "grabber.h"
#include "imagegrabber.h"
#include "keyboardhandler.h"
#include "mousehandler.h"
#include "rectanglemanager.h"
#include "videograbber.h"
#include "xmlwriter.h"
#include "xmlreader.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * \brief Create a new object MainWindow
     *
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    /**
     * \brief Manage the key pressed event
     *
     * \param event
     */
    void keyPressEvent(QKeyEvent *event);
    /**
     * \brief Manage the key released event
     *
     * \param event
     */
    void keyReleaseEvent(QKeyEvent *event);
    /**
     * \brief Filter the window deactivate event
     *
     */
    bool eventFilter(QObject *obj, QEvent *event);
    /**
     * \brief Resize the widgets of the GUI according to the image size
     *
     * \param img: the input image
     */
    bool event(QEvent *ev);
    void resizeWidgets(const cv::Mat &img);
    /**
     * \brief Activate the button when a video or a set of images is selected
     *
     */
    void activateButtons();
    /**
     * \brief Set the Frame Number
     *
     */
    void setFrameNumber();
    grabber::Grabber *my_grabber;
    cv::Mat frame;
    int imageWidth, imageHeight;
    DisplayManager *display;
    bool pressed, shift;
    MouseHandler *mouseHandler;
    bbox::RectangleManager *rectManager;
    KeyboardHandler keyboardHandler;
    int last_x, last_y;
    bool interaction, rightClick;
    QMenu* mouseMenu;
    bool video, images;

private slots:
    void mouse_current_position();
    void mouse_pressed();
    void mouse_leave();
    void mouse_release();
    void mouse_right_click();
    void open_directory_images();
    void open_video_file();
    void hide();
    void associate();
    void delete_rect();
    void onChangeComboBox(const int &idComboBox);
    void loadXml();
    void next();
    void save();
    void prev();
};

#endif // MAINWINDOW_H
