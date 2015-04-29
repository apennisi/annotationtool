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
 * \file imagegrabber.h
 *
 * \class ImageGrabber
 *
 * \brief Class for grabbing images from a folder
 *
 **/

#ifndef IMAGEGRABBER_H
#define IMAGEGRABBER_H

#include <iostream>

#include "grabber.h"
#include "imagemanager.h"

namespace grabber {

    class ImageGrabber : public Grabber
    {
    public:
        /**
         * \brief Create a new object ImageGrabber
         *
         * \param dir_name: the input directory
         *
         */
        ImageGrabber(const std::string &dir_name);
        /**
         * \brief Return the next image
         *
         * \return return the next image
         *
         */
        cv::Mat next();
        /**
         * \brief Return the previous image
         *
         * \return return the previous image
         *
         */
        cv::Mat prev();
        /**
         * \brief Return current frame number
         *
         * \return return current frame number
         *
         */
        int getEnd();
        /**
         * \brief ImageGrabber Destructor
         *
         */
        ~ImageGrabber();
    private:
        ImageManager *imageManager;
        std::string dir;
    };

}

#endif // IMAGEGRABBER_H
