
#include "QFramer/futil.h"
#include "mainwindow/mainwindow.h"
#include "qtsingleapplication.h"
#include "dialogs/settingdialog.h"



int main(int argc, char *argv[])
{
	QtSingleApplication instance(argc, argv);
	QtSingleApplication::setOrganizationName("DJF");
	QtSingleApplication::setOrganizationDomain("https://github.com/dragondjf");
	QtSingleApplication::setApplicationName(FromBits("稀宝远程会诊"));
	QtSingleApplication::setWindowIcon(QIcon(":/YYT/skin/YYT/XBHZ.png"));

	if (argc >= 2)
	{
		if (instance.sendMessage(argv[1]))
			return 0;
	}
	else
	{
		if (instance.sendMessage("show login"))
			return 0;
	}
	

	MainWindow *main = MainWindow::getInstance();
	main->setAttribute(Qt::WA_DeleteOnClose);
	main->hide();
	if (argc >= 2)
	{
		main->setloginData(argv[1]);
	}
	else
	{
		SettingDialog* settingDialog = new SettingDialog;
		settingDialog->show();
	}

    instance.setActivationWindow(main);

	QObject::connect(&instance, SIGNAL(messageReceived(const QString&)),
		main, SLOT(OnMessage(const QString&)));

	return instance.exec();
}
