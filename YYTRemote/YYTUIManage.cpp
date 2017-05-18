#include "YYTUIManage.h"

YYTUIManage::YYTUIManage(QObject *parent)
	: QObject(parent)
{
	mainDlg = MainWindow::getInstance();
	mainDlg->setAttribute(Qt::WA_DeleteOnClose);

	settingDialog = SettingDialog::getInstance();
}

YYTUIManage::~YYTUIManage()
{

}

MainWindow* YYTUIManage::getMianWindow()
{
	return mainDlg;
}

SettingDialog* YYTUIManage::getSettingDlg()
{
	return settingDialog;
}
