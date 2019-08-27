/*
 * CardRecordManager.cpp
 *
 *  Created on: 2019年8月23日
 *      Author: zhouke
 */

#include "../include/CardRecordManager.h"

namespace basemodule {

CardRecordManager::CardRecordManager() {
	//string &uid, string &name, string &ip, string &device_type
	char ip[100] = { 0 };
	int ips = DeviceUtil::get_local_ip("wlp3s0", ip);
	string strip(ip);
//	cardRecordData = new CardRecordData(DeviceUtil::getDeviceUUid().DeviceUtil::getDeviceName(), ip,DeviceUtil::getDeviceType());
	/*cardRecordData = new CardRecordData(DeviceUtil::getDeviceUUid().DeviceUtil::getDeviceName(),
	 strip,DeviceUtil::getDeviceType());*/
	; //string uid, string name, string ip, string device_type
	cardRecordData = new CardRecordData(DeviceUtil::getDeviceUUid(),
			DeviceUtil::getDeviceName(), strip, DeviceUtil::getDeviceType());

}

CardRecordManager::~CardRecordManager() {
	delete cardRecordData;
}

} /* namespace basemodule */
