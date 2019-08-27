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

	//服务接口请求路径
	static const string path[];
	static FaceService *faceService;

public:
	//接口请求action
	const static  int syncExceptionAction = -1;
	const static int syncFaceAction = 0;
	const static int syncRecordAction = syncFaceAction + 1;
	const static int addPeopleAction = syncFaceAction + 2;
	const static int syncHeartbeatActions = syncFaceAction + 3;
	const static int getDeviceInfoActions = syncFaceAction + 4;
	const static int syncDevicesCreateOrUpdateDeviceAction = syncFaceAction + 5;
	const static int syncRecordStranagerAction = syncFaceAction + 6;

	FaceService();
	/**
	 *统一业务回调接口
	 *@jsonStr 网络返回的json串  action 为-1的时候 jsonStr 为 "" 字符
	 *@action 业务回调action ，接口异常 为syncExceptionAction
	 *@curlResultCode curl 返回吗

	static void respCallback(string &jsonStr, int action,int curlResultCode);*/

	static FaceService* getInstance();
	/**
	 *同步人员信息接口
	 *@param current_verion 当前本地版本
	 */
	void syncFace(string current_verion,httpRespCallback fun);

	/**
	 * 识别上传接口
	 */
	void syncRecord(string &jsonRequest,httpRespCallback fun);


	/**
	 * 增加人员接口
	 */
	void addPeople(string name, string position, string &imagebase64,httpRespCallback fun);

	/**
	 * 删除人员信息，暂未实现
	 */
	void deletePeople(string &uuid,httpRespCallback fun);
	/**
	 * 心跳 接口
	 */
	void syncHeartbeats(string &jsonRequest,httpRespCallback fun);

	/**
	 * 获取设备信息
	 */
	void getDeviceInfo(string uuid,httpRespCallback fun);

	/**
	 *设备修改创建接口
	 */
	void syncDevicesCreateOrUpdateDevices(string &jsonRequest,httpRespCallback fun);

	/**
	 * 陌生人同步
	 */
	void syncRecordStranger(string &jsonRequest,httpRespCallback fun);


	virtual ~FaceService();
};

#endif /* FACESERVICE_H_ */
