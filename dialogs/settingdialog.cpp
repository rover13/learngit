/****************************************************************************
**
** Copyright (C) 2014 dragondjf
**
** QFramer is a frame based on Qt5.3, you will be more efficient with it. 
** As an Qter, Qt give us a nice coding experience. With user interactive experience(UE) 
** become more and more important in modern software, deveployers should consider business and UE.
** So, QFramer is born. QFramer's goal is to be a mature solution 
** which you only need to be focus on your business but UE for all Qters.
**
** Version	: 0.2.5.0
** Author	: dragondjf
** Website	: https://github.com/dragondjf
** Project	: https://github.com/dragondjf/QCFramer
** Blog		: http://my.oschina.net/dragondjf/home/?ft=atme
** Wiki		: https://github.com/dragondjf/QCFramer/wiki
** Lincence: LGPL V2
** QQ: 465398889
** Email: dragondjf@gmail.com, ding465398889@163.com, 465398889@qq.com
** 
****************************************************************************/
#include "YYTVideoShow.h"
#include "YYTServerHelper.h"
#include "YYTRoomMemerDlg.h"
#include "LiveServerHelper.h"
/*#include "ConsultationApplyDlg.h"*/
#include "ConsultationReportDlg.h"
#include "YYTStateManage.h"
#include "YYTPluginManage.h"

#include "settingdialog.h"
#include <QVBoxLayout>
#include <QTabWidget>
#include <QGroupBox>
#include "mainwindow/mainwindow.h"

SettingDialog* SettingDialog::instance = NULL;

SettingDialog::SettingDialog(QWidget *parent) :
    FBaseDialog(parent)
{
    initUI();
	initConnect();
}

void SettingDialog::initUI()
{
    normalSize = QSize(400, 475);
    getTitleBar()->getTitleLabel()->setText(FromBits("µÇÂ¼"));
    QVBoxLayout* mainLayout = (QVBoxLayout*)layout();

	//! Account
	QLabel* labelAccount = new QLabel();
	labelAccount->setText(FromBits("ÕË      ºÅ"));
	m_lEditAccount = new QLineEdit;

	QHBoxLayout* hLayoutAccount = new QHBoxLayout;
	hLayoutAccount->addWidget(labelAccount);
	hLayoutAccount->addWidget(m_lEditAccount);
	
	//! password
	QLabel* labelPsword = new QLabel();
	labelPsword->setText(FromBits("ÃÜ      Âë"));
	m_lEditPsword = new QLineEdit;

	QHBoxLayout* hLayoutPsword = new QHBoxLayout;
	hLayoutPsword->addWidget(labelPsword);
	hLayoutPsword->addWidget(m_lEditPsword);
	
	//! roomID
	QLabel* labelRoomID = new QLabel();
	labelRoomID->setText(FromBits("»áÒéÑûÇëÂë"));
	m_lEditRoomID = new QLineEdit;

	//! fortest
	m_lEditAccount->setText("13880334484");
	m_lEditPsword->setText("111111");
	m_lEditRoomID->setText("M1");


	QHBoxLayout* hLayoutRoomID = new QHBoxLayout;
	hLayoutRoomID->addWidget(labelRoomID);
	hLayoutRoomID->addWidget(m_lEditRoomID);
	
	m_btnLogin = new QPushButton(FromBits("µÇÂ¼"), this);
	m_btnLogin->setFixedSize(100, 60);
	//m_btnQuit  = new QPushButton(tr("Quit"), this);
	//m_btnQuit->setFixedSize(100, 60);

	QHBoxLayout* hLayoutBtn = new QHBoxLayout;
	hLayoutBtn->addWidget(m_btnLogin);
	//hLayoutBtn->addWidget(m_btnQuit);

	QVBoxLayout* vlayout = new QVBoxLayout;
	vlayout->addLayout(hLayoutAccount);
	vlayout->addLayout(hLayoutPsword);
	vlayout->addLayout(hLayoutRoomID);
	vlayout->addLayout(hLayoutBtn);
	
	QGroupBox* gBox = new QGroupBox;
	gBox->setLayout(vlayout);
	
	mainLayout->addWidget(gBox);
}

void SettingDialog::initConnect()
{
	connect(m_btnLogin, SIGNAL(clicked()), this, SLOT(on_pushBtn_clicked()));
	//connect(m_btnQuit, SIGNAL(clicked()), this, SLOT(on_pushBtn_clicked()));
}


void SettingDialog::SetUserInfo(QString strData)
{
	QMap<QString,QString> paramMap;
	int a;
	QString strBuf;
	QString strBuf1;
	a = strData.indexOf("?");
	if (-1 == a)
	{
		return;
	}
	strBuf = strData.right(strData.size() - a - 1);
	do 
	{
		a = strBuf.indexOf("&");
		if (-1 == a)
		{
			break;
		}
		strBuf1 = strBuf.left(a);

		int b = strBuf1.indexOf("=");
		paramMap[strBuf1.left(b)] = strBuf1.right(strBuf1.size() - b - 1);
		strBuf = strBuf.right(strBuf.size() - a - 1);

	} while (1);

	QString strToken;
	QString strRoomId;

	if (!strBuf.isEmpty())
	{
		int b = strBuf.indexOf("=");
		paramMap[strBuf.left(b)] = strBuf.right(strBuf.size() - b - 1);
	}

	if (paramMap.contains("dgid"))
	{
		strRoomId = paramMap.value("dgid"); //= /*.toInt()*/;
	}
	if (paramMap.contains("access_token"))
	{
		strToken = paramMap.value("access_token");
	}

	if (strRoomId.isEmpty() || strToken.isEmpty())
	{
		ShowErrorTips(FromBits("»ñÈ¡ÓÃ»§ÐÅÏ¢Ê§°Ü£¬ÇëÖØÐÂµÇÂ¼"), this);
		return;
	}
	YYTPluginManage::getInstance()->getYYTServerHelper()->setToken(strToken);
	YYTPluginManage::getInstance()->getYYTServerHelper()->setRoomID(strRoomId);
	YYTPluginManage::getInstance()->getYYTServerHelper()->serGetUserInfo();

	this->close();
	MainWindow::getInstance()->showMaximized();
}

void SettingDialog::closeEve()
{
// 	YYTServerHelper::getInstance()->destroyed();
// 	YYTStateManage::getInstance()->destroy();
// 	YYTVideoShow::getInstance()->destroy();
}

SettingDialog* SettingDialog::getInstance()
{
	if(!instance)
	{
		instance = new SettingDialog();
	}
	return instance;
}

void SettingDialog::on_pushBtn_clicked()
{
	QPushButton* pBtn = static_cast<QPushButton*>(sender());

	if (NULL != pBtn)
	{
		if (m_btnLogin == pBtn)
		{
			OnBtnLogin();
		}
// 		else if (m_btnQuit == pBtn)
// 		{
// 			OnBtnQuit();
// 		}
	}
}


void SettingDialog::OnBtnLogin()
{
	QString szAccount	= m_lEditAccount->text();
	QString szPsword	= m_lEditPsword->text(); 
	QString szRoomID	= m_lEditRoomID->text();

	if (szAccount.isEmpty())
	{
		return;
	}

	if (szAccount.isEmpty())
	{
		return;
	}

	if (szAccount.isEmpty())
	{
		return;
	}

	//YYTPluginManage::getInstance()->getYYTServerHelper()
	YYTPluginManage::getInstance()->getYYTServerHelper()->setUserAccount(szAccount);
	YYTPluginManage::getInstance()->getYYTServerHelper()->setUserPsword(szPsword);
	YYTPluginManage::getInstance()->getYYTServerHelper()->setRoomID(szRoomID);

	YYTPluginManage::getInstance()->getYYTServerHelper()->loginYYT();

	this->close();
	MainWindow::getInstance()->showMaximized();
}

void SettingDialog::OnBtnQuit()
{
}