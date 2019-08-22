/*
 * FaceController.h
 *
 *  Created on: 2019年8月22日
 *      Author: root
 */

#ifndef FACECONTROLLER_H_
#define FACECONTROLLER_H_
#include <sys/time.h>
#include <signal.h>
#include <iostream>
#include <unistd.h>
using namespace std;
namespace basemodule {

class FaceController {
public:
	FaceController();
	static void alarm_handle(int singal);
	static void set_time();
	static void start_timer();
	static void stop_timer();
	virtual ~FaceController();

};

} /* namespace basemodule */

#endif /* FACECONTROLLER_H_ */
