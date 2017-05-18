#ifndef SCREENSHAREDLG_H
#define SCREENSHAREDLG_H

#include <QObject>
#include "VideoRender.h"
#include "QFramer/fbasedialog.h"
#include <QVBoxLayout>

class ScreenShareDlg : public QWidget
{
	Q_OBJECT

public:
	ScreenShareDlg(QWidget *parent = NULL);
	~ScreenShareDlg();

	void initUI();
	void initConnect();
	VideoRender* getScreenShareRender();

	void closeScreenShareEvent();

	void setScreenShareID(QString id);
	QString  getScreenShareID();

	void setScreenShareState(bool state);
	bool  getScreenShareState();

	void ApplyScreenShareContrl(QString strname);

private slots:
	void OnBtnOpenScreenshare();
	void OnBtnScreenShareControl();
	void OnBtnFreeScreenShareControl();

protected:
	void showEvent(QShowEvent * event);

private:
	VideoRender*	m_pScreenShareRender;	//! 屏幕分享
	QWidget*		m_NullDlg;			//! 没有影像时的窗口

	QPushButton*	m_pBtnOpenScreenShare;

	QVBoxLayout*	m_gDlgLayout;				
	QVBoxLayout*	m_gNullLayout;

	bool			m_bShowState;

	QPushButton*	m_pBtnScreenShareControl;

	QString			m_ScreenShareUserID;
	bool			m_bScreenShareState;
};

#endif // SCREENSHAREDLG_H
