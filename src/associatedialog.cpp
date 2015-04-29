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

#include "associatedialog.h"
#include "ui_associatedialog.h"

AssociateDialog::AssociateDialog(const int &currentIdx,
                                 const std::map<int, int> &_idList,
                                 QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AssociateDialog)
{
    ui->setupUi(this);
    ui->to->addItem("Not Selected", QVariant(-1));
    idList = _idList;

    std::map<int, int>::iterator it;
    for(it = idList.begin(); it != idList.end(); ++it)
    {
        std::stringstream ss;
        ss << it->first;
        ui->to->addItem(QString::fromStdString(ss.str()), QVariant(it->second));
    }

    connect(ui->to, SIGNAL(activated(int)), this, SLOT(onChangeTo(int)) );
    ui->to->setCurrentIndex(0);

    std::stringstream ss;
    ss << currentIdx;
    ui->from->setText(QString::fromStdString(ss.str()));

    idFrom = currentIdx;
    idTo = -1;
}

AssociateDialog::~AssociateDialog()
{
    delete ui;
}


void AssociateDialog::onChangeTo(const int &idList)
{
    if(idFrom != -1)
    {
        idTo = ui->to->itemData(idList).toInt();
    }
}
