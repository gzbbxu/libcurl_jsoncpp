/*
 * HttpUtils.h
 *
 *  Created on: 2019年8月19日
 *      Author: root
 */

#include "../include/HttpUtils.h"
HttpUtils *HttpUtils::httpUtilsInstance = new HttpUtils;
string HttpUtils::baseUrl = "http://192.168.1.105/face6/TestServlet/";
HttpUtils::HttpUtils() {

	getMethod = "get";
	postMethod = "post";

	curl_global_init(CURL_GLOBAL_ALL);
	thp = threadpool_create(3, 100, 100);
	cout << "http utils gou zao ok " << thp << endl;
}
size_t HttpUtils::write_data_call(void *ptr, size_t size, size_t nmemb,
		void *stream) {
	string data((const char*) ptr, (size_t) size * nmemb);
	*((stringstream*) stream) << data << endl;
	return size * nmemb;
}
HttpUtils* HttpUtils::getInstance() {
	return HttpUtils::httpUtilsInstance;
}
void HttpUtils::freeRequest(struct Request *&request) {
	int i;
	if (request->jsonstr) {
		free(request->jsonstr);
		request->jsonstr = NULL;
	}
	if (request->url) {
		free(request->url);
		request->url = NULL;
	}

	/*if (request->entryKey) {
	 for (i = 0; i < request->entryKey->len; i++) {
	 free(request->entryKey->item[i]);
	 request->entryKey->item[i] = NULL;
	 }
	 }
	 if (request->entryValues) {
	 for (i = 0; i < request->entryValues->len; i++) {
	 free(request->entryValues->item[i]);
	 request->entryValues->item[i] = NULL;
	 }
	 }*/

}
void* HttpUtils::process(void *arg) {
//		printf("thread 0x%x working on task ",(unsigned int)pthread_self());

	cout << "working on process process task" << pthread_self() << endl;
	Request *request = (Request*) arg;
	cout << "method " << request->postmethod << endl;
	cout << "url " << request->url << endl;
	cout << "action " << request->action << endl;
	HttpUtils *httpUtil = request->httpUtil;
	int action = request->action;
	httpRespCallback fun = request->funCallBack;
//		printf("task %d is end\n",*(int *)arg);

	struct curl_slist *headers = NULL;
	CURL *curl;
	CURLcode res;
	stringstream out;
	int i;

	curl = curl_easy_init();
	//		curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.1.105:8080/register");

	curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 50);
	curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 5);
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5);
	if (request->postmethod) {
		curl_easy_setopt(curl, CURLOPT_URL, request->url);
		//post
		cout << "post post ========= post post" << endl;

		curl_easy_setopt(curl, CURLOPT_POST, 1); //post

		if (request->isKeyValue) {
			//post form
			headers =
					curl_slist_append(headers,
							"Content-TYpe:application/x-www-form-urlencoded;charset=UTF-8");

		} else {
			//post json
			headers = curl_slist_append(headers,
					"Content-TYpe:application/json;charset=UTF-8");
		}
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request->jsonstr);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(request->jsonstr));

	} else if (!request->postmethod) {
		headers = curl_slist_append(headers,
				"Content-TYpe:application/json;charset=UTF-8");

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_URL, request->url);
		cout << "get get  =========get get " << endl;
		/*	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request->jsonstr);
		 curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE,
		 strlen(request->jsonstr));*/
	}
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
	//set call balc
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_call);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
	//execute

	res = curl_easy_perform(curl);
	string json = out.str();
	cout << "execute end end " << endl;
	freeRequest(request);
	(*fun)(json, action);

	//free the list
	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);

	return NULL;
}

void HttpUtils::get(string path, map<string, string> &keys, int action,
		httpRespCallback fun) {
	path = HttpUtils::baseUrl + path;
	if (keys.size() > 0) {
		path += "?";
		int i;
		map<string, string>::iterator it;
		for (it = keys.begin(), i = 0; it != keys.end(); it++) {
			it->first;
			path += it->first;
			path += "=";
			path += it->second;
			it->second;
			i++;
			if (i < keys.size()) {
				path += "&";
			}
		}
	}
	Request *request = (Request*) malloc(sizeof(Request));
	memset(request, 0, sizeof(Request));
	request->postmethod = false;
	request->url = (char*) malloc(path.size() + 1);
	request->action = action;
	request->funCallBack = fun;

	strcpy(request->url, path.c_str());
	request->httpUtil = this;

	threadpool_add(thp, process, (void*) request);
	cout << "get -----------------66 url " << path << endl;
}
void HttpUtils::post(string path, map<string, string> &mapentry, int action,
		httpRespCallback fun) {
	path = HttpUtils::baseUrl + path;
	Request *request = (Request*) malloc(sizeof(Request));
	memset(request, 0, sizeof(Request));
	request->isKeyValue = true;
	string text;

	if (mapentry.size() > 0) {
		int i;
		map<string, string>::iterator it;
		for (it = mapentry.begin(), i = 0; it != mapentry.end(); it++) {
			it->first;
			text += it->first;
			text += "=";
			text += it->second;
			it->second;
			i++;
			if (i < mapentry.size()) {
				text += "&";
			}
		}
	}
	request->jsonstr = (char*) malloc(text.size() + 1);
	memset(request->jsonstr, 0, text.size() + 1);
	strcpy(request->jsonstr, text.c_str());

	request->postmethod = false; //= const_cast<char*>(postMethod.c_str());
	request->url = (char*) malloc(path.size() + 1);
	strcpy(request->url, path.c_str());
	request->httpUtil = this;
	request->action = action;
	request->funCallBack = fun;
	request->postmethod = true;
	threadpool_add(thp, process, (void*) request);

}
void HttpUtils::post(string path, string &jsonStr, int action,
		httpRespCallback fun) {
	path = HttpUtils::baseUrl + path;
//	init();
//		threadpool_add(thp,process,(void*)&num[i]);
//		char * method = "post";
//	const char *urlchar = jsonStr.c_str();

//		char (* arrPtr)[3] = NULL;
	Request *request = (Request*) malloc(sizeof(Request));
	memset(request, 0, sizeof(Request));

	request->postmethod = false; //= const_cast<char*>(postMethod.c_str());
	request->url = (char*) malloc(path.size() + 1);
	strcpy(request->url, path.c_str());
	request->jsonstr = (char*) malloc(jsonStr.size() + 1);
	memset(request->jsonstr, 0, jsonStr.size() + 1);
	strcpy(request->jsonstr, jsonStr.c_str());
	request->httpUtil = this;
	request->action = action;
	request->funCallBack = fun;
	request->postmethod = true;
	threadpool_add(thp, process, (void*) request);
//		request->url = (char*)malloc(sizeof(jsonStr.size()));
//		request->jsonstr= malloc(sizeof());

}
void HttpUtils::release() {
	threadpool_destroy(thp);
	thp = NULL;
	delete httpUtilsInstance;
	httpUtilsInstance = NULL;
	curl_global_cleanup();
//		 pthread_mutex_destroy(&mtx);
}

