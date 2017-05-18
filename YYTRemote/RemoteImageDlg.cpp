#include "common/YYTCommon/common.h"
#include "RemoteImageDlg.h"
#include "YYTServerHelper.h"
#include "YYTPluginManage.h"



RemoteImageDlg::RemoteImageDlg(QWidget *parent)
	: QWidget(parent)
{
	initUI();
	initConnect();
}

RemoteImageDlg::~RemoteImageDlg()
{
	
// 	if (m_loadUrlThread != NULL)
// 	{
// 		delete m_loadUrlThread;
// 		m_loadUrlThread = NULL;
// 	}
	//QCefQuit();
	qDebug(qPrintable("**********************************RemoteImageDlg"));

	SafeDelete(m_gWebLayout);
	SafeDelete(m_pWebViewRemoteImage);
	SafeDelete(m_NullDlg);

	if (NULL != m_loadUrlThread)
	{
		if (m_loadUrlThread->isRunning() | !m_loadUrlThread->isFinished())
		{
			m_loadUrlThread->quit();
			m_loadUrlThread->wait();
			m_loadUrlThread->deleteLater();
			qDebug(qPrintable("**********************************RemoteImageDlg*********************************************"));
		}
	}
	
	
}


void RemoteImageDlg::initUI()
{
	
	m_gWebLayout = new QGridLayout;
	m_pWebViewRemoteImage = NULL;//new QAxWidget;
	//m_pWebViewRemoteImage = NULL;
// 	
// 	m_pWebViewRemoteImage = new QAxWidget;
// 	m_pWebViewRemoteImage->setControl(QStringLiteral("{8856F961-340A-11D0-A96B-00C04FD705A2}"));
// 	m_pWebViewRemoteImage->setObjectName(QStringLiteral("webWidget"));//设置控件的名称
// 	m_pWebViewRemoteImage->setFocusPolicy(Qt::StrongFocus);//设置控件接收键盘焦点的方式：鼠标单击、Tab键
// 	m_pWebViewRemoteImage->setProperty("DisplayAlerts",false); //不显示任何警告信息。
// 	m_pWebViewRemoteImage->setProperty("DisplayScrollBars",true); // 显示滚动条
// 
// 	m_pWebViewRemoteImage->dynamicCall("Navigate(const QString&)", "http://rtpacs.cn:8000");

	//m_gWebLayout->addWidget(m_pWebViewRemoteImage);

	m_NullDlg = new QWidget;
	QLabel* lab = new QLabel(FromBits("暂无影像"));
	QGridLayout* layout1 = new QGridLayout;
	layout1->addWidget(lab);
	m_NullDlg->setLayout(layout1);
	
	
	m_gWebLayout->addWidget(m_NullDlg);

	this->setLayout(m_gWebLayout);
	
	m_bShowState = false;

	m_loadUrlThread = NULL;
	
	int i = 0;
	//QCefInit(i, nullptr);
	//m_cefWebView = new QCefWebView;
	
}

void RemoteImageDlg::initConnect()
{
	connect(this, SIGNAL(signal_loadUrl(QString)), this, SLOT(OnloadUrl(QString)), Qt::QueuedConnection);
}

void RemoteImageDlg::loadUrl(QString strUrl /*= ""*/)
{
	emit signal_loadUrl(strUrl);
}

void RemoteImageDlg::OnloadUrl(QString strUrl)
{
	QVector<QString> vecPacsid = YYTPluginManage::getInstance()->getYYTServerHelper()->getPaceid();
	QStringList pacslist = vecPacsid.toList();

	foreach(auto str, pacslist)
	{
		qDebug() << str;
	}
	

	if (!vecPacsid.isEmpty())
	{
		
		m_Url = YYTPluginManage::getInstance()->getYYTServerHelper()->getServerUrl() + QString("/dicom/web?aid=") + vecPacsid[0] + QString("&access_token=") + YYTPluginManage::getInstance()->getYYTServerHelper()->getToken();		//m_pWebViewRemoteImage->load(QUrl(strUrl));	

// 		if (!m_bShowState)
// 		{
// 			m_cefWebView->load(QUrl(m_Url));
// 			m_gWebLayout->removeWidget(m_NullDlg);
// 			m_gWebLayout->addWidget(m_cefWebView);
// 			m_NullDlg->hide();
 			m_bShowState = true;

			m_loadUrlThread = new QThread(this);

			connect(m_loadUrlThread, SIGNAL(started()), this, SLOT(doWork()));
			connect(m_loadUrlThread, SIGNAL(finished()), this, SLOT(deleteLater()));

			this->moveToThread(m_loadUrlThread);

			m_loadUrlThread->start();
//		}
	}
	else
	{
		
		if (NULL != m_pWebViewRemoteImage)
		{
			m_gWebLayout->removeWidget(m_pWebViewRemoteImage);
		}
		
		m_gWebLayout->addWidget(m_NullDlg);

		this->update();
	}
}

void RemoteImageDlg::doWork()
{
	
	
	if (NULL == m_pWebViewRemoteImage)
	{
		m_pWebViewRemoteImage = new QAxWidget(this);
	}

	m_pWebViewRemoteImage->setControl(QStringLiteral("{8856F961-340A-11D0-A96B-00C04FD705A2}"));
	m_pWebViewRemoteImage->setObjectName(QStringLiteral("webWidget"));//设置控件的名称
	m_pWebViewRemoteImage->setFocusPolicy(Qt::StrongFocus);//设置控件接收键盘焦点的方式：鼠标单击、Tab键
	m_pWebViewRemoteImage->setProperty("DisplayAlerts",false); //不显示任何警告信息。
	m_pWebViewRemoteImage->setProperty("DisplayScrollBars",true); // 显示滚动条

	m_pWebViewRemoteImage->dynamicCall("Navigate(const QString&)", m_Url);
	m_pWebViewRemoteImage->setProperty("DisplayStatusBars", false);
	m_gWebLayout->removeWidget(m_NullDlg);
	m_gWebLayout->addWidget(m_pWebViewRemoteImage);

	m_bShowState = true;

	this->update();
}

void RemoteImageDlg::showEvent(QShowEvent * event)
{
// 	
// 	m_cefWebView->load(QUrl("file:///F:/hcx_WorkSpace/YYTsource/test.html"));
// 	m_cefWebView->show();
// 	m_gWebLayout->addWidget(m_cefWebView);

	if (m_Url.isEmpty())
	{
		return;
	}
	
	int i = 0;
}
