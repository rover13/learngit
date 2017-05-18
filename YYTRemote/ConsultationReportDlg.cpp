#include "common/YYTCommon/common.h"
#include "ConsultationReportDlg.h"
#include "YYTServerHelper.h"
#include "YYTPluginManage.h"
#include<ActiveQt\QAxWidget>

ConsultationReportDlg::ConsultationReportDlg(QWidget *parent)
	: QWidget(parent)
{
	initUI();
	initConnect();
}

ConsultationReportDlg::~ConsultationReportDlg()
{
	qDebug(qPrintable("ConsultationReportDlg"));
    SafeDelete(m_pWebViewConsultationReport);	//! 会诊报告
	SafeDelete(m_NullDlg);						//! 没有影像时的窗口

	SafeDelete(m_gWebLayout);
}

// ConsultationReportDlg* ConsultationReportDlg::getInstance()
// {
// 	static ConsultationReportDlg instance;
//	return &instance;
// }

void ConsultationReportDlg::initUI()
{
    m_pWebViewConsultationReport = new QWebView(this);
	m_gWebLayout = new QGridLayout;
	
	//m_pWebViewConsultationReport->load(QUrl("http://rtpacs.cn:8000"));
	//m_gWebLayout->addWidget(m_pWebViewConsultationReport);
	
	//QAxWidget *IEwidget= new QAxWidget(this);  

	//m_gWebLayout->addWidget(m_pWebViewConsultationReport);
	

	m_NullDlg = new QWidget;
	QLabel* lab = new QLabel(FromBits("暂无会诊报告"));
	QGridLayout* layout1 = new QGridLayout;
	layout1->addWidget(lab);
	m_NullDlg->setLayout(layout1);

	//m_gWebLayout->addWidget(m_NullDlg);



	this->setLayout(m_gWebLayout);

}

void ConsultationReportDlg::initConnect()
{
	connect(this, SIGNAL(signal_loadUrl(QString)), this, SLOT(OnloadUrl(QString)), Qt::QueuedConnection);
}

void ConsultationReportDlg::loadUrl(QString strUrl /*= ""*/)
{
	emit signal_loadUrl(strUrl);
}

void ConsultationReportDlg::OnloadUrl(QString strUrl)
{
	if (!YYTPluginManage::getInstance()->getYYTServerHelper()->getCiid().isEmpty())
	{
		strUrl =  YYTPluginManage::getInstance()->getYYTServerHelper()->getServerUrl() + QString("/webui/consultation/report?cid=") + YYTPluginManage::getInstance()->getYYTServerHelper()->getCiid();
        m_pWebViewConsultationReport->load(QUrl(strUrl));

		m_gWebLayout->removeWidget(m_NullDlg);
        m_gWebLayout->addWidget(m_pWebViewConsultationReport);

		this->update();
	}
	else
	{
        m_gWebLayout->removeWidget(m_pWebViewConsultationReport);
		m_gWebLayout->addWidget(m_NullDlg);

		this->update();
	}
}

void ConsultationReportDlg::showEvent(QShowEvent * event)
{

}
