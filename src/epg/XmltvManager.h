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

#ifndef TANO_XMLTVMANAGER_H_
#define TANO_XMLTVMANAGER_H_

#include <QtCore/QFutureWatcher>
#include <QtCore/QObject>
#include <QtCore/QTimer>

#include "core/Enums.h"
#include "epg/XmltvHandler.h"

extern bool loadXmltvStart(XmltvHandler *handler,
                           const QString &location);

class XmltvChannel;
class XmltvChannelsModel;
class XmltvList;
class XmltvProgramme;
class XmltvProgrammeModel;

class XmltvManager : public QObject
{
Q_OBJECT
public:
    XmltvManager(QObject *parent = 0);
    ~XmltvManager();

    void loadXmltv(const QString &location);

public slots:
    void request(const QString &id,
                 const Tano::Id &identifier);
    void requestProgramme(const QString &id);
    void requestProgrammeNext(XmltvProgramme *current);
    void requestProgrammePrevious(XmltvProgramme *current);
    void stop();

signals:
    void channels(XmltvChannelsModel *);
    void current(const QString,
                 const QString);
    void schedule(XmltvProgrammeModel *,
                  const Tano::Id);
    void programme(XmltvProgramme *);

private slots:
    void current();
    void loadXmltvFinish();

private:
    QString processCurrentString(XmltvProgramme *programme) const;

    QString _location;

    bool _loading;

    Tano::Id _currentIdentifier;
    QString _currentXmltvId;

    XmltvHandler *_handler;
    QTimer *_timer;
    QFutureWatcher<bool> *_watcher;
    XmltvList *_xmltv;
};

#endif // TANO_XMLTVMANAGER_H_
