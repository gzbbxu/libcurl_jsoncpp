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
	const int syncFaceAction = 10;
	const int syncRecordAction = syncFaceAction+1;
	const int addPeopleAction = syncFaceAction+2;
	static FaceService* faceService;

public:
	FaceService();

	static void respCallback(string & jsonStr,int action);

	static FaceService* getInstance();

	void syncFace(string current_verion);

	void syncFaceResponse(SyncFaceResponse * syncFaceResp);

	void syncRecord(string &jsonRequest);

	void syncRecordResponse(BaseResponse * baseResponse);

	void addPeople(string name, string position, string &imagebase64);

	void addPeopleResponse(AddPeopleResponce * addPeopleResponse);

	void deletePeople(string &uuid);

	void syncHeartbeats(string *jsonRequest);

	void getDeviceInfo(string uuid);

	void syncDevicesCreateOrUpdateDevices(string &jsonRequest);

	void syncRecordStranger(string &jsonRequest);

	virtual ~FaceService();
};

#endif /* FACESERVICE_H_ */
