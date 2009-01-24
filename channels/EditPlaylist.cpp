#include <QMessageBox>
#include <QHeaderView>
#include <QDir>
#include <QFileDialog>

#include "EditPlaylist.h"

EditPlaylist::EditPlaylist(QWidget *parent, QString fileName)
    : QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.actionDelete, SIGNAL(triggered()), this, SLOT(deleteItem()));
	connect(ui.actionAddCategory, SIGNAL(triggered()), this, SLOT(addItemCategory()));
	connect(ui.actionAddChannel, SIGNAL(triggered()), this, SLOT(addItemChannel()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(save()));

	ui.playlist->header()->setResizeMode(QHeaderView::Stretch);

	treeStyle();

	load = new TanoHandler(ui.playlist, true);

	QXmlSimpleReader reader;
	reader.setContentHandler(load);
	reader.setErrorHandler(load);

	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Tano Player"),
							tr("Cannot read file %1:\n%2.")
							.arg(fileName)
							.arg(file.errorString()));
		return;
	}
	QXmlInputSource xmlInputSource(&file);
	reader.parse(xmlInputSource);
}

EditPlaylist::~EditPlaylist()
{

}

void EditPlaylist::treeStyle()
{
	categoryIcon.addPixmap(QPixmap(":/icons/images/folder.png"),
	                     QIcon::Normal, QIcon::Off);
	categoryIcon.addPixmap(QPixmap(":/icons/images/folder_video.png"),
	                     QIcon::Normal, QIcon::On);
	channelIcon = QIcon(":/icons/images/video.png");
}

void EditPlaylist::deleteItem()
{
	QTreeWidgetItem *parent = ui.playlist->currentItem()->parent();
	if(parent)
		ui.playlist->currentItem()->parent()->removeChild(ui.playlist->currentItem());
	else
		ui.playlist->takeTopLevelItem(ui.playlist->indexOfTopLevelItem(ui.playlist->currentItem()));
}

void EditPlaylist::addItemCategory()
{
	QStringList defaults;
	defaults << tr("Category");
	QTreeWidgetItem *item = new QTreeWidgetItem(defaults);
	item->setIcon(0,categoryIcon);
	item->setData(0, Qt::UserRole, "category");
	ui.playlist->addTopLevelItem(item);
}


void EditPlaylist::addItemChannel()
{
	QStringList defaults;
	defaults << tr("Channel") << tr("New channel") << tr("language") << "NI" << "URL";

	if(ui.playlist->currentItem()->text(1) == "") {
		QTreeWidgetItem *item = new QTreeWidgetItem(ui.playlist->currentItem(), defaults);
		item->setIcon(0,channelIcon);
		item->setData(0, Qt::UserRole, "channel");
	}
	else
		QMessageBox::warning(this, tr("Tano Player"),
									tr("Please, add channel to a category."));
}

void EditPlaylist::save()
{
	fileName =
		QFileDialog::getSaveFileName(this, tr("Save Channel list"),
									QDir::homePath(),
									tr("Tano TV Channel list Files (*.tano *.xml)"));
	if (fileName.isEmpty())
		return;

	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Tano Player"),
							tr("Cannot write file %1:\n%2.")
							.arg(fileName)
							.arg(file.errorString()));
		return;
	}

	generator = new TanoGenerator(ui.playlist);
	generator->write(&file);
}