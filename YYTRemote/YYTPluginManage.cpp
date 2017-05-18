#include "common/YYTCommon/common.h"
#include "YYTPluginManage.h"
#include <process.h>

YYTPluginManage::YYTPluginManage(QObject *parent)
	: QObject(parent)
{
	m_ConsultationApplyDlg = new ConsultationApplyDlg;
	m_ConsultationReportDlg = new ConsultationReportDlg;
	m_PatientCase = new PatientCase;
	m_RemoteImageDlg = new RemoteImageDlg;
	m_ScreenShareDlg = new ScreenShareDlg;
	m_YYTServerHelper = new YYTServerHelper;
	m_YYTVideoShow = new YYTVideoShow;
	m_RoomManage = new RoomManage;
	m_LiveServerHelper = new LiveServerHelper;
}

YYTPluginManage::~YYTPluginManage()
{
	qDebug() << " ~YYTPluginManage()";
	//m_LiveServerHelper->iLiveQuitRoom();
 	SafeDelete(m_YYTServerHelper);
	YYTPluginManage::getInstance()->getLiveServerHelper()->iLiveQuitRoom();
	Sleep(2000);
 	//SafeDelete(m_LiveServerHelper);
}

ConsultationApplyDlg* YYTPluginManage::getConsultationApplyDlg()
{
	return m_ConsultationApplyDlg;
}

ConsultationReportDlg* YYTPluginManage::getConsultationReportDlg()
{
	return m_ConsultationReportDlg;
}

PatientCase* YYTPluginManage::getPatientCase()
{
	return m_PatientCase;
}

RemoteImageDlg* YYTPluginManage::getRemoteImageDlg()
{
	return m_RemoteImageDlg;
}

ScreenShareDlg* YYTPluginManage::getScreenShareDlg()
{
	return m_ScreenShareDlg;
}

YYTServerHelper* YYTPluginManage::getYYTServerHelper()
{
	return m_YYTServerHelper;
}

YYTVideoShow* YYTPluginManage::getYYTVideoShow()
{
	return m_YYTVideoShow;
}

RoomManage* YYTPluginManage::getRoomManage()
{
	return m_RoomManage;
}

LiveServerHelper* YYTPluginManage::getLiveServerHelper()
{
	return m_LiveServerHelper;
}

YYTPluginManage* YYTPluginManage::getInstance()
{
	static YYTPluginManage instance;
	return &instance;
}
