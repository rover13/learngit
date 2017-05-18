#ifndef YYTSERVERHELPER_H
#define YYTSERVERHELPER_H

#include <QObject>
#include "iLiveSDKWrap.h"
#include <QSettings>
#include <QVector>

enum E_LoginState
{
	E_YYTInvalidState = -1,
	E_YYTLogout,			
	E_YYTLogining,
	E_YYTLogin,
};

class YYTServerHelper : public QObject
{
	Q_OBJECT

public:
	//static YYTServerHelper* getInstance();

	YYTServerHelper(QObject *parent = NULL);
	~YYTServerHelper();

	//! YYT用户相关
	QString getUserId();					//! 获取用户ID
	QString	getServerUrl();					//! 获取服务器地址
	QString getToken();						//! 获取用户Token
	QString getUserName();					//! 获取用户姓名
	QString getMrid();						//! 获取病例ID
	QString getRoomID();					//! 获取会议邀请码
	QString getUserSig();					//! 获取用户Sig
	QString getRoomCreteID();				//! 房间创建者ID
	QVector<QString> getPaceid();			//! 获取影像ID
	QString getCiid();						//! 获取会诊ID
	int		getAppID();						//! 获取腾讯云账号
	int		getAppAccountTyep();			//! 获取腾讯云账号类型

	
	void setUserAccount(QString szAccount); //! 设置账号
	void setUserPsword(QString szPsword);	//! 设置密码
	void setRoomID(QString szRoomID);		//! 设置会议邀请码
	void setToken(QString szToken);			//! 设置Token
	
		
	//! YYT会话组相关
	void serGetUserInfo();					//! 获取用户信息
	void serGerGroupList();					//! 获取会话组列表
	void serGetGroupInfo();					//! 获取会话组信息
	
	//! 服务器相关
	void loginYYT();						//! 登录YYT服务器
	void logoutYYT();						//! 登出YYT服务器
	E_LoginState getLoginState();			//! 获取YYT登录状态
	void getMemUserInfo(QString strUserID);	//! 从服务器上获取成员信息

	//! 回调
	static void OnSerGetUserInfo(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnserGerGroupList(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnSerGetGroupInfo(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnLoginYYT(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnLogoutYYT(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnGetMemUserInfo(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);

	//! 配置相关
	void readConfig();
	void saveConfig();

protected:
	void customEvent(QEvent * event) override;

private:
	
	//! 腾讯云相关
	QSettings*			m_pSetting;			//! 写配置文件
	int					m_nAppId;			//! 腾讯云账号
	int					m_nAccountType;		//! 腾讯云账号类型
	QString				m_szServerUrl;		//! YYT服务器地址


	QString				m_szUserId;			//! YYT用户ID
	QString				m_szUserAccount;	//! YYT用户账号
	QString				m_szUserPassword;	//! YYT用户密码
	QString				m_szUserSig;		//! YYT用户Sig
	QString				m_szUserToken;		//! YYT用户Token
	QString				m_szUserName;		//! YYT用户姓名

	QString				m_szRoomCreteID;	//! 房间创建者ID(即群主)
	QString				m_szMrid;			//! 病例ID 
	QVector<QString>	m_vecPaceid;		//! 影像ID 一个病例，多个影像
	QString				m_szCiid;			//! 会诊信息表ID
	QString				m_szRoomID;			//! 会议邀请码(即房间ID）

	E_LoginState		m_eLoginState;		//! YYT登录状态

	QMap<QString, int>  m_mapRoomManage;	//! 房间管理员

};

#endif // YYTSERVERHELPER_H
