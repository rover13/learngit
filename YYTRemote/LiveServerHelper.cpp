#include "common/YYTCommon/common.h"
#include "LiveServerHelper.h"
#include "iLiveSDKWrap.h"
#include "YYTServerHelper.h"
#include <QRegExp>
#include "Event.h"
#include "YYTVideoShow.h"
#include "MessageCallBack.h"
#include "YYTPluginManage.h"
/*#include "ConsultationApplyDlg.h"*/



LiveServerHelper::LiveServerHelper(QObject *parent)
	: QObject(parent)
{
	m_eLiveLoginState = E_LiveInvalidState;
	m_x0 = 0;
	m_y0 = 0;
	m_fps = 10;
	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect screenRect = desktopWidget->screenGeometry();
	m_x1 = screenRect.width();
	m_y1 = screenRect.height();


	initSDK();
}

LiveServerHelper::~LiveServerHelper()
{
	//exit(0);
	qDebug() << "~LiveServerHelper()";
}

void LiveServerHelper::onForceOffline()
{

}

void LiveServerHelper::initSDK()
{
	iLiveSDKWrap::getInstance()->setGroupMessageCallBack(MessageCallBack::OnGropuMessage);
	iLiveSDKWrap::getInstance()->setC2CMessageCallBack(MessageCallBack::OnC2CMessage);
	iLiveSDKWrap::getInstance()->setForceOfflineCallback(onForceOffline);
	iLiveSDKWrap::getInstance()->setLocalVideoCallBack(LiveServerHelper::OnLocalVideo, NULL);
	iLiveSDKWrap::getInstance()->setRemoteVideoCallBack(LiveServerHelper::OnRemoteVideo, NULL);

	int nRet = iLiveSDKWrap::getInstance()->initSdk(YYTPluginManage::getInstance()->getYYTServerHelper()->getAppID(), YYTPluginManage::getInstance()->getYYTServerHelper()->getAppAccountTyep());
	if (nRet != ilivesdk::NO_ERR)
	{
//		ShowErrorTips( "init sdk failed.",this );
		exit(0);
	}
}

// LiveServerHelper* LiveServerHelper::getInstance()
// {
// 	static LiveServerHelper instance;
//	return &instance;
// }

void LiveServerHelper::iLiveLogin()
{
	iLiveSDKWrap::getInstance()->LiveLogin(YYTPluginManage::getInstance()->getYYTServerHelper()->getUserId().toStdString(), 
										YYTPluginManage::getInstance()->getYYTServerHelper()->getUserSig().toStdString(), 
										OniLiveLoginSuccess, 
										OniLiveLoginError, this);
}

void LiveServerHelper::iLiveLogout()
{
	iLiveSDKWrap::getInstance()->LiveLogout(OniLiveLogoutSuccess, OniLiveLogoutError, this);
}

void LiveServerHelper::iLiveCreateRoom()
{
	ilivesdk::iLiveRoomOption roomOption;
	QString str = YYTPluginManage::getInstance()->getYYTServerHelper()->getRoomID().remove(QRegExp("[a-zA-Z]"));
	roomOption.roomId = str.toUInt();
	roomOption.auth_buffer = "";
	roomOption.control_role = LiveMaster;
	roomOption.audio_category = AUDIO_CATEGORY_MEDIA_PLAY_AND_RECORD;//互动直播场景
	roomOption.video_recv_mode = VIDEO_RECV_MODE_SEMI_AUTO_RECV_CAMERA_VIDEO; //半自动模式
	roomOption.screen_recv_mode = SCREEN_RECV_MODE_SEMI_AUTO_RECV_SCREEN_VIDEO;//半自动模式
	roomOption.m_roomDisconnectListener = OnRoomDisconnect;
	roomOption.m_memberStatusListener = OnMemStatusChange;
	roomOption.m_autoRecvCameraListener = OnSemiAutoRecvCameraVideo;
	roomOption.m_autoRecvScreenListener = OnSemiAutoRecvScreenVideo;
	roomOption.m_autoRecvMediaFileListener = OnSemiAutoRecvMediaFileVideo;
	roomOption.data = this;
	iLiveSDKWrap::getInstance()->createRoom( roomOption, OniLiveCreateRoomSuc, OniLiveCreateRoomErr, this);
}

void LiveServerHelper::iLiveJoinRoom()
{
	ilivesdk::iLiveRoomOption roomOption;
	QString str = YYTPluginManage::getInstance()->getYYTServerHelper()->getRoomID().remove(QRegExp("[a-zA-Z]"));
	roomOption.roomId = str.toUInt();
	roomOption.audio_category = AUDIO_CATEGORY_MEDIA_PLAY_AND_RECORD;//直播场景
	roomOption.auth_buffer = "";
	roomOption.control_role = LiveMaster;
	roomOption.video_recv_mode = VIDEO_RECV_MODE_SEMI_AUTO_RECV_CAMERA_VIDEO; //半自动模式
	roomOption.screen_recv_mode = SCREEN_RECV_MODE_SEMI_AUTO_RECV_SCREEN_VIDEO; //半自动模式
	roomOption.m_autoRecvCameraListener = OnSemiAutoRecvCameraVideo;
	roomOption.m_autoRecvScreenListener = OnSemiAutoRecvScreenVideo;
	roomOption.m_autoRecvMediaFileListener = OnSemiAutoRecvMediaFileVideo;
	roomOption.m_memberStatusListener = OnMemStatusChange;
	roomOption.m_roomDisconnectListener = OnRoomDisconnect;
	roomOption.data = this;
	iLiveSDKWrap::getInstance()->joinRoom( roomOption, OniLiveJoinRoomSuc, OniLiveJoinRoomErr, this );
}

void LiveServerHelper::iLiveChangeAuthority(uint64 authBits, const std::string& authBuffer)
{
	iLiveSDKWrap::getInstance()->changeAuthority(authBits, authBuffer, OnChangeAuthoritySuc, OnChangeAuthorityErr, this);
}

void LiveServerHelper::iLiveQuitRoom()
{
	iLiveSDKWrap::getInstance()->quitRoom(OnQuitRoomSuccess, OnQuitRoomError, this);
}

void LiveServerHelper::OniLiveLoginSuccess(void* data)
{
	LiveServerHelper* pLiveServerHelper = reinterpret_cast<LiveServerHelper*>(data);
	postCusEvent( pLiveServerHelper, new Event(E_CELogin, 0, "") );
}

void LiveServerHelper::OniLiveLoginError(int code, const std::string& desc, void* data)
{
	LiveServerHelper* pLiveServerHelper = reinterpret_cast<LiveServerHelper*>(data);
	postCusEvent( pLiveServerHelper, new Event(E_CELogin, code, desc) );
}

void LiveServerHelper::OniLiveLogoutSuccess(void* data)
{
	LiveServerHelper* pLiveServerHelper = reinterpret_cast<LiveServerHelper*>(data);
	postCusEvent( pLiveServerHelper, new Event(E_CELogout, 0, "") );
}

void LiveServerHelper::OniLiveLogoutError(int code, const std::string& desc, void* data)
{
	LiveServerHelper* pLiveServerHelper = reinterpret_cast<LiveServerHelper*>(data);
	postCusEvent( pLiveServerHelper, new Event(E_CELogout, code, desc) );
}

void LiveServerHelper::OniLiveCreateRoomSuc(void* data)
{
	LiveServerHelper* pLiveServerHelper = reinterpret_cast<LiveServerHelper*>(data);
	postCusEvent( pLiveServerHelper, new Event(E_CECreateRoom, 0, "") );
}

void LiveServerHelper::OniLiveCreateRoomErr(int code, const std::string& desc, void* data)
{
	LiveServerHelper* pLiveServerHelper = reinterpret_cast<LiveServerHelper*>(data);
	postCusEvent( pLiveServerHelper, new Event(E_CECreateRoom, code, desc) );
}

void LiveServerHelper::OniLiveJoinRoomSuc(void* data)
{
	LiveServerHelper* pLiveServerHelper = reinterpret_cast<LiveServerHelper*>(data);
	//LiveServerHelper::getInstance()->iLiveChangeAuthority(AUTH_BITS_DEFAULT, "");
	YYTPluginManage::getInstance()->getLiveServerHelper()->iLiveChangeAuthority(AUTH_BITS_DEFAULT, "");
// 	RoomListItem* pRoomListItem = reinterpret_cast<RoomListItem*>(data);
// 	pRoomListItem->m_room.info.groupid = 40;
// 	g_pMainWindow->setCurRoomIdfo(pRoomListItem->m_room);
 	postCusEvent( pLiveServerHelper, new Event(E_CEJoinRoom, 0, "") );
	int i = 0;
	sendGroupCustomCmd( AVIMCMD_EnterLive, YYTPluginManage::getInstance()->getYYTServerHelper()->getUserId() );

}

void LiveServerHelper::OniLiveJoinRoomErr(int code, const std::string& desc, void* data)
{
	LiveServerHelper* pLiveServerHelper = reinterpret_cast<LiveServerHelper*>(data);
	postCusEvent( pLiveServerHelper, new Event(E_CEJoinRoom, code, desc) );
	int i = 0;
}

void LiveServerHelper::OnChangeAuthoritySuc(void* data)
{
	int i = 0;
}

void LiveServerHelper::OnChangeAuthorityErr(int code, const std::string& desc, void* data)
{
	iLiveSDKWrap::getInstance()->destroy();
	int i = 0;
}

void LiveServerHelper::OnQuitRoomSuccess(void* data)
{
	LiveServerHelper* pLiveServerHelper = reinterpret_cast<LiveServerHelper*>(data);
	postCusEvent( pLiveServerHelper, new Event(E_CEQuitRoom, 0, "") );
	int i = 0;
}

void LiveServerHelper::OnQuitRoomError(int code, const std::string& desc, void* data)
{
	LiveServerHelper* pLiveServerHelper = reinterpret_cast<LiveServerHelper*>(data);
	postCusEvent( pLiveServerHelper, new Event(E_CEQuitRoom, code, desc) );
	int i = 0;
}

void LiveServerHelper::OnMemStatusChange(AVRoomMulti::EndpointEventId event_id, std::vector<std::string> identifier_list, void* data)
{
	LiveServerHelper* pLive = reinterpret_cast<LiveServerHelper*>(data);
	switch(event_id)
	{
	case AVRoomMulti::EVENT_ID_ENDPOINT_ENTER: //! 进入房间
		{
			for (std::vector<std::string>::iterator it = identifier_list.begin(); it != identifier_list.end(); it++)
			{
				YYTPluginManage::getInstance()->getYYTServerHelper()->getMemUserInfo(it->data());
				
				
			}

			break;
		}
	case AVRoomMulti::EVENT_ID_ENDPOINT_EXIT: //! 离开房间
		{
			for (std::vector<std::string>::iterator it = identifier_list.begin(); it != identifier_list.end(); it++)
			{
				YYTPluginManage::getInstance()->getYYTVideoShow()->removeRoomMember(it->data(), false, nullptr);
				YYTPluginManage::getInstance()->getRoomManage()->removeRoomUser(it->data());
				//RoomManage::getInstance()->removeRoomUser(it->data());
				
			}
			YYTPluginManage::getInstance()->getRoomManage()->updateMemberList();
			break;
		}
	case AVRoomMulti::EVENT_ID_ENDPOINT_HAS_CAMERA_VIDEO:  //! 有视频
		{
			std::vector<View> views;
			for (size_t i=0; i<identifier_list.size(); ++i)
			{
				View view;
				view.video_src_type = VIDEO_SRC_TYPE_CAMERA;
				view.size_type = VIEW_SIZE_TYPE_BIG;
				views.push_back(view);
			}

			YYTPluginManage::getInstance()->getYYTVideoShow()->addRequestViews(identifier_list, views);
			
			for (std::vector<std::string>::iterator it = identifier_list.begin(); it != identifier_list.end(); it++)
			{
				//YYTPluginManage::getInstance()->getYYTVideoShow()->SetVideoState(it->data(), true);

				if (!YYTPluginManage::getInstance()->getRoomManage()->getRoomMember().contains(it->data()))
				{
					YYTPluginManage::getInstance()->getYYTServerHelper()->getMemUserInfo(it->data());
				}
				else
				{
					RoomMember roomMem;
					QMap<QString, RoomMember> mapRoomMem = YYTPluginManage::getInstance()->getRoomManage()->getRoomMember();

					roomMem = mapRoomMem[it->data()];
					roomMem.bVideoState = true;

					YYTPluginManage::getInstance()->getRoomManage()->addRoomUser(it->data(), roomMem);
				}
				
			}

			break;
		}
	case AVRoomMulti::EVENT_ID_ENDPOINT_HAS_SCREEN_VIDEO: //! 有屏幕共享
		{
			std::vector<View> views;
			for (size_t i=0; i<identifier_list.size(); ++i)
			{
				YYTPluginManage::getInstance()->getScreenShareDlg()->setScreenShareID(identifier_list[i].data());

				View view;
				view.video_src_type = VIDEO_SRC_TYPE_SCREEN;
				view.size_type = VIEW_SIZE_TYPE_BIG;
				views.push_back(view);
			}
			YYTPluginManage::getInstance()->getYYTVideoShow()->addRequestViews(identifier_list, views);

			break;
		}
	case AVRoomMulti::EVENT_ID_ENDPOINT_NO_CAMERA_VIDEO: //! 没有视频
		{
			YYTPluginManage::getInstance()->getYYTVideoShow()->freeCameraVideoRenders(identifier_list);

			for (std::vector<std::string>::iterator it = identifier_list.begin(); it != identifier_list.end(); it++)
			{
//				YYTPluginManage::getInstance()->getYYTVideoShow()->SetVideoState(it->data(), false);

				if (!YYTPluginManage::getInstance()->getRoomManage()->getRoomMember().contains(it->data()))
				{
					YYTPluginManage::getInstance()->getYYTServerHelper()->getMemUserInfo(it->data());
				}
				else
				{
					RoomMember roomMem;
					QMap<QString, RoomMember> mapRoomMem = YYTPluginManage::getInstance()->getRoomManage()->getRoomMember();

					roomMem = mapRoomMem[it->data()];
					roomMem.bVideoState = false;

					YYTPluginManage::getInstance()->getRoomManage()->addRoomUser(it->data(), roomMem);
				}

			}

			break;
		}
	case AVRoomMulti::EVENT_ID_ENDPOINT_NO_SCREEN_VIDEO://! 没有视频共享
		{
			int i = 0;

			YYTPluginManage::getInstance()->getScreenShareDlg()->closeScreenShareEvent();
// 			pLive->m_ScreenShareUserID.clear();
// 			pLive->SetScreenShareBtnStatus(true);
// 
// 			pLive->freeScreenVideoRender();
// 			pLive->m_pScreenShareRender->hide();
			break;
		}

	case AVRoomMulti::EVENT_ID_ENDPOINT_HAS_AUDIO: //! 有发音频事件
		{
			for (std::vector<std::string>::iterator it = identifier_list.begin(); it != identifier_list.end(); it++)
			{
				YYTPluginManage::getInstance()->getYYTVideoShow()->setMicState(it->data(), true);
			}

			for (std::vector<std::string>::iterator it = identifier_list.begin(); it != identifier_list.end(); it++)
			{
				if (!YYTPluginManage::getInstance()->getRoomManage()->getRoomMember().contains(it->data()))
				{
					YYTPluginManage::getInstance()->getYYTServerHelper()->getMemUserInfo(it->data());
				}
				else
				{
					RoomMember roomMem;
					QMap<QString, RoomMember> mapRoomMem = YYTPluginManage::getInstance()->getRoomManage()->getRoomMember();

					roomMem = mapRoomMem[it->data()];
					roomMem.bMicState = true;

					YYTPluginManage::getInstance()->getRoomManage()->addRoomUser(it->data(), roomMem);
				}

			}
			break;
		}

	case AVRoomMulti::EVENT_ID_ENDPOINT_NO_AUDIO: //! 无发音频事件
		{
			for (std::vector<std::string>::iterator it = identifier_list.begin(); it != identifier_list.end(); it++)
			{
				YYTPluginManage::getInstance()->getYYTVideoShow()->setMicState(it->data(), false);
			}

			for (std::vector<std::string>::iterator it = identifier_list.begin(); it != identifier_list.end(); it++)
			{
				if (!YYTPluginManage::getInstance()->getRoomManage()->getRoomMember().contains(it->data()))
				{
					YYTPluginManage::getInstance()->getYYTServerHelper()->getMemUserInfo(it->data());
				}
				else
				{
					RoomMember roomMem;
					QMap<QString, RoomMember> mapRoomMem = YYTPluginManage::getInstance()->getRoomManage()->getRoomMember();

					roomMem = mapRoomMem[it->data()];
					roomMem.bMicState = false;

					YYTPluginManage::getInstance()->getRoomManage()->addRoomUser(it->data(), roomMem);
				}

			}
			break;
		}
	}
}

void LiveServerHelper::OnSemiAutoRecvCameraVideo(std::vector<std::string> identifier_list, void* data)
{

}

void LiveServerHelper::OnSemiAutoRecvScreenVideo(std::vector<std::string> identifier_list, void* data)
{

}

void LiveServerHelper::OnSemiAutoRecvMediaFileVideo(std::vector<std::string> identifier_list, void* data)
{

}

void LiveServerHelper::OnRoomDisconnect(int32 reason, std::string errorinfo, void* data)
{

}

void LiveServerHelper::OnLocalVideo(VideoFrame* video_frame, void* custom_data)
{
	//Live* pLive = reinterpret_cast<Live*>(custom_data);

	if(video_frame->desc.src_type == VIDEO_SRC_TYPE_SCREEN)
	{
		//pLive->m_pScreenShareRender->DoRender(video_frame);
	}
	else if (video_frame->desc.src_type == VIDEO_SRC_TYPE_CAMERA)
	{
		//pLive->m_pLocalCameraRender->setFixedSize(QSize(320, 240));
		YYTPluginManage::getInstance()->getYYTVideoShow()->getLocalRender()->DoRender(video_frame);
	}
}

void LiveServerHelper::OnRemoteVideo(VideoFrame* video_frame, void* custom_data)
{
	if (video_frame->desc.src_type == VIDEO_SRC_TYPE_SCREEN)
	{
		YYTPluginManage::getInstance()->getScreenShareDlg()->getScreenShareRender()->DoRender(video_frame);
	}
	else if(video_frame->desc.src_type == VIDEO_SRC_TYPE_CAMERA)
	{
		VideoRender* pRender = YYTPluginManage::getInstance()->getYYTVideoShow()->getVideoRender(video_frame->identifier);
		if (pRender)
		{
			pRender->DoRender(video_frame);
		}
		else
		{
			//iLiveLog_e("suixinbo", "Render is not enough.");
		}
	}
}

void LiveServerHelper::OnSendInviteInteractSuc(void* data)
{
	postCusEvent(YYTPluginManage::getInstance()->getLiveServerHelper(), new Event(E_CESendInviteInteract, 0, "") );
}

void LiveServerHelper::OnSendInviteInteractErr(int code, const std::string& desc, void* data)
{
	postCusEvent( YYTPluginManage::getInstance()->getLiveServerHelper(), new Event(E_CESendInviteInteract, code, desc) );
}

void LiveServerHelper::setLiveLoginState(E_SDKLoginState eState)
{
	m_eLiveLoginState = eState;
}

E_SDKLoginState LiveServerHelper::getLiveLoginState()
{
	return m_eLiveLoginState;
}

bool LiveServerHelper::openScreenShareArea()
{
	if (E_ScreenShareNone == iLiveSDKWrap::getInstance()->getScreenShareState())
	{
		int nRet = iLiveSDKWrap::getInstance()->openScreenShare(m_x0, m_y0, m_x1, m_y1, m_fps);
		if (nRet==0)
		{
			//updatePushAndRecordStateUI();
			//updateScreenShareUI();
			return true;
		}
		else
		{
			
			if (nRet==1008)
			{
				//ShowErrorTips( FromBits("房间内只允许一个用户打开屏幕分享"), this );
			}
			else
			{
				//ShowCodeErrorTips( nRet, "Open Screen Share Failed.", this );
			}
			return false;
		}
	}
// 	else
// 	{
// 		OnBtnCloseScreenShare();
// 	}

}

bool LiveServerHelper::closeScreenShareArea()
{
	int nRet = iLiveSDKWrap::getInstance()->closeScreenShare();
	if (nRet==0)
	{
		return true;
// 		m_pScreenShareRender->update();
// 		updateScreenShareUI();
// 		updatePushAndRecordStateUI();
	}
	else
	{
		return false;
// 		updateScreenShareUI();
// 		ShowErrorTips( "Close Screen Share Failed.", this );
	}
}

bool LiveServerHelper::openMic()
{
	int nRet = iLiveSDKWrap::getInstance()->openMic();
	if (nRet==0)
	{		
		return true;
		//updateMicVol();
	}
	else
	{
		return false;
		//ShowErrorTips( "Open Mic Failed.", this );
	}

	
}

bool LiveServerHelper::closeMic()
{
	int nRet = iLiveSDKWrap::getInstance()->closeMic();
	if (nRet==0)
	{
		return true;
		//updateMicVol();
	}
	else
	{
		return false;
		//ShowErrorTips( "Close Mic Failed.", this );
	}

	
}

bool LiveServerHelper::openPlayer()
{
	int nRet = iLiveSDKWrap::getInstance()->openPlayer();
	if (nRet==0)
	{		
		return true;
		//updatePlayerVol();
	}
	else
	{
		return false;
		//ShowErrorTips( "Open Player Failed.", this );
	}

	
}

bool LiveServerHelper::closePlayer()
{
	int nRet = iLiveSDKWrap::getInstance()->closePlayer();
	if (nRet==0)
	{		
		return true;
		//updatePlayerVol();
	}
	else
	{
		return false;
		//ShowErrorTips( "Close Player Failed.", this );
	}

	
}

void LiveServerHelper::dealMessages()
{
	QQueue<TIMMessage>&	msgs = MessageCallBack::ms_messageQueue;
	while( !msgs.empty() )
	{
		const TIMMessage& msg = msgs.first();
		
		dealMessage(msg);
		MessageCallBack::ms_messageQueue.pop_front();
	}
}

void LiveServerHelper::dealMessage(const TIMMessage& msg)
{
	std::string szSender = msg.GetSender();
	int nCount = msg.GetElemCount();
	for (int i = 0; i < nCount; ++i)
	{
		TIMElem* pElem = msg.GetElem(i);
		switch( pElem->type() )
		{
		case kElemText:
			{
				QString szShow = QString::fromStdString( szSender + ": " );
				break;
			}
		case kElemCustom:
			{
				std::string szExt = pElem->GetCustomElem()->ext();
				//if (szExt==LiveNoti) //当前版本暂不启用此信令标记,待三个平台一起启用
				{
					std::string szDate = pElem->GetCustomElem()->data();
					parseCusMessage(szSender, szDate);
				}
				break;
			}
		case kElemImage:
			break;
		case kElemFace:
			break;
		case kElemGroupTips: //群事件消息: TIM_GROUP_TIPS_TYPE_INVITE等类型
			break;
		case kElemGroupReport://群系统消息: TIM_GROUP_SYSTEM_DELETE_GROUP_TYPE(群解散)、TIM_GROUP_SYSTEM_ADD_GROUP_REQUEST_TYPE(申请加群)等类型
			break;
		default:
			break;
		}
	}
}

void LiveServerHelper::parseCusMessage(const std::string& sender,std::string msg)
{
	QString qmsg = QString::fromStdString(msg);
	QJsonDocument doc = QJsonDocument::fromJson( qmsg.toLocal8Bit() );
	if (doc.isObject())
	{
		QJsonObject obj = doc.object();
		QVariantMap varmap = obj.toVariantMap();
		int nUserAction = AVIMCMD_None;
		QString szActionParam;
		if ( varmap.contains("userAction") )
		{
			nUserAction = varmap.value("userAction").toInt();
		}
		if ( varmap.contains("actionParam") )
		{
			szActionParam = varmap.value("actionParam").toString();
		}
		dealCusMessage( sender, nUserAction, szActionParam);
	}
}

void LiveServerHelper::dealCusMessage(const std::string& sender, int nUserAction, QString szActionParam)
{
	switch(nUserAction)
	{
	case AVIMCMD_Multi_Host_Invite: //观众收到连线邀请
		{
			int i = 0;

			
			QMap<QString/*成员ID*/, RoomMember/*成员信息*/> mapRoomMem = YYTPluginManage::getInstance()->getRoomManage()->getRoomMember();
			RoomMember stRoomMem = mapRoomMem[QString::fromStdString(sender)];
			YYTPluginManage::getInstance()->getScreenShareDlg()->ApplyScreenShareContrl(stRoomMem.szName);
// 			RoomMember stRoomMem = //m_RoomUserInfo[QString::fromStdString(sender)];
// 
// 			QString mes = stRoomMem.szName + FromBits("请求分享屏幕控制权，是否同意?");
// 			QMessageBox::StandardButton ret = QMessageBox::question(this, FromBits("屏幕分享申请控制"), mes);
// 			if ( ret == QMessageBox::Yes )
// 			{
// 				//OnBtnCloseScreenShare();
// 			}
// 			else
// 			{
// 				//refuseInteract();
// 			}
// 			break;
// 		}
		}
	}
}

void LiveServerHelper::sendScreenShareControl()
{
	sendC2CCustomCmd( YYTPluginManage::getInstance()->getScreenShareDlg()->getScreenShareID(), AVIMCMD_Multi_Host_Invite, "", OnSendInviteInteractSuc, OnSendInviteInteractErr, this );
}

void LiveServerHelper::customEvent(QEvent * event)
{
	Event* e = dynamic_cast<Event*>(event);
	switch(e->type())
	{
		case E_CELogin:
			{
				if (e->code==0)
				{
					//setLiveLoginState(E_LiveLogin);
					//iLiveCreateRoom();
					//int i = 0;
					//itchLoginState(E_Login);
					/*pMainWindow->*///serGerGroupList();
					//serGetGroupInfo();
					YYTPluginManage::getInstance()->getLiveServerHelper()->setLiveLoginState(E_LiveLogin);
					YYTPluginManage::getInstance()->getYYTServerHelper()->serGerGroupList();
				}
				else if (e->code == 6015)
				{
					YYTPluginManage::getInstance()->getLiveServerHelper()->setLiveLoginState(E_LiveLogin);
					YYTPluginManage::getInstance()->getYYTServerHelper()->serGerGroupList();
				}
			}
			break;
		case E_CELogout:
			{
				if (e->code==0)
				{
					//setLiveLoginState(E_LiveLogin);
					YYTPluginManage::getInstance()->getLiveServerHelper()->setLiveLoginState(E_LiveLogout);
				}
				else
				{

				}
				
				//int i = 0;
			}
			break;
		case E_CECreateRoom:
			{
				if (e->code==0)
				{
					YYTPluginManage::getInstance()->getYYTVideoShow()->updateCameraList();
					YYTPluginManage::getInstance()->getLiveServerHelper()->setLiveLoginState(E_LiveInRoom);

					YYTPluginManage::getInstance()->getYYTVideoShow()->OnBtnSpeaker();
					YYTPluginManage::getInstance()->getYYTVideoShow()->OnBtnVolume();

					//YYTPluginManage::getInstance()->getYYTVideoShow()->openCamera();
				}
				else if (e->code == 10021)
				{
					Sleep(1000);
					//YYTPluginManage::getInstance()->getLiveServerHelper()->iLiveJoinRoom();
					YYTPluginManage::getInstance()->getLiveServerHelper()->setLiveLoginState(E_LiveInRoom);
					//ShowErrorTips(FromBits("创建会议失败，请退出重新进入"));
					//exit(0);
				}
				else
				{
					YYTPluginManage::getInstance()->getLiveServerHelper()->setLiveLoginState(E_LiveLogin);
					ShowErrorTips(FromBits("创建会议失败，请退出重新进入"));
				}
			}
			break;
		case E_CEJoinRoom:
			{
				if (e->code==0)
				{
					YYTPluginManage::getInstance()->getLiveServerHelper()->setLiveLoginState(E_LiveInRoom);
					YYTPluginManage::getInstance()->getYYTVideoShow()->updateCameraList();
					YYTPluginManage::getInstance()->getYYTVideoShow()->OnBtnSpeaker();
					YYTPluginManage::getInstance()->getYYTVideoShow()->OnBtnVolume();
					//YYTPluginManage::getInstance()->getYYTVideoShow()->openCamera();
					
				}
				else if(e->code == 1003)
				{
					YYTPluginManage::getInstance()->getLiveServerHelper()->setLiveLoginState(E_LiveInRoom);
					YYTPluginManage::getInstance()->getYYTVideoShow()->OnBtnSpeaker();
					YYTPluginManage::getInstance()->getYYTVideoShow()->OnBtnVolume();
					//YYTPluginManage::getInstance()->getYYTVideoShow()->closeCamera();
					//ShowErrorTips(FromBits("加入会议失败，请退出重新进入"));
					//exit(0);
				}
				else
				{
					YYTPluginManage::getInstance()->getLiveServerHelper()->setLiveLoginState(E_LiveLogin);
					ShowErrorTips(FromBits("加入会议失败，请退出重新进入"));
				}
			}
			break;	
		case E_CESendInviteInteract:
			{
			}
			break;
		case E_CERecMsg:
			{
				dealMessages();
				break;
			}
		case E_CEQuitRoom:
			{
				if (e->code==0)
				{
					YYTPluginManage::getInstance()->getYYTVideoShow()->QuitRoomClear();

					if (YYTPluginManage::getInstance()->getLiveServerHelper()->getLiveLoginState() == E_LiveAgainLogin)
					{
						YYTPluginManage::getInstance()->getYYTServerHelper()->serGerGroupList();
					}
				}
				else
				{
					YYTPluginManage::getInstance()->getLiveServerHelper()->setLiveLoginState(E_LiveLogin);
				}
				
				
				int i = 0;
				break;
			}
	}
}
