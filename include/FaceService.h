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
	string uuid;
	vector<string> mils;
	RecordsBean(string uid) :
			uuid(uid) {

	}
	RecordsBean() {
		uuid = "";
	}
	Json::Value serializer() {
		Json::Value JSroot;
		Json::Value JSuuid;
		Json::Value JSmils;
		JSroot["uuid"] = uuid;
		for (int i = 0; i < mils.size(); i++) {

			JSmils[i] = mils[i];
		}
		JSroot["mils"] = JSmils;
//		string out = JSroot.toStyledString();
		return JSroot;
	}
	void deserialize(const Json::Value &value) {
		this->uuid = value["uuid"].asString();
		Json::Value milsValue = value["mils"];
		if (!milsValue.isNull() && milsValue.size() > 0) {
			int i;
			for (i = 0; i < milsValue.size(); i++) {
				string s = milsValue[i].asString();
				this->mils.push_back(s);
			}
		}
	}
};

class DeviceInfoBean {
public:
	string uuid;
	string name;
	string ip;
	string device_type;
	DeviceInfoBean(string uid, string name, string ip, string device_type) :
			uuid(uid), name(name), ip(ip), device_type(device_type) {

	}
	DeviceInfoBean() {
		uuid = "";
		name = "";
		ip = "";
		device_type = "";
	}
	Json::Value serializer() {
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
		return JSroot;
	}
	void deserialize(const Json::Value &value) {

		this->ip = value["ip"].asString();
		this->name = value["name"].asString();
		this->device_type = value["device_type"].asString();
		this->uuid = value["uuid"].asString();
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

	CardRecordData() {
		device_info = new DeviceInfoBean;
	}

	void deserialize(const string &json) {
		Json::Reader reader;
		Json::Value value;
		if (reader.parse(json, value)) {
			Json::Value deviceInfoValue = value["device_info"];
			Json::Value recordsValue = value["records"];
			if (!deviceInfoValue.isNull()) {
				device_info->deserialize(deviceInfoValue);
			}
			if (!recordsValue.isNull() && recordsValue.size() > 0) {
				/*cout << "recordsValue " << recordsValue[0] << "size = "
						<< recordsValue.size() << endl;*/
				int i;
				for (i = 0; i < recordsValue.size(); i++) {
					/*
					 string uuidValueStr = recordsValue[i]["uuid"].asString();
					 RecordsBean * recordBean = new RecordsBean(uuidValueStr);
					 recordBean->uuid = uuidValueStr;*/
					RecordsBean *recordBean = new RecordsBean;
					recordBean->deserialize(recordsValue[i]);

					records.push_back(recordBean);
				}
			}

		} else {
			cout << "parse error " << endl;
		}
	}
	string serializer() {
		Json::Value JSroot;
		Json::Value JSrecords;
		Json::Value JSdevice_info;
		JSroot["device_info"] = device_info->serializer();
		int i = 0;
		for (list<RecordsBean*>::iterator it = records.begin();
				it != records.end();) {
			RecordsBean *r = *it;
//			string s = "test";
			JSrecords[i] = r->serializer();
			;
			it++;
			i++;
		}
		JSroot["records"] = JSrecords;
		string out = JSroot.toStyledString();
		return out;

	}
	~CardRecordData() {
		for (list<RecordsBean*>::iterator it = records.begin();
				it != records.end(); it++) {
			RecordsBean *r = *it;
			delete r;
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
