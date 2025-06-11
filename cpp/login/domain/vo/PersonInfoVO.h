#pragma once
/*

*/
#ifndef _PERSONINFOVO_H_
#define _PERSONINFOVO_H_

#include "../GlobalInclude.h"
#include "../dto/PersonInfoDTO.h"


#include OATPP_CODEGEN_BEGIN(DTO)


/**
 * �����û���Ϣ��ʾJsonVO����������Ӧ���ͻ���
 */
class PersonInfoJsonVO:public JsonVO<PersonInfoDTO::Wrapper>{
	DTO_INIT(PersonInfoJsonVO,JsonVO<PersonInfoDTO::Wrapper>)
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PERSONINFOVO_H_