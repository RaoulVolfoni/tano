#ifndef ABOUT_H
#define ABOUT_H

#include <QtGui/QDialog>
#include "ui_About.h"

class About : public QDialog
{
    Q_OBJECT

public:
    About(QWidget *parent = 0, QString version = "Unknown");
    ~About();

private:
    Ui::About ui;

    QString qt;
};

#endif // ABOUT_H