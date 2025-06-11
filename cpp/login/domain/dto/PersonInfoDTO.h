#pragma once

/*

*/
#ifndef _PERSONINFODTO_H_
#define _PERSONINFODTO_H_

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * ������ʾ�û���Ϣ�����ݴ���ģ��
 */
class PersonBaseInfoDTO : public oatpp::DTO {
	DTO_INIT(PersonBaseInfoDTO, DTO);
	//ѧ��
	API_DTO_FIELD_DEFAULT(String, school_id, ZH_WORDS_GETTER("person.info.name"));
	//����
	API_DTO_FIELD_DEFAULT(String, pasword, ZH_WORDS_GETTER("person.info.psw"));
	//����
	API_DTO_FIELD_DEFAULT(String, pname, ZH_WORDS_GETTER("person.info.name"));
	//�ֻ���
	API_DTO_FIELD_DEFAULT(String, phone_number, ZH_WORDS_GETTER("person.info.phone"));
	//�幤��
	API_DTO_FIELD_DEFAULT(String, voluntary_id, ZH_WORDS_GETTER("person.info.volunid"));
	//������ò
	API_DTO_FIELD_DEFAULT(String, political_status, ZH_WORDS_GETTER("person.info.indentity"));
};

class PersonInfoDTO:public PersonBaseInfoDTO {
	DTO_INIT(PersonInfoDTO, PersonBaseInfoDTO);
	//־Ըʱ��
	API_DTO_FIELD_DEFAULT(UInt64, voluntary_time, ZH_WORDS_GETTER("person.info.time"));
};

class PersonAllInfoDTO :public PersonInfoDTO {
	DTO_INIT(PersonAllInfoDTO, PersonInfoDTO);
	//ѧԺ
	API_DTO_FIELD_DEFAULT(String, college, ZH_WORDS_GETTER("person.info.college"));
	//�Ա�
	API_DTO_FIELD_DEFAULT(String, gender, ZH_WORDS_GETTER("person.info.gender"));
	//�꼶
	API_DTO_FIELD_DEFAULT(UInt64, grade, ZH_WORDS_GETTER("person.info.grade"));
	//ѧ��
	API_DTO_FIELD_DEFAULT(String, edu_background, ZH_WORDS_GETTER("person.info.edubackground"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PERSONINFODTO_H_