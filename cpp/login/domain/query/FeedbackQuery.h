#pragma once
/*

*/
#ifndef _FEEDBACKQUERY_H_
#define _FEEDBACKQUERY_H_

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class FeedbackQuery :public oatpp::DTO {
	//�����ʼ��
	DTO_INIT(FeedbackQuery, DTO);
	//��ѯ����
	DTO_FIELD(String, qdate);
	DTO_FIELD_INFO(qdate) {
		info->description = ZH_WORDS_GETTER("feedback.info.date");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_FEEDBACKQUERY_H_