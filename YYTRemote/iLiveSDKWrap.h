#ifndef iLiveSDKWrap_h_
#define iLiveSDKWrap_h_

#include <ilivesdk/iLiveLog.h>
#include <ilivesdk/iLiveSDK.h>
#include <ilivesdk/iLiveLoginMgr.h>
#include <ilivesdk/iLiveRoomMgr.h>

using namespace ilivesdk;

#pragma comment(lib, "iLiveSDK.lib")

class iLiveSDKWrap
{
public:
	static iLiveSDKWrap* getInstance();

	int initSdk(const int appId, const int accountType);///< ��ʼ��sdk
	void destroy();//!�ͷ���Դ
	
	//!����ǿ�����߻ص�
	void setForceOfflineCallback( ForceOfflineCallback cb );
	//!����Ⱥ��Ϣ�ص�
	void setGroupMessageCallBack( GropuMessageCallback cb );
	//!����C2C��Ϣ�ص�
	void setC2CMessageCallBack( C2CMessageCallback cb );
	//!����ϵͳ��Ϣ�ص�
	void setSysemMessageCallback( SysemMessageCallback cb );
	//!���ñ�����Ƶ�ص�
	void setLocalVideoCallBack( AVSupportVideoPreview::PreviewCallback pLocalVideoCB, void* pCustomData );

	void setRemoteVideoCallBack( AVSupportVideoPreview::PreviewCallback pRemoteVideoCB, void* pCustomData );//����Զ����Ƶ�ص�,��Ҫ�ڽ��뷿��ǰ����

	//!��¼
	void LiveLogin ( const std::string szUserId, const std::string szUserSig, SuccessCalllback suc, ErrorCallback err, void* data );///< ��¼
	void LiveLogout( SuccessCalllback suc, ErrorCallback err, void* data );///< �ǳ�

	//!��������
	void createRoom( const iLiveRoomOption& roomOption, SuccessCalllback suc, ErrorCallback err, void* data );
	//!���뷿��
	void joinRoom( const iLiveRoomOption& roomOption, SuccessCalllback suc, ErrorCallback err, void* data );
	//!�˳�����
	void quitRoom( SuccessCalllback suc, ErrorCallback err, void* data );
	
	//!������Ƶ�б�
	void requestViewList( const std::vector<std::string>& identifiers, const std::vector<View>& views, SuccessCalllback suc, ErrorCallback err, void* data );
	//!ȡ�������б�
	void cancelViewList( const std::vector<std::string>& identifiers, const std::vector<View>& views, SuccessCalllback suc, ErrorCallback err, void* data );
	//!ȡ��������Ƶ
	void cancelAllView( SuccessCalllback suc, ErrorCallback err, void* data );

	//!����C2C��Ϣ
	void sendC2CMessage( const std::string dstUser, TIMMessage& message, SuccessCalllback suc, ErrorCallback err, void* data );
	//!����Ⱥ��Ϣ
	void sendGroupMessage( TIMMessage& message, SuccessCalllback suc, ErrorCallback err, void* data );

	//!��ʼ¼��
	void startRecordVideo( const iLiveRecordOption& recordOption, SuccessCalllback suc, ErrorCallback err, void* data );
	//!ֹͣ¼��
	void stopRecordVideo( ilivesdk::Type<std::list<std::string>&>::VlaueSuccessCallback suc, ErrorCallback err, void* data );

	//!��ʼ����
	void startPushStream( const iLivePushOption& pushOption, ilivesdk::Type<TIMStreamRsp&>::VlaueSuccessCallback suc, ErrorCallback err, void* data );
	//!ֹͣ����
	void stopPushStream( uint64 channelId, SuccessCalllback suc, ErrorCallback err, void* data );

	//!�ı�Ȩ��
	void changeAuthority( uint64 authBits, const std::string& authBuffer, SuccessCalllback suc, ErrorCallback err, void* data );
	//!�ı��ɫ
	void changeRole( const std::string& szControlRole, SuccessCalllback suc, ErrorCallback err, void* data );

	//!�������ճ̶�
	int SetSkinSmoothGrade(int grade);
	//!�������׳̶�
	int SetSkinWhitenessGrade(int grade);

	//!��ȡ����ͷ�б�
	int getCameraList( std::vector< std::pair<std::string/*id*/, std::string/*name*/> >& cameraList );
	//!������ͷ
	int	openCamera(std::string szCameraId);
	//!�ر�����ͷ
	int closeCamera();

	//!���Զ���ɼ�
	int openExternalCapture();
	//!�ر��Զ���ɼ�
	int closeExternalCapture();
	//!�ⲿ��Ƶ��������
	int fillExternalCaptureFrame( const VideoFrame& frame );

	//!����˷�
	int openMic();
	//!��������
	int	setMicVolume(uint32 value);
	//!��ȡ����
	uint32 getMicVolume();
	//!�ر����
	int closeMic();

	//!��������
	int openPlayer();
	//!��������
	int setPlayerVolume( uint32 value );
	//!��ȡ����
	uint32 getPlayerVolume();
	//!�ر�������
	int closePlayer();

	//!����Ļ����
	int openScreenShare( HWND hWnd, uint32& fps );
	//!����Ļ����
	int openScreenShare( uint32& left, uint32& top, uint32& right, uint32& bottom, uint32& fps );
	//!�ı�����С
	int changeScreenShareSize( uint32& left, uint32& top, uint32& right, uint32& bottom );
	//!�ر���Ļ����
	int closeScreenShare();

	//!��ȡ����ͷ״̬
	bool getCurCameraState();
	//!��ȡ�Զ���ɼ�״̬
	bool getExternalCaptureState();
	//!��ȡ���״̬
	bool getCurMicState();
	//!��ȡ������״̬
	bool getCurPlayerState();
	//!
	E_ScreenShareState getScreenShareState();
	//!
	bool getPushStreamState();
	//!
	bool getRecordState();

private:
	iLiveSDKWrap();
	~iLiveSDKWrap();
};


#endif //iLiveSDKWrap_h_