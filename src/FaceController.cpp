/*
 * FaceController.cpp
 *
 *   业务控制模块
 *  Created on: 2019年8月22日
 *      Author: zhouke
 */

#include "../include/FaceController.h"

namespace basemodule {
bool FaceController::needClearDb = false;
const int FaceController::perSecondsAlarm = 5;
const int FaceController::syncFaceTime = 60;
void FaceController::alarm_handle(int sig) {

	cout << "alarm_handle sig = " << sig << endl;
	asyncHearbetas();
//	asyncFace();
}
void FaceController::start_timer() {
	signal(SIGALRM, alarm_handle);
	set_time();

	//添加设备
	createOrUpdateDevice();
}
void FaceController::stop_timer() {
	alarm(0);
}
void FaceController::set_time() {
	struct itimerval itv;
	itv.it_interval.tv_sec = perSecondsAlarm; //per
	itv.it_interval.tv_usec = 0;
	itv.it_value.tv_sec = 3; // first time
	itv.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &itv, NULL);
	cout << "set time" << perSecondsAlarm << endl;

}
void FaceController::respCallback(string &jsonStr, int action,
		int curlResultCode) {
	cout << "FaceController httpRespCallback action >> " << action
			<< "respstr >> " << jsonStr << endl;
	if (action == FaceService::syncFaceAction) {
		SyncFaceResponse syncFaceResp;
		BaseSerializerBean *base = &syncFaceResp;
		base->deserialize(jsonStr);
		syncFaceResponse(&syncFaceResp);
	} else if (action == FaceService::syncRecordAction) {
		BaseResponse baseResp;
		BaseSerializerBean *base = &baseResp;
		base->deserialize(jsonStr);
		syncRecordResponse(&baseResp);
	} else if (action == FaceService::addPeopleAction) {
		AddPeopleResponce addPeopleResp;
		BaseSerializerBean *base = &addPeopleResp;
		base->deserialize(jsonStr);
		addPeopleResponse(&addPeopleResp);
	} else if (action == FaceService::syncHeartbeatActions) {
		BaseResponse baseResp;
		BaseSerializerBean *base = &baseResp;
		base->deserialize(jsonStr);
		syncHeartbeatsResp(&baseResp);
	} else if (action == FaceService::getDeviceInfoActions) {
		DeviceInfoBean device;
		BaseSerializerBean *base = &device;
		base->deserialize(jsonStr);
		getDeviceInfoResp(&device);
	} else if (action == FaceService::syncDevicesCreateOrUpdateDeviceAction) {
		BaseResponse baseResp;
		baseResp.deserialize(jsonStr);
		syncDevicesCreateOrUpdateDevicesResp(&baseResp);
	} else if (action == FaceService::syncRecordStranagerAction) {
		BaseResponse baseResp;
		baseResp.deserialize(jsonStr);
		syncRecordStrangerResp(&baseResp);
	} else if (action == FaceService::syncExceptionAction) {
		//异常信息
		switch (curlResultCode) {
		case CURLE_COULDNT_RESOLVE_HOST:
			cout << "无法解析主机!" << endl;
			break;
		case CURLE_COULDNT_CONNECT:
			cout << "无法连接到主机" << endl;
			break;
		case CURLE_COULDNT_RESOLVE_PROXY:
			cout << "无法解析代理" << endl;
			break;
		case CURLE_FTP_WEIRD_SERVER_REPLY:
			cout << "curl数据解析失败" << endl;
			break;
		default:
			cout << "其他错误" << curlResultCode << endl;
			break;
		}
	}

}
void FaceController::createOrUpdateDevice(){
	char ip[64] = { 0 };
	DeviceUtil::get_local_ip("eth0", ip);
	string sip(ip);
	DeviceData deviceData(DeviceUtil::getDeviceUUid(),
			DeviceUtil::getDeviceName(), sip, DeviceUtil::getDeviceType());
	string json = deviceData.serializer();
	httpRespCallback fun = respCallback;
	FaceService::getInstance()->syncDevicesCreateOrUpdateDevices(json,fun);
}

void FaceController::asyncHearbetas() {
	char ip[64] = { 0 };
	DeviceUtil::get_local_ip("eth0", ip);
	string sip(ip);
	DeviceData deviceData(DeviceUtil::getDeviceUUid(),
			DeviceUtil::getDeviceName(), sip, DeviceUtil::getDeviceType());
	string json = deviceData.serializer();
	httpRespCallback fun = respCallback;
	FaceService::getInstance()->syncHeartbeats(json, fun);
}

void FaceController::syncRecord(){
	static int asyncRecordHandTime = 0;
	asyncRecordHandTime++;
	if(asyncRecordHandTime* perSecondsAlarm > 10){
		asyncRecordHandTime = 0;

	}
}



void FaceController::cardRecordSignal(){

}

void FaceController::asyncFace() {
	static int asyncFaceHandTime = 0;
	asyncFaceHandTime++;
	if (asyncFaceHandTime * perSecondsAlarm >= 10) {
		cout << "asyncFaceHandTime >> asyncFace" << asyncFaceHandTime << endl;
		asyncFaceHandTime = 0;
		FaceDao faceDao;
		if (needClearDb) {
			//如果needClearDb 为true ,则 需要清除数据库。
			faceDao.resetOnlineDb();
			needClearDb = false;
		}
		httpRespCallback fun = respCallback;
		FaceService::getInstance()->syncFace(faceDao.getOnlineDbVersion(), fun);
	}
}

void FaceController::syncFaceResponse(SyncFaceResponse *syncFaceResp) {
	//同步数据库回调
	FaceDao faceDao;
	cout << syncFaceResp->detail << syncFaceResp->error << endl;

	if (syncFaceResp->is_latest && !syncFaceResp->error) {
		//当前已经是最后版本，不需要同步数据
		return;
	}
	if (syncFaceResp->error) {
		cout << "同步人脸错误,服务器返回信息：" << syncFaceResp->detail << endl;
		return;
	}
	//todo
	//开始同步 发送开始同步信号
	cout << "syncFaceResponse" << syncFaceResp->deleted.size() << endl;
	if (syncFaceResp->deleted.size() > 0) {
		list<string>::iterator it;
		for (it = syncFaceResp->deleted.begin();
				it != syncFaceResp->deleted.end(); it++) {
			string uuid = *it;
			cout << "删除 uuid = " << uuid << endl;
			faceDao.deleteOnLineById(uuid);
		}
	}

	if (syncFaceResp->created.size() > 0) {
		list<UserBean*>::iterator it;
		for (it = syncFaceResp->created.begin();
				it != syncFaceResp->created.end(); it++) {
			UserBean *userBean = *it;
			cout << "创建" << userBean->name << endl;

		}
	}

	if (syncFaceResp->updated.size() > 0) {
		list<UserBean*>::iterator it;
		for (it = syncFaceResp->updated.begin();
				it != syncFaceResp->updated.end(); it++) {
			UserBean *userBean = *it;
			cout << "修改" <<userBean->name << endl;

		}
	}
	faceDao.setOnLineDbVersion(syncFaceResp->current_version+"");
	//todo
	//结束同步 发送结束同步信号

}

void FaceController::addPeopleResponse(AddPeopleResponce *addPeopleResp) {
	cout << "addPeopleResponse" << addPeopleResp->detail << " "
			<< addPeopleResp->error << endl;
}

void FaceController::syncRecordResponse(BaseResponse *baseResponse) {
	cout << "syncRecordResponse " << baseResponse->detail << "  "
			<< baseResponse->error << endl;
}

void FaceController::syncHeartbeatsResp(BaseResponse *baseResponse) {
	cout << "syncResp " << baseResponse->detail << "" << endl;
}

void FaceController::getDeviceInfoResp(DeviceInfoBean *deviceInfo) {
	cout << "getDeviceInfoResp " << deviceInfo->uuid << endl;
}

void FaceController::syncRecordStrangerResp(BaseResponse *baseResponse) {
	cout << "syncRecordStrangerResp" << " " << baseResponse->detail << endl;
}

void FaceController::syncDevicesCreateOrUpdateDevicesResp(
		BaseResponse *baseResponse) {
	cout << "syncDevicesCreateOrUpdateDevicesResp " << baseResponse->detail
			<< endl;
}
FaceController::FaceController() {

}

FaceController::~FaceController() {
}

} /* namespace basemodule */
