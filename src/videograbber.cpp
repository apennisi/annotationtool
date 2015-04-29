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

#include "videograbber.h"

using namespace grabber;

VideoGrabber::VideoGrabber(const std::string &video_file)
    : video(video_file)
{
    cap = cv::VideoCapture(video);
    if(!cap.isOpened())
    {
        throw std::invalid_argument( "Invalid Video File Name" );
    }
    frameNumber = 0;
    resetFirst = false;
    first = true;
}

VideoGrabber::~VideoGrabber()
{
    if(history.size() > 0)
    {
        for(int i = 0 ; i < int(history.size()); ++i)
        {
            delete history[i];
        }
    }
}

cv::Mat VideoGrabber::next()
{
    cv::Mat frame;
    if(!resetFirst && frameNumber + 1 < int(history.size()))
    {

        /*(frameNumber == 0) ? frameNumber = 0 : */
        frameNumber++;
        frame = *(history[frameNumber]);
    }
    else
    {
        if(cap.read(frame))
        {
            history.push_back(new cv::Mat(frame.clone()));
            (first) ? first = false : frameNumber++;
        }
        else
        {
            if(!resetFirst) reset();
            (frameNumber + 1 < end) ? frameNumber++ : frameNumber = 0;
            frame = *(history[frameNumber]);
        }
    }
    return frame;
}

cv::Mat VideoGrabber::prev()
{
    if(!resetFirst)
    {
        if(--frameNumber >= 0)
        {
            return *(history[frameNumber]);
        }
        else
        {
           frameNumber = 0;
           return *(history[0]);
        }
    }
    else
    {
        if(--frameNumber >= 0)
        {
            return *(history[frameNumber]);
        }
        else
        {
            frameNumber = end - 1;
            return *(history[frameNumber]);
        }
    }
}

int VideoGrabber::getEnd()
{
    return end;
}

void VideoGrabber::reset()
{
    resetFirst = true;
    frameNumber = -1;
    end = history.size();
}
