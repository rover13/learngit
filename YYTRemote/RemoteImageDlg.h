#ifndef REMOTEIMAGEDLG_H
#define REMOTEIMAGEDLG_H

#include <QObject>
#include "QFramer/fbasedialog.h"
//#include <QtWebKitWidgets/QWebView>
#include <QGridLayout>
#include<ActiveQt\QAxWidget>
#include <QThread>
// #include "QCefClient.h"
// #include "qcefwebview.h"

class RemoteImageDlg : public QWidget
{
	Q_OBJECT

public:
	explicit RemoteImageDlg(QWidget *parent = NULL);
	~RemoteImageDlg();

	//static RemoteImageDlg* getInstance();

	void initUI();
	void initConnect();


	void loadUrl(QString strUrl = "");

signals:
	void signal_loadUrl(QString strUrl);
private slots:
	void OnloadUrl(QString strUrl);

	void doWork();

protected:
	void showEvent(QShowEvent * event);

private:
	QAxWidget*			m_pWebViewRemoteImage;			//! Զ��Ӱ��
	QWidget*			m_NullDlg;						//! û��Ӱ��ʱ�Ĵ���

	QGridLayout*		m_gWebLayout;	

    QString				m_Url;

	bool				m_bShowState;
	QThread*			m_loadUrlThread;

	//QCefWebView*		m_cefWebView;
	
};

#endif // REMOTEIMAGEDLG_H
