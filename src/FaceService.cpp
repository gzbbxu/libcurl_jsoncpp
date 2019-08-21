/*
 * FaceService.cpp
 *
 *  Created on: 2019年8月16日
 *      Author: root
 */

#include "../include/FaceService.h"
FaceService *FaceService::faceService = new FaceService;
FaceService::FaceService() {

	cout << "gouzao zhixing faceservice" << endl;
}
FaceService* FaceService::getInstance() {
	return faceService;
}
void FaceService::respCallback(string &jsonStr, int action) {
	cout << "faceService httpRespCallback action >> " << action << "respstr >> "
			<< jsonStr << endl;
	if (action == faceService->syncFaceAction) {
		SyncFaceResponse syncFaceResp;
		BaseSerializerBean *base = &syncFaceResp;
		base->deserialize(jsonStr);
		/*cout << "deserialize over" << endl;
		 cout << syncFaceResp.current_version << endl;
		 cout << syncFaceResp.created.size() << endl;
		 list<UserBean *>::iterator it;
		 for(it = syncFaceResp.created.begin();it !=syncFaceResp.created.end();it++){
		 UserBean * userbean = *it;
		 cout << "userbean" << userbean->name << endl;

		 }*/
		faceService->syncFaceResponse(&syncFaceResp);
	} else if (action == faceService->syncRecordAction) {
		BaseResponse baseResp;
		BaseSerializerBean *base = &baseResp;
		base->deserialize(jsonStr);
		faceService->syncRecordResponse(&baseResp);
	} else if (action == faceService->addPeopleAction) {
		AddPeopleResponce addPeopleResp;
		BaseSerializerBean *base = &addPeopleResp;
		base->deserialize(jsonStr);
		faceService->addPeopleResponse(&addPeopleResp);
	}

}
/*write_data_call{"error":false,"detail":null,"is_latest":true,"current_version":0,"clear":true,"created":
 [{"uuid":"00158f931ba-18d9-4d2a-b27a-e16a88694988","name":"jack","position":"产品经理","image":"iv111VBORw0KGgoAAAANSUhEUgAAAGQAAABkCAYAAABw4pVUAACJmUlEQVR4nA","character":0},
 {"uuid":"44258f931ba-18d9-4d2a-b27a-e16a88694988","name":"tomcat44","position":"产品经理44","image":"iv44VBORw0KGgoAAAANSUhEUgAAAGQAAABkCAYAAABw4pVUAACJmUlEQVR4nA","character":0}],
 "updated":[{"uuid":"333158f931ba-18d9-4d2a-b27a-e16a88694988","name":"jack","position":"产品经理33","image":"iv333VBORw0KGgoAAAANSUhEUgAAAGQAAABkCAYAAABw4pVUAACJmUlEQVR4nA","character":0},
 {"uuid":null,"name":null,"position":null,"image":null,"character":0}],"deleted":null}*/

void FaceService::syncFace(string current_verion) {
	map<string, string> keys;
	keys["current_version"] = current_verion;
	httpRespCallback fun = (httpRespCallback) respCallback;
	HttpUtils::getInstance()->get("syncFace", keys, syncFaceAction, fun);
}
void FaceService::syncFaceResponse(SyncFaceResponse *syncFaceResp) {
	cout << syncFaceResp->detail << syncFaceResp->error << endl;
}

void FaceService::syncRecord(string &jsonRequest) {
	httpRespCallback fun = (httpRespCallback) respCallback;
	HttpUtils::getInstance()->post("syncRecord", jsonRequest, syncRecordAction,
			fun);
}

void FaceService::syncRecordResponse(BaseResponse *baseResponse) {
	cout << "syncRecordResponse " << baseResponse->detail << "  "
			<< baseResponse->error << endl;
}

void FaceService::addPeople(string name, string position,
		string &imagebase64) {
	map<string, string> keys;
	keys["name"] = name;
	keys["position"] = position;
	keys["image"] = imagebase64;
	httpRespCallback fun = (httpRespCallback) respCallback;
	HttpUtils::getInstance()->post("addPeople", keys, addPeopleAction, fun);

}
void FaceService::addPeopleResponse(AddPeopleResponce * addPeopleResp){

}

void FaceService::deletePeople(string &uuid) {

}

void FaceService::syncHeartbeats(string *jsonRequest) {

}

void FaceService::getDeviceInfo(string uuid) {

}

void FaceService::syncDevicesCreateOrUpdateDevices(string &jsonRequest) {

}

void FaceService::syncRecordStranger(string &jsonRequest) {

}

FaceService::~FaceService() {
//	httpUtl->release();
	HttpUtils::getInstance()->release();
}

