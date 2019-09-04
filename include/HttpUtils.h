/*
 * HttpUtils.h
 *
 *  Created on: 2019年8月20日
 *  http 网络层接口
 *      Author: root
 */

#ifndef INCLUDE_HTTPUTILS_HPP_
#define INCLUDE_HTTPUTILS_HPP_

#include <string>
#include "json/json.h"
#include "curl/curl.h"
#include <sstream>
#include <iostream>
#include "threadpool.h"
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdarg.h>
using namespace std;
typedef void (*httpRespCallback)(string &jsonStr, int action,int curlResultCode);
class HttpUtils;

struct Entry{
	char * item[10];
	int len;
};
//请求结构体
struct Request {
	/*当前是否是post*/
	bool postmethod;
	/*当前是否是post 并且 keyvalue 的形式上传*/
	bool isKeyValue;
	/*网络最终url*/
	char *url;
	/*json 传 ，有可能也是key value 拼接*/
	char *jsonstr;
	/*请求action 作为回调到业务模块*/
	int action;
	/*http 实例*/
	HttpUtils *httpUtil;
	/*业务层回调函数 */
	httpRespCallback funCallBack;
//	struct Entry * entryKey;
//	struct Entry * entryValues;
};


class HttpUtils {
private:

	HttpUtils();
public:
	/*当前线程池结构体指针*/
	threadpool_t *thp;
	/*基本url*/
	static string baseUrl;
	static HttpUtils *httpUtilsInstance;
	/**
	 * get 请求 key&value 拼接
	 * @url  路径
	 * @keys 请求的key,value
	 * @action 业务层action
	 * @fun 业务回调接口
	 */
	void get(string url, map<string, string> &keys, int action,
			httpRespCallback fun);
	/**
	 * post 请求 json 字符串
	 * @url 路径
	 * @jsonStr 要提交的 json字符串
	 * @action 业务层action
	 * @fun 业务回调函数
	 */
	void post(string url, string &jsonStr, int action, httpRespCallback fun);
	/**
	 * post 请求 表单形式
	 * @url 路径
	 * @keys 提交的 key,value参数
	 * @action 业务层action
	 * @fun 业务层回调函数
	 */
	void post(string url, map<string, string> &keys, int action,
			httpRespCallback fun);
	void release();
	/**
	 *  接口请求成功回调
	 *  @ptr 字节开始的指针
	 *  @size 每块大小
	 *  @nmemb 块数
	 *  @stream 接受 ptr的流 指针
	 */
	static size_t write_data_call(void *ptr, size_t size, size_t nmemb,
			void *stream);
	/**
	 *  线程回调函数
	 */
	static void* process(void *arg);
	static HttpUtils* getInstance();
	/**
	 * 释放request 结构体
	 */
	static  void freeRequest( struct Request* & request);

};

#endif /* INCLUDE_HTTPUTILS_HPP_ */
