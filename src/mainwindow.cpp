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


#include <QFileDialog>
#include <QString>
#include <iostream>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mouselabel.h"
#include <unistd.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->image->setStyleSheet("background-color: black");
    ui->next->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");
    ui->prev->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");
    ui->delete_->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");
    ui->associate->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");
    ui->save->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");
    ui->loadXML->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");
    ui->hide->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");
    ui->associate->setStyleSheet("color: rgb(120, 120, 120); color: rgb(120, 120, 120)");

    connect(ui->image, SIGNAL(Mouse_Position()), this, SLOT(mouse_current_position()));
    connect(ui->image, SIGNAL(Mouse_Pressed()), this, SLOT(mouse_pressed()));
    connect(ui->image, SIGNAL(Mouse_Release()), this, SLOT(mouse_release()));
    connect(ui->image, SIGNAL(Mouse_Right()), this, SLOT(mouse_right_click()));
    connect(ui->image, SIGNAL(Mouse_Leave()), this, SLOT(mouse_leave()));

    connect(ui->openImages , SIGNAL( clicked() ), this, SLOT( open_directory_images()) );
    connect(ui->openVideo , SIGNAL( clicked() ), this, SLOT( open_video_file() ) );
    connect(ui->loadXML, SIGNAL(clicked()), this, SLOT( loadXml()) );
    connect(ui->next, SIGNAL(clicked()), this, SLOT(next()) );
    connect(ui->prev, SIGNAL(clicked()), this, SLOT(prev()) );


    connect(ui->associate, SIGNAL(clicked()), this, SLOT(associate()) );
    connect(ui->save, SIGNAL(clicked()), this, SLOT(save()) );
    connect(ui->hide, SIGNAL(clicked()), this, SLOT(hide()) );
    connect(ui->delete_, SIGNAL(clicked()), this, SLOT(delete_rect()) );
    connect(ui->idBox, SIGNAL(activated(int)), this, SLOT(onChangeComboBox(int)));

    imageWidth = ui->image->width();
    imageHeight = ui->image->height();

    ui->centralWidget->setFixedSize(944, 560);
    ui->frameLabel->setText("");
    ui->frameLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    pressed = false;

    display = new DisplayManager(ui->image);

    my_grabber = NULL;

    rectManager = new bbox::RectangleManager(ui->idBox);
    mouseHandler = new MouseHandler(rectManager);

    ui->idBox->addItem("Not Selected", QVariant(-1));

    last_x = last_y = -1;
    interaction = rightClick = false;

    this->installEventFilter(this);

    images = video = false;
}

MainWindow::~MainWindow()
{
    delete display;
    if(video)
    {
        delete dynamic_cast<grabber::VideoGrabber*>(my_grabber);
    }
    else
    {
        delete dynamic_cast<grabber::ImageGrabber*>(my_grabber);
    }
    //delete rectManager; !FIXMEEEEEEEEEEEEEEEEEEEEEE
    delete mouseHandler;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(mouseHandler->getStatus() == RECTANGLE_SELECTED)
    {
        cv::Mat frame_clone = frame.clone();
        rectManager->drawRectangles(frame_clone);
        keyboardHandler.set(rectManager->getRectangle());
        bool draw = true;
        switch (event->key()) {
        case Qt::Key_Up:
            keyboardHandler.up(frame_clone);
            break;
        case Qt::Key_Down:
            keyboardHandler.down(frame_clone);
            break;
        case Qt::Key_Left:
            keyboardHandler.left(frame_clone);
            break;
        case Qt::Key_Right:
            keyboardHandler.right(frame_clone);
            break;
        default:
            draw = false;
            break;
        }
        if(draw)
        {
            rectManager->setCurrentRect(keyboardHandler.getCurrentRect());
            display->display(frame_clone);
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        default:
            break;
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::WindowDeactivate)
    {
        //qDebug() << "QUI: state: Deactivate";
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::activateButtons()
{
    ui->next->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");
    ui->prev->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");
    ui->hide->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");
    ui->associate->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");
    ui->save->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");
    ui->loadXML->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");
    ui->delete_->setStyleSheet("color: rgb(0, 0, 0); color: rgb(0, 0, 0)");
}

void MainWindow::resizeWidgets(const cv::Mat &img)
{
    imageWidth = img.cols;
    imageHeight = img.rows;
    ui->image->resize(imageWidth, imageHeight);
    int widthGap = imageWidth + 20;

    ui->menuWidget->move(widthGap, ui->buttonBox->y());
    ui->buttonWidget->move(ui->buttonWidget->x(), imageHeight + 15);
    ui->frameLabel->move(widthGap - ui->frameLabel->width() - 10,
                         imageHeight + 15);

    ui->selectId->move(widthGap, ui->selectId->y());

    ui->centralWidget->setFixedSize(imageWidth + 210,
                                    imageHeight + 30 + ui->buttonWidget->height());
}

void MainWindow::setFrameNumber()
{
    std::stringstream ss;
    int frameNum = my_grabber->getFrameNum();
    ss << "Frame: " << frameNum;
    ui->frameLabel->setText(QString::fromUtf8(ss.str().c_str()));
}

void MainWindow::mouse_current_position()
{

    last_x = ui->image->x;
    last_y = ui->image->y;

    if(pressed)
    {
        cv::Mat frame_clone = frame.clone();
        mouseHandler->moved(ui->image->x, ui->image->y, frame_clone);
        display->display(frame_clone);
    }
}

void MainWindow::mouse_pressed()
{
    if(interaction)
    {
        pressed = true;
        mouseHandler->pressed(last_x, last_y);
    }
}

void MainWindow::mouse_leave()
{
    if(interaction)
    {
    
    }
}

void MainWindow::mouse_release()
{
    if(interaction)
    {
        pressed = false;
        cv::Mat frame_clone = frame.clone();
        mouseHandler->released(last_x, last_y, frame_clone);
        display->display(frame_clone);
    }
}

void MainWindow::mouse_right_click()
{
    if(interaction && mouseHandler->getStatus() == RECTANGLE_SELECTED)
    {
        mouseMenu = new QMenu();
        mouseMenu->addAction("Associate", this, SLOT( associate() ) );
        mouseMenu->addSeparator();
        mouseMenu->addAction("Hide", this, SLOT( hide() ) );
        mouseMenu->addSeparator();
        mouseMenu->addAction("Delete", this, SLOT( delete_rect()) );
        mouseMenu->popup( QCursor::pos() );
    }
}


void MainWindow::open_directory_images()
{

    QString dirname = QFileDialog::getExistingDirectory(this,
                                                tr("Choose the Image Directory"),
                                                ".",
                                                QFileDialog::ShowDirsOnly);
    if(dirname != "")
    {
        if(my_grabber != NULL)
        {
            delete dynamic_cast<grabber::VideoGrabber*>(my_grabber);
        }

        my_grabber = new grabber::ImageGrabber(dirname.toStdString());

        activateButtons();

        frame = my_grabber->next();
        resizeWidgets(frame);
        display->display(frame);
        setFrameNumber();
        images = interaction = true;
    }
}

void MainWindow::open_video_file()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open Video File"),
                ".",
                tr("Video (*.avi *.mpg *.mkv *.mpeg *.mov);;") );

    if(filename != "")
    {
        if(my_grabber != NULL)
        {
            delete dynamic_cast<grabber::ImageGrabber*>(my_grabber);
        }

        my_grabber = new grabber::VideoGrabber(filename.toStdString());

        activateButtons();

        frame = my_grabber->next();
        resizeWidgets(frame);
        display->display(frame);
        setFrameNumber();
        video = interaction = true;
    }
}

void MainWindow::hide()
{
    if(interaction)
    {
        cv::Mat frame_clone = frame.clone();
        rectManager->hide(frame_clone);
        mouseHandler->setStatus(NONE);
        ui->image->setFocus();
        display->display(frame_clone);
    }
}

void MainWindow::associate()
{
    if(interaction)
    {
        cv::Mat frame_clone = frame.clone();
        if(rectManager->associate(frame_clone))
        {
            mouseHandler->setStatus(NONE);
            display->display(frame_clone);
        }
        ui->image->setFocus();
    }
}

void MainWindow::delete_rect()
{
    if(interaction)
    {
        cv::Mat frame_clone = frame.clone();
        rectManager->delete_rect(frame_clone);
        mouseHandler->setStatus(NONE);
        ui->image->setFocus();
        display->display(frame_clone);
    }
}

void MainWindow::onChangeComboBox(const int &idComboBox)
{
    int id = ui->idBox->itemData(idComboBox).toInt();
    cv::Mat frame_clone = frame.clone();
    if(id != -1)
    {
        rectManager->selectById(id, frame_clone);
        mouseHandler->setSelectedStatus();
        ui->image->setFocus();
    }
    else
    {
        mouseHandler->setNoneState();
        rectManager->drawRectangles(frame_clone);
    }
    display->display(frame_clone);
}

void MainWindow::loadXml()
{
    if(interaction)
    {
        QString filename = QFileDialog::getOpenFileName(
                    this,
                    tr("Open XML File"),
                    ".",
                    tr("File (*.xml);;") );

        if(filename != "")
        {
            XmlReader *xmlReader = new XmlReader(filename.toStdString());
            frame = my_grabber->load(xmlReader->getRectangles().size());
            rectManager->copyRect(xmlReader->getRectangles());
            cv::Mat frame_clone = frame.clone();
            rectManager->drawRectangles(frame_clone);
            display->display(frame_clone);
            setFrameNumber();
            delete xmlReader;
        }
    }
}

void MainWindow::next()
{
    if(interaction)
    {
        frame = my_grabber->next();
        cv::Mat frame_clone = frame.clone();
        mouseHandler->setNoneState();
        rectManager->nextFrame(frame_clone, my_grabber->getEnd());
        display->display(frame_clone);
        setFrameNumber();
        ui->idBox->setCurrentIndex(0);
    }
}

void MainWindow::save()
{
    if(interaction)
    {
        QString filename = QFileDialog::getSaveFileName(
                    this,
                    tr("Save Document"),
                    QDir::currentPath(),
                    tr("Documents (*.xml)") );
        if( !filename.isNull() )
        {
            cv::Mat frame_clone = frame.clone();
            mouseHandler->setNoneState();
            rectManager->nextFrame(frame_clone, my_grabber->getEnd());
            XmlWriter xmlWriter(filename.toStdString(),
                      rectManager->getRectangles());
        }
    }
}

void MainWindow::prev()
{
    if(interaction)
    {
        frame = my_grabber->prev();
        cv::Mat frame_clone = frame.clone();
        mouseHandler->setNoneState();
        rectManager->prevFrame(frame_clone, my_grabber->getEnd());
        display->display(frame_clone);
        setFrameNumber();
        ui->idBox->setCurrentIndex(0);
    }
}

bool MainWindow::event(QEvent *ev)
{
    if(ev->type() == QEvent::LayoutRequest)
    {
        setFixedSize(sizeHint());
    }
    return QMainWindow::event(ev);
}
