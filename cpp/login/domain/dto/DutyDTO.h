#pragma once
/*

*/
#ifndef _DUTYDTO_H_
#define _DUTYDTO_H_

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)
class DutyBaseDTO : public oatpp::DTO {
	DTO_INIT(DutyBaseDTO, DTO);
	//��ѯʱ��
	API_DTO_FIELD_DEFAULT(String, qdate, ZH_WORDS_GETTER("duty.info.date"));
	//��ʼʱ��
	API_DTO_FIELD_DEFAULT(String, begin_time, ZH_WORDS_GETTER("duty.info.begin_time"));
	//����ʱ��
	API_DTO_FIELD_DEFAULT(String, end_time, ZH_WORDS_GETTER("duty.info.end_time"));
};

class DutyCountDTO :public DutyBaseDTO {
	DTO_INIT(DutyCountDTO, DutyBaseDTO);
	//����
	API_DTO_FIELD_DEFAULT(Int64, cnt, ZH_WORDS_GETTER("duty.info.cnt"));
};

class DutyListDTO :public oatpp::DTO {
	DTO_INIT(DutyListDTO, DTO);
	API_DTO_FIELD_DEFAULT(List<DutyCountDTO::Wrapper>, list, ZH_WORDS_GETTER("duty.info.cnt"));
};

class DeleteDutyDTO : public DutyBaseDTO {
	DTO_INIT(DeleteDutyDTO, DutyBaseDTO);
	//ѧ��
	API_DTO_FIELD_DEFAULT(String, school_id, ZH_WORDS_GETTER("duty.info.school_id"));
};


class DutyDTO:public DeleteDutyDTO {
	DTO_INIT(DutyDTO, DeleteDutyDTO);
	//ǩ��
	API_DTO_FIELD_DEFAULT(Int64, sign_in, ZH_WORDS_GETTER("duty.info.sign_in"));
	//ǩ��
	API_DTO_FIELD_DEFAULT(Int64, sign_out, ZH_WORDS_GETTER("duty.info.sign_out"));
};

//������ӱ�����Ϣ
class AddDutyDTO :public oatpp::DTO {
	DTO_INIT(AddDutyDTO, DTO);
	DTO_FIELD(List<DutyDTO::Wrapper>, dtolist);
	DTO_FIELD_INFO(dtolist) {
		info->description = ZH_WORDS_GETTER("duty.info.info");
	}
};
#include OATPP_CODEGEN_END(DTO)
#endif // !_DUTYDTO_H_