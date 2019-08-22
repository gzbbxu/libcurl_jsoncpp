/*
 * HttpUtils.h
 *
 *  Created on: 2019年8月20日
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
#include <stdarg.h>
using namespace std;
typedef void (*httpRespCallback)(string &jsonStr, int action);
class HttpUtils;

struct Entry{
	char * item[10];
	int len;
};

struct Request {
	bool postmethod;
	bool isKeyValue;
	char *url;
	char *jsonstr;
	int action;
	HttpUtils *httpUtil;
	httpRespCallback funCallBack;
//	struct Entry * entryKey;
//	struct Entry * entryValues;
};


class HttpUtils {
private:

	HttpUtils();
public:
	threadpool_t *thp;
	string postMethod;
	string getMethod;
	static string baseUrl;
	static HttpUtils *httpUtilsInstance;

	void get(string url, map<string, string> &keys, int action,
			httpRespCallback fun);
	void post(string url, string &jsonStr, int action, httpRespCallback fun);
	void post(string url, map<string, string> &keys, int action,
			httpRespCallback fun);
	void release();
	static size_t write_data_call(void *ptr, size_t size, size_t nmemb,
			void *stream);
	static void* process(void *arg);
	static HttpUtils* getInstance();
	static  void freeRequest( struct Request* & request);

};

#endif /* INCLUDE_HTTPUTILS_HPP_ */
