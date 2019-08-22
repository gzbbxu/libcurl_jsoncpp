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
void FaceService::respCallback(string &jsonStr, int action,
		int curlResultCode) {
	cout << "faceService httpRespCallback action >> " << action << "respstr >> "
			<< jsonStr << endl;
	if (action == faceService->syncFaceAction) {
		SyncFaceResponse syncFaceResp;
		BaseSerializerBean *base = &syncFaceResp;
		base->deserialize(jsonStr);
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
	} else if (action == faceService->syncHeartbeatActions) {
		BaseResponse baseResp;
		BaseSerializerBean *base = &baseResp;
		base->deserialize(jsonStr);
		faceService->syncHeartbeatsResp(&baseResp);
	} else if (action == faceService->getDeviceInfoActions) {
		DeviceInfoBean device;
		BaseSerializerBean *base = &device;
		base->deserialize(jsonStr);
		faceService->getDeviceInfoResp(&device);
	} else if (action == faceService->syncDevicesCreateOrUpdateDeviceAction) {
		BaseResponse baseResp;
		baseResp.deserialize(jsonStr);
		faceService->syncDevicesCreateOrUpdateDevicesResp(&baseResp);
	} else if (action == faceService->syncRecordStranagerAction) {
		BaseResponse baseResp;
		baseResp.deserialize(jsonStr);
		faceService->syncRecordStrangerResp(&baseResp);
	} else if (action == faceService->syncExceptionAction) {
		//异常信息
		switch (curlResultCode) {
		case CURLE_COULDNT_RESOLVE_HOST:
			cout << "无法解析主机!" << endl;
			break;
		case CURLE_COULDNT_CONNECT:
			cout << "无法连接到主机" << endl;
			break;
		case CURLE_COULDNT_RESOLVE_PROXY:
			cout << "无法解析代理" <<endl;
			break;
		case CURLE_FTP_WEIRD_SERVER_REPLY:
			cout << "curl数据解析失败" <<endl;
			break;
		default:
			cout << "其他错位" << curlResultCode << endl;
			break;
		}
	}

}

void FaceService::syncFace(string current_verion) {
	map<string, string> keys;
	keys["current_version"] = current_verion;
	httpRespCallback fun = (httpRespCallback) respCallback;
	HttpUtils::getInstance()->get(path[syncFaceAction], keys, syncFaceAction,
			fun);
}
void FaceService::syncFaceResponse(SyncFaceResponse *syncFaceResp) {
	cout << syncFaceResp->detail << syncFaceResp->error << endl;
}

void FaceService::syncRecord(string &jsonRequest) {
	postCommon(jsonRequest, syncRecordAction);
}

void FaceService::syncRecordResponse(BaseResponse *baseResponse) {
	cout << "syncRecordResponse " << baseResponse->detail << "  "
			<< baseResponse->error << endl;
}

void FaceService::addPeople(string name, string position, string &imagebase64) {
	map<string, string> keys;
	keys["name"] = name;
	keys["position"] = position;
	keys["image"] = imagebase64;
	httpRespCallback fun = (httpRespCallback) respCallback;
	HttpUtils::getInstance()->post(path[addPeopleAction], keys, addPeopleAction,
			fun);

}
void FaceService::addPeopleResponse(AddPeopleResponce *addPeopleResp) {
	cout << "addPeopleResponse" << addPeopleResp->detail << " "
			<< addPeopleResp->error << endl;
}

void FaceService::deletePeople(string &uuid) {

}

void FaceService::syncHeartbeats(string &jsonRequest) {

	/*	httpRespCallback fun = (httpRespCallback) respCallback;
	 HttpUtils::getInstance()->post(path[syncHeartbeatActions], jsonRequest,
	 syncHeartbeatActions, fun);*/
	postCommon(jsonRequest, syncHeartbeatActions);
}
void FaceService::syncHeartbeatsResp(BaseResponse *baseResponse) {
	cout << "syncResp " << baseResponse->detail << "" << endl;
}

void FaceService::getDeviceInfo(string uuid) {

	map<string, string> keys;
	keys["uuid"] = uuid;
	httpRespCallback fun = (httpRespCallback) respCallback;
	HttpUtils::getInstance()->get(path[getDeviceInfoActions], keys,
			getDeviceInfoActions, fun);
}
void FaceService::getDeviceInfoResp(DeviceInfoBean *deviceInfo) {
	cout << "getDeviceInfoResp " << deviceInfo->uuid << endl;
}

void FaceService::syncDevicesCreateOrUpdateDevices(string &jsonRequest) {
	postCommon(jsonRequest, syncDevicesCreateOrUpdateDeviceAction);
}
void FaceService::syncDevicesCreateOrUpdateDevicesResp(
		BaseResponse *baseResponse) {
	cout << "syncDevicesCreateOrUpdateDevicesResp " << baseResponse->detail
			<< endl;
}
void FaceService::syncRecordStranger(string &jsonRequest) {
	postCommon(jsonRequest, syncRecordStranagerAction);
}

void FaceService::syncRecordStrangerResp(BaseResponse *baseResponse) {
	cout << "syncRecordStrangerResp" << " " << baseResponse->detail << endl;
}
void FaceService::postCommon(string &jsonRequest, int action) {
	httpRespCallback fun = (httpRespCallback) respCallback;
	HttpUtils::getInstance()->post(path[action], jsonRequest, action, fun);
}

FaceService::~FaceService() {
//	httpUtl->release();
	HttpUtils::getInstance()->release();
}

