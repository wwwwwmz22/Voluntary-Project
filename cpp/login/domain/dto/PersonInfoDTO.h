#pragma once

/*

*/
#ifndef _PERSONINFODTO_H_
#define _PERSONINFODTO_H_

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义显示用户信息的数据传输模型
 */
class PersonBaseInfoDTO : public oatpp::DTO {
	DTO_INIT(PersonBaseInfoDTO, DTO);
	//学号
	API_DTO_FIELD_DEFAULT(String, school_id, ZH_WORDS_GETTER("person.info.name"));
	//密码
	API_DTO_FIELD_DEFAULT(String, pasword, ZH_WORDS_GETTER("person.info.psw"));
	//姓名
	API_DTO_FIELD_DEFAULT(String, pname, ZH_WORDS_GETTER("person.info.name"));
	//手机号
	API_DTO_FIELD_DEFAULT(String, phone_number, ZH_WORDS_GETTER("person.info.phone"));
	//义工号
	API_DTO_FIELD_DEFAULT(String, voluntary_id, ZH_WORDS_GETTER("person.info.volunid"));
	//政治面貌
	API_DTO_FIELD_DEFAULT(String, political_status, ZH_WORDS_GETTER("person.info.indentity"));
};

class PersonInfoDTO:public PersonBaseInfoDTO {
	DTO_INIT(PersonInfoDTO, PersonBaseInfoDTO);
	//志愿时长
	API_DTO_FIELD_DEFAULT(UInt64, voluntary_time, ZH_WORDS_GETTER("person.info.time"));
};

class PersonAllInfoDTO :public PersonInfoDTO {
	DTO_INIT(PersonAllInfoDTO, PersonInfoDTO);
	//学院
	API_DTO_FIELD_DEFAULT(String, college, ZH_WORDS_GETTER("person.info.college"));
	//性别
	API_DTO_FIELD_DEFAULT(String, gender, ZH_WORDS_GETTER("person.info.gender"));
	//年级
	API_DTO_FIELD_DEFAULT(UInt64, grade, ZH_WORDS_GETTER("person.info.grade"));
	//学历
	API_DTO_FIELD_DEFAULT(String, edu_background, ZH_WORDS_GETTER("person.info.edubackground"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PERSONINFODTO_H_