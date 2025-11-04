#pragma once
/*

*/
#ifndef _FEEDBACKDO_H_
#define _FEEDBACKDO_H_
#include "DoInclude.h"

class FeedbackDO{
	CC_SYNTHESIZE(int, id, Id);
	CC_SYNTHESIZE(string, school_id, SchoolId);
	CC_SYNTHESIZE(string, qdate, Qdate);
	CC_SYNTHESIZE(string, pname, pName);
	CC_SYNTHESIZE(string, isclean, isClean);
	CC_SYNTHESIZE(string, isnoise, isNoise);
	CC_SYNTHESIZE(string, isfood, isFood);
	CC_SYNTHESIZE(string, isseat, isSeat);
	CC_SYNTHESIZE(string, isother, isOther);
	CC_SYNTHESIZE(string, begin_time, BeginTime);
	CC_SYNTHESIZE(string, end_time, EndTime);
public:
	FeedbackDO() {
		id = 0;
		school_id = "";
		qdate = "";
		pname = "";
		isclean = "";
		isnoise = "";
		isfood = "";
		isseat = "";
		isother = "";
		begin_time = "";
		end_time = "";
	}
};
typedef std::shared_ptr<FeedbackDO> PtrFeedbackDO;
#endif // !_FEEDBACKDO_H_