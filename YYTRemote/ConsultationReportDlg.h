#ifndef CONSULTATIONREPORTDLG_H
#define CONSULTATIONREPORTDLG_H

#include <QObject>
#include "QFramer/fbasedialog.h"
#include <QtWebKitWidgets/QWebView>
#include <QGridLayout>
#include<ActiveQt\QAxWidget>

class ConsultationReportDlg : public QWidget
{
	Q_OBJECT

public:
	explicit ConsultationReportDlg(QWidget *parent = NULL);
	~ConsultationReportDlg();

	/*static ConsultationReportDlg* getInstance();*/

	void initUI();
	void initConnect();

	void loadUrl(QString strUrl = "");

signals:
	void signal_loadUrl(QString strUrl);
private slots:
	void OnloadUrl(QString strUrl);

protected:
	void showEvent(QShowEvent * event);

private:
    QWebView*			m_pWebViewConsultationReport;	//! 会诊报告
	QWidget*			m_NullDlg;						//! 没有影像时的窗口

	QGridLayout*		m_gWebLayout;
	
};

#endif // CONSULTATIONREPORTDLG_H
