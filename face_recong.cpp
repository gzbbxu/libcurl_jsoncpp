#include <iostream>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include "include/FaceService.h"
using namespace std;

size_t write_data(void *ptr,size_t size  ,size_t nmemb ,void * stream){
	int len = size* nmemb;// real length

	return 0;

}
//test json CardRecordData
int main(int argc, char **argv) {


	string str ="222";
	string & s = str;

	string mi1 = "mi1";
	string &refmi1 = mi1;


	string mi2 = "mi2";
	string &refmi2 = mi2;


	string uid1 = "uid1";
		string &refuid1 = uid1;


		string uid2 = "uid2";
		string &refuid2 = uid2;

		string ip = "192.168.1.1";
		string & refip = ip;

		string name = "zhangsan";
		string & refname = name;

		string devicettype = "in";
		string & refDeviceTYpe = devicettype;

		CardRecordData  cardRecordData(s,refname,refip,refDeviceTYpe);
		RecordsBean r1(uid1);
		RecordsBean r2(uid2);
//	cardRecordData.device_info.uuid = "1111";


	r1.mils.push_back(&mi1);


	r2.mils.push_back(&mi2);


	cardRecordData.records.push_back(&r1);
	cardRecordData.records.push_back(&r2);

	cout << r1.uuid << "  "<<r2.uuid<<endl;
	std::string sb  = cardRecordData.serializer();
	cout << sb <<endl;

	return 0;

//	cardRecordData.records;

}

//test net work
int mainnet(int argc, char **argv) {
	CURL * curl;

	CURLcode res;

	curl = curl_easy_init();

	if(curl !=NULL){
		//set curl opt
		cout << "set curl \n";
		curl_easy_setopt(curl,CURLOPT_URL,"http://www.baidu.com");
		curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_data);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	cout << "Hello world";
	return 0;
}
