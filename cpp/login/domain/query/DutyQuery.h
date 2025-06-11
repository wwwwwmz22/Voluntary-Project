#pragma once
/*

*/
#ifndef _DUTYQUERY_H_
#define _DUTYQUERY_H_

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class DutyQuery :public oatpp::DTO{
	//�����ʼ��
	DTO_INIT(DutyQuery, DTO);
	//��ѯ����
	DTO_FIELD(String, qdate);
	DTO_FIELD_INFO(qdate) {
		info->description = ZH_WORDS_GETTER("duty.info.date");
	}

};

#include OATPP_CODEGEN_END(DTO)
#endif // !_DUTYQUERY_H_