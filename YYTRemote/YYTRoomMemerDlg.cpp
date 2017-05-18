#include "YYTRoomMemerDlg.h"

// YYTRoomMemerDlg::YYTRoomMemerDlg(QWidget *parent)
// 	: QWidget(parent)
// {
// 	QString strName = "123";
// 	m_labName = new QLabel(strName);
// 
// 	m_labVideo = new QLabel;
// 	m_labVideo->setStyleSheet("background-image: url(:/YYT/skin/YYT/mic_check.png);");
// 	m_labVideo->setFixedSize(23, 25);
// 
// 	m_labMic = new QLabel;
// 	m_labMic->setStyleSheet("background-image: url(:/YYT/skin/YYT/mic_check.png);");
// 	m_labMic->setFixedSize(23, 25);
// 
// 	m_hLayout = new QHBoxLayout;
// 	m_hLayout->addWidget(m_labName);
// 	m_hLayout->addWidget(m_labVideo);
// 	m_hLayout->addWidget(m_labMic);
// 	m_hLayout->setSpacing(0);
// 	this->setLayout(m_hLayout);
// }

YYTRoomMemerDlg::YYTRoomMemerDlg(QString strName, bool bMicState, bool bSpeakerState, QWidget* parent /*= NULL*/)
	:QWidget(parent)
{
	m_labName = new QLabel(strName);

	m_labVideo = new QPushButton;
	m_labVideo->setIcon(QIcon(":/YYT/skin/YYT/closeCame.png"));
	m_labVideo->setIconSize(QSize(24,24));
	m_labVideo->setFixedSize(24, 24);
	m_labVideo->setStyleSheet("background: transparent");

	m_labMic = new QPushButton;
	m_labMic->setIcon(QIcon(":/YYT/skin/YYT/closeSpeaker.png"));
	m_labMic->setIconSize(QSize(24,24));
	m_labMic->setFixedSize(24, 24);
	m_labMic->setStyleSheet("background: transparent");

	m_hLayout = new QHBoxLayout;
	m_hLayout->addWidget(m_labName);
	m_hLayout->addWidget(m_labVideo);
	m_hLayout->addWidget(m_labMic);
	//m_hLayout->setSpacing();

	this->setLayout(m_hLayout);
}

YYTRoomMemerDlg::~YYTRoomMemerDlg()
{
	qDebug(qPrintable("YYTRoomMemerDlg"));
	if (NULL != m_labName)
	{
		delete m_labName;
		m_labName = NULL;
	}

	if (NULL != m_labVideo)
	{
		delete m_labVideo;
		m_labVideo = NULL;
	}

	if (NULL != m_labMic)
	{
		delete m_labMic;
		m_labMic = NULL;
	}

	if (NULL != m_hLayout)
	{
		delete m_hLayout;
		m_hLayout = NULL;
	}
}

void YYTRoomMemerDlg::setMicState(bool bState)
{
	if (nullptr == m_labMic)
	{
		return;
	}

	if (bState)
	{
		m_labMic->setIcon(QIcon(":/YYT/skin/YYT/openSpeaker.png"));
	}
	else
	{
		m_labMic->setIcon(QIcon(":/YYT/skin/YYT/closeSpeaker.png"));
	}

	m_labMic->setIconSize(QSize(24,24));
	m_labMic->setFixedSize(24, 24);
}

void YYTRoomMemerDlg::setVideoState(bool bState)
{
	if (nullptr == m_labVideo)
	{
		return;
	}

	if (bState)
	{
		m_labVideo->setIcon(QIcon(":/YYT/skin/YYT/openCame.png"));

	}
	else
	{
		m_labVideo->setIcon(QIcon(":/YYT/skin/YYT/closeCame.png"));
	}

	m_labVideo->setIconSize(QSize(24,24));
	m_labVideo->setFixedSize(24, 24);
}
