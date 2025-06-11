#pragma once
/*

*/
#ifndef _PERSONINFODO_H_
#define _PERSONINFODO_H_
#include "DoInclude.h"


class PersonInfoDO{
	CC_SYNTHESIZE(uint64_t, id, Id);
	CC_SYNTHESIZE(string, pname, pName);
	CC_SYNTHESIZE(string, school_id, SchoolId);
	CC_SYNTHESIZE(string, pasword, Pasword);
	CC_SYNTHESIZE(string, college, College);
	CC_SYNTHESIZE(string, voluntary_id, VoluntaryId);
	CC_SYNTHESIZE(string, political_status, PoliticalStatus);
	CC_SYNTHESIZE(string, phone_number, PhoneNumber);
	CC_SYNTHESIZE(uint64_t, voluntary_time, VoluntaryTime);
	CC_SYNTHESIZE(string, gender, Gender);
	CC_SYNTHESIZE(uint64_t, grade, Grade);
	CC_SYNTHESIZE(string, identity, Identity);
	CC_SYNTHESIZE(string, edu_background, EduBackground);
public:
	PersonInfoDO() {
		id = 0;
		pname = "";
		school_id = "";
		pasword = "";
		college = "";
		voluntary_id = "";
		political_status = "";
		phone_number = "";
		voluntary_time = 0;
		gender = "";
		grade = 0;
		identity = "";
		edu_background = "";
	}

};

// 给PersonInfoDO智能指针设定一个别名方便使用
typedef std::shared_ptr<PersonInfoDO> PtrPersonInfoDO;

#endif // !_PERSONINFODO_H_