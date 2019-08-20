/*
 * FaceService.cpp
 *
 *  Created on: 2019年8月16日
 *      Author: root
 */

#include "../include/FaceService.h"

FaceService::FaceService() {
	httpUtils= HttpUtils::getInstance();
}

void FaceService::synFace(int current_verion) {
	map<string,string> keys ;
	keys["current_verion"] = current_verion;
	httpUtils->get("sync",keys);
}

void FaceService::syncRecord(string &jsonRequest) {

}

void FaceService::addPeople(string &name, string &position,
		string &imagebase64) {

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
}

