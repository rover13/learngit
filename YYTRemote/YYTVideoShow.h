#ifndef YYTVIDEOSHOW_H
#define YYTVIDEOSHOW_H

/************************************************************************/
/* YYT视频显示模块                                                        */
/************************************************************************/
#include <QObject>
#include "VideoRender.h"
#include "QFramer/fbasedialog.h"
#include <QShowEvent>
#include "YYTRoomMemerDlg.h"

#define MaxVideoRender 3
#define MaxShowMembers 50



class YYTVideoShow : public QWidget
{
	Q_OBJECT

public:
	explicit YYTVideoShow(QWidget *parent = NULL);
	~YYTVideoShow();

	//static YYTVideoShow* getInstance();

	void initUI();
	void initConnect();

	void addVideoRender(VideoRender* video);
	void removeVideoRender(VideoRender* video);

	void addRoomMember(QString szMemberName, bool bIsVideo, VideoRender* video);
	void removeRoomMember(QString szMemberName, bool bIsVideo, VideoRender* video);


	void addRequestViews(const std::vector<std::string>& identifiers, const std::vector<View>& views);
	void updateCameraList();

	VideoRender* getVideoRender(std::string szIdentifier);
	VideoRender* getLocalRender();
	VideoRender* getScreenShareRender();

	void freeCameraVideoRenders(std::vector<std::string> arrNeedFreeRenders);
	void freeAllCameraVideoRender();
	void freeScreenVideoRender();


	static void OnRequestViewListSuc(void* data);
	static void OnRequestViewListErr(int code, const std::string& desc, void* data);


	bool openCamera();
	bool closeCamera();


	//! 按钮响应函数
	void OnBtnSpeaker();
	void OnBtnVideo();
	void OnBtnVolume();
	//void OnBtnSetting();
	void OnBtnScreenShare();

	void SetSliderSpeaker(uint32 value);
	void SetSliderMic(uint32 value);


	void setMicState(QString stUserID, bool bState);
	void SetVideoState(QString stUserID, bool bState, VideoRender* video);

	void QuitRoomClear();

	bool getVideoRenderState(QString strUserID);

private slots:
	void on_pushbtn_clicked();
	void OnRequestViewsTimer();
	void on_SliderChanged(int iValue);

	void OnUpdateLaterTimer();
protected:
	void showEvent(QShowEvent * event);
signals:

public slots:
	//void animationClose();
private:
	QVBoxLayout*			 m_vLayout;									//! 界面布局

	VideoRender*			 m_pLocalCameraRender;						//! 本地视频
	bool					 m_bIsLocalShow;							//! 本地视频是否已经显示

	VideoRender*			 m_pScreenShareRender;						//! 桌面共享
	bool					 m_bIsScreenShareShow;						//! 桌面共享是否已经显示

	std::vector<std::string> m_arrRemoteIdentifiers;
	VideoRender*			 m_pRemoteVideoRenders[MaxVideoRender];		//! 远程视频
	bool					 m_bRemoteVideoRenderFrees[MaxVideoRender];

	std::vector< std::pair<std::string/*id*/, std::string/*name*/> > m_cameraList;


	QTimer*						m_pRequestViewsTimer;
	bool						m_bIsRequesting;
	std::vector<std::string>	m_toRequestIdentifiers;
	std::vector<View>			m_toRequestViews;


	//!修改界面
	QWidget*					m_wgtControl;
	QWidget*					m_wgtVideo;
	
	QPushButton*				m_btnSpeaker;
	QPushButton*				m_btnVideo;
	QPushButton*				m_btnVolume;
	QPushButton*				m_btnSettings;
	QPushButton*				m_btnScreenShare;
	QSlider*					m_sliderSpeaker;	//! 话筒音量
	QSlider*					m_sliderMic;		//! 麦克风音量


	
	QMap<QString/*index*/,QVBoxLayout*>		m_mapRoomMemberLyout;
	QMap<QString,YYTRoomMemerDlg*>			m_mapRoomMemberDlg;
	QMap<QString, bool>						m_mapRoomMemVideoState;
	QMap<QString, QString>					m_mapRoomMemInfo;
	QGroupBox*					m_gBoxVideo;
	
	QTimer*						m_upDateLater;;
	QMap<QString, VideoRender*> m_upDateMap;
	
	
};

#endif // YYTVIDEOSHOW_H
