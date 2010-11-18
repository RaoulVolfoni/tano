/****************************************************************************
* Tano - An Open IP TV Player
* Copyright (C) 2008-2010 Tadej Novak <ntadej@users.sourceforge.net>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef TANO_MENUCORE_H_
#define TANO_MENUCORE_H_

#include <QtGui/QMenu>

class MenuCore : public QMenu
{
Q_OBJECT
public:
	MenuCore(QWidget *parent = 0);
	~MenuCore();

	void addItem(QAction *action);
	QAction *actionNext() { return _next; }

private slots:
	void next();

private:
	QActionGroup *_group;
	QAction *_next;
};

#endif // TANO_MENUCORE_H_
