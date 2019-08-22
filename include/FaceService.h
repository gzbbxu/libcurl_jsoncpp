/*
 * FaceService.h
 *
 *  Created on: 2019年8月16日
 *      Author: zhouke
 *
 */

#ifndef FACESERVICE_H_
#define FACESERVICE_H_
#include <string>
#include <list>
#include <jsoncpp/json/json.h>
#include <iostream>
#include "modules.h"

#include "HttpUtils.h"

using namespace std;
using namespace modules;
class FaceService {
private:
	//接口请求action
	const int syncExceptionAction = -1;
	const int syncFaceAction = 0;
	const int syncRecordAction = syncFaceAction + 1;
	const int addPeopleAction = syncFaceAction + 2;
	const int syncHeartbeatActions = syncFaceAction + 3;
	const int getDeviceInfoActions = syncFaceAction + 4;
	const int syncDevicesCreateOrUpdateDeviceAction = syncFaceAction + 5;
	const int syncRecordStranagerAction = syncFaceAction + 6;
	//服务接口请求路径
	static const string path[];
	static FaceService *faceService;

public:
	FaceService();
	/**
	 *统一业务回调接口
	 *@jsonStr 网络返回的json串  action 为-1的时候 jsonStr 为 "" 字符
	 *@action 业务回调action ，接口异常 为syncExceptionAction
	 *@curlResultCode curl 返回吗
	 */
	static void respCallback(string &jsonStr, int action,int curlResultCode);
	/**
	 *通用post一般請求
	 */
	void postCommon(string &json, int action);

	static FaceService* getInstance();
	/**
	 *同步人员信息接口
	 *@param current_verion 当前本地版本
	 */
	void syncFace(string current_verion);
	/**
	 *同步人员信息接口 回调
	 */
	void syncFaceResponse(SyncFaceResponse *syncFaceResp);
	/**
	 * 识别上传接口
	 */
	void syncRecord(string &jsonRequest);
	 /**
	  * 识别上传接口回调
	  */
	void syncRecordResponse(BaseResponse *baseResponse);

	/**
	 * 增加人员接口
	 */
	void addPeople(string name, string position, string &imagebase64);
	/**
		 * 增加人员接口回调
		 */
	void addPeopleResponse(AddPeopleResponce *addPeopleResponse);
	/**
	 * 删除人员信息，暂未实现
	 */
	void deletePeople(string &uuid);
	/**
	 * 心跳 接口
	 */
	void syncHeartbeats(string &jsonRequest);
	/**
	 * 心跳 接口回调
	 * */
	void syncHeartbeatsResp(BaseResponse *baseResponse);
	/**
	 * 获取设备信息
	 */
	void getDeviceInfo(string uuid);
	/**
	 * 获取设备信息回调
	 */
	void getDeviceInfoResp(DeviceInfoBean *deviceInfo);
	/**
	 *设备修改创建接口
	 */
	void syncDevicesCreateOrUpdateDevices(string &jsonRequest);
	/**
	 * 设备 修改创建 接口回调
	 */
	void syncDevicesCreateOrUpdateDevicesResp(BaseResponse *baseResponse);
	/**
	 * 陌生人同步
	 */
	void syncRecordStranger(string &jsonRequest);
	/**
	 * 陌生人同步回调
	 */
	void syncRecordStrangerResp(BaseResponse *baseResponse);

	virtual ~FaceService();
};

#endif /* FACESERVICE_H_ */
