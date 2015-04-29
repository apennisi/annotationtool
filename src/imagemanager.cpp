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

#include "imagemanager.h"
#include "natural_less.h"
#include <assert.h>

ImageManager::ImageManager(const std::string &d)
{
    dir_name = d;
    DIR *dir;
    try
    {
        dir = opendir(d.c_str());
    } catch (std::exception& e)
    {
        std::cout << "Directory does not exist " << e.what() << std::endl;
    }

    struct dirent *dp;
    while ((dp=readdir(dir)) != NULL) {
        if(strcmp(dp->d_name, "..") != 0  &&  strcmp(dp->d_name, ".") != 0 && dp->d_name[0] != '.'
                && dp->d_name[0] != '~') {
            filename.push_back(dir_name + "/" + std::string(dp->d_name));
        }
    }



    assert(filename.size() != 0);

    sorting(filename);

    count = -1;
    end = -1;

    firstReset = false;
}

ImageManager::~ImageManager() {
    filename.clear();
}

void ImageManager::sorting(std::vector<std::string>& data)
{
    std::sort(data.begin(), data.end(), natural_sort);
}

std::string ImageManager::next() {
    (count < filename.size()) ? count++ : count = 0;
    if(!firstReset && count >= filename.size())
    {
        end = filename.size();
        firstReset = true;
    }
    return filename[count];
}

std::string ImageManager::prev() {
    (count > 0 && !firstReset) ? count-- : count = 0;
    if(firstReset)
    {
        count = filename.size() - 1;
    }
    return filename[count];
}
