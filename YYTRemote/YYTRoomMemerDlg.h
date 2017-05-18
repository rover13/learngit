#ifndef YYTROOMMEMERDLG_H
#define YYTROOMMEMERDLG_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>

class YYTRoomMemerDlg : public QWidget
{
	Q_OBJECT

public:
	//YYTRoomMemerDlg(QWidget *parent = NULL);
	YYTRoomMemerDlg(QString strName = "test", bool bMicState = true, bool bSpeakerState = false, QWidget* parent = NULL);
	~YYTRoomMemerDlg();

	void setMicState(bool bState);
	void setVideoState(bool bState);

private:
	QLabel*			m_labName;
	QPushButton*	m_labVideo;
	QPushButton*	m_labMic;
	QHBoxLayout*	m_hLayout;
};

#endif // YYTROOMMEMERDLG_H
