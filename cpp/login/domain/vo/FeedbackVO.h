#pragma once
/*

*/
#ifndef _FEEDBACKVO_H_
#define _FEEDBACKVO_H_

#include "../GlobalInclude.h"
#include "../dto/FeedbackDTO.h"


#include OATPP_CODEGEN_BEGIN(DTO)


/**
 * �����û���Ϣ��ʾJsonVO����������Ӧ���ͻ���
 */
class FeedbackJsonVO :public JsonVO<FeedbackListDTO::Wrapper> {
	DTO_INIT(FeedbackJsonVO, JsonVO<FeedbackListDTO::Wrapper>)
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_FEEDBACKVO_H_