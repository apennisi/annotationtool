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


#include "xmlwriter.h"

XmlWriter::XmlWriter(const std::string &name,
                     const std::vector< std::vector<bbox::Rectangle*> > &rectangles)
{
    file.open(name.c_str());

    this->write(rectangles);

    file.close();

}

void XmlWriter::write(const std::vector<std::vector<bbox::Rectangle*> > &rectangles)
{
    std::vector<std::vector<bbox::Rectangle*> >::const_iterator it;
    std::vector<bbox::Rectangle*>::const_iterator it2;

    file << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
    file << "<dataset>" << std::endl;

    for(it = rectangles.begin(); it != rectangles.end(); ++it)
    {
        if((*it).size() != 0)
        {
            file << "\t<frame number=\"" << it - rectangles.begin() << "\">" << std::endl;
            file << "\t\t<objectlist>" << std::endl;

            for(it2 = (*it).begin(); it2 != (*it).end(); ++it2)
            {
                RectangleInformation info = (*it2)->getInfo();
                file << "\t\t\t<object id=\"" << info.getId() << "\">" << std::endl;
                file << "\t\t\t\t<box h=\"" << info.getHeight() << "\" w=\"" << info.getWidth() << "\" xc=\""
                     << info.getCenter().x << "\" yc=\"" << info.getCenter().y << "\" />" << std::endl;
                file << "\t\t\t</object>" << std::endl;
            }

            file << "\t\t</objectlist>" << std::endl;
            file << "\t</frame>" << std::endl;
        }
    }

    file << "</dataset>" << std::endl;
}
