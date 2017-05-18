#ifndef ROOMMANAGE_H
#define ROOMMANAGE_H

#include <QObject>
#include <QMap>
#include <QTimer>
#include "avsdk/av_common.h"


using namespace tencent;
using namespace av;

enum E_RoomUserType
{
	E_RoomUserInvalid = -1,
	E_RoomUserWatcher, //
	E_RoomUserCreator, //
	E_RoomUserJoiner,  //
};

struct RoomMember
{
	QString szID;		//! 
	QString szName;
	E_RoomUserType userType;
	bool	bMicState;
	bool	bVideoState;
};


class RoomManage : public QObject
{
	Q_OBJECT

public:
	//static RoomManage* getInstance();

	void addRoomUser(QString szUserID, RoomMember stRoomMem);
	void removeRoomUser(QString szUserID);

	QMap<QString, RoomMember> getRoomMember();
	

	void updateMemberList();

// 	void updateCameraList();
// 	VideoRender* getVideoRender(std::string szIdentifier);
// 	void freeCameraVideoRenders(std::vector<std::string> arrNeedFreeRenders);
// 	void freeAllCameraVideoRender();
// 	void freeScreenVideoRender();



	RoomManage(QObject *parent = NULL);
	~RoomManage();

// private slots:
// 	void OnRequestViewsTimer();

private:
	



private:
	E_RoomUserType  m_userType;														//! 房间用户类型

	QMap<QString/*成员ID*/, RoomMember/*成员信息*/>	m_RoomUserInfo;					//! 房间成员管理
	QString											m_ScreenShareUserID;			//! 屏幕分享者ID
};

#endif // ROOMMANAGE_H
