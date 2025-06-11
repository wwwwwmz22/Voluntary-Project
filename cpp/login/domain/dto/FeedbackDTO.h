#pragma once
/*

*/
#ifndef _FEEDBACKDTO_H_
#define _FEEDBACKDTO_H_
#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)


class FeedbackDTO : public oatpp::DTO {
	DTO_INIT(FeedbackDTO, DTO);
	//��ѯʱ��
	API_DTO_FIELD_DEFAULT(String, qdate, ZH_WORDS_GETTER("feedback.info.qdate"));
	//����
	API_DTO_FIELD_DEFAULT(String, pname, ZH_WORDS_GETTER("feedback.info.pname"));
	//ѧ��
	API_DTO_FIELD_DEFAULT(String, school_id, ZH_WORDS_GETTER("feedback.info.stuid"));
	//�������
	API_DTO_FIELD_DEFAULT(String, isclean, ZH_WORDS_GETTER("feedback.info.isclean"));
	//�����������
	API_DTO_FIELD_DEFAULT(String, isnoise, ZH_WORDS_GETTER("feedback.info.isnoise"));
	//�Զ������
	API_DTO_FIELD_DEFAULT(String, isfood, ZH_WORDS_GETTER("feedback.info.isfood"));
	//ռ�����
	API_DTO_FIELD_DEFAULT(String, isseat, ZH_WORDS_GETTER("feedback.info.isseat"));
	//�������
	API_DTO_FIELD_DEFAULT(String, isother, ZH_WORDS_GETTER("feedback.info.isother"));
};

class FeedbackListDTO :public oatpp::DTO {
	DTO_INIT(FeedbackListDTO, DTO);
	API_DTO_FIELD_DEFAULT(List<FeedbackDTO::Wrapper>, list, ZH_WORDS_GETTER("feedback.info.list"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_FEEDBACKDTO_H_