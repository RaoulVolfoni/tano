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

#include <QtGui/QFileDialog>

#include "SettingsPlaylist.h"
#include "ui_SettingsPlaylist.h"

#include "core/Settings.h"

SettingsPlaylist::SettingsPlaylist(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::SettingsPlaylist)
{
	ui->setupUi(this);

	connect(ui->browsePlaylistButton, SIGNAL(clicked()), this, SLOT(playlistBrowse()));
	connect(ui->resetPlaylistButton, SIGNAL(clicked()), this, SLOT(playlistReset()));
}

SettingsPlaylist::~SettingsPlaylist()
{
	delete ui;
}

void SettingsPlaylist::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
		default:
			break;
	}
}

QString SettingsPlaylist::playlist() const
{
	return ui->playlistLineEdit->text();
}

void SettingsPlaylist::setPlaylist(const QString &playlist)
{
	ui->playlistLineEdit->setText(playlist);
}

void SettingsPlaylist::playlistReset()
{
	ui->playlistLineEdit->setText("");
}

void SettingsPlaylist::playlistBrowse()
{
	QString file = QFileDialog::getOpenFileName(this, tr("Open channel list"),
												QDir::homePath(),
												tr("Tano TV channel list files(*.m3u)"));
	ui->playlistLineEdit->setText(file);
}
