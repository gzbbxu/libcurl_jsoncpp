/*
 * FaceService.h
 *
 *  Created on: 2019年8月16日
 *      Author: root
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
	const int syncFaceAction = 0;
	const int syncRecordAction = syncFaceAction+1;
	const int addPeopleAction = syncFaceAction+2;
	const int syncHeartbeatActions = syncFaceAction+3;
	const int getDeviceInfoActions = syncFaceAction+4;
	const int syncDevicesCreateOrUpdateDeviceAction = syncFaceAction+5;
	const int syncRecordStranagerAction = syncFaceAction+6;
	static const string path[];
	static FaceService* faceService;

public:
	FaceService();

	static void respCallback(string & jsonStr,int action);

	void postCommon(string & json,int action);

	static FaceService* getInstance();

	void syncFace(string current_verion);

	void syncFaceResponse(SyncFaceResponse * syncFaceResp);

	void syncRecord(string &jsonRequest);

	void syncRecordResponse(BaseResponse * baseResponse);

	void addPeople(string name, string position, string &imagebase64);

	void addPeopleResponse(AddPeopleResponce * addPeopleResponse);

	void deletePeople(string &uuid);

	void syncHeartbeats(string &jsonRequest);

	void syncHeartbeatsResp(BaseResponse * baseResponse);

	void getDeviceInfo(string uuid);

	void getDeviceInfoResp(DeviceInfoBean * deviceInfo);

	void syncDevicesCreateOrUpdateDevices(string &jsonRequest);

	void syncDevicesCreateOrUpdateDevicesResp(BaseResponse * baseResponse);

	void syncRecordStranger(string &jsonRequest);

	void syncRecordStrangerResp(BaseResponse * baseResponse);

	virtual ~FaceService();
};

#endif /* FACESERVICE_H_ */
