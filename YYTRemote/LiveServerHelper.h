#ifndef LIVESERVERHELPER_H
#define LIVESERVERHELPER_H


#include <QObject>
#include "avsdk/av_room_multi.h"
#include "RoomManage.h"
#include "imsdk/tim_msg.h"

/*using namespace imcore;*/
using namespace tencent;
using namespace av;
using namespace imcore;
/*using namespace ilivesdk;*/

enum E_SDKLoginState
{
	E_LiveInvalidState = -1,
	E_LiveLogout,			
	E_LiveLogining,
	E_LiveLogin,
	E_LiveInRoom,
	E_LiveAgainLogin,
};

class LiveServerHelper : public QObject
{
	Q_OBJECT

public:

	//static LiveServerHelper* getInstance();

	LiveServerHelper(QObject *parent = NULL);
	~LiveServerHelper();
	
	static void onForceOffline();

	//iLiveSDKÏà¹Ø²Ù×÷
	void initSDK();	
	void iLiveLogin();
	void iLiveLogout();
	void iLiveCreateRoom();
	void iLiveJoinRoom();
	void iLiveChangeAuthority(uint64 authBits, const std::string& authBuffer);
	void iLiveQuitRoom();

	static void OniLiveLoginSuccess(void* data);
	static void OniLiveLoginError(int code, const std::string& desc, void* data);
	
	static void OniLiveLogoutSuccess(void* data);
	static void OniLiveLogoutError(int code, const std::string& desc, void* data);
	
	static void OniLiveCreateRoomSuc(void* data);
	static void OniLiveCreateRoomErr(int code, const std::string& desc, void* data);
	
	static void OniLiveJoinRoomSuc(void* data);
	static void OniLiveJoinRoomErr(int code, const std::string& desc, void* data);

	static void OnChangeAuthoritySuc(void* data);
	static void OnChangeAuthorityErr(int code, const std::string& desc, void* data);

	static void OnQuitRoomSuccess(void* data);
	static void OnQuitRoomError(int code, const std::string& desc, void* data);


	static void OnMemStatusChange(AVRoomMulti::EndpointEventId event_id, std::vector<std::string> identifier_list, void* data);
	static void OnSemiAutoRecvCameraVideo(std::vector<std::string> identifier_list, void* data);
	static void OnSemiAutoRecvScreenVideo(std::vector<std::string> identifier_list, void* data);
	static void OnSemiAutoRecvMediaFileVideo(std::vector<std::string> identifier_list, void* data);
	static void OnRoomDisconnect(int32 reason, std::string errorinfo, void* data);

	static void OnLocalVideo(VideoFrame* video_frame, void* custom_data);
	static void OnRemoteVideo(VideoFrame* video_frame, void* custom_data);

	static void OnSendInviteInteractSuc(void* data);
	static void OnSendInviteInteractErr(int code, const std::string& desc, void* data);



	//!
	void setLiveLoginState(E_SDKLoginState eState);
	E_SDKLoginState getLiveLoginState();

	bool openScreenShareArea();
	bool closeScreenShareArea();
	bool openMic();
	bool closeMic();
	bool openPlayer();
	bool closePlayer();

	void dealMessages();
	void dealMessage(const TIMMessage& msg);
	void parseCusMessage(const std::string& sender,std::string msg);
	void dealCusMessage(const std::string& sender, int nUserAction, QString szActionParam);

	void sendScreenShareControl();


protected:
	void customEvent(QEvent * event) override;

private:
	void addRequestViews(const std::vector<std::string>& identifiers, const std::vector<View>& views);

private:
	E_SDKLoginState m_eLiveLoginState;

	uint32	m_x0;
	uint32	m_y0;
	uint32	m_x1;
	uint32	m_y1;
	uint32	m_fps;

	QTimer*						m_pRequestViewsTimer;
	bool						m_bIsRequesting;
	std::vector<std::string>	m_toRequestIdentifiers;
	std::vector<View>			m_toRequestViews;

	
};

#endif // LIVESERVERHELPER_H
