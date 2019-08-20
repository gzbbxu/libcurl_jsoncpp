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

}
size_t HttpUtils::write_data_call(void *ptr, size_t size, size_t nmemb,
		void *stream) {
	cout << "write_ data_call" << endl;
	string data((const char*) ptr, (size_t) size * nmemb);
	cout << "write_data_call" << data << endl;
	*((stringstream*) stream) << data << endl;
	return size * nmemb;
}
HttpUtils* HttpUtils::getInstance() {
	if (HttpUtils::httpUtilsInstance != NULL) {
		return HttpUtils::httpUtilsInstance;
	}
	return NULL;
}
void* HttpUtils::process(void *arg) {
//		printf("thread 0x%x working on task ",(unsigned int)pthread_self());

	cout << "working on task" << pthread_self() << endl;
	Request *request = (Request*) arg;
	cout << request->jsonstr << endl;
	cout << request->method << endl;
	cout << request->url << endl;
	HttpUtils *httpUtil = request->httpUtil;
//		printf("task %d is end\n",*(int *)arg);

	struct curl_slist *headers = NULL;
	CURL *curl;
	CURLcode res;
	stringstream out;

	curl = curl_easy_init();

	cout << "post post ======1111=== post post" << endl;
	//		curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.1.105:8080/register");

	headers = curl_slist_append(headers,
			"Content-TYpe:application/json;charset=UTF-8");

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 50);
	curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 5);
	if (!strcmp(request->method, httpUtil->postMethod.c_str())) {
		curl_easy_setopt(curl, CURLOPT_URL, request->url);
		//post
		cout << "post post ========= post post" << endl;

		curl_easy_setopt(curl, CURLOPT_POST, 1); //post

		//post json
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request->jsonstr);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(request->jsonstr));

	} else if (strcmp(request->method, httpUtil->postMethod.c_str())) {
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
	cout << "post post ======4444=== post post" << endl;
	//free the list
	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);
	cout << "post post ======333=== post post" << endl;

	return NULL;
}

void HttpUtils::init() {
	if (!thp) {
		curl_global_init(CURL_GLOBAL_ALL);
		thp = threadpool_create(3, 100, 100);
		cout << "init thread pool " << endl;
	}

}

void HttpUtils::get(string url, map<string, string> &keys) {
	url += HttpUtils::baseUrl;
	init();
	if (keys.size() > 0) {
		url += "?";
		int i;
		map<string, string>::iterator it;
		for (it = keys.begin(), i = 0; it != keys.end(); it++) {
			it->first;
			url += it->first;
			url += "=";
			url += it->second;
			it->second;
			i++;
			if (i < keys.size()) {
				url += "&";
			}
		}
	}
	cout << "get url " << url << endl;
}
void HttpUtils::post(string url, string &jsonStr) {
	url += HttpUtils::baseUrl;
	init();
//		threadpool_add(thp,process,(void*)&num[i]);
//		char * method = "post";
	const char *urlchar = jsonStr.c_str();

//		char (* arrPtr)[3] = NULL;
	Request *request = (Request*) malloc(sizeof(Request));
	memset(request, 0, sizeof(Request));

	request->method = const_cast<char*>(postMethod.c_str());
	request->url = (char*) malloc(url.size() + 1);
	strcpy(request->url, url.c_str());
	request->jsonstr = (char*) malloc(jsonStr.size() + 1);
	memset(request->jsonstr, 0, jsonStr.size() + 1);
	strcpy(request->jsonstr, jsonStr.c_str());
	request->httpUtil = this;
	cout << "thread start" << endl;
	threadpool_add(thp, process, (void*) request);
//		request->url = (char*)malloc(sizeof(jsonStr.size()));
//		request->jsonstr= malloc(sizeof());

}
void HttpUtils::release(HttpUtils **httpUtil) {
	threadpool_destroy(thp);
	thp = NULL;
	delete httpUtilsInstance;
	httpUtilsInstance = NULL;
	*httpUtil = NULL;
	curl_global_cleanup();
//		 pthread_mutex_destroy(&mtx);
}

