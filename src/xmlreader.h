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
 * \file xmlreader.h
 *
 * \class XmlReader
 *
 * \brief Class for managing xml files
 *
 **/


#ifndef XMLREADER_H
#define XMLREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <boost/tokenizer.hpp>

#include "rectanglemanager.h"

class XmlReader
{
public:
    /**
     * \brief Create a new object XmlReader
     *
     * \param name: file name
     *
     */
    XmlReader(const std::string &name);
    /**
     * \brief Return the rectangles read from the file
     *
     * \return return the rectangles read from the file
     *
     */
    inline std::vector<std::vector< bbox::Rectangle *> > getRectangles() const
    {
        return rectangles;
    }
private:
    /**
     * \brief Read the file
     *
     * \param name: file name
     *
     */
    void read(const std::string &name);
    /**
     * \brief Parse a line
     *
     * \param line: line to parse
     *
     */
    bool parsingLine(const std::string &line);
    std::vector<std::vector< bbox::Rectangle *> > rectangles;
    std::map<std::string, int> xmlMap;
    std::vector<bbox::Rectangle *> currentRects;
    bool box, frame, object, objectlist, push, first;
};

#endif // XMLREADER_H
