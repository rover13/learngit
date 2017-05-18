#include "RoomManage.h"
#include <assert.h>
#include "iLiveSDKWrap.h"
#include <QDebug>

RoomManage::RoomManage(QObject *parent)
	: QObject(parent)
{

}

RoomManage::~RoomManage()
{
	qDebug() << "~RoomManage()";
}

// void RoomManage::OnRequestViewsTimer()
// {
// 	if (m_bIsRequesting)
// 	{
// 		return;
// 	}
// 	m_bIsRequesting = true;
// 	iLiveSDKWrap::getInstance()->requestViewList(m_toRequestIdentifiers, m_toRequestViews, OnRequestViewListSuc, OnRequestViewListErr, this);
// 	m_toRequestIdentifiers.clear();
// 	m_toRequestViews.clear();
// }

//void RoomManage::OnRequestViewListSuc(void* data)
//{
//	RoomManage* pRoomManage = reinterpret_cast<RoomManage*>(data);
//	//postCusEvent( g_pMainWindow, new Event(E_CERequestViewList, 0, "") );
//	if ( pRoomManage->m_toRequestIdentifiers.empty() )
//	{
//		pRoomManage->m_pRequestViewsTimer->stop();
//	}
//	pRoomManage->m_bIsRequesting = false;
//}
//
//void RoomManage::OnRequestViewListErr(int code, const std::string& desc, void* data)
//{
//	RoomManage* pRoomManage = reinterpret_cast<RoomManage*>(data);
//	pRoomManage->m_bIsRequesting = false;
//	pRoomManage->m_pRequestViewsTimer->stop();
//	//postCusEvent( g_pMainWindow, new Event(E_CERequestViewList, code, desc) );
//}

// RoomManage* RoomManage::getInstance()
// {
// 	static RoomManage instance;
// 	return &instance;
// }

void RoomManage::addRoomUser(QString szUserID, RoomMember stRoomMem)
{
	m_RoomUserInfo[szUserID] = stRoomMem;
}

void RoomManage::removeRoomUser(QString szUserID)
{
	m_RoomUserInfo.remove(szUserID);
}

QMap<QString, RoomMember> RoomManage::getRoomMember()
{
	return m_RoomUserInfo;
}

//void RoomManage::addRequestViews(const std::vector<std::string>& identifiers, const std::vector<View>& views)
//{
//	assert(identifiers.size() == views.size());
//	for (int i=0; i<identifiers.size(); ++i)
//	{
//		m_toRequestIdentifiers.push_back(identifiers[i]);
//		m_toRequestViews.push_back(views[i]);
//	}
//	if ( !m_pRequestViewsTimer->isActive() )
//	{
//		m_pRequestViewsTimer->start(0);
//	}
//}

void RoomManage::updateMemberList()
{
// 	m_nRoomSize = m_RoomUserInfo.size();
// 	m_ui.sbTotalMemNum->setValue(m_nRoomSize);
// 	m_ui.liMembers->clear();
// 	for (QMap<QString, RoomMember>::Iterator it = m_RoomUserInfo.begin(); it != m_RoomUserInfo.end(); it++)
// 	{
// 		RoomMember& member = *it;
// 		m_ui.liMembers->addItem( new QListWidgetItem(member.szName) );
// 	}

}

//void RoomManage::updateCameraList()
//{
//	iLiveSDKWrap::getInstance()->getCameraList(m_cameraList);
//}

// VideoRender* RoomManage::getVideoRender(std::string szIdentifier)
// {
// 	for(int i=0; i<MaxVideoRender; ++i)
// 	{
// 		if (m_arrRemoteIdentifiers[i]==szIdentifier)
// 		{
// 			return m_pRemoteVideoRenders[i];
// 		}
// 	}
// 	for(int i=0; i<MaxVideoRender; ++i)
// 	{
// 		if (m_bRemoteVideoRenderFrees[i])
// 		{
// 			m_bRemoteVideoRenderFrees[i] = false;
// 			m_arrRemoteIdentifiers[i] = szIdentifier;
// 			return m_pRemoteVideoRenders[i];
// 		}
// 	}
// 	return NULL;

//}

// void RoomManage::freeCameraVideoRenders(std::vector<std::string> arrNeedFreeRenders)
// {
// 	for (size_t i=0; i<arrNeedFreeRenders.size(); ++i)
// 	{
// 		for (size_t j = 0; j < m_arrRemoteIdentifiers.size(); ++j)
// 		{
// 			std::string str1 = m_arrRemoteIdentifiers[j];
// 			std::string str2 = arrNeedFreeRenders[i];
// 			if (str1 == str2)
// 			{
// 				m_arrRemoteIdentifiers[j] = "";
// 				m_bRemoteVideoRenderFrees[j] = true;
// 				m_pRemoteVideoRenders[j]->update();
// 			}
// 		}
// 	}

//}

