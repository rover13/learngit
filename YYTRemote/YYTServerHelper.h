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

	//! YYT�û����
	QString getUserId();					//! ��ȡ�û�ID
	QString	getServerUrl();					//! ��ȡ��������ַ
	QString getToken();						//! ��ȡ�û�Token
	QString getUserName();					//! ��ȡ�û�����
	QString getMrid();						//! ��ȡ����ID
	QString getRoomID();					//! ��ȡ����������
	QString getUserSig();					//! ��ȡ�û�Sig
	QString getRoomCreteID();				//! ���䴴����ID
	QVector<QString> getPaceid();			//! ��ȡӰ��ID
	QString getCiid();						//! ��ȡ����ID
	int		getAppID();						//! ��ȡ��Ѷ���˺�
	int		getAppAccountTyep();			//! ��ȡ��Ѷ���˺�����

	
	void setUserAccount(QString szAccount); //! �����˺�
	void setUserPsword(QString szPsword);	//! ��������
	void setRoomID(QString szRoomID);		//! ���û���������
	void setToken(QString szToken);			//! ����Token
	
		
	//! YYT�Ự�����
	void serGetUserInfo();					//! ��ȡ�û���Ϣ
	void serGerGroupList();					//! ��ȡ�Ự���б�
	void serGetGroupInfo();					//! ��ȡ�Ự����Ϣ
	
	//! ���������
	void loginYYT();						//! ��¼YYT������
	void logoutYYT();						//! �ǳ�YYT������
	E_LoginState getLoginState();			//! ��ȡYYT��¼״̬
	void getMemUserInfo(QString strUserID);	//! �ӷ������ϻ�ȡ��Ա��Ϣ

	//! �ص�
	static void OnSerGetUserInfo(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnserGerGroupList(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnSerGetGroupInfo(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnLoginYYT(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnLogoutYYT(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnGetMemUserInfo(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);

	//! �������
	void readConfig();
	void saveConfig();

protected:
	void customEvent(QEvent * event) override;

private:
	
	//! ��Ѷ�����
	QSettings*			m_pSetting;			//! д�����ļ�
	int					m_nAppId;			//! ��Ѷ���˺�
	int					m_nAccountType;		//! ��Ѷ���˺�����
	QString				m_szServerUrl;		//! YYT��������ַ


	QString				m_szUserId;			//! YYT�û�ID
	QString				m_szUserAccount;	//! YYT�û��˺�
	QString				m_szUserPassword;	//! YYT�û�����
	QString				m_szUserSig;		//! YYT�û�Sig
	QString				m_szUserToken;		//! YYT�û�Token
	QString				m_szUserName;		//! YYT�û�����

	QString				m_szRoomCreteID;	//! ���䴴����ID(��Ⱥ��)
	QString				m_szMrid;			//! ����ID 
	QVector<QString>	m_vecPaceid;		//! Ӱ��ID һ�����������Ӱ��
	QString				m_szCiid;			//! ������Ϣ��ID
	QString				m_szRoomID;			//! ����������(������ID��

	E_LoginState		m_eLoginState;		//! YYT��¼״̬

	QMap<QString, int>  m_mapRoomManage;	//! �������Ա

};

#endif // YYTSERVERHELPER_H
