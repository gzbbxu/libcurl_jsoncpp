#include <iostream>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include "../include/FaceService.h"
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <sys/time.h>
#include "../include/HttpUtils.hpp"
using namespace std;

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
	int len = size * nmemb; // real length

	return 0;

}
//test json CardRecordData
string testserializer() {

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
	std::string sb = cardRecordData.serializer();
//	cout << sb <<endl;

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
size_t write_data_call(void *ptr, size_t size, size_t nmemb, void *stream) {
	cout << "write_data_call" << endl;
	string data((const char*) ptr, (size_t) size * nmemb);
	cout << "write_data_call" << data << endl;
	*((stringstream*) stream) << data << endl;
	return size * nmemb;
}
void testDeserializer(string &jsonstr) {
	CardRecordData cardRecordData;
	cardRecordData.deserialize(jsonstr);

	std::string sb = cardRecordData.serializer();

	cout << "sb  testDeserializer = " << sb << endl;
}
int testPost() {

	CURL *curl;
	CURLcode res;
	char tmp_str[256] = { 0 };
	string jsonStr = testserializer();
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
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_call);
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
int main(){
	HttpUtils * httpUtil = HttpUtils::getInstance();

	cout << httpUtil<<endl;

	httpUtil->release(&httpUtil);
	cout << httpUtil <<endl;

	int i;
	int j;
	string a ="abc";
	char * b = new char[10];
	HttpUtils * httpUtil2 = HttpUtils::getInstance();
	cout << httpUtil2 <<endl;
	cout << "main end " << endl;


	HttpUtils * httpUtil3 = HttpUtils::getInstance();
	char * c = new char[10];
	cout << httpUtil3 <<endl;
	return 0;

}

