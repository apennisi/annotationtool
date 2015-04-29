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
 * \file associatedialog.h
 *
 * \class AssociateDialog
 *
 * \brief Class for creating a Dialog for association IDs
 *
 **/

#ifndef ASSOCIATEDIALOG_H
#define ASSOCIATEDIALOG_H

#include <QDialog>
#include <iostream>
#include <sstream>
#include <map>

#include "rectangle.h"

namespace Ui {
class AssociateDialog;
}

class AssociateDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * \brief Create a new object AssociateDialog
     * 
     * \param currentIdx: id of the selected rectangle
     * \param _idList: list of IDs
     *
     */
    explicit AssociateDialog(const int &currentIdx,
                             const std::map<int, int> &_idList,
                             QWidget *parent = 0);
    /**
     * \brief return the id to associate
     *
     * \return return the id to associate
     */
    inline int getIdTo() const { return idTo; }
    /**
     * \brief Destructor AssociateDialog
     *
     */
    ~AssociateDialog();

private:
    Ui::AssociateDialog *ui;
    std::map<int, int> idList;
    int idFrom, idTo;

private slots:
    void onChangeTo(const int &idList);
};

#endif // ASSOCIATEDIALOG_H
