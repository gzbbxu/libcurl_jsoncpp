/*
 * FaceService.cpp
 *
 *  Created on: 2019年8月16日
 *
 *      Author: root
 */

#include "../include/FaceService.h"
FaceService *FaceService::faceService = new FaceService;
//服务接口请求路径
const string FaceService::path[] = { "syncFace", "syncRecord", "addPeople",
		"syncHeart", "getDeviceInfo", "createOrUpdate", "recordStranger" };
FaceService::FaceService() {

}
FaceService* FaceService::getInstance() {
	return faceService;
}


void FaceService::syncFace(string current_verion,httpRespCallback fun) {
	map<string, string> keys;
	keys["current_version"] = current_verion;
//	httpRespCallback fun = (httpRespCallback) respCallback;
	HttpUtils::getInstance()->get(path[syncFaceAction], keys, syncFaceAction,
			fun);
}


void FaceService::syncRecord(string &jsonRequest,httpRespCallback fun) {
	HttpUtils::getInstance()->post(path[syncRecordAction], jsonRequest, syncRecordAction, fun);
}



void FaceService::addPeople(string name, string position, string &imagebase64,httpRespCallback fun) {
	map<string, string> keys;
	keys["name"] = name;
	keys["position"] = position;
	keys["image"] = imagebase64;
	HttpUtils::getInstance()->post(path[addPeopleAction], keys, addPeopleAction,
			fun);

}


void FaceService::deletePeople(string &uuid,httpRespCallback fun) {

}

void FaceService::syncHeartbeats(string &jsonRequest,httpRespCallback fun) {

	HttpUtils::getInstance()->post(path[syncHeartbeatActions], jsonRequest, syncHeartbeatActions, fun);
}


void FaceService::getDeviceInfo(string uuid,httpRespCallback fun) {

	map<string, string> keys;
	keys["uuid"] = uuid;
	HttpUtils::getInstance()->get(path[getDeviceInfoActions], keys,
			getDeviceInfoActions, fun);
}

void FaceService::syncDevicesCreateOrUpdateDevices(string &jsonRequest,httpRespCallback fun) {
	HttpUtils::getInstance()->post(path[syncDevicesCreateOrUpdateDeviceAction], jsonRequest, syncDevicesCreateOrUpdateDeviceAction, fun);
}

void FaceService::syncRecordStranger(string &jsonRequest,httpRespCallback fun) {
//	postCommon(jsonRequest, syncRecordStranagerAction);
	HttpUtils::getInstance()->post(path[syncRecordStranagerAction], jsonRequest, syncRecordStranagerAction, fun);
}



FaceService::~FaceService() {
//	httpUtl->release();
	HttpUtils::getInstance()->release();
}

