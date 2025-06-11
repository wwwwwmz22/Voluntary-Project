#pragma once
/*

*/
#ifndef _FEEDBACKQUERY_H_
#define _FEEDBACKQUERY_H_

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class FeedbackQuery :public oatpp::DTO {
	//定义初始化
	DTO_INIT(FeedbackQuery, DTO);
	//查询日期
	DTO_FIELD(String, qdate);
	DTO_FIELD_INFO(qdate) {
		info->description = ZH_WORDS_GETTER("feedback.info.date");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_FEEDBACKQUERY_H_