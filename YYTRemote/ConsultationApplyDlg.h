#ifndef CONSULTATIONAPPLYDLG_H
#define CONSULTATIONAPPLYDLG_H

#include <QObject>
#include "QFramer/fbasedialog.h"
#include <QtWebKitWidgets/QWebView>
#include <QGridLayout>

class ConsultationApplyDlg : public QWidget
{
	Q_OBJECT

public:
	explicit ConsultationApplyDlg(QWidget *parent = NULL);
	~ConsultationApplyDlg();

	//static ConsultationApplyDlg* getInstance();

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
    QWebView*			m_pWebViewConsultationApply;	//! ��������
	QWidget*			m_NullDlg;						//! û��Ӱ��ʱ�Ĵ���

	QGridLayout*		m_gNullLayout;
	QGridLayout*		m_gWebLayout;
};

#endif // CONSULTATIONAPPLYDLG_H
