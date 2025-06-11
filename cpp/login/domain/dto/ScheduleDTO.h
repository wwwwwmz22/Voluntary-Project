#pragma once
/*

*/
#ifndef _SCHEDULEDTO_H_
#define _SCHEDULEDTO_H_
#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)
class ScheduleDTO :public oatpp::DTO {
	DTO_INIT(ScheduleDTO, DTO);

	//查询时间
	API_DTO_FIELD_DEFAULT(String, qdate, ZH_WORDS_GETTER("duty.info.date"));
	//开始时间
	API_DTO_FIELD_DEFAULT(String, begin_time, ZH_WORDS_GETTER("duty.info.begin_time"));
	//结束时间
	API_DTO_FIELD_DEFAULT(String, end_time, ZH_WORDS_GETTER("duty.info.end_time"));
	//姓名列表
	API_DTO_FIELD_DEFAULT(String, pname_list, ZH_WORDS_GETTER("duty.info.pname_list"));
};

class ScheduleListDTO :public oatpp::DTO {
	DTO_INIT(ScheduleListDTO, DTO);
	API_DTO_FIELD_DEFAULT(List<ScheduleDTO::Wrapper>, list, ZH_WORDS_GETTER("duty.info.schedulecnt"));
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_SCHEDULEDTO_H_