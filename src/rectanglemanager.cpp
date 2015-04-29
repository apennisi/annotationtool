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

#include "rectanglemanager.h"

using namespace bbox;

RectangleManager::RectangleManager(QComboBox *_comboBox)
{
    currentIdx = -1;
    previousIdx = -1;
    frameCount = 0;
    idCounter = 0;
    idComboBoxCounter = 0;
    comboBox = _comboBox;
    selectedById = false;
}

RectangleManager::~RectangleManager()
{
    std::vector<bbox::Rectangle*>::iterator it;
    std::vector< std::vector<bbox::Rectangle*> >::iterator it2;

    for(it = currentRectangles.begin(); it != currentRectangles.end(); ++it)
    {
        delete *it;
    }

    for(it2 = rectangles.begin(); it2 != rectangles.end(); ++it2)
    {
        for(it = (*it2).begin(); it != (*it2).end(); ++it)
        {
            delete *it;
        }
    }
}

bool RectangleManager::associate(cv::Mat &frame_clone)
{
    bool value = false;
    if(currentIdx != -1)
    {
        int idTo = -1;

        AssociateDialog associateDialog(currentRectangles[currentIdx]->getInfo().getId(),
                                        idList);
        associateDialog.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
        int dialogCode = associateDialog.exec();
        idTo = associateDialog.getIdTo();
        if(idTo != 0)
        {
            switch (dialogCode) {
                case QDialog::Accepted:
                {
                    std::map<int, int>::iterator it, it_to, it_delete;

                    for(it_to = idList.begin(); it_to != idList.end(); ++it_to)
                    {
                        if(it_to->second == idTo) break;
                    }

                    it_delete = idList.find(currentRectangles[currentIdx]->getInfo().getId());
                    if(it_delete != idList.end())
                    {
                        comboBox->removeItem(it_delete->second);
                        idComboBoxCounter--;
                        for(it = it_delete; it != idList.end(); ++it)
                        {
                            it->second--;
                        }
                        idList.erase(it_delete);
                    }

                    rectangleList.erase(rectangleList.find(
                                            currentRectangles[currentIdx]->getInfo().getId()));
                    currentRectangles[currentIdx]->setId(it_to->first);
                    currentRectangles[currentIdx]->setColor(rectangleList.find(it_to->first)->second);
                    currentRectangles[currentIdx]->deselect();

                    comboBox->setItemData(it_to->second, 33, Qt::UserRole - 1);
                    comboBox->setCurrentIndex(0);
                    currentIdx = -1;
                    value = true;
                    drawRectangles(frame_clone);
                    break;
                }
                case QDialog::Rejected:
                default:
                    break;
            }
        }
    }
    return value;
}

void RectangleManager::add(const cv::Scalar &_color)
{
    currentRectangles.push_back(new bbox::Rectangle(current_rect, 4, _color, 2, idCounter++));
    rectangleList.insert(std::pair<int, cv::Scalar>(idCounter - 1, currentRectangles[currentRectangles.size() - 1]->getColor()));
    idList.insert(std::pair<int, int>(idCounter - 1, ++idComboBoxCounter));
    std::stringstream ss;
    ss << idCounter - 1;
    comboBox->addItem(QString::fromStdString(ss.str()), QVariant(idComboBoxCounter - 1));
}

void RectangleManager::select(cv::Mat &img)
{
    currentRectangles[currentIdx]->select();
    this->drawRectangles(img);
}

void RectangleManager::moving(const cv::Point &p1, const cv::Point &p2, cv::Mat &img,
                              const cv::Scalar &color)
{
    this->drawRectangles(img);
    current_rect = cv::Rect(p1, p2);
    cv::rectangle(img, current_rect, color, LINE_WEIGHT, 8, 0);
    bbox::Rectangle::drawCornerRect(p1, OFFSET_CORNER, img);
    bbox::Rectangle::drawCornerRect(p2, OFFSET_CORNER, img);
}

void RectangleManager::selected(cv::Mat &img)
{
    if(currentIdx != -1)
    {
        currentRectangles[currentIdx]->select();
        current_rect = currentRectangles[currentIdx]->getRect();
        currentRectangles[currentIdx]->draw(img);
        previousIdx = currentIdx;
        selectedById = true;
        comboBox->setCurrentIndex(idList[currentRectangles[currentIdx]->getInfo().getId()]);
    }
}

void RectangleManager::release()
{
    if(previousIdx != -1)
    {
        currentRectangles[previousIdx]->deselect();
        currentRectangles[previousIdx]->set(current_rect);
        selectedById = false;
    }
}

void RectangleManager::selectById(const int &_id, cv::Mat &img)
{
    if(selectedById)
    {
        this->release();
        selectedById = false;
    }

    std::vector<bbox::Rectangle *>::iterator it;

    for(it = currentRectangles.begin(); it != currentRectangles.end(); ++it)
    {
        if( (*it)->getInfo().getId() == _id )
        {
            currentIdx = it - currentRectangles.begin();
            selectedById = true;
            break;
        }
    }

    this->drawRectangles(img);
    this->selected(img);
}

void RectangleManager::copyRectVector(const std::vector<Rectangle *> &_rect)
{
    std::vector<bbox::Rectangle *> currentTmp = _rect;
    std::vector<bbox::Rectangle *>::iterator it;

    currentRectangles.clear();

    for(it = currentTmp.begin(); it != currentTmp.end(); ++it)
    {
        currentRectangles.push_back(new bbox::Rectangle(*it));
    }
}

void RectangleManager::selectBR(cv::Mat &img, const int &xGap, const int &yGap)
{
    this->select(img);
    cv::Rect old = currentRectangles[currentIdx]->getRect();
    cv::Point newBr = cv::Point(old.br().x + xGap, old.br().y + yGap);
    this->drawSelectedRectangle(old.tl(), newBr, img);
}

void RectangleManager::selectTL(cv::Mat &img, const int &xGap, const int &yGap)
{
    this->select(img);
    cv::Rect old = currentRectangles[currentIdx]->getRect();
    cv::Point newTL = cv::Point(old.tl().x + xGap, old.tl().y + yGap);
    this->drawSelectedRectangle(newTL, old.br(), img);
}

void RectangleManager::moveRect(cv::Mat &img, const int &xGap, const int &yGap)
{
    this->select(img);
    cv::Rect old = currentRectangles[currentIdx]->getRect();
    current_rect = cv::Rect(old.tl().x + xGap, old.tl().y + yGap, old.width, old.height);
    cv::rectangle(img, current_rect, RED_COLOR, 2, 8, 0);
    bbox::Rectangle::drawCornerRect(current_rect.tl(), OFFSET_CORNER, img);
    bbox::Rectangle::drawCornerRect(current_rect.br(), OFFSET_CORNER, img);
}

void RectangleManager::copyRect(const std::vector<std::vector<bbox::Rectangle *> > &_rectangles)
{
    std::vector< std::vector<bbox::Rectangle *> >::const_iterator it;
    std::set<int> ids;

    for(it = _rectangles.begin(); it != _rectangles.end(); ++it)
    {
        std::vector< bbox::Rectangle *>::const_iterator it2;
        std::vector< bbox::Rectangle *> currRects;

        for(it2 = (*it).begin(); it2 != (*it).end(); ++it2)
        {
            currRects.push_back(new bbox::Rectangle(*it2));
            int id = (*it2)->getInfo().getId();
            ids.insert(id);
            rectangleList.insert(std::pair<int, cv::Scalar>(id, (*it2)->getColor()));
            currRects[currRects.size() - 1]->setColor(rectangleList[id]);
        }

        rectangles.push_back(currRects);
        frameCount++;
    }

    currentRectangles = rectangles[rectangles.size() - 1];

    std::set<int>::iterator it2;
    idCounter = *ids.rbegin() + 1;

    int i = 0;
    for(it2 = ids.begin(); it2 != ids.end(); ++it2)
    {
        idList.insert(std::pair<int, int>(*it2, i + 1));
        std::stringstream ss;
        ss << *it2;
        comboBox->addItem(QString::fromStdString(ss.str()), QVariant(i));
        i++;
    }

    idComboBoxCounter = idList[ids.size()-1];
}

void RectangleManager::deselect()
{
    if(currentIdx != -1)
    {
        currentRectangles[currentIdx]->set(current_rect);
        currentRectangles[currentIdx]->deselect();
        currentIdx = -1;
        selectedById = false;
        comboBox->setCurrentIndex(0);
    }
}

int RectangleManager::findPoint(const int &x, const int &y)
{
    if ( findBRPoint(x, y) )
         return 0;
    else if ( findTLPoint(x, y) )
         return 1;
    else if ( findRectangle(x, y) )
         return 2;
    else
        return -1;
}

void RectangleManager::drawSelectedRectangle(const cv::Point &tl, const cv::Point &br, cv::Mat &img)
{
    current_rect = cv::Rect(tl, br);
    cv::rectangle(img, current_rect, currentRectangles[currentIdx]->getColor(), 2, 8, 0);
    bbox::Rectangle::drawCornerRect(tl, OFFSET_CORNER, img);
    bbox::Rectangle::drawCornerRect(br, OFFSET_CORNER, img);
}

bool RectangleManager::findTLPoint(const int &x, const int &y)
{
    std::vector<bbox::Rectangle*>::iterator it;
    for(it = currentRectangles.begin(); it != currentRectangles.end(); ++it)
    {
        if((*it)->isTopLeft(cv::Point(x, y)))
        {
            currentIdx = it - currentRectangles.begin();
            return true;
        }
    }
    return false;
}

bool RectangleManager::findBRPoint(const int &x, const int &y)
{
    std::vector<bbox::Rectangle*>::iterator it;
    for(it = currentRectangles.begin(); it != currentRectangles.end(); ++it)
    {
        if((*it)->isBottomRight(cv::Point(x, y)))
        {
            currentIdx = it - currentRectangles.begin();
            return true;
        }
    }
    return false;
}

bool RectangleManager::findRectangle(const int &x, const int &y)
{
    std::vector<bbox::Rectangle*>::iterator it;
    for(it = currentRectangles.begin(); it != currentRectangles.end(); ++it)
    {
        if((*it)->isSelected(cv::Point(x, y)))
        {
            currentIdx = it - currentRectangles.begin();
            return true;
        }
    }
    return false;
}

void RectangleManager::drawRectangles(cv::Mat &img)
{
    std::vector<bbox::Rectangle*>::iterator it;

    for(it = currentRectangles.begin(); it != currentRectangles.end(); ++it)
    {
        if(!(*it)->isRectSelected())
        {
            (*it)->draw(img);
        }
    }
}

void RectangleManager::nextFrame(cv::Mat &img, const int &end)
{
    if(end == -1)
    {
        if(++frameCount < int(rectangles.size()))
        {

            this->updateRectangles();
        }
        else
        {
            rectangles.push_back(currentRectangles);
            copyRectVector(rectangles[rectangles.size() - 1]);
        }
    }
    else
    {
        if(frameCount >= int(rectangles.size()))
        {
            frameCount = 0;
        }
        else
            frameCount++;
        copyRectVector(rectangles[frameCount]);
    }
    drawRectangles(img);
}

void RectangleManager::prevFrame(cv::Mat &img, const int &end)
{
    if(end == -1)
    {
        if(frameCount >= 0)
        {
            copyRectVector();
            if(--frameCount == -1 ) frameCount = 0;
            copyRectVector(rectangles[frameCount]);
        }
    }
    else
    {
        if(frameCount >= 0)
        {
            copyRectVector();
            if(--frameCount == -1 ) frameCount = 0;
            copyRectVector(rectangles[frameCount]);
        }
        else
        {
            copyRectVector();
            frameCount = end - 1;
            copyRectVector(rectangles[frameCount]);
        }
    }
    drawRectangles(img);
}

void RectangleManager::hide(cv::Mat &img)
{
    if(currentIdx != -1)
    {
        currentRectangles.erase(currentRectangles.begin() + currentIdx);
        comboBox->setItemData(currentIdx + 1, 0, Qt::UserRole - 1);
        comboBox->setCurrentIndex(0);
        currentIdx = -1;
        selectedById = false;
    }
    drawRectangles(img);
}

void RectangleManager::delete_rect(cv::Mat &img)
{
    if(currentIdx != -1)
    {
        int id = currentRectangles[currentIdx]->getInfo().getId();
        std::map<int, int>::iterator it = idList.find(id), it2;
        if(it != idList.end())
        {
            comboBox->removeItem(it->second);
            idComboBoxCounter--;
            for(it2 = it; it2 != idList.end(); ++it2)
            {
                it2->second--;
            }
            idList.erase(it);
        }
        rectangleList.erase(rectangleList.find(id));
        currentRectangles.erase(currentRectangles.begin() + currentIdx);
        comboBox->setCurrentIndex(0);
        currentIdx = -1;
        selectedById = false;
    }
    drawRectangles(img);
}

void RectangleManager::copyRectVector()
{
    if(frameCount == int(rectangles.size()))
    {
        rectangles.push_back(currentRectangles);
    }
    else
    {
        rectangles.erase(rectangles.begin() + frameCount);
        rectangles.insert(rectangles.begin() + frameCount, currentRectangles);
    }
}

void RectangleManager::updateRectangles()
{
    std::vector<bbox::Rectangle *> currentTmp;
    std::vector<bbox::Rectangle *>::iterator it, it2;

    for(it = currentRectangles.begin(); it != currentRectangles.end(); ++it)
    {
        currentTmp.push_back(new bbox::Rectangle(*it));
    }

    rectangles[frameCount - 1] = currentTmp;

    currentRectangles.clear();

    currentRectangles = rectangles[frameCount];

    if(currentRectangles.size() < currentTmp.size())
    {
        for(it = currentTmp.begin() + currentRectangles.size(); it != currentTmp.end(); ++it)
        {
            currentRectangles.push_back(new bbox::Rectangle(*it));
        }
    }
}
