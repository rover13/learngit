#include "common/YYTCommon/common.h"
#include "PatientCase.h"
#include "YYTServerHelper.h"
#include "YYTPluginManage.h"

PatientCase::PatientCase(QWidget *parent)
	: QWidget(parent)
{
	initUI();
	initConnect();
}

PatientCase::~PatientCase()
{
	qDebug(qPrintable("PatientCase"));

    SafeDelete(m_pWebViewPatientCase);			//! 患者病历
	SafeDelete(m_NullDlg);						//! 没有影像时的窗口

	SafeDelete(m_gWebLayout);
}

// PatientCase* PatientCase::getInstance()
// {
// 	static PatientCase instance;
	//return &instance;
// }

void PatientCase::initUI()
{
    m_pWebViewPatientCase = new QWebView;
	m_gWebLayout = new QGridLayout;
	//gLayout->addWidget(m_pWebViewPatientCase);
	
	m_NullDlg = new QWidget;
	QLabel* lab = new QLabel(FromBits("暂无病历"));
	QGridLayout* layout1 = new QGridLayout;
	layout1->addWidget(lab);
	m_NullDlg->setLayout(layout1);
	
	m_gWebLayout->addWidget(m_NullDlg);

	this->setLayout(m_gWebLayout);
}

void PatientCase::initConnect()
{
	connect(this, SIGNAL(signal_loadUrl(QString)), this, SLOT(OnloadUrl(QString)), Qt::QueuedConnection);
}

void PatientCase::loadUrl(QString strUrl /*= ""*/)
{
	emit signal_loadUrl(strUrl);
}

void PatientCase::OnloadUrl(QString strUrl)
{
	if (!YYTPluginManage::getInstance()->getYYTServerHelper()->getMrid().isEmpty())
	{
		strUrl = YYTPluginManage::getInstance()->getYYTServerHelper()->getServerUrl() + QString("/web/case/casedetail") + QString("?access_token=") + YYTPluginManage::getInstance()->getYYTServerHelper()->getToken() + QString("&cid=") + YYTPluginManage::getInstance()->getYYTServerHelper()->getMrid();
        m_pWebViewPatientCase->load(QUrl(strUrl));

		m_gWebLayout->removeWidget(m_NullDlg);
        m_gWebLayout->addWidget(m_pWebViewPatientCase);

		this->update();
	}
	else
	{
        m_gWebLayout->removeWidget(m_pWebViewPatientCase);
		m_gWebLayout->addWidget(m_NullDlg);

		this->update();
	}
}

void PatientCase::showEvent(QShowEvent * event)
{

}
