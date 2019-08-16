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
using namespace std;

class StrangerBean {
public:
	string &image;
	vector<string*> mils;
	StrangerBean(string &image) :
			image(image) {

	}
	string serializer() {
		Json::Value JSroot;
		Json::Value JSmils;
		if (!image.empty()) {
			JSroot["image"] = image;
		}
		for (int i = 0; i < mils.size(); i++) {

			JSmils[i] = *mils[i];
		}
		JSroot["mils"] = JSmils;
		string out = JSroot.toStyledString();
		return out;
	}
};
class RecordsBean {
public:
	string &uuid;
	vector<string*> mils;
	RecordsBean(string &uid) :
			uuid(uid) {

	}
	string serializer() {
		Json::Value JSroot;
		Json::Value JSuuid;
		Json::Value JSmils;
		JSroot["uuid"] = uuid;
		for (int i = 0; i < mils.size(); i++) {

			JSmils[i] = *mils[i];
		}
		JSroot["mils"] = JSmils;
		string out = JSroot.toStyledString();
		return out;
	}
};

class DeviceInfoBean {
public:
	string &uuid;
	string &name;
	string &ip;
	string &device_type;
	DeviceInfoBean(string &uid, string &name, string &ip, string &device_type) :
			uuid(uid), name(name), ip(ip), device_type(device_type) {

	}
	string serializer() {
		Json::Value JSroot;
		if (!uuid.empty()) {
			JSroot["uuid"] = uuid;
		}

		if (!name.empty()) {
			JSroot["name"] = name;
		}

		if (!ip.empty()) {
			JSroot["ip"] = ip;
		}

		if (!device_type.empty()) {
			JSroot["device_type"] = device_type;
		}
		string out = JSroot.toStyledString();
		return out;
	}

};
class DeviceData {
public:
	DeviceInfoBean *device_info;

	DeviceData(string &uid, string &name, string &ip, string &device_type) {
		device_info = new DeviceInfoBean(uid, name, ip, device_type);
	}
	string serializer() {
		Json::Value JSroot;
		JSroot["device_info"] = device_info->serializer();
		string out = JSroot.toStyledString();
		return out;
	}

};
class CardRecordData {
public:
	DeviceInfoBean *device_info;
	list<RecordsBean*> records;

	list<RecordsBean*> getRecords() {
		return records;
	}

	CardRecordData(string &uid, string &name, string &ip, string &device_type) {
		device_info = new DeviceInfoBean(uid, name, ip, device_type);
	}

	string serializer() {
		Json::Value JSroot;
		Json::Value JSrecords;
		Json::Value JSdevice_info;
		JSroot["device_info"] = device_info->serializer();
		cout << "=================" << endl;
		int i = 0;
		for (list<RecordsBean*>::iterator it = records.begin();
				it != records.end();) {
			RecordsBean *r = *it;
			string s = r->serializer();
			JSrecords[i] = s;
			it++;
			i++;
		}
		JSroot["records"] = JSrecords;
		string out = JSroot.toStyledString();
//		cout << out << endl;
		return out;

	}
	~CardRecordData() {
		for (list<RecordsBean*>::iterator it = records.begin();
				it != records.end();) {
			RecordsBean *r = *it;
			delete r;
			it++;
		}
		delete device_info;
	}
};

class FaceService {
public:
	FaceService();

	void synFace(int current_verion);

	void syncRecord(string &jsonRequest);

	void addPeople(string &name, string &position, string &imagebase64);

	void deletePeople(string &uuid);

	void syncHeartbeats(string *jsonRequest);

	void getDeviceInfo(string uuid);

	void syncDevicesCreateOrUpdateDevices(string &jsonRequest);

	void syncRecordStranger(string &jsonRequest);

	virtual ~FaceService();
};

#endif /* FACESERVICE_H_ */
