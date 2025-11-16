#pragma once
/*

*/
#ifndef _DUTYQUERY_H_
#define _DUTYQUERY_H_

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class DutyOneDayQuery :public oatpp::DTO {
	//定义初始化
	DTO_INIT(DutyOneDayQuery, DTO);
	//查询学号
	//查询日期
	DTO_FIELD(String, qdate);
	DTO_FIELD_INFO(qdate) {
		info->description = ZH_WORDS_GETTER("duty.info.date");
	}

};

class DutyQuery :public oatpp::DTO{
	//定义初始化
	DTO_INIT(DutyQuery, DTO);
	//查询学号
	DTO_FIELD(String, school_id);
	DTO_FIELD_INFO(school_id) {
		info->description = ZH_WORDS_GETTER("duty.info.school_id");
	}
	//查询日期
	DTO_FIELD(String, qdate);
	DTO_FIELD_INFO(qdate) {
		info->description = ZH_WORDS_GETTER("duty.info.date");
	}

};

class DutyExportQuery :public oatpp::DTO {
	//定义初始化
	DTO_INIT(DutyExportQuery, DTO);
	//查询开始日期
	DTO_FIELD(String, begin_date);
	DTO_FIELD_INFO(begin_date) {
		info->description = ZH_WORDS_GETTER("duty.info.begin_date");
	}
	//查询结束日期
	DTO_FIELD(String, end_date);
	DTO_FIELD_INFO(end_date) {
		info->description = ZH_WORDS_GETTER("duty.info.end_date");
	}

};

#include OATPP_CODEGEN_END(DTO)
#endif // !_DUTYQUERY_H_