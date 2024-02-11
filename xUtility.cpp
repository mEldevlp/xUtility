#include "xUtility.h"

xUtility::xUtility(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::xUtilityClass())
{
    ui->setupUi(this);
}

xUtility::~xUtility()
{
    delete ui;
}
