/*
 * modules.h
 *
 *  Created on: 2019年8月21日
 *      Author: root
 */

#ifndef INCLUDE_MODULES_H_
#define INCLUDE_MODULES_H_
#include <string>
#include <list>
#include "json/json.h"
#include <iostream>
using namespace std;
namespace modules {
class BaseSerializerBean {
public:

	virtual string serializer()=0;
	virtual void deserialize(const string &json)=0;
	virtual ~BaseSerializerBean() {

	}
};

class BaseResponse: public BaseSerializerBean {
public:
	bool error;
	string detail;
	virtual void deserialize(const string &json) {
		Json::Reader reader;
		Json::Value value;
		if (reader.parse(json, value)) {
			this->error = value["error"].asBool();
			this->detail = value["detail"].asString();
		}
	}
	void deserialize(Json::Value &value) {
		this->error = value["error"].asBool();
		this->detail = value["detail"].asString();
	}
	virtual string serializer() {
		return "";
	}
};
class AddPeopleResponce: public BaseResponse {
public:
	int pk;
	string uuid;
	string name;
	string position;
	string image;
	virtual void deserialize(const string &json) {
		Json::Reader reader;
		Json::Value value;
		if (reader.parse(json, value)) {
			this->uuid = value["uuid"].asString();
			this->name = value["name"].asString();
			this->position = value["position"].asString();
			this->image = value["image"].asString();
			this->pk = value["pk"].asInt();
			BaseResponse::deserialize(value);
		}
	}
};

class UserBean: public BaseSerializerBean {
public:
	string uuid;
	string name;
	string position;
	string image;
	string character;
	UserBean() {

	}
	virtual void deserialize(const string &json) {
		Json::Reader reader;
		Json::Value value;
		if (reader.parse(json, value)) {
			this->uuid = value["uuid"].asString();
			this->name = value["name"].asString();
			this->position = value["position"].asString();
			this->image = value["image"].asString();
			this->character = value["character"].asString();
		} else {
			cout << "deserialize error UserBean" << endl;
		}

	}
	virtual string serializer() {
		Json::Value value;
		return "";
	}
};

class SyncFaceResponse: public BaseResponse {
public:
	bool is_latest;
	int current_version;
	bool clear;
	list<UserBean*> created;
	list<UserBean*> updated;
	list<string> deleted;
	virtual void deserialize(const string &json) {

		Json::Reader reader;
		Json::Value value;
		if (reader.parse(json, value)) {
			this->is_latest = value["is_latest"].asBool();
			this->current_version = value["current_version"].asInt();
			this->clear = value["clear"].asBool();
			this->error = value["error"].asBool();
			this->detail = value["detail"].asString();
			BaseResponse::deserialize(value);
			Json::Value createdValue = value["created"];
			Json::Value updatedalue = value["updated"];
			Json::Value deletedValue = value["deleted"];

			if (!createdValue.isNull() && createdValue.size() > 0) {
				int i;
				for (i = 0; i < createdValue.size(); i++) {
					UserBean *userBean = new UserBean;
					userBean->deserialize(createdValue[i].toStyledString());

					created.push_back(userBean);
				}
			}

			if (!updatedalue.isNull() && updatedalue.size() > 0) {
				int i;
				for (i = 0; i < updatedalue.size(); i++) {
					UserBean *userBean = new UserBean;
					userBean->deserialize(updatedalue[i].toStyledString());

					updated.push_back(userBean);
				}
			}
			if (!deletedValue.isNull() && deletedValue.size() > 0) {
				int i;
				for (i = 0; i < deletedValue.size(); i++) {
					deleted.push_back(deletedValue[i].asString());
				}
			}
		} else {
			cout << "SyncFaceResponce deserialize error" << endl;
		}

	}
	virtual string serializer() {
		Json::Value value;
		return "";
	}
	~SyncFaceResponse() {
		for (list<UserBean*>::iterator it = created.begin();
				it != created.end(); it++) {
			UserBean *r = *it;
			delete r;
		}

		for (list<UserBean*>::iterator it = updated.begin();
				it != updated.end(); it++) {
			UserBean *r = *it;
			delete r;
		}

	}
};

class StrangerBean: public BaseSerializerBean {
public:
	string image;
	vector<string> mils;
	StrangerBean(string image) :
			image(image) {

	}
	StrangerBean() {
		image = "";
	}

	virtual void deserialize(const string &json) {
		Json::Reader reader;
		Json::Value value;
		if (reader.parse(json, value)) {
			this->image = value["image"].asString();
			Json::Value milsValue = value["mils"];
			if (!milsValue.isNull() && milsValue.size() > 0) {
				int i;
				for (i = 0; i < milsValue.size(); i++) {
					string s = milsValue[i].asString();
					this->mils.push_back(s);
				}
			}
		}
	}
	virtual string serializer() {
		Json::Value JSroot;
		Json::Value JSmils;
		if (!image.empty()) {
			JSroot["image"] = image;
		}
		for (int i = 0; i < mils.size(); i++) {

			JSmils[i] = mils[i];
		}
		JSroot["mils"] = JSmils;
		string out = JSroot.toStyledString();
		return out;
	}
};
class StrangerUploadBean: public BaseSerializerBean {
public:
	list<StrangerBean*> records;
	list<StrangerBean*>& getStrangerList() {
		return records;
	}

	virtual void deserialize(const string &json) {
		Json::Reader reader;
		Json::Value value;
		if (reader.parse(json, value)) {
			Json::Value recordsValue = value["records"];
			if (!recordsValue.isNull() && recordsValue.size() > 0) {
				int i;
				for (i = 0; i < recordsValue.size(); i++) {
					StrangerBean *recordBean = new StrangerBean;
					recordBean->deserialize(recordsValue[i].toStyledString());

					records.push_back(recordBean);
				}
			}
		} else {
			cout << "deserialize error" << endl;
		}
	}
	virtual string serializer() {
		Json::Value JSroot;
		Json::Value JSrecords;
		Json::Reader JSreade;
		int i = 0;
		for (list<StrangerBean*>::iterator it = records.begin();
				it != records.end();) {
			StrangerBean *r = *it;
			Json::Value JSItem;
			JSreade.parse(r->serializer(), JSItem);
			JSrecords[i] = JSItem;
			it++;
			i++;
		}
		JSroot["records"] = JSrecords;

		string out = JSroot.toStyledString();
		return out;
	}
};
class RecordsBean: public BaseSerializerBean {
public:
	string uuid;
	vector<string> mils;
	RecordsBean(string uid) :
			uuid(uid) {

	}
	RecordsBean() {
		uuid = "";
	}
	virtual string serializer() {
		Json::Value JSroot;
		Json::Value JSuuid;
		Json::Value JSmils;
		JSroot["uuid"] = uuid;
		for (int i = 0; i < mils.size(); i++) {

			JSmils[i] = mils[i];
		}
		JSroot["mils"] = JSmils;
		return JSroot.toStyledString();
	}
	virtual void deserialize(const string &json) {
		Json::Reader reader;
		Json::Value value;
		if (reader.parse(json, value)) {
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

	}
};

class DeviceInfoBean: public BaseSerializerBean {
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
	virtual string serializer() {
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
//		cout<< "out >> device " << out << endl;
		return out;
	}

	virtual void deserialize(const string &json) {
		Json::Reader reader;
		Json::Value value;
		if (reader.parse(json, value)) {
			this->ip = value["ip"].asString();
			this->name = value["name"].asString();
			this->device_type = value["device_type"].asString();
			this->uuid = value["uuid"].asString();
		} else {
			cout << "deserialize DeviceInfoBean error" << endl;
		}

	}

};
class DeviceData: public BaseSerializerBean {
public:
	DeviceInfoBean *device_info;

	DeviceData(string uid, string name, string ip, string device_type) {
		device_info = new DeviceInfoBean(uid, name, ip, device_type);
	}
	DeviceData() {
		device_info = new DeviceInfoBean;
	}
	virtual string serializer() {
		Json::Value JSroot;
		Json::Reader reader;
		Json::Value jsDeviceInfo;
		reader.parse(device_info->serializer(), jsDeviceInfo);
		JSroot["device_info"] = jsDeviceInfo;
		string out = JSroot.toStyledString();
		return out;
	}

	virtual void deserialize(const string &json) {

	}
	~DeviceData() {
		delete device_info;
	}

};
class CardRecordData: public BaseSerializerBean {
public:
	DeviceInfoBean *device_info;
	list<RecordsBean*> records;

	list<RecordsBean*> getRecords() {
		return records;
	}

	CardRecordData(string uid, string name, string ip, string device_type) {
		device_info = new DeviceInfoBean(uid, name, ip, device_type);
	}

	CardRecordData() {
		device_info = new DeviceInfoBean;
	}

	void clear() {
		for (list<RecordsBean*>::iterator it = records.begin();
				it != records.end(); it++) {
			RecordsBean *r = *it;
			delete r;
		}
	}

	virtual void deserialize(const string &json) {
		Json::Reader reader;
		Json::Value value;
		if (reader.parse(json, value)) {
			Json::Value deviceInfoValue = value["device_info"];
			Json::Value recordsValue = value["records"];
			if (!deviceInfoValue.isNull()) {
				device_info->deserialize(deviceInfoValue.toStyledString());
			}
			if (!recordsValue.isNull() && recordsValue.size() > 0) {
				int i;
				for (i = 0; i < recordsValue.size(); i++) {
					RecordsBean *recordBean = new RecordsBean;
					recordBean->deserialize(recordsValue[i].toStyledString());

					records.push_back(recordBean);
				}
			}
		} else {
			cout << "deserialize error" << endl;
		}

	}
	virtual string serializer() {
		Json::Value JSroot;
		Json::Value JSrecords;
		Json::Value JSdeviceInfo;
		Json::Reader JSreade;
//		Json::Reader JSItemReader;
		JSreade.parse(device_info->serializer(), JSdeviceInfo);
		JSroot["device_info"] = JSdeviceInfo;
		int i = 0;
		for (list<RecordsBean*>::iterator it = records.begin();
				it != records.end();) {
			RecordsBean *r = *it;
			Json::Value item;

			JSreade.parse(r->serializer(), item);
			JSrecords[i] = item;
			it++;
			i++;
		}
		JSroot["records"] = JSrecords;

		string out = JSroot.toStyledString();
		return out;

	}
	virtual ~CardRecordData() {
		clear();
		delete device_info;
	}
};
}

#endif /* INCLUDE_MODULES_H_ */
