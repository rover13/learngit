
#include "InteractionServerHelper.h"
#include <QJsonDocument>
#include <QJsonObject>

InteractionServerHelper::InteractionServerHelper( const QString& url, const QString& content, SxbRecFun receiver, void* data )
{
	m_url = url;
	m_content = content;
	m_receiver = receiver;
	m_pCusdata = data;
}

InteractionServerHelper::~InteractionServerHelper()
{
	
}

void InteractionServerHelper::request( QVariantMap varmap, QString strUrl, QString cmd, SxbRecFun receiver, void* data )
{
	QString szUrl =  strUrl;
	QJsonDocument jsondoc;
	jsondoc.setObject( QJsonObject::fromVariantMap(varmap) );
	QString szContent = jsondoc.toJson();
	InteractionServerHelper* p = new InteractionServerHelper(szUrl, szContent, receiver, data);
	p->doRequest();
}

void InteractionServerHelper::doRequest()
{
	NetworkHelper::post( m_url, m_content, OnNetworkReply, this );
}

void InteractionServerHelper::OnNetworkReply( int errCode, const QByteArray& bytes, void* pCusData )
{
	InteractionServerHelper* pInteractionServerHelper = reinterpret_cast<InteractionServerHelper*>(pCusData);
	
	if (!pInteractionServerHelper->m_receiver)
	{
		delete pInteractionServerHelper;
		return;
	}

	if (errCode==E_NetTimeOut)
	{
		pInteractionServerHelper->m_receiver(E_YYTTimeOut, "Not received reply unitl timeout.", QVariantMap(), pInteractionServerHelper->m_pCusdata);
	}
	else if (errCode==E_NetReplyError)
	{
		pInteractionServerHelper->m_receiver(E_YYTNetReplyError, "Network reply error.", QVariantMap(), pInteractionServerHelper->m_pCusdata);
	}
	else if (errCode==E_NetOK)
	{		
		//解析接收到的json
		QJsonParseError json_error;
		QJsonDocument parse_doucment = QJsonDocument::fromJson(bytes, &json_error);
		if( json_error.error == QJsonParseError::NoError && parse_doucment.isObject() )
		{
			QJsonObject obj = parse_doucment.object();
			QVariantMap varmap = obj.toVariantMap();

			int errorCode = E_YYTJsonParseError;
			QString errorInfo;


			if (varmap.contains("status"))
			{
				bool bRes = varmap.value("status").toBool();
				if (bRes)
				{
					errorCode  = E_YYTOK;
				}
				else
				{
					errorCode  = E_YYTNetReplyError;
				}
				
			}
			if (varmap.contains("msg"))
			{
				errorInfo = varmap.value("msg").toString();
			}

			pInteractionServerHelper->m_receiver(errorCode, errorInfo, varmap, pInteractionServerHelper->m_pCusdata);
		}
		else
		{
			pInteractionServerHelper->m_receiver(E_YYTJsonParseError, "Josn parse error.", QVariantMap(), pInteractionServerHelper->m_pCusdata);
		}
	}

	if (NULL != pInteractionServerHelper->m_receiver)
	{
		delete pInteractionServerHelper;
	}
	
}

