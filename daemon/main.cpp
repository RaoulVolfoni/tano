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

#include <QtSingleCoreApplication>

#include "daemon/DBusAdaptorRecorder.h"
#include "daemon/DBusAdaptorXmltv.h"
#include "daemon/DaemonMain.h"

#ifdef Q_WS_X11
    #include <X11/Xlib.h>
#endif

int main(int argc, char *argv[])
{
#ifdef Q_WS_X11
    XInitThreads();
#endif

    QtSingleCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("Tano Daemon");

    if(a.isRunning())
        return 0;

    DaemonMain *daemon = new DaemonMain();

    new DBusAdaptorRecorder(daemon->recorder(), daemon);
    new DBusAdaptorXmltv(daemon->xmltv(), daemon);
    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.registerObject("/Daemon", daemon);
    connection.registerService("si.Tano");

    return a.exec();
}
