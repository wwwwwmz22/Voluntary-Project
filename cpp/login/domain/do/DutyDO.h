/*

*/
#ifndef _DUTYDO_H_
#define _DUTYDO_H_
#include "DoInclude.h"

class DutyDO{
	CC_SYNTHESIZE(int, id, Id);
	CC_SYNTHESIZE(string, school_id, SchoolId);
	CC_SYNTHESIZE(string, qdate, Qdate);
	CC_SYNTHESIZE(string, begin_time, BeginTime);
	CC_SYNTHESIZE(string, end_time, EndTime);
	CC_SYNTHESIZE(int, sign_in, SignIn);
	CC_SYNTHESIZE(int, sign_out, SignOut);
public:
	DutyDO() {
		id = 0;
		school_id = "";
		qdate = "";
		begin_time = "";
		end_time = "";
		sign_in = 0;
		sign_out = 0;
	}
};

// 给DutyDO智能指针设定一个别名方便使用
typedef std::shared_ptr<DutyDO> PtrDutyDO;

class DeleteDutyDO {
	CC_SYNTHESIZE(string, school_id, SchoolId);
	CC_SYNTHESIZE(string, qdate, Qdate);
	CC_SYNTHESIZE(string, begin_time, BeginTime);
	CC_SYNTHESIZE(string, end_time, EndTime);
public:
	DeleteDutyDO() {
		school_id = "";
		qdate = "";
		begin_time = "";
		end_time = "";
	}
};

// 给DutyDO智能指针设定一个别名方便使用
typedef std::shared_ptr<DeleteDutyDO> PtrDeleteDutyDO;


class ScheduleDO {
	CC_SYNTHESIZE(string, qdate, Qdate);
	CC_SYNTHESIZE(string, begin_time, BeginTime);
	CC_SYNTHESIZE(string, end_time, EndTime);
	CC_SYNTHESIZE(string, pnamelist, pNamelist);
public:
	ScheduleDO() {
		qdate = "";
		begin_time = "";
		end_time = "";
		pnamelist = "";
	}
};

// 给DutyDO智能指针设定一个别名方便使用
typedef std::shared_ptr<ScheduleDO> PtrScheduleDO;

#endif // !_DUTYDO_H_