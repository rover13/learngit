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

	int initSdk(const int appId, const int accountType);///< 初始化sdk
	void destroy();//!释放资源
	
	//!设置强制下线回调
	void setForceOfflineCallback( ForceOfflineCallback cb );
	//!设置群消息回调
	void setGroupMessageCallBack( GropuMessageCallback cb );
	//!设置C2C消息回调
	void setC2CMessageCallBack( C2CMessageCallback cb );
	//!设置系统消息回调
	void setSysemMessageCallback( SysemMessageCallback cb );
	//!设置本地视频回调
	void setLocalVideoCallBack( AVSupportVideoPreview::PreviewCallback pLocalVideoCB, void* pCustomData );

	void setRemoteVideoCallBack( AVSupportVideoPreview::PreviewCallback pRemoteVideoCB, void* pCustomData );//设置远程视频回调,需要在进入房间前调用

	//!登录
	void LiveLogin ( const std::string szUserId, const std::string szUserSig, SuccessCalllback suc, ErrorCallback err, void* data );///< 登录
	void LiveLogout( SuccessCalllback suc, ErrorCallback err, void* data );///< 登出

	//!创建房间
	void createRoom( const iLiveRoomOption& roomOption, SuccessCalllback suc, ErrorCallback err, void* data );
	//!加入房间
	void joinRoom( const iLiveRoomOption& roomOption, SuccessCalllback suc, ErrorCallback err, void* data );
	//!退出房间
	void quitRoom( SuccessCalllback suc, ErrorCallback err, void* data );
	
	//!请求视频列表
	void requestViewList( const std::vector<std::string>& identifiers, const std::vector<View>& views, SuccessCalllback suc, ErrorCallback err, void* data );
	//!取消请求列表
	void cancelViewList( const std::vector<std::string>& identifiers, const std::vector<View>& views, SuccessCalllback suc, ErrorCallback err, void* data );
	//!取消所有视频
	void cancelAllView( SuccessCalllback suc, ErrorCallback err, void* data );

	//!发送C2C消息
	void sendC2CMessage( const std::string dstUser, TIMMessage& message, SuccessCalllback suc, ErrorCallback err, void* data );
	//!发送群消息
	void sendGroupMessage( TIMMessage& message, SuccessCalllback suc, ErrorCallback err, void* data );

	//!开始录制
	void startRecordVideo( const iLiveRecordOption& recordOption, SuccessCalllback suc, ErrorCallback err, void* data );
	//!停止录制
	void stopRecordVideo( ilivesdk::Type<std::list<std::string>&>::VlaueSuccessCallback suc, ErrorCallback err, void* data );

	//!开始推流
	void startPushStream( const iLivePushOption& pushOption, ilivesdk::Type<TIMStreamRsp&>::VlaueSuccessCallback suc, ErrorCallback err, void* data );
	//!停止推流
	void stopPushStream( uint64 channelId, SuccessCalllback suc, ErrorCallback err, void* data );

	//!改变权限
	void changeAuthority( uint64 authBits, const std::string& authBuffer, SuccessCalllback suc, ErrorCallback err, void* data );
	//!改变角色
	void changeRole( const std::string& szControlRole, SuccessCalllback suc, ErrorCallback err, void* data );

	//!设置美颜程度
	int SetSkinSmoothGrade(int grade);
	//!设置美白程度
	int SetSkinWhitenessGrade(int grade);

	//!获取摄像头列表
	int getCameraList( std::vector< std::pair<std::string/*id*/, std::string/*name*/> >& cameraList );
	//!打开摄像头
	int	openCamera(std::string szCameraId);
	//!关闭摄像头
	int closeCamera();

	//!打开自定义采集
	int openExternalCapture();
	//!关闭自定义采集
	int closeExternalCapture();
	//!外部视频数据输入
	int fillExternalCaptureFrame( const VideoFrame& frame );

	//!打开麦克风
	int openMic();
	//!设置音量
	int	setMicVolume(uint32 value);
	//!获取音量
	uint32 getMicVolume();
	//!关闭麦克
	int closeMic();

	//!打开扬声器
	int openPlayer();
	//!设置音量
	int setPlayerVolume( uint32 value );
	//!获取音量
	uint32 getPlayerVolume();
	//!关闭扬声器
	int closePlayer();

	//!打开屏幕分享
	int openScreenShare( HWND hWnd, uint32& fps );
	//!打开屏幕分享
	int openScreenShare( uint32& left, uint32& top, uint32& right, uint32& bottom, uint32& fps );
	//!改变分享大小
	int changeScreenShareSize( uint32& left, uint32& top, uint32& right, uint32& bottom );
	//!关闭屏幕分享
	int closeScreenShare();

	//!获取摄像头状态
	bool getCurCameraState();
	//!获取自定义采集状态
	bool getExternalCaptureState();
	//!获取麦克状态
	bool getCurMicState();
	//!获取扬声器状态
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