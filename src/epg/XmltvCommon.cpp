/****************************************************************************
* Tano - An Open IP TV Player
* Copyright (C) 2011 Tadej Novak <tadej@tano.si>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include "epg/XmltvCommon.h"

QString Tano::Xmltv::dateFormat()
{
    QString format = "yyyyMMddHHmmss";
    return format;
}

QString Tano::Xmltv::dateFormatDisplay()
{
    QString format = "dd.MM.yyyy";
    return format;
}

QString Tano::Xmltv::dateFormatMobile()
{
    QString format = "dd.MM.";
    return format;
}

QRegExp Tano::Xmltv::dateRegExp()
{
    QRegExp exp = QRegExp(" .[0-9][0-9][0-9][0-9]");
    return exp;
}
