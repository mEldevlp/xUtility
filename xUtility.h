#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_xUtility.h"

#include "atd/TList.h"
#include "atd/TStack.h"
#include "atd/TQueue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class xUtilityClass; };
QT_END_NAMESPACE

class xUtility : public QMainWindow
{
    Q_OBJECT

public:
    xUtility(QWidget *parent = nullptr);
    ~xUtility();

private:
    Ui::xUtilityClass *ui;

private:
    UTIL::TList<int> list; // uni
    //UTIL::TStack<int> stack;
    //UTIL::TQueue<int> queue;
};
