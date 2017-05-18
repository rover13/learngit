#include "common/YYTCommon/common.h"
#include "ScreenShareDlg.h"
#include <QPushButton>
#include "LiveServerHelper.h"
#include "iLiveSDKWrap.h"
#include "YYTPluginManage.h"


ScreenShareDlg::ScreenShareDlg(QWidget *parent)
	: QWidget(parent)
{
	initUI();
	initConnect();
}

ScreenShareDlg::~ScreenShareDlg()
{
	qDebug(qPrintable("ScreenShareDlg"));
}

void ScreenShareDlg::initUI()
{
	m_pScreenShareRender = new VideoRender;
	//m_pScreenShareRender->setFixedSize();
	//m_gDlgLayout = new QVBoxLayout;
	//m_gDlgLayout->setSpacing(0);

	//m_gDlgLayout->addWidget(m_pScreenShareRender);
	
	m_NullDlg = new QWidget;
	//QLabel* lab = new QLabel();
	m_pBtnScreenShareControl = new QPushButton;
	m_pBtnScreenShareControl->setText(FromBits("申请屏幕分享控制权"));
	m_pBtnScreenShareControl->setFixedSize(150, 60);
	m_pBtnScreenShareControl->hide();

	m_pBtnOpenScreenShare = new QPushButton;
	m_pBtnOpenScreenShare->setText(FromBits("点击->开启屏幕共享"));
	m_pBtnOpenScreenShare->setFixedSize(150, 60);

	QHBoxLayout* vboxLay = new QHBoxLayout;
	vboxLay->addWidget(m_pBtnScreenShareControl);
	vboxLay->addWidget(m_pBtnOpenScreenShare);


// 	QGridLayout* layout1 = new QGridLayout;
// 	layout1->addWidget(m_pBtnOpenScreenShare);
	m_NullDlg->setLayout(vboxLay);

	m_gNullLayout = new QVBoxLayout;
	m_gNullLayout->addWidget(m_NullDlg);
	m_gNullLayout->setSpacing(0);

	//m_NullDlg->setFixedSize(m_NullDlg->geometry().width(),70);

	this->setLayout(m_gNullLayout);

	m_bShowState = false;
	m_bScreenShareState = false;
	m_ScreenShareUserID = "";

}

void ScreenShareDlg::initConnect()
{
	connect(m_pBtnOpenScreenShare, SIGNAL(clicked()), this, SLOT(OnBtnOpenScreenshare()));
	connect(m_pBtnScreenShareControl, SIGNAL(clicked()), this, SLOT(OnBtnScreenShareControl()));
}

VideoRender* ScreenShareDlg::getScreenShareRender()
{
	if (!m_bShowState)
	{
		m_bShowState = true;
		m_gNullLayout->addWidget(m_pScreenShareRender);
		//m_gNullLayout->removeWidget(m_NullDlg);
		m_NullDlg->setFixedSize(m_NullDlg->geometry().width(),70);
		//m_NullDlg->hide();

		m_pScreenShareRender->show();
	}

	return m_pScreenShareRender;
}

void ScreenShareDlg::closeScreenShareEvent()
{
	if (m_bShowState)
	{
		
		m_gNullLayout->removeWidget(m_pScreenShareRender);
		//m_NullDlg->setFixedSize(m_NullDlg->geometry().width(),70);
		m_gNullLayout->addWidget(m_NullDlg);
		m_NullDlg->show();
		m_pScreenShareRender->hide();
		m_bShowState = false;
	}
}

void ScreenShareDlg::setScreenShareID(QString id)
{
	m_ScreenShareUserID = id;
}

QString ScreenShareDlg::getScreenShareID()
{
	return m_ScreenShareUserID;
}

void ScreenShareDlg::setScreenShareState(bool state)
{
	m_bShowState = state;
}

bool ScreenShareDlg::getScreenShareState()
{
	return m_bScreenShareState;
}

void ScreenShareDlg::ApplyScreenShareContrl(QString strname)
{
	QString mes = strname + FromBits("请求分享屏幕控制权，是否同意?");
	QMessageBox::StandardButton ret = QMessageBox::question(this, FromBits("屏幕分享申请控制"), mes);
	if ( ret == QMessageBox::Yes )
	{
	 	//OnBtnCloseScreenShare();
	}
	else
	{
	 	//refuseInteract();
	}
}

void ScreenShareDlg::OnBtnOpenScreenshare()
{
	//LiveServerHelper::getInstance()->m_eLiveLoginState
	if (E_ScreenShareNone == iLiveSDKWrap::getInstance()->getScreenShareState())
	{
		if (YYTPluginManage::getInstance()->getLiveServerHelper()->openScreenShareArea())
		{
			m_pBtnOpenScreenShare->setText(FromBits("点击->关闭屏幕共享"));
			m_ScreenShareUserID = YYTPluginManage::getInstance()->getYYTServerHelper()->getUserId();
		}
		else
		{
			ShowErrorTips(FromBits("一个房间只能有一个屏幕共享"));
		}
	}
	else
	{
		if (YYTPluginManage::getInstance()->getLiveServerHelper()->closeScreenShareArea())
		{
			if (m_bShowState)
			{
				m_pScreenShareRender->hide();
				m_gNullLayout->removeWidget(m_pScreenShareRender);
				m_NullDlg->setFixedSize(m_NullDlg->geometry().width(),70);
				m_gNullLayout->addWidget(m_NullDlg);
				m_bShowState = false;
			}
			

			m_pBtnOpenScreenShare->setText(FromBits("点击->开启屏幕共享"));
			
			m_bShowState = false;
		}
	}
	
}

void ScreenShareDlg::OnBtnScreenShareControl()
{
	YYTPluginManage::getInstance()->getLiveServerHelper()->sendScreenShareControl();
}

void ScreenShareDlg::OnBtnFreeScreenShareControl()
{
	//OnBtnCloseScreenShare();
}

void ScreenShareDlg::showEvent(QShowEvent * event)
{

}
