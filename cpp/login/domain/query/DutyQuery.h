#pragma once
/*

*/
#ifndef _DUTYQUERY_H_
#define _DUTYQUERY_H_

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class DutyQuery :public oatpp::DTO{
	//定义初始化
	DTO_INIT(DutyQuery, DTO);
	//查询日期
	DTO_FIELD(String, qdate);
	DTO_FIELD_INFO(qdate) {
		info->description = ZH_WORDS_GETTER("duty.info.date");
	}

};

#include OATPP_CODEGEN_END(DTO)
#endif // !_DUTYQUERY_H_