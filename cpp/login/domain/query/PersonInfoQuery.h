#pragma once
/*

*/
#ifndef _PERSONINFOQUERY_H_
#define _PERSONINFOQUERY_H_

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class PersonInfoQuery :public oatpp::DTO{
	//定义初始化
	DTO_INIT(PersonInfoQuery, DTO);
	//学号
	DTO_FIELD(String, school_id);
	DTO_FIELD_INFO(school_id) {
		info->description = ZH_WORDS_GETTER("person.info.stuid");
	}
	//密码
	DTO_FIELD(String, pasword);
	DTO_FIELD_INFO(pasword) {
		info->description = ZH_WORDS_GETTER("person.info.psw");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_PERSONINFOQUERY_H_