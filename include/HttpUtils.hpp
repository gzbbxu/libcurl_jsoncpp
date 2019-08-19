/*
 * HttpUtils.h
 *
 *  Created on: 2019年8月19日
 *      Author: root
 */

#ifndef INCLUDE_HTTPUTILS_HPP_
#define INCLUDE_HTTPUTILS_HPP_
#include <string>
#include <jsoncpp/json/json.h>
#include <curl/curl.h>
#include <sstream>
#include <iostream>
#include "threadpool.h"
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;

class HttpUtils{
private :
	static HttpUtils* httpUtilsInstance;
	static pthread_mutex_t mtx;
	threadpool_t *thp;
	HttpUtils(){
		pthread_mutex_init(&mtx,NULL);
	}
public:
	static size_t write_data_call(void *ptr, size_t size, size_t nmemb, void *stream) {
		cout << "write_ data_call" << endl;
		string data((const char*) ptr, (size_t) size * nmemb);
		cout << "write_data_call" << data << endl;
		*((stringstream*) stream) << data << endl;
		return size * nmemb;
	}
	static HttpUtils* getInstance(){
		if(httpUtilsInstance!=NULL){
			return httpUtilsInstance;
		}
		pthread_mutex_lock(&mtx);
		httpUtilsInstance =  new HttpUtils;
		pthread_mutex_unlock(&mtx);
		return httpUtilsInstance;
	}

	 void init(){
		thp = threadpool_create(3,100,100);
	}

	 void get(string  url){

	}
	 void post(string url,string jsonStr){
		struct curl_slist *headers = NULL;
		CURL *curl;
		CURLcode res;
		stringstream out;
		curl = curl_easy_init();
//		curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.1.105:8080/register");
		curl_easy_setopt(curl, CURLOPT_URL, url);
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

	}
	 void release(HttpUtils ** httpUtil){
		 threadpool_destroy(thp);
		 thp = NULL;
		 delete httpUtilsInstance;
		 httpUtilsInstance = NULL;
		 *httpUtil = NULL;
//		 pthread_mutex_destroy(&mtx);
	 }
};

HttpUtils * HttpUtils::httpUtilsInstance = new HttpUtils;
HttpUtils* HttpUtils::mtx =  PTHREAD_MUTEX_INITIALIZER;

#endif /* INCLUDE_HTTPUTILS_HPP_ */
