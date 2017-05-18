#include "YYTVideoShow.h"
#include "iLiveSDKWrap.h"
#include "LiveServerHelper.h"
#include "YYTServerHelper.h"
#include "RoomManage.h"
#include "YYTPluginManage.h"

YYTVideoShow::YYTVideoShow(QWidget *parent)
	: QWidget(parent)
{
	initUI();
	initConnect();
	m_bIsLocalShow = false; 
	m_bIsScreenShareShow = false;
}

YYTVideoShow::~YYTVideoShow()
{
 	qDebug(qPrintable("YYTVideoShow"));
}

void YYTVideoShow::initUI()
{
	m_pLocalCameraRender = new VideoRender;
	m_pLocalCameraRender->setFixedSize(QSize(150,200));
	


	m_vLayout = new QVBoxLayout;
	m_vLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding));

	for(int i=0; i<MaxVideoRender; ++i)
	{
		m_arrRemoteIdentifiers.push_back("");
		m_pRemoteVideoRenders[i] = new VideoRender;
		m_pRemoteVideoRenders[i]->setFixedSize(QSize(150,200));
		m_bRemoteVideoRenderFrees[i] = true;
	}

	m_pRequestViewsTimer = new QTimer;

	m_wgtControl = new QWidget;
	m_wgtVideo	 = new QWidget;

	QVBoxLayout* vWgtlayout = new QVBoxLayout;
	vWgtlayout->addWidget(m_wgtControl, 1);
	vWgtlayout->addWidget(m_wgtVideo, 5);
	vWgtlayout->setSpacing(0);
	
	m_gBoxVideo = new QGroupBox;
	m_gBoxVideo->setLayout(m_vLayout);
	m_gBoxVideo->setFixedWidth(170);

	QGridLayout* wgtGLayout = new QGridLayout;
	wgtGLayout->addWidget(m_gBoxVideo);
	wgtGLayout->setSpacing(0);

	m_wgtVideo->setLayout(wgtGLayout);
	this->setLayout(vWgtlayout);


	m_btnSpeaker = new QPushButton;

	m_btnSpeaker->setStyleSheet("background: transparent");
	
	m_btnSpeaker->setIcon(QIcon(":/YYT/skin/YYT/QT/mic_shut2x.png"));
	m_btnSpeaker->setIconSize(QSize(48,48));
	m_btnSpeaker->setFixedSize(48, 48);

	m_btnVideo = new QPushButton;
	m_btnVideo->setIcon(QIcon(":/YYT/skin/YYT/QT/camera_off2x.png"));
	m_btnVideo->setIconSize(QSize(48,48));
	m_btnVideo->setFixedSize(48, 48);
	m_btnVideo->setStyleSheet("background: transparent");

	m_btnVolume = new QPushButton;
	m_btnVolume->setIcon(QIcon(":/YYT/skin/YYT/QT/speaker_disable2x.png"));
	m_btnVolume->setIconSize(QSize(48, 48));
	m_btnVolume->setFixedSize(48, 48);
	m_btnVolume->setStyleSheet("background: transparent");

	m_btnScreenShare = new QPushButton;
	m_btnScreenShare->setFixedSize(99,29);
	m_btnScreenShare->setText(FromBits("开启屏幕分享"));


// 	QLabel* lab = new QLabel;
// 	lab->setFixedSize(82, 16);
// 	lab->setStyleSheet("background-image: url(:/YYT/skin/YYT/wlzl_6.png);");

	m_sliderSpeaker = new QSlider;
	m_sliderSpeaker->setOrientation(Qt::Horizontal);
	m_sliderSpeaker->setFixedSize(75,29);
	m_sliderSpeaker->setEnabled(false);

	QLabel* labSpeaker = new QLabel;
	labSpeaker->setText(FromBits("播 放 器"));

	m_sliderMic = new QSlider;
	m_sliderMic->setOrientation(Qt::Horizontal);
	m_sliderMic->setFixedSize(75,29);
	m_sliderMic->setEnabled(false);
	
	QLabel* labMic = new QLabel;
	labMic->setText(FromBits("麦 克 风"));


	QHBoxLayout* vLayout1 = new QHBoxLayout;

	vLayout1->addWidget(m_sliderSpeaker);
	vLayout1->addWidget(labSpeaker);
	vLayout1->setSpacing(0);

	QHBoxLayout* vLayout2 = new QHBoxLayout;
	vLayout2->addWidget(m_sliderMic);
	vLayout2->addWidget(labMic);
	vLayout2->setSpacing(0);

	QHBoxLayout* vlayout3 = new QHBoxLayout;
	vlayout3->addWidget(m_btnVideo);
	vlayout3->addWidget(m_btnSpeaker);
	vlayout3->addWidget(m_btnVolume);

	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addLayout(vLayout1);
	vLayout->addLayout(vLayout2);
	vLayout->addLayout(vlayout3);
	vLayout->setSpacing(0);

	QGroupBox* pGBox = new QGroupBox;
	pGBox->setLayout(vLayout);

	QGridLayout* pGLayout = new QGridLayout;
	pGLayout->addWidget(pGBox);
	pGLayout->setSpacing(0);

	m_wgtControl->setLayout(pGLayout);

	m_bIsRequesting = false;
	m_upDateLater = new QTimer;
}

void YYTVideoShow::initConnect()
{
	connect(m_btnSpeaker, SIGNAL(clicked()), this, SLOT(on_pushbtn_clicked()));
	connect(m_btnVideo, SIGNAL(clicked()), this, SLOT(on_pushbtn_clicked()));
	connect(m_btnVolume, SIGNAL(clicked()), this, SLOT(on_pushbtn_clicked()));
	connect(m_btnScreenShare, SIGNAL(clicked()), this, SLOT(on_pushbtn_clicked()));
	connect( m_pRequestViewsTimer, SIGNAL(timeout()), this, SLOT(OnRequestViewsTimer()) );

	connect( m_sliderSpeaker, SIGNAL(valueChanged(int)), this, SLOT(on_SliderChanged(int)) );
	connect( m_sliderMic, SIGNAL(valueChanged(int)), this, SLOT(on_SliderChanged(int)) );

	connect(m_upDateLater, SIGNAL(timeout()), this, SLOT(OnUpdateLaterTimer()));
	
}

void YYTVideoShow::addVideoRender(VideoRender* video)
{
	if (video == m_pLocalCameraRender)
	{
		m_bIsLocalShow = true;
	}
// 	if (video == m_pScreenShareRender)
// 	{
// 		m_bIsScreenShareShow = true;
// 	}
	

	m_vLayout->insertWidget(0, video);
}

void YYTVideoShow::removeVideoRender(VideoRender* video)
{
	if (video == m_pLocalCameraRender)
	{
		m_bIsLocalShow = false;
	}
// 	if (video == m_pScreenShareRender)
// 	{
// 		m_bIsScreenShareShow = false;
// 	}
	m_vLayout->removeWidget(video);
}

void YYTVideoShow::addRoomMember(QString szUserID, bool bIsVideo, VideoRender* video)
{
	QMap<QString, RoomMember> mapRoomMem = YYTPluginManage::getInstance()->getRoomManage()->getRoomMember();
	RoomMember roomMem = mapRoomMem[szUserID];
	QString szMemberName = roomMem.szName;
	
	m_mapRoomMemInfo[szMemberName] = szUserID;

	if (szMemberName.isEmpty())
	{
		return;
	}

	QVBoxLayout* vBoxlayout = NULL;

	if (m_mapRoomMemberLyout.contains(szMemberName))
	{
		vBoxlayout = m_mapRoomMemberLyout[szMemberName];
	}
	else
	{
		vBoxlayout = new QVBoxLayout;
		YYTRoomMemerDlg* stRoomMember = new YYTRoomMemerDlg(szMemberName, true, true, this);
		vBoxlayout->addWidget(stRoomMember);
		m_mapRoomMemberDlg[szMemberName] = stRoomMember;
		//SetVideoState(szMemberName,true);
	}

	if (bIsVideo)
	{
		if (NULL != video)
		{
			if (video == m_pLocalCameraRender)
			{
				m_bIsLocalShow = true;
			}
// 			if (video == m_pScreenShareRender)
// 			{
// 				m_bIsScreenShareShow = true;
// 			}

			vBoxlayout->addWidget(video);
			video->show();
			//m_mapRoomMemVideo[szUserID] = video;
		}
	}

	if (!m_mapRoomMemberLyout.contains(szMemberName))
	{
		m_vLayout->insertLayout(m_vLayout->count()-1, vBoxlayout);
	}

	m_mapRoomMemberLyout[szMemberName] = vBoxlayout;
	
}

void YYTVideoShow::removeRoomMember(QString szUserID, bool bIsVideo, VideoRender* video)
{
	QMap<QString, RoomMember> mapRoomMem = YYTPluginManage::getInstance()->getRoomManage()->getRoomMember();
	QStringList str1 = mapRoomMem.keys();

	RoomMember roomMem = mapRoomMem[szUserID];
	QString szMemberName = roomMem.szName;

	if (szMemberName.isEmpty()/* | NULL == video*/)
	{
		return;
	}

	QVBoxLayout* vBoxlayout = m_mapRoomMemberLyout[szMemberName];
	if (NULL == vBoxlayout)
	{
		return;
	}

	if (bIsVideo)
	{
		vBoxlayout->removeWidget(video);
		video->hide();
	}

	
	YYTRoomMemerDlg* stRoomMe = m_mapRoomMemberDlg[szMemberName];
	if (NULL == stRoomMe)
	{
		return;
	}
	vBoxlayout->removeWidget(stRoomMe);

	m_mapRoomMemberLyout.remove(szMemberName);
	m_mapRoomMemberDlg.remove(szMemberName);
//	SetVideoState(szMemberName,false);

	delete stRoomMe;
	stRoomMe = NULL;

	delete vBoxlayout;

	vBoxlayout = NULL;

	if (video == m_pLocalCameraRender)
	{
		m_bIsLocalShow = false;
	}
// 	if (video == m_pScreenShareRender)
// 	{
// 		m_bIsScreenShareShow = false;
// 	}

	
// 	this->raise();
// 	this->update();
	
}

void YYTVideoShow::addRequestViews(const std::vector<std::string>& identifiers, const std::vector<View>& views)
{
	assert(identifiers.size() == views.size());
	for (int i=0; i<identifiers.size(); ++i)
	{
		m_toRequestIdentifiers.push_back(identifiers[i]);
		m_toRequestViews.push_back(views[i]);
	}
	if ( !m_pRequestViewsTimer->isActive() )
	{
		m_pRequestViewsTimer->start(0);
	}
}

void YYTVideoShow::updateCameraList()
{
	iLiveSDKWrap::getInstance()->getCameraList(m_cameraList);
}

VideoRender* YYTVideoShow::getVideoRender(std::string szIdentifier)
{
	for(int i=0; i<MaxVideoRender; ++i)
	{
	 	if (m_arrRemoteIdentifiers[i]==szIdentifier)
	 	{
			
			QMap<QString, RoomMember> mapRoomMem = YYTPluginManage::getInstance()->getRoomManage()->getRoomMember();
			RoomMember roomMem = mapRoomMem[QString::fromStdString(szIdentifier)];
			QStringList strlist = m_mapRoomMemVideoState.keys();
			if (!m_mapRoomMemberLyout.contains(roomMem.szName))
			{
				m_mapRoomMemVideoState[QString::fromStdString(szIdentifier)] = true;
				addRoomMember(QString::fromStdString(szIdentifier), true, m_pRemoteVideoRenders[i]);
				SetVideoState(QString::fromStdString(szIdentifier), true, m_pRemoteVideoRenders[i]);
				//SetVideoState(QString::fromStdString(szIdentifier), true, m_pRemoteVideoRenders[i]);
			}
			if (!m_mapRoomMemVideoState[QString::fromStdString(szIdentifier)])
			{
				m_mapRoomMemVideoState[QString::fromStdString(szIdentifier)] = true;
				SetVideoState(QString::fromStdString(szIdentifier), true, m_pRemoteVideoRenders[i]);
			}
			
		
	 		return m_pRemoteVideoRenders[i];
	 	}
	}
	for(int i=0; i<MaxVideoRender; ++i)
	{
	 	if (m_bRemoteVideoRenderFrees[i])
	 	{
	 		m_bRemoteVideoRenderFrees[i] = false;
	 		m_arrRemoteIdentifiers[i] = szIdentifier;
			
			//addVideoRender(m_pRemoteVideoRenders[i]);
			QMap<QString, RoomMember> mapRoomMem = YYTPluginManage::getInstance()->getRoomManage()->getRoomMember();
			RoomMember roomMem = mapRoomMem[QString::fromStdString(szIdentifier)];
			m_mapRoomMemVideoState[QString::fromStdString(szIdentifier)] = true;
			addRoomMember(QString::fromStdString(szIdentifier), true, m_pRemoteVideoRenders[i]);
			SetVideoState(QString::fromStdString(szIdentifier), true, m_pRemoteVideoRenders[i]);
			//SetVideoState(QString::fromStdString(szIdentifier), true, m_pRemoteVideoRenders[i]);
			

	 		return m_pRemoteVideoRenders[i];
	 	}

	}
	return NULL;
}

VideoRender* YYTVideoShow::getLocalRender()
{
	if (!m_bIsLocalShow)
	{
		//addVideoRender(m_pLocalCameraRender);
		addRoomMember(YYTPluginManage::getInstance()->getYYTServerHelper()->getUserId(), true, m_pLocalCameraRender);
		m_mapRoomMemVideoState[YYTPluginManage::getInstance()->getYYTServerHelper()->getUserId()] = true;
		//SetVideoState(YYTPluginManage::getInstance()->getYYTServerHelper()->getUserId(), true, m_pLocalCameraRender);
	}

	return m_pLocalCameraRender;
}

VideoRender* YYTVideoShow::getScreenShareRender()
{
// 	if (!m_bIsScreenShareShow)
// 	{
// 		addVideoRender(m_pScreenShareRender);
// 	}
// 
 	return NULL;
}

void YYTVideoShow::freeCameraVideoRenders(std::vector<std::string> arrNeedFreeRenders)
{
	for (size_t i=0; i<arrNeedFreeRenders.size(); ++i)
	{
		for (size_t j = 0; j<m_arrRemoteIdentifiers.size(); ++j)
		{
			std::string str1 = m_arrRemoteIdentifiers[j];
			std::string str2 = arrNeedFreeRenders[i];
			if (str1 == str2)
			{
				QMap<QString, RoomMember> mapRoomMem = YYTPluginManage::getInstance()->getRoomManage()->getRoomMember();
				RoomMember roomMem = mapRoomMem[QString::fromStdString(str1)];
				//removeRoomMember(roomMem.szName, true, m_pRemoteVideoRenders[j]);
				

				m_arrRemoteIdentifiers[j] = "";
				m_bRemoteVideoRenderFrees[j] = true;
				//m_pRemoteVideoRenders[j]->update();
				
				//Sleep(2000);
				//SetVideoState(QString::fromStdString(str1), false, m_pRemoteVideoRenders[j]);
				//m_upDateLaterUserID = QString::fromStdString(str1);
				//m_upDateLaterVideo = m_pRemoteVideoRenders[j];
				m_mapRoomMemVideoState[QString::fromStdString(str1)] = false;

				m_upDateMap[QString::fromStdString(str1)] = m_pRemoteVideoRenders[j];
				m_upDateLater->start(500);
				//removeVideoRender(m_pRemoteVideoRenders[i]);
				//removeRoomMember()
			}
		}
	}
	//updateLater();
	
}

void YYTVideoShow::freeAllCameraVideoRender()
{
// 	m_pLocalCameraRender->exitFullScreen();
// 	m_pLocalCameraRender->recoverRender();
	m_pLocalCameraRender->hide();
	for (int i=0; i<MaxVideoRender; ++i)
	{

		//m_pRemoteVideoRenders[i]->exitFullScreen();
		//m_pRemoteVideoRenders[i]->recoverRender();
		m_pRemoteVideoRenders[i]->hide();
		m_arrRemoteIdentifiers[i] = "";
		m_bRemoteVideoRenderFrees[i] = true;

	}
}

void YYTVideoShow::freeScreenVideoRender()
{
	m_pScreenShareRender->update();
	//updateLater();
}

void YYTVideoShow::OnRequestViewListSuc(void* data)
{
	YYTVideoShow* pYYTVideoShow = reinterpret_cast<YYTVideoShow*>(data);

	if ( pYYTVideoShow->m_toRequestIdentifiers.empty() )
	{
		pYYTVideoShow->m_pRequestViewsTimer->stop();
	}

	pYYTVideoShow->m_bIsRequesting = false;
}

void YYTVideoShow::OnRequestViewListErr(int code, const std::string& desc, void* data)
{
	YYTVideoShow* pYYTVideoShow = reinterpret_cast<YYTVideoShow*>(data);
	pYYTVideoShow->m_bIsRequesting = false;
	pYYTVideoShow->m_pRequestViewsTimer->stop();
}

bool YYTVideoShow::openCamera()
{
	if (iLiveSDKWrap::getInstance()->getCurCameraState())
	{
		//closeCamera();
	}
	else
	{
		if (m_cameraList.size()==0)
		{
			ShowErrorTips( FromBits("没有摄像头可用"), this );
			return false;
		}
	
		int ndx = 0;
		int nRet = iLiveSDKWrap::getInstance()->openCamera(m_cameraList[ndx].first);
		if (nRet==NO_ERR)
		{
			m_mapRoomMemberLyout[YYTPluginManage::getInstance()->getYYTServerHelper()->getUserName()]->addWidget(m_pLocalCameraRender);
			m_pLocalCameraRender->show();

			SetVideoState(YYTPluginManage::getInstance()->getYYTServerHelper()->getUserId(), true, m_pLocalCameraRender);
			m_btnVideo->setIcon(QIcon(":/YYT/skin/YYT/QT/camera_on2x.png"));
			m_btnVideo->setIconSize(QSize(64,64));
			//updatePushAndRecordStateUI();
			return true;
		}
		else
		{
			ShowCodeErrorTips( nRet, FromBits("打开摄像头失败"), this );
			return false;
		}
	}
}

bool YYTVideoShow::closeCamera()
{
	int nRet = iLiveSDKWrap::getInstance()->closeCamera();
	if (nRet==0)
	{
		m_btnVideo->setIcon(QIcon(":/YYT/skin/YYT/QT/camera_off2x.png"));
		m_btnVideo->setIconSize(QSize(64,64));

		//removeRoomMember(YYTPluginManage::getInstance()->getYYTServerHelper()->getUserName(), true, m_pLocalCameraRender);
		m_pLocalCameraRender->hide();
		SetVideoState(YYTPluginManage::getInstance()->getYYTServerHelper()->getUserId(), false, m_pLocalCameraRender);
		return true;
	}
	else
	{
		
		//		m_ui.btnCloseCamera->setEnabled(true);
		ShowErrorTips( FromBits("关闭摄像头失败"), this );
		return false;
	}
}

void YYTVideoShow::OnBtnSpeaker()
{
	if (YYTPluginManage::getInstance()->getLiveServerHelper()->getLiveLoginState() != E_LiveInRoom)
	{
		ShowErrorTips(FromBits("还未加入会议，请加入会议"));
		return ;
	}

	if (iLiveSDKWrap::getInstance()->getCurMicState())
	{
		if (YYTPluginManage::getInstance()->getLiveServerHelper()->closeMic())
		{
			//m_btnSpeaker->setStyleSheet("border-image: url(:/YYT/skin/YYT/mic_check.png)0 44 0 66;");
			m_btnSpeaker->setIcon(QIcon(":/YYT/skin/YYT/QT/mic_shut2x.png"));
			m_btnSpeaker->setIconSize(QSize(48,48));
			m_sliderSpeaker->setEnabled(false);
		}
		else
		{
			ShowErrorTips( FromBits("关闭麦克风失败"), this );
		}
	}
	else
	{
		if (YYTPluginManage::getInstance()->getLiveServerHelper()->openMic())
		{
			//m_btnSpeaker->setStyleSheet("border-image: url(:/YYT/skin/YYT/mic_check.png)0 110 0 0;");
			m_btnSpeaker->setIcon(QIcon(":/YYT/skin/YYT/QT/mic2x.png"));
			m_btnSpeaker->setIconSize(QSize(48,48));
			m_sliderSpeaker->setEnabled(true);
		}
		else
		{
			ShowErrorTips( FromBits("打开麦克风失败"), this );
		}
	}
	
	
}

void YYTVideoShow::OnBtnVideo()
{
	if (YYTPluginManage::getInstance()->getLiveServerHelper()->getLiveLoginState() != E_LiveInRoom)
	{
		ShowErrorTips(FromBits("还未加入会议，请加入会议"));
		return ;
	}

	if (iLiveSDKWrap::getInstance()->getCurCameraState())
	{
		if (closeCamera())
		{
			
			//m_btnVideo->setIconSize(QSize(64,64));
			//m_btnVideo->setFixedSize(100, 60);
		}		
	}
	else
	{
		updateCameraList();
		if (openCamera())
		{
			
			//m_btnVideo->setIconSize(QSize(64,64));
			//m_btnVideo->setFixedSize(100, 60);
		}
		
	}
}

void YYTVideoShow::OnBtnVolume()
{
	if (iLiveSDKWrap::getInstance()->getCurPlayerState())
	{
		if (YYTPluginManage::getInstance()->getLiveServerHelper()->closePlayer())
		{
			m_btnVolume->setIcon(QIcon(":/YYT/skin/YYT/QT/speaker_disable2x.png"));
			m_btnVolume->setIconSize(QSize(48, 48));

			m_sliderMic->setEnabled(false);
		}
		else
		{
			ShowErrorTips( FromBits("关闭播放器失败"), this );
		}
	}
	else
	{
		if (YYTPluginManage::getInstance()->getLiveServerHelper()->openPlayer())
		{
			m_btnVolume->setIcon(QIcon(":/YYT/skin/YYT/QT/speaker_enable2x.png"));
			m_btnVolume->setIconSize(QSize(48, 48));
			m_sliderMic->setEnabled(true);
		}
		else
		{
			ShowErrorTips( FromBits("打开播放器失败"), this );
		}
	}
	
}

void YYTVideoShow::OnBtnScreenShare()
{
	if (E_ScreenShareNone == iLiveSDKWrap::getInstance()->getScreenShareState())
	{
		if (YYTPluginManage::getInstance()->getLiveServerHelper()->openScreenShareArea())
		{
			m_btnScreenShare->setText(FromBits("关闭屏幕分享"));
		}
	}
	else
	{
		if (YYTPluginManage::getInstance()->getLiveServerHelper()->closeScreenShareArea())
		{
			m_btnScreenShare->setText(FromBits("开启屏幕分享"));
		}

	}
}

void YYTVideoShow::SetSliderSpeaker(uint32 value)
{
	iLiveSDKWrap::getInstance()->setPlayerVolume(value);
}

void YYTVideoShow::SetSliderMic(uint32 value)
{
	iLiveSDKWrap::getInstance()->setMicVolume(value);
}

void YYTVideoShow::setMicState(QString stUserID, bool bState)
{
	QMap<QString, RoomMember> mapRoomMem = YYTPluginManage::getInstance()->getRoomManage()->getRoomMember();
	RoomMember roomMem = mapRoomMem[stUserID];

	if (m_mapRoomMemberDlg.contains(roomMem.szName))
	{
		m_mapRoomMemberDlg[roomMem.szName]->setMicState(bState);
	}
	
}

void YYTVideoShow::SetVideoState(QString stUserID, bool bState, VideoRender* video)
{
	QMap<QString, RoomMember> mapRoomMem = YYTPluginManage::getInstance()->getRoomManage()->getRoomMember();
	RoomMember roomMem = mapRoomMem[stUserID];

	if (m_mapRoomMemberDlg.contains(roomMem.szName))
	{
		m_mapRoomMemberDlg[roomMem.szName]->setVideoState(bState);

		if (bState)
		{
// 			bool state = m_mapRoomMemVideoState[stUserID];
// 			if (state)
// 			{
				video->show();
//			}
			
		}
		else
		{
			video->hide();
			//m_mapRoomMemVideoState[stUserID] = false;
		}
	}
	
}

void YYTVideoShow::QuitRoomClear()
{

	QStringList strUserNamelist = m_mapRoomMemberDlg.keys();

	foreach(auto strUserName, strUserNamelist)
	{
		QString strUserID = m_mapRoomMemInfo[strUserName];
		removeRoomMember(strUserID, false, nullptr);
	}


	auto itState = m_mapRoomMemVideoState.begin();
	for (itState; itState != m_mapRoomMemVideoState.end(); itState++)
	{
		
	}

	m_mapRoomMemVideoState.clear();
	m_mapRoomMemberDlg.clear();

	m_btnVideo->setIcon(QIcon(":/YYT/skin/YYT/QT/camera_off2x.png"));
	m_btnVideo->setIconSize(QSize(48,48));

	freeAllCameraVideoRender();
	
}

bool YYTVideoShow::getVideoRenderState(QString strUserID)
{
	return m_mapRoomMemVideoState[strUserID];
}

void YYTVideoShow::on_pushbtn_clicked()
{
	QPushButton* pBtn = static_cast<QPushButton*>(sender());

	if (NULL != pBtn)
	{
		if (pBtn == m_btnSpeaker)
		{
			OnBtnSpeaker();
		}
		else if (pBtn == m_btnVideo)
		{
			OnBtnVideo();
		}
		else if (pBtn == m_btnVolume)
		{
			OnBtnVolume();
		}
		else if (pBtn == m_btnScreenShare)
		{
			OnBtnScreenShare();
		}
	}
}


void YYTVideoShow::OnRequestViewsTimer()
{
	if (m_bIsRequesting)
	{
		return;
	}
	m_bIsRequesting = true;
	iLiveSDKWrap::getInstance()->requestViewList(m_toRequestIdentifiers, m_toRequestViews, OnRequestViewListSuc, OnRequestViewListErr, this);
	m_toRequestIdentifiers.clear();
	m_toRequestViews.clear();
}

void YYTVideoShow::on_SliderChanged(int iValue)
{
	QSlider* pSlider = static_cast<QSlider*>(sender());

	if (NULL != pSlider)
	{
		if (pSlider == m_sliderSpeaker)
		{
			SetSliderSpeaker(iValue);
		}
		else if (m_sliderMic == m_sliderSpeaker)
		{
			SetSliderMic(iValue);
		}
	}
	
}

void YYTVideoShow::OnUpdateLaterTimer()
{
	m_upDateLater->stop();
	if (m_upDateMap.isEmpty())
	{
		return;
	}

	SetVideoState(m_upDateMap.begin().key(), false, m_upDateMap.begin().value());
	m_mapRoomMemVideoState[m_upDateMap.begin().key()] = false;
	m_upDateMap.clear();
}

void YYTVideoShow::showEvent(QShowEvent * event)
{

}
