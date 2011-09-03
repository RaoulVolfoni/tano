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

#ifndef TANO_PLAYLISTEDIT_H_
#define TANO_PLAYLISTEDIT_H_

#include <QtCore/QTimer>
#include <QtGui/QMainWindow>
#include <QtGui/QTreeWidgetItem>

#include "Config.h"

#if EDITOR
class UpdateDialog;
#endif

#if WITH_EDITOR_VLCQT
class VlcInstance;
class VlcMediaPlayer;
#endif

namespace Ui
{
	class PlaylistEdit;
}

class PlaylistEdit : public QMainWindow
{
Q_OBJECT
public:
	PlaylistEdit(const WId &video = 0,
				 QWidget *parent = 0);
	~PlaylistEdit();

	void setStandalone(const bool &standalone);

public slots:
	void newPlaylist();
	void open(const QString &playlist = 0,
			  const bool &refresh = false);

protected:
	void changeEvent(QEvent *e);
	void closeEvent(QCloseEvent *event);

private slots:
	void aboutTano();
	void setTitle(const QString &title);

	void deleteItem();
	void addItem();
	void addItem(const QString &name,
				 const QString &url);

	void save();
	void exportM3UClean();
	void exportCSV();
	void importCSV();
	void exportJs();
	void importJs();
	void importTanoOld();
	void print();

	void menuOpenExport();
	void menuOpenImport();
	void exit();

	void editItem(QTreeWidgetItem *item);

	void editChannelNumber();
	void editChannelName(const QString &text);
	void editChannelUrl(const QString &text);
	void editChannelCategories(const QString &text);
	void editChannelLanguage(const QString &text);
	void editChannelEpg(const QString &text);

	void moveUp();
	void moveDown();

	void refreshPlaylist(const bool &refresh);
	void checkIp();
	void checkCurrentIp();
	void setState(const bool &playing);

    void updateAvailable();

private:
	void createConnections();
	void createSettings();

	Ui::PlaylistEdit *ui;

	bool _closeEnabled;
	QMenu *_menuExport;
	QMenu *_menuImport;

	bool _standalone;

#if EDITOR
    UpdateDialog *_update;
#endif

	// Update playlist
	QString currentIp();

#if WITH_EDITOR_VLCQT
	VlcInstance *_instance;
	VlcMediaPlayer *_player;
	int _refresh;
	int _currentIp[4];
	int _currentPort;
	int _currentTimeout;
	bool _currentIpPlaying;
	QTimer *_timer;
#endif
};

#endif // TANO_PLAYLISTEDIT_H_
