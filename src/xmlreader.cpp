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

#include <string>

#include "xmlreader.h"

XmlReader::XmlReader(const std::string &name)
{

    box = frame = object = objectlist = push = false;

    xmlMap.insert(std::pair<std::string, int>("<frame", 0));
    xmlMap.insert(std::pair<std::string, int>("<object", 1));
    xmlMap.insert(std::pair<std::string, int>("<box", 2));
    xmlMap.insert(std::pair<std::string, int>("number=", 3));
    xmlMap.insert(std::pair<std::string, int>("id=", 4));
    xmlMap.insert(std::pair<std::string, int>("h=", 5));
    xmlMap.insert(std::pair<std::string, int>("w=", 6));
    xmlMap.insert(std::pair<std::string, int>("xc=", 7));
    xmlMap.insert(std::pair<std::string, int>("yc=", 8));
    xmlMap.insert(std::pair<std::string, int>("<objectlist>", 9));
    xmlMap.insert(std::pair<std::string, int>("</objectlist>", 10));

    first = true;

    this->read(name);
}

void XmlReader::read(const std::string &name)
{
    std::ifstream file(name.c_str());
    std::string line;

    while (std::getline(file, line))
    {
        line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
        this->parsingLine(line);
        if(push)
        {
            rectangles.push_back(currentRects);
            push = false;
            currentRects.clear();
        }
    }
}

bool XmlReader::parsingLine(const std::string &line)
{

    boost::char_separator<char> sep(" ");
    boost::tokenizer< boost::char_separator<char> > tok(line, sep);
    sep = boost::char_separator<char>("\"");
    int id;
    int width, height;
    cv::Point tl;
    for(boost::tokenizer< boost::char_separator<char> >::iterator it = tok.begin(); it != tok.end(); ++it)
    {
        boost::tokenizer< boost::char_separator<char> > tok_(*it, sep);
        for(boost::tokenizer< boost::char_separator<char> >::iterator it2=tok_.begin(); it2 != tok_.end(); ++it2)
        {
            std::string s(*it2);

            switch (xmlMap[s])
            {
                case 0:
                    frame = true;
                    break;
                case 1:
                    if(objectlist)
                    {
                        object = true;
                    }
                    break;
                case 2:
                    box = true;
                    break;
                case 3:
                    if (frame)
                    {
                        int fnum = atoi((*(++it2)).c_str());
                        if(fnum > 0 && first)
                        {
                            for(int i = 0; i < fnum; ++i)
                            {
                                rectangles.push_back(std::vector<bbox::Rectangle *>());
                            }
                            first = false;
                        }
                        else
                        {
                            first = false;
                        }
                        frame = false;
                    }
                    break;
                case 4:
                    if( object && objectlist)
                    {
                        id = atoi((*(++it2)).c_str());
                        object = false;
                    }
                    break;
                case 5:
                    if( box && objectlist)
                    {
                        height = atoi((*(++it2)).c_str());
                    }
                    break;
                case 6:
                    if( box && objectlist)
                    {
                        width = atoi((*(++it2)).c_str());
                    }
                    break;
                case 7:
                    if( box && objectlist)
                    {
                        tl.x = atoi((*(++it2)).c_str()) - width/2;
                    }
                    break;
                case 8:
                    if( box && objectlist)
                    {
                        tl.y = atoi((*(++it2)).c_str()) - height/2;
                        currentRects.push_back(new bbox::Rectangle(cv::Rect(tl.x, tl.y, width, height), id));
                        box = false;
                    }
                    break;
                case 9:
                    objectlist = true;
                    break;
                case 10:
                    if(objectlist)
                    {
                        objectlist = false;
                        push = true;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return true;
}
