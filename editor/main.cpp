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

#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include <QtGui/QBitmap>
#include <QtGui/QSplashScreen>

#include "ui/playlist/PlaylistEdit.h"

#ifdef Q_WS_X11
    #include <X11/Xlib.h>
#endif

int main(int argc, char *argv[])
{
#ifdef Q_WS_X11
    XInitThreads();
#endif

    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Tano Editor");

    QPixmap pixmap(":/images/splash-editor.png");
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->setMask(pixmap.mask());
    splash->show();

    PlaylistEdit main;
    main.show();

    splash->hide();
    delete splash;

    return app.exec();
}
