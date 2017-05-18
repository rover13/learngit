#include "common/YYTCommon/common.h"
#include "ConsultationApplyDlg.h"
#include "YYTServerHelper.h"
#include <QGridLayout>
#include "YYTPluginManage.h"

ConsultationApplyDlg::ConsultationApplyDlg(QWidget *parent)
	: QWidget(parent)
{
	initUI();
	initConnect();
}

ConsultationApplyDlg::~ConsultationApplyDlg()
{
 	qDebug(qPrintable("ConsultationApplyDlg"));
    //SafeDelete(m_pWebViewConsultationApply);
	SafeDelete(m_NullDlg);						
	SafeDelete(m_gWebLayout);
 }

// ConsultationApplyDlg* ConsultationApplyDlg::getInstance()
// {
// 	static ConsultationApplyDlg instance;
//	return &instance;
// }

void ConsultationApplyDlg::initUI()
{
    m_pWebViewConsultationApply = new QWebView;
	m_gWebLayout = new QGridLayout;
	
	

	m_NullDlg = new QWidget;
	QLabel* lab = new QLabel(FromBits("ÔÝÎÞ»áÕïÉêÇë"));
	QGridLayout* layout1 = new QGridLayout;
	layout1->addWidget(lab);
	m_NullDlg->setLayout(layout1);

	m_gWebLayout->addWidget(m_NullDlg);

	this->setLayout(m_gWebLayout);
}

void ConsultationApplyDlg::initConnect()
{
	connect(this, SIGNAL(signal_loadUrl(QString)), this, SLOT(OnloadUrl(QString)), Qt::QueuedConnection);
}

void ConsultationApplyDlg::loadUrl(QString strUrl)
{
	emit signal_loadUrl(strUrl);
}

void ConsultationApplyDlg::OnloadUrl(QString strUrl)
{
	if (!YYTPluginManage::getInstance()->getYYTServerHelper()->getCiid().isEmpty())
	{
		strUrl = YYTPluginManage::getInstance()->getYYTServerHelper()->getServerUrl() + QString("/web/consultation/applyshow") + QString("?cid=") + YYTPluginManage::getInstance()->getYYTServerHelper()->getCiid() +  QString("&access_token=") + YYTPluginManage::getInstance()->getYYTServerHelper()->getToken();
        m_pWebViewConsultationApply->load(QUrl(strUrl));

		m_gWebLayout->removeWidget(m_NullDlg);
        m_gWebLayout->addWidget(m_pWebViewConsultationApply);

		this->update();
	}
	else
	{
		m_gWebLayout->removeWidget(m_pWebViewConsultationApply);
		m_gWebLayout->addWidget(m_NullDlg);

		this->update();
	}

}

void ConsultationApplyDlg::showEvent(QShowEvent * event)
{

}
