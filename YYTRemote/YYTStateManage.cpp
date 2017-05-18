#include "YYTStateManage.h"
#include "YYTVideoShow.h"
#include <QIcon>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include "iLiveSDKWrap.h"
#include "LiveServerHelper.h"
#include <QDateTime>
#include "YYTPluginManage.h"


YYTStateManage::YYTStateManage(QWidget *parent)
	: QWidget(parent)
{
	initUI();
	initConnect();
}

YYTStateManage::~YYTStateManage()
{

//	delete LiveServerHelper::getInstance();
	qDebug(qPrintable("YYTStateManage"));
//YYTVideoShow::getInstance()->close();
// 	m_timer->stop();
// 	if (NULL != m_labUserName)
// 	{
// 		SafeDelete(m_labUserName);
// 	}
// 	if (NULL != m_labTime)
// 	{
// 		SafeDelete(m_labTime);
// 	}
// 	if (NULL != m_timer)
// 	{
// 		SafeDelete(m_timer);
// 	}	
}

void YYTStateManage::initUI()
{
// 	m_btnSpeaker = new QPushButton;
// 	m_btnSpeaker->setStyleSheet("background-image: url(:/YYT/skin/YYT/mic_check.png);");
// 	m_btnSpeaker->setFixedSize(23, 25);
// 
// 	m_btnVideo = new QPushButton;
// 	m_btnVideo->setFixedSize(99, 29);
// 	m_btnVideo->setStyleSheet("background-image: url(:/YYT/skin/YYT/btnST.png);");
// 
// 	m_btnVolume = new QPushButton;
// 	m_btnVolume->setStyleSheet("background-image: url(:/YYT/skin/YYT/speaker_check.png);");
// 	m_btnVolume->setFixedSize(23, 25);
// 
// 	m_btnScreenShare = new QPushButton;
// 	m_btnScreenShare->setFixedSize(99,29);
// 	m_btnScreenShare->setText(FromBits("开启屏幕分享"));
// 
// 
// 	QLabel* lab = new QLabel;
// 	lab->setFixedSize(82, 16);
// 	lab->setStyleSheet("background-image: url(:/YYT/skin/YYT/wlzl_6.png);");
// 
// 	QLabel* lab1 = new QLabel;
// 	lab1->setFixedSize(75, 16);
// 	lab1->setStyleSheet("background-image: url(:/YYT/skin/YYT/zysh_1.png);");
// 
// 	QSlider* slider = new QSlider;
// 	slider->setOrientation(Qt::Horizontal);
// 	slider->setFixedSize(75,29);
// 
// 
// 
// 
// 
// 	QHBoxLayout* m_vLayout = new QHBoxLayout;
// 	
// 
// 	m_vLayout->addWidget(lab1);
// 	m_vLayout->addWidget(m_btnSpeaker);
// 	m_vLayout->addSpacing(40);
// 
// 	
// 	m_vLayout->addWidget(slider);
//  	m_vLayout->addWidget(m_btnVolume);
// 	m_vLayout->addSpacing(40);
// 
// 
// 	m_vLayout->addWidget(m_btnVideo);
// 	m_vLayout->addSpacing(40);
// 
// 	m_vLayout->addWidget(m_btnScreenShare);
// 	m_vLayout->addSpacing(40);
// 
// 
// // 	m_vLayout->addWidget(m_btnSettings);
// 
// 	m_vLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding));
// 
// 	m_vLayout->addWidget(lab);
// 	m_vLayout->addSpacing(40);

	//this->setLayout(m_vLayout);

	m_labUserName = new QLabel(FromBits("当前用户: "));
	//m_labCompanyName = new QLabel(FromBits("北京东方瑞云科技有限公司"));
	m_labTime = new QLabel(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss"));

	QHBoxLayout* vLayout = new QHBoxLayout;
	vLayout->addWidget(m_labUserName);
	vLayout->addSpacing(40);

	vLayout->addWidget(m_labTime);
	vLayout->addSpacing(40);

	vLayout->addSpacerItem(new QSpacerItem(20, 100, QSizePolicy::Expanding, QSizePolicy::Expanding));

	//vLayout->addWidget(m_labCompanyName);
	vLayout->addSpacing(40);

	this->setLayout(vLayout);
	
	m_timer = new QTimer;
	m_timer->start(1000);

}

void YYTStateManage::initConnect()
{
// 	connect(m_btnSpeaker, SIGNAL(clicked()), this, SLOT(on_pushbtn_clicked()));
// 	connect(m_btnVideo, SIGNAL(clicked()), this, SLOT(on_pushbtn_clicked()));
// 	connect(m_btnVolume, SIGNAL(clicked()), this, SLOT(on_pushbtn_clicked()));
// 	connect(m_btnSettings, SIGNAL(clicked()), this, SLOT(on_pushbtn_clicked()));
// 	connect(m_btnScreenShare, SIGNAL(clicked()), this, SLOT(on_pushbtn_clicked()));

	connect(m_timer, SIGNAL(timeout()), this, SLOT(OnTimerOut()));
}

// YYTStateManage* YYTStateManage::getInstance()
// {
// 	static YYTStateManage instance;
//	return &instance;
// }

void YYTStateManage::showEvent(QShowEvent * event)
{

}

// void YYTStateManage::OnBtnSpeaker()
// {
// 
// 	//YYTVideoShow::getInstance()->o
// }
// 
// void YYTStateManage::OnBtnVideo()
// {
// 	if (iLiveSDKWrap::getInstance()->getCurCameraState())
// 	{
// 		YYTVideoShow::getInstance()->closeCamera();
// 		m_btnVideo->setStyleSheet("background-image: url(:/YYT/skin/YYT/btnST.png);");
// 	}
// 	else
// 	{
// 		YYTVideoShow::getInstance()->updateCameraList();
// 		YYTVideoShow::getInstance()->openCamera();
// 		m_btnVideo->setStyleSheet("background-image: url(:/YYT/skin/YYT/xiatai_1.png);");
// 	}
// 	
// 	
// }
// 
// void YYTStateManage::OnBtnVolume()
// {
// 
// }
// 
// void YYTStateManage::OnBtnScreenShare()
// {
// 	if (E_ScreenShareNone == iLiveSDKWrap::getInstance()->getScreenShareState())
// 	{
// 		if (LiveServerHelper::getInstance()->openScreenShareArea())
// 		{
// 			m_btnScreenShare->setText(FromBits("关闭屏幕分享"));
// 		}
// 	}
// 	else
// 	{
// 		if (LiveServerHelper::getInstance()->closeScreenShareArea())
// 		{
// 			m_btnScreenShare->setText(FromBits("开启屏幕分享"));
// 		}
// 		
// 	}
// }
// 
// void YYTStateManage::on_pushbtn_clicked()
// {
// 	QPushButton* pBtn = static_cast<QPushButton*>(sender());
// 	
// 	if (NULL != pBtn)
// 	{
// 		if (pBtn == m_btnSpeaker)
// 		{
// 			OnBtnSpeaker();
// 		}
// 		else if (pBtn == m_btnVideo)
// 		{
// 			OnBtnVideo();
// 		}
// 		else if (pBtn == m_btnVolume)
// 		{
// 			OnBtnVolume();
// 		}
// 		else if (pBtn == m_btnScreenShare)
// 		{
// 			OnBtnScreenShare();
// 		}
// 	}
// }

void YYTStateManage::OnTimerOut()
{
	m_labUserName->setText(FromBits("当前用户: ") + YYTPluginManage::getInstance()->getYYTServerHelper()->getUserName());
	m_labTime->setText(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss"));
	this->raise();
}
