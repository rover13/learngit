#ifndef PATIENTCASE_H
#define PATIENTCASE_H

#include <QObject>
#include "QFramer/fbasedialog.h"
#include <QtWebKitWidgets/QWebView>
#include <QGridLayout>

class PatientCase : public QWidget
{
	Q_OBJECT

public:
	explicit PatientCase(QWidget *parent = NULL);
	~PatientCase();

	//static PatientCase* getInstance();

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
    QWebView*			m_pWebViewPatientCase;			//! 患者病历
	QWidget*			m_NullDlg;						//! 没有影像时的窗口

	QGridLayout*		m_gWebLayout;
};

#endif // PATIENTCASE_H
