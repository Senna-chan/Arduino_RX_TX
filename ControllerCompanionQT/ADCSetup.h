#pragma once

#include <QWidget>
#include "ui_ADCSetup.h"

class ADCSetup : public QWidget
{
	Q_OBJECT

public:
	ADCSetup(QWidget *parent = nullptr);
	~ADCSetup();

private:
	Ui::ADCSetupClass ui;
};
