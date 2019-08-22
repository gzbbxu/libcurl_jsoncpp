/*
 * FaceController.cpp
 *
 *   业务控制模块
 *  Created on: 2019年8月22日
 *      Author: zhouke
 */

#include "FaceController.h"

namespace basemodule {
void FaceController::alarm_handle(int sig) {
	/*handle_count++;
	 cout << handle_count<<endl;*/

}
void FaceController::start_timer() {
	signal(SIGALRM, alarm_handle);
	set_time();
}
void FaceController::stop_timer(){
	alarm(0);
}
void FaceController::set_time() {
	struct itimerval itv;
	itv.it_interval.tv_sec = 1; //per / 10s
	itv.it_interval.tv_usec = 0;
	itv.it_value.tv_sec = 3; // first time 5
	itv.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &itv, NULL);
	cout << "set time" << endl;

}
FaceController::FaceController() {

}

FaceController::~FaceController() {
}

} /* namespace basemodule */
