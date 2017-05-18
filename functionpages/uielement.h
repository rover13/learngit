/****************************************************************************
**
** Copyright (C) 2014 dragondjf
**
** QFramer is a frame based on Qt5.3, you will be more efficient with it. 
** As an Qter, Qt give us a nice coding experience. With user interactive experience(UE) 
** become more and more important in modern software, deveployers should consider business and UE.
** So, QFramer is born. QFramer's goal is to be a mature solution 
** which you only need to be focus on your business but UE for all Qters.
**
** Version	: 0.2.5.0
** Author	: dragondjf
** Website	: https://github.com/dragondjf
** Project	: https://github.com/dragondjf/QCFramer
** Blog		: http://my.oschina.net/dragondjf/home/?ft=atme
** Wiki		: https://github.com/dragondjf/QCFramer/wiki
** Lincence: LGPL V2
** QQ: 465398889
** Email: dragondjf@gmail.com, ding465398889@163.com, 465398889@qq.com
** 
****************************************************************************/

#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <QProgressBar>
#include "QFramer/ftabwidget.h"
// #include "waterwidget.h"
// #include "waterview.h"
#include "animationgradientlabel.h"

#include "YYTVideoShow.h"
#include "ConsultationApplyDlg.h"
#include "PatientCase.h"
#include "ConsultationReportDlg.h"
#include "RemoteImageDlg.h"
#include "ScreenShareDlg.h"

class UIElement : public FTabWidget
{
    Q_OBJECT
private:
    QList<QProgressBar *> progressBars;

	YYTVideoShow*			m_YYTVideoShowDlg;		//! YYT视频显示模块
	ConsultationApplyDlg*   m_YYTConsultaApplyDlg;	//! YYT会诊申请模块
	PatientCase*			m_YYTPatientCaseDlg;	//! YYT患者病历模块
	ConsultationReportDlg*	m_YYTConsultaReportDlg;	//! YYT会诊报告模块
	RemoteImageDlg*			m_YYTRemoteImageDlg;	//! YYT远程影像模块
	ScreenShareDlg*			m_YYTScreenShareDlg;	//! YYT屏幕分享模块

public:
    explicit UIElement(QWidget *parent = 0);
    void initUI();
    void initBaseElements();
    void initTableWidget();
    void initTreeWidget();
    void initProgressBar();
    void initAboutLabel();
//     void initWaterWidget();
//     void initWaterView();
    void initAnimationLabel();
signals:

public slots:
    void updateProgressBar();
};

#endif // UIELEMENT_H
