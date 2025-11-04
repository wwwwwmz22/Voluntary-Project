#pragma once
/*

*/
#ifndef _DUTYRESULTDO_H_
#define _DUTYRESULTDO_H_

class DutyResultDO {
	CC_SYNTHESIZE(string, school_id, SchoolId);
	CC_SYNTHESIZE(string, qdate, Qdate);
	CC_SYNTHESIZE(string, begin_time, BeginTime);
	CC_SYNTHESIZE(string, end_time, EndTime);
	CC_SYNTHESIZE(int, sign_in, SignIn);
	CC_SYNTHESIZE(int, sign_out, SignOut);
public:
	DutyResultDO() {
		school_id = "";
		qdate = "";
		begin_time = "";
		end_time = "";
		sign_in = 0;
		sign_out = 0;
	}

};
// 给DutyResultDO智能指针设定一个别名方便使用
typedef std::shared_ptr<DutyResultDO> PtrDutyResultDO;
#endif // !_DUTYRESULTDO_H_