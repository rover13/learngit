#ifndef YYTPLUGINMANAGE_H
#define YYTPLUGINMANAGE_H

#include <QObject>
#include "ConsultationApplyDlg.h"
#include "ConsultationReportDlg.h"
#include "PatientCase.h"
#include "RemoteImageDlg.h"
#include "ScreenShareDlg.h"
#include "YYTVideoShow.h"
#include "LiveServerHelper.h"
#include "RoomManage.h"
#include "YYTServerHelper.h"

class YYTPluginManage : public QObject
{
	Q_OBJECT

public:
	YYTPluginManage(QObject *parent = NULL);
	~YYTPluginManage();

	ConsultationApplyDlg*	getConsultationApplyDlg();
	ConsultationReportDlg*	getConsultationReportDlg();
	PatientCase*			getPatientCase();
	RemoteImageDlg*			getRemoteImageDlg();
	ScreenShareDlg*			getScreenShareDlg();
	YYTServerHelper*		getYYTServerHelper();
	YYTVideoShow*			getYYTVideoShow();
	RoomManage*				getRoomManage();
	LiveServerHelper*		getLiveServerHelper();

	static YYTPluginManage* getInstance();

private:
	ConsultationApplyDlg*		m_ConsultationApplyDlg;
	ConsultationReportDlg*		m_ConsultationReportDlg;
	PatientCase*				m_PatientCase;
	RemoteImageDlg*				m_RemoteImageDlg;
	ScreenShareDlg*				m_ScreenShareDlg;
	YYTServerHelper*			m_YYTServerHelper;
	YYTVideoShow*				m_YYTVideoShow;
	RoomManage*					m_RoomManage;
	LiveServerHelper*			m_LiveServerHelper;

	
};

#endif // YYTPLUGINMANAGE_H
