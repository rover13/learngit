#ifndef YYTSTATEMANAGE_H
#define YYTSTATEMANAGE_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>

class YYTStateManage : public QWidget
{
	Q_OBJECT

public:
	YYTStateManage(QWidget *parent = NULL);
	~YYTStateManage();

	void initUI();
	void initConnect();

	//static YYTStateManage* getInstance();

protected:
	void showEvent(QShowEvent * event);
	
// 	void OnBtnSpeaker();
// 	void OnBtnVideo();
// 	void OnBtnVolume();
// 	void OnBtnSetting();
// 	void OnBtnScreenShare();

private slots:
	//void on_pushbtn_clicked();
	void OnTimerOut();

private:
// 	QPushButton* m_btnSpeaker;
// 	QPushButton* m_btnVideo;
// 	QPushButton* m_btnVolume;
// 	QPushButton* m_btnSettings;
// 	QPushButton* m_btnScreenShare;
	
	QLabel*		 m_labUserName;
	QLabel*		 m_labCompanyName;
	QLabel*		 m_labTime;

	QTimer*		 m_timer;
	
};

#endif // YYTSTATEMANAGE_H
