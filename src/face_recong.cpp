#include <iostream>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include "../include/FaceService.h"
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <sys/time.h>
#include <map>
#include <sys/time.h>
#include <signal.h>
#include "../include/HttpUtils.h"
#include "../include/modules.h"
using namespace std;
using namespace modules;

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
	int len = size * nmemb; // real length

	return 0;

}
string deviceDataSer() {
	DeviceData deviceData;
	deviceData.device_info->device_type = "in";
	deviceData.device_info->uuid = "001";
	deviceData.device_info->ip = "192.168";
	deviceData.device_info->name = "zhagn3";
	return deviceData.serializer();
}
string deviceInfoStr() {
	DeviceInfoBean deviceData;
	deviceData.device_type = "in";
	deviceData.uuid = "001";
	deviceData.ip = "192.168";
	deviceData.name = "zhagn3";
	return deviceData.serializer();
}
//test json CardRecordData
string CardRecordDataserializer() {

	string str = "222";
	string &s = str;

	string mi1 = "mi1";
	string &refmi1 = mi1;

	string mi2 = "mi2";
	string &refmi2 = mi2;

	string uid1 = "uid1";
	string &refuid1 = uid1;

	string uid2 = "uid2";
	string &refuid2 = uid2;

	string ip = "192.168.1.1";
	string &refip = ip;

	string name = "zhangsan";
	string &refname = name;

	string devicettype = "in";
	string &refDeviceTYpe = devicettype;

	CardRecordData cardRecordData(s, refname, refip, refDeviceTYpe);
	RecordsBean *r1 = new RecordsBean(uid1);
	RecordsBean *r2 = new RecordsBean(uid2);

	r1->mils.push_back(mi1);

	r2->mils.push_back(mi2);

	cardRecordData.records.push_back(r1);
	cardRecordData.records.push_back(r2);

	cout << r1->uuid << "  " << r2->uuid << endl;
	string sb = cardRecordData.serializer();
	cout << sb << endl;
	return sb;

//	cardRecordData.records;

}

//test json CardRecordData
string strangerDataserializer() {
	cout << "serializer111 serializer" << endl;
	string str = "222";
	string &s = str;

	string mi1 = "mi1";
	string &refmi1 = mi1;

	string mi2 = "mi2";
	string &refmi2 = mi2;

	string uid1 = "uid1";
	string &refuid1 = uid1;

	string uid2 = "uid2";
	string &refuid2 = uid2;

	string ip = "192.168.1.1";
	string &refip = ip;

	string name = "zhangsan";
	string &refname = name;

	string devicettype = "in";
	string &refDeviceTYpe = devicettype;

	StrangerUploadBean cardRecordData;
	StrangerBean *r1 = new StrangerBean("im1");
	StrangerBean *r2 = new StrangerBean("im2");

	r1->mils.push_back(mi1);

	r2->mils.push_back(mi2);

	cardRecordData.records.push_back(r1);
	cardRecordData.records.push_back(r2);
	cout << "serializer serializer" << endl;
	string sb = cardRecordData.serializer();
	cout << sb << endl;
	return sb;

//	cardRecordData.records;

}

string AsciiToUtf8(const string &str) {
//	return UnicodeToUtf8(AsciiToUnicode(str));
	return "";

}
//test net work
int mainnet(int argc, char **argv) {
	CURL *curl;

	CURLcode res;

	curl = curl_easy_init();

	if (curl != NULL) {
		//set curl opt
		cout << "set curl \n";
		curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	cout << "Hello world";
	return 0;
}
size_t write_data_call222(void *ptr, size_t size, size_t nmemb, void *stream) {
	cout << "write_data_call" << endl;
	string data((const char*) ptr, (size_t) size * nmemb);
	cout << "write_data_call" << data << endl;
	*((stringstream*) stream) << data << endl;
	return size * nmemb;
}
void testDeserializer(string &jsonstr) {
	cout << "sb  Deserializer  = Deserializer Deserializer" << endl;
	CardRecordData cardRecordData;
	cardRecordData.deserialize(jsonstr);
	std::string sb = cardRecordData.serializer();

	cout << "sb  testDeserializer = " << sb << endl;
}
int testPost() {

	CURL *curl;
	CURLcode res;
	char tmp_str[256] = { 0 };
	string jsonStr = CardRecordDataserializer();
	cout << "json = " << jsonStr << endl;
	struct curl_slist *headers = NULL;
	stringstream out;

	curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.1.105:8080/register");
//	cout << "===========" << endl;
//	sprintf(tmp_str,"Content-Length: %s",jsonStr.c_str());

	headers = curl_slist_append(headers,
			"Content-TYpe:application/json;charset=UTF-8");

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	curl_easy_setopt(curl, CURLOPT_POST, 1); //post

	//post json
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonStr.size());

	//set call balc
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_call222);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);

	//execute
	res = curl_easy_perform(curl);
	//free the list
	curl_slist_free_all(headers);

	//return
	string result_json = out.str();

//	cout << "result json: " << result_json <<endl;

	testDeserializer(result_json);
	curl_easy_cleanup(curl);

}
//post man
int main11(int argc, char **argv) {
//	testserializer(argc,argv);

	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);

	cout << tv.tv_sec << endl;
	testPost();

	cout << "main end " << endl;
	return 0;
}
void t(map<string, string> &map2) {

}
int main000() {
	HttpUtils *httpUtil = HttpUtils::getInstance();
	string jsonStr = CardRecordDataserializer();
	cout << "jsonStr " << jsonStr << endl;
	//	httpUtil->post("http://192.168.1.105/face6/TestServlet/syncFace",jsonStr);
	map<string, string> map;

	map["current_version"] = "0";
//	 httpUtil->get("http://192.168.1.105/face6/TestServlet/syncFace", map);
	fgetc(stdin);
	cout << "==== fgetc ===" << endl;
	return 0;

}
class A {

};
int testPostForm() {

	CURL *curl;
	CURLcode res;
	char tmp_str[256] = { 0 };
	string jsonStr;
	jsonStr = "name=zhang3";
	cout << "json = " << jsonStr << endl;
	struct curl_slist *headers = NULL;
	stringstream out;

	curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL,
			"http://192.168.1.105/face6/TestServlet/addPeople");
//	cout << "===========" << endl;
//	sprintf(tmp_str,"Content-Length: %s",jsonStr.c_str());

	headers = curl_slist_append(headers,
			"Content-TYpe:application/x-www-form-urlencoded;charset=UTF-8");

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	curl_easy_setopt(curl, CURLOPT_POST, 1); //post

	//post json
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonStr.size());

	//set call balc
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_call222);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);

	//execute
	res = curl_easy_perform(curl);
	//free the list
	curl_slist_free_all(headers);

	//return
	string result_json = out.str();

//	cout << "result json: " << result_json <<endl;

	testDeserializer(result_json);
	curl_easy_cleanup(curl);

}
int main() {
	/*string s = testserializer();
	 cout << "-------------" << endl;
	 cout << s << endl;*/

//	testDeserializer(s);
	FaceService *f = FaceService::getInstance();

	/*gouzao zhixing faceservice
	 http utils gou zao ok 0x2211bc0*/

//	f->syncFace("100");
//	string s = CardRecordDataserializer();
//	cout << "s " << s <<endl;
//	f->syncRecord(s);
	string iamge = "imagest";
//	f->addPeople("lisi","leader",iamge);
//	testPostForm();
	string s2 = deviceDataSer();
//	cout  << "s2 == " << s2 <<endl;
//	f->syncHeartbeats(s2);
//	f->getDeviceInfo("001");
	string s3 = deviceInfoStr();
//	f->syncDevicesCreateOrUpdateDevices(s3);
	string s4 = strangerDataserializer();
	cout << "s4" << s4 << endl;
	f->syncRecordStranger(s4);
	cout << "==== pause === " << endl;
//	cout << sizeof(EntryKey) << endl;
	fgetc(stdin);
	cout << "==== fgetc ===" << endl;

	cout << "main end " << endl;
	return 0;
}
void set_time() {
	struct itimerval itv;
	itv.it_interval.tv_sec = 1; //per / 10s
	itv.it_interval.tv_usec= 0;
	itv.it_value.tv_sec=5; // first time 5
	itv.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL,&itv,NULL);
	cout <<  "set time" <<endl;

}
int handle_count = 0;
void alarm_handle(int sig){
	handle_count++;
	cout << handle_count<<endl;
}
/*int main() {
	signal(SIGALRM,alarm_handle);
	set_time();
	int n = sleep(15);

	cout << " destory " << n << endl;
	alarm(0);

	return 0;
}*/

