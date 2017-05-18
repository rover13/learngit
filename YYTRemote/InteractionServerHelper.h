#pragma once
#include "NetworkHelper.h"

enum E_YYTServerRelpy
{
	E_YYTOK,
	E_YYTTimeOut,//³¬Ê±
	E_YYTNetReplyError,
	E_YYTJsonParseError,//Json½âÎö´íÎó
};

typedef void (*SxbRecFun)(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);

class InteractionServerHelper
{
public:
	static void request( QVariantMap varmap, QString svc, QString cmd, SxbRecFun receiver, void* data );

private:
	InteractionServerHelper(const QString& url, const QString& content, SxbRecFun receiver, void* data);
	~InteractionServerHelper();
	void doRequest();

	static void OnNetworkReply(int errCode, const QByteArray& bytes, void* pCusData);

private:
	QString	  m_url;
	QString	  m_content;
	SxbRecFun m_receiver;
	void*	  m_pCusdata;
};

