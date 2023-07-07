#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ControllerCompanionQT.h"

class ControllerCompanionQT : public QMainWindow
{
    Q_OBJECT

public:
    ControllerCompanionQT(QWidget *parent = nullptr);
    ~ControllerCompanionQT();

private:
    Ui::ControllerCompanionQTClass ui;
};
