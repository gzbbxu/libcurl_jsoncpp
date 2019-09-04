/*
 * FaceController.h
 *
 *  Created on: 2019年8月22日
 *      Author: root
 */

#ifndef FACECONTROLLER_H_
#define FACECONTROLLER_H_
#include <sys/time.h>
#include <signal.h>
#include <iostream>
#include <unistd.h>
#include "FaceService.h"
#include "FaceDao.h"
#include "DeviceUtil.h"
using namespace std;
namespace basemodule {

class FaceController {
public:
	FaceController();

	/**
	 *定时执行任务 每间隔 5s 执行此函数
	 */
	static void alarm_handle(int singal);
	/**
	 * 注册定时间隔和alarm
	 */
	static void set_time();
	/**
	 * 开启定时任务
	 */
	static void start_timer();
	/**
	 * 停止定时任务
	 */
	static void stop_timer();

	virtual ~FaceController();
private:
	/**
	 * 发送心跳连接 5s每次
	 */
	static void asyncHearbetas();

	/**
	 * 同步人脸60s 每次
	 */
	static void asyncFace();

	/**
	 *发送识别结果 60s 每次
	 */
	static void syncRecord();

	/**
	 * 识别成功 接收到信号
	 */
	static void cardRecordSignal();

	/**
	 * 更改或者添加设备
	 */
	static void createOrUpdateDevice();

	/**
	 * 需要清除数据库
	 */
	static bool needClearDb;

	/**
	 * 每间隔5s回调一次alarm_handle 函数
	 */
	const static int perSecondsAlarm;

	/**
	 * 同步人脸的一次时间
	 */
	const static int syncFaceTime;

	/**
	 *统一业务回调接口
	 *@jsonStr 网络返回的json串  action 为-1的时候 jsonStr 为 "" 字符
	 *@action 业务回调action ，接口异常 为syncExceptionAction
	 *@curlResultCode curl 返回吗
	 */
	static void respCallback(string &jsonStr, int action, int curlResultCode);

	/**
	 *同步人员信息接口 回调
	 */
	static void syncFaceResponse(SyncFaceResponse *syncFaceResp);

	/**
	 * 识别上传接口回调
	 */
	static void syncRecordResponse(BaseResponse *baseResponse);
	/**
	 * 增加人员接口回调
	 */
	static void addPeopleResponse(AddPeopleResponce *addPeopleResponse);

	/**
	 * 心跳 接口回调
	 * */
	static void syncHeartbeatsResp(BaseResponse *baseResponse);
	/**
	 * 获取设备信息回调
	 */
	static void getDeviceInfoResp(DeviceInfoBean *deviceInfo);

	/**
	 * 设备 修改创建 接口回调
	 */
	static void syncDevicesCreateOrUpdateDevicesResp(BaseResponse *baseResponse);

	/**
	 * 陌生人同步回调
	 */
	static void syncRecordStrangerResp(BaseResponse *baseResponse);


};

} /* namespace basemodule */

#endif /* FACECONTROLLER_H_ */
