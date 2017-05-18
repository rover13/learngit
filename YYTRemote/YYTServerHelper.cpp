#include "common/YYTCommon/Util.h"
#include "YYTServerHelper.h"
#include "InteractionServerHelper.h"
#include "sha1_Psword.h"
#include "RoomManage.h"
#include "LiveServerHelper.h"
#include "Event.h"
#include "ConsultationApplyDlg.h"
#include "ConsultationReportDlg.h"
#include "PatientCase.h"
#include "RemoteImageDlg.h"
#include "YYTPluginManage.h"

YYTServerHelper::YYTServerHelper(QObject *parent)
	: QObject(parent)
{
	m_pSetting = new QSettings("config.ini", QSettings::IniFormat, this);
	readConfig();
}

YYTServerHelper::~YYTServerHelper()
{
	qDebug() << "~YYTServerHelper()";
	/*saveConfig();*/
}

// YYTServerHelper* YYTServerHelper::getInstance()
// {
// 	static YYTServerHelper instance;
//	return &instance;
// }



QString YYTServerHelper::getUserId()
{
	return m_szUserId;
}

QString YYTServerHelper::getServerUrl()
{
	return m_szServerUrl;
}

QString YYTServerHelper::getToken()
{
	return m_szUserToken;
}

QString YYTServerHelper::getUserName()
{
	return m_szUserName;
}

QString YYTServerHelper::getMrid()
{
	return m_szMrid;
}

QString YYTServerHelper::getRoomID()
{
	return m_szRoomID;
}

QString YYTServerHelper::getUserSig()
{
	return m_szUserSig;
}

QString YYTServerHelper::getRoomCreteID()
{
	return m_szRoomCreteID;
}

QVector<QString> YYTServerHelper::getPaceid()
{
	return m_vecPaceid;
}

QString YYTServerHelper::getCiid()
{
	return m_szCiid;
}

int YYTServerHelper::getAppID()
{
	return m_nAppId;
}

int YYTServerHelper::getAppAccountTyep()
{
	return m_nAccountType;
}

void YYTServerHelper::setUserAccount(QString szAccount)
{
	m_szUserAccount = szAccount;
}

void YYTServerHelper::setUserPsword(QString szPsword)
{
	m_szUserPassword = szPsword;
}

void YYTServerHelper::setRoomID(QString szRoomID)
{
	m_szRoomID = szRoomID;
}

void YYTServerHelper::setToken(QString szToken)
{
	m_szUserToken = szToken;
}

void YYTServerHelper::serGetUserInfo()
{
	QVariantMap varmap;
	QString strUrl = m_szServerUrl + "/api/user" + "?access_token=" + m_szUserToken;
	InteractionServerHelper::request(varmap, strUrl, "login", OnSerGetUserInfo, this);
}

void YYTServerHelper::serGerGroupList()
{
	QVariantMap varmap;
	QString strUrl = m_szServerUrl + "/api/group/chats"+ "?access_token=" + m_szUserToken;
	InteractionServerHelper::request(varmap, strUrl, "getGroupList", OnserGerGroupList, this);
}

void YYTServerHelper::serGetGroupInfo()
{
	QVariantMap varmap;
	QString strUrl = m_szServerUrl + "/api/group"+ "?access_token=" + m_szUserToken + "&dgid=" + m_szRoomID;
	InteractionServerHelper::request(varmap, strUrl, "getGroupInfo", OnSerGetGroupInfo, this);
}

void YYTServerHelper::loginYYT()
{
	QString encryPs;
	encryptPsword(m_szUserPassword, encryPs);

	m_eLoginState = E_YYTLogining;

	QString strUrl = m_szServerUrl + "/api/login?uaccount=" + m_szUserAccount + "&upassword=" + encryPs;

	QVariantMap varmap;

	InteractionServerHelper::request(varmap, strUrl, "login", OnLoginYYT, this);
}

void YYTServerHelper::logoutYYT()
{

}

void YYTServerHelper::getMemUserInfo(QString strUserID)
{
	QVariantMap varmap;
	QString strUrl = m_szServerUrl + "/api/user" + "?access_token=" + m_szUserToken + "&userid=" + strUserID;
	InteractionServerHelper::request(varmap, strUrl, "login", OnGetMemUserInfo, this);
}

E_LoginState YYTServerHelper::getLoginState()
{
	return m_eLoginState;
}



void YYTServerHelper::OnSerGetUserInfo(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData)
{
	YYTServerHelper* pYYTServerHelper = reinterpret_cast<YYTServerHelper*>(pCusData);
	QStringList strlist = datamap.keys();

	if (errorCode == E_YYTOK)
	{
		if (datamap.contains("userid"))
		{
			pYYTServerHelper->m_szUserId = datamap.value("userid").toString();
		}
		if (datamap.contains("sig"))
		{
			pYYTServerHelper->m_szUserSig = datamap.value("sig").toString();
		}
		if (datamap.contains("uname"))
		{
			pYYTServerHelper->m_szUserName = datamap.value("uname").toString();
		}

		//pYYTServerHelper->serGerGroupList();					//! 获取会话组列表
		pYYTServerHelper->serGetGroupInfo();	

		if (YYTPluginManage::getInstance()->getLiveServerHelper()->getLiveLoginState() == E_LiveInRoom)
		{
			YYTPluginManage::getInstance()->getLiveServerHelper()->setLiveLoginState(E_LiveAgainLogin);
			YYTPluginManage::getInstance()->getLiveServerHelper()->iLiveQuitRoom();
		}
		else if(YYTPluginManage::getInstance()->getLiveServerHelper()->getLiveLoginState() == E_LiveLogin)
		{
			YYTPluginManage::getInstance()->getYYTServerHelper()->serGerGroupList();
		}
		else
		{
			//!YYT登录成功之后，登录腾讯云
			YYTPluginManage::getInstance()->getLiveServerHelper()->iLiveLogin();
		}
	}
	else
	{
		//QString strMsg = FromBits("获取用户信息失败，请重新登录。会议邀请码为：") + pYYTServerHelper->m_szRoomID);
		//ShowCodeErrorTips( errorCode, strMsg, pMainWindow, FromBits("获取用户信息失败") );
	}
}

void YYTServerHelper::OnserGerGroupList(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData)
{
	YYTServerHelper* pYYTServerHelper = reinterpret_cast<YYTServerHelper*>(pCusData);
	QStringList strlist = datamap.keys();

	if (errorCode == E_YYTOK)
	{
		if (datamap.contains("list"))
		{
			QVariantList grouplist = datamap.value("list").toList();
			for (int i = 0; i < grouplist.size(); i++)
			{
				QVariantMap groupmap = grouplist[i].toMap();

				if (groupmap.contains("dgid")) //! 查找会议ＩＤ
				{
					if (pYYTServerHelper->m_szRoomID == groupmap.value("dgid").toString())//! 如果会议ID与房间ID相同
					{
						if (groupmap.contains("dgrecordid"))//！ 查看房间创建者ID即群主
						{
							pYYTServerHelper->m_szRoomCreteID =  groupmap.value("dgrecordid").toString();
						}
					}
				}
			}
		}

		postCusEvent(pYYTServerHelper, new Event(E_CEGETUSERINFO, 0, "") );
	}
	else
	{
 		ShowCodeErrorTips( errorCode, FromBits("获取用户信息失败"), NULL, FromBits("获取用户信息失败") );
		exit(0);
	}
}

void YYTServerHelper::OnSerGetGroupInfo(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData)
{
	YYTServerHelper* pYYTServerHelper = reinterpret_cast<YYTServerHelper*>(pCusData);

	if (errorCode==E_YYTOK)
	{
		if (datamap.contains("mrecord")) //！ 病例信息
		{
			QVariantMap groupmap = datamap.value("mrecord").toMap();
			QStringList strlist = groupmap.keys();

			if (groupmap.contains("mrid"))//!病例ID
			{
				pYYTServerHelper->m_szMrid = groupmap.value("mrid").toString();
			}
		}

		if (datamap.contains("pacs"))  //! 影像信息
		{
			QVariantList pacsList = datamap.value("pacs").toList();
			pYYTServerHelper->m_vecPaceid.clear();
			for (int i = 0; i < pacsList.size(); i++)
			{
				QVariantMap paceMap = pacsList[i].toMap();

				if (paceMap.contains("mrid")) //! 关联病历ID
				{
					QString strMrid = paceMap.value("mrid").toString();
					if (pYYTServerHelper->m_szMrid == strMrid)
					{
						if (paceMap.contains("maid")) //! 影像ID
						{
							pYYTServerHelper->m_vecPaceid.push_back(paceMap.value("maid").toString());
						}
					}
				}
			}
		}
		if (datamap.contains("consultationinfor")) //! 会诊信息
		{
			QVariantMap consultMap = datamap.value("consultationinfor").toMap();
			QStringList strlist = consultMap.keys();

			if (consultMap.contains("ciid"))
			{
				pYYTServerHelper->m_szCiid = consultMap.value("ciid").toString();
			}
		}
		if (datamap.contains("users"))	//! 管理员信息
		{
			QVariantList usersList = datamap.value("users").toList();
			pYYTServerHelper->m_mapRoomManage.clear();

			for (int i = 0; i < usersList.size(); i++)
			{
				QVariantMap usersMap = usersList[i].toMap();
				
				QString strUserID;
				int		iUserTyep;

				if (usersMap.contains("userid")) //! 关联病历ID
				{
					strUserID = usersMap.value("userid").toString();					
				}
				if (usersMap.contains("type"))
				{
					iUserTyep = usersMap.value("type").toUInt();
				}

				if (!strUserID.isEmpty())
				{
					
					pYYTServerHelper->m_mapRoomManage[strUserID] =  iUserTyep;
				}
			}
		}

		YYTPluginManage::getInstance()->getConsultationApplyDlg()->loadUrl();//ConsultationApplyDlg::getInstance()->loadUrl();
		/*ConsultationReportDlg::getInstance()*/YYTPluginManage::getInstance()->getConsultationReportDlg()->loadUrl();
		YYTPluginManage::getInstance()->getPatientCase()->loadUrl();
		YYTPluginManage::getInstance()->getRemoteImageDlg()->loadUrl();//RemoteImageDlg::getInstance()->loadUrl();
	}
	else
	{
		//ShowCodeErrorTips( errorCode, errorInfo, pMainWindow, FromBits("获取会话组信息失败") );
	}
}

void YYTServerHelper::OnLoginYYT(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData)
{
	YYTServerHelper* pYYTServerHelper = reinterpret_cast<YYTServerHelper*>(pCusData);

	if (errorCode == E_YYTOK)
	{
		pYYTServerHelper->m_eLoginState = E_YYTLogin;

		if (datamap.contains("access_token"))
		{
			pYYTServerHelper->m_szUserToken = datamap.value("access_token").toString();
		}

		pYYTServerHelper->serGetUserInfo();
	}
	else
	{
		ShowErrorTips(FromBits("登录失败，请重新登录"));
		//ShowCodeErrorTips(errorCode, errorInfo,NULL);
		pYYTServerHelper->m_eLoginState = E_YYTLogout;
	}

	
}

void YYTServerHelper::OnLogoutYYT(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData)
{

}

void YYTServerHelper::OnGetMemUserInfo(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData)
{
	YYTServerHelper* pServerHelper = reinterpret_cast<YYTServerHelper*>(pCusData);

	RoomMember stMemInfo;
	stMemInfo.bMicState = false;
	stMemInfo.bVideoState = false;

	if (E_YYTOK == errorCode)
	{
		if (datamap.contains("userid"))
		{
			stMemInfo.szID = datamap.value("userid").toString();
		}
		if (datamap.contains("utype"))
		{
			//stMemInfo.szID = datamap.value("sig").toString();
		}
		if (datamap.contains("uname"))
		{
			stMemInfo.szName = datamap.value("uname").toString();
		}


		YYTPluginManage::getInstance()->getRoomManage()->addRoomUser(stMemInfo.szID, stMemInfo);

		if (YYTPluginManage::getInstance()->getYYTVideoShow()->getVideoRenderState(stMemInfo.szID))
		{
			return;
		}
		YYTPluginManage::getInstance()->getYYTVideoShow()->addRoomMember(stMemInfo.szID,false,nullptr);

		//YYTPluginManage::getInstance()->getYYTVideoShow()->addRoomMember(stMemInfo.szName, false, NULL);
// 		pLive->m_RoomUserInfo[stMemInfo.szID] = stMemInfo;
// 		pLive->addRoomMemb(stMemInfo);
// 		pLive->updateMemberList();
	}
}

void YYTServerHelper::readConfig()
{
	if ( m_pSetting->contains("appId") && m_pSetting->contains("accountType") )
	{
		QVariant varAppid = m_pSetting->value("appId");
		QVariant varAccountType = m_pSetting->value("accountType");
		m_nAppId = varAppid.value<int>();
		m_nAccountType = varAccountType.value<int>();
	}
	else
	{
		m_nAppId = 1400029090;
		m_nAccountType = 12188;
	}

	if ( m_pSetting->contains("serverUrl") )
	{
		QVariant varServerUrl = m_pSetting->value("serverUrl");
		m_szServerUrl = varServerUrl.value<QString>();
	}
	else
	{
		m_szServerUrl = "http://xb.eastraycloud.net";
	}

	if ( m_pSetting->contains("userAccount") )
	{
		m_szUserAccount =  m_pSetting->value("userAccount").toString();
	}
	if ( m_pSetting->contains("userPwd") )
	{
		m_szUserPassword = m_pSetting->value("userPwd").toString();
	}
}

void YYTServerHelper::saveConfig()
{
	m_pSetting->setValue( "appId", QVariant(m_nAppId) );
	m_pSetting->setValue( "accountType", QVariant(m_nAccountType) );
	m_pSetting->setValue( "serverUrl", QVariant(m_szServerUrl) );
	m_pSetting->setValue( "userAccount", QVariant(m_szUserAccount) );
	m_pSetting->setValue( "userPwd", QVariant(m_szUserPassword) );
	SafeDelete(m_pSetting);
}

void YYTServerHelper::customEvent(QEvent * event)
{
	Event* e = dynamic_cast<Event*>(event); 
	switch(e->type())
	{
	case E_CEGETUSERINFO:
		{
			if (m_mapRoomManage.contains(m_szUserId))
			{
				if (m_mapRoomManage[m_szUserId] == 2)
				{
					YYTPluginManage::getInstance()->getLiveServerHelper()->iLiveCreateRoom();
				}
				else
				{
					YYTPluginManage::getInstance()->getLiveServerHelper()->iLiveJoinRoom();
				}
			}
			else
			{
				YYTPluginManage::getInstance()->getLiveServerHelper()->iLiveJoinRoom();
			}

// 			if (m_szUserId == m_szRoomCreteID)
// 			{
// 				YYTPluginManage::getInstance()->getLiveServerHelper()->iLiveCreateRoom();
// 			}
// 			else
// 			{
// 				YYTPluginManage::getInstance()->getLiveServerHelper()->iLiveJoinRoom();
// 			}
		}
	}
}

