#ifndef YYTUIMANAGE_H
#define YYTUIMANAGE_H

#include <QObject>
#include "mainwindow/mainwindow.h"
#include "dialogs/settingdialog.h"

class YYTUIManage : public QObject
{
	Q_OBJECT

public:
	YYTUIManage(QObject *parent = nullptr);
	~YYTUIManage();

	MainWindow* getMianWindow();
	SettingDialog* getSettingDlg();
public:
	MainWindow *mainDlg;
	SettingDialog* settingDialog;
private:
	
};

#endif // YYTUIMANAGE_H
