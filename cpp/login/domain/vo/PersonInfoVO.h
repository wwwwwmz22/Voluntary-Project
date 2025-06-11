#pragma once
/*

*/
#ifndef _PERSONINFOVO_H_
#define _PERSONINFOVO_H_

#include "../GlobalInclude.h"
#include "../dto/PersonInfoDTO.h"


#include OATPP_CODEGEN_BEGIN(DTO)


/**
 * 定义用户信息显示JsonVO对象，用于响应给客户端
 */
class PersonInfoJsonVO:public JsonVO<PersonInfoDTO::Wrapper>{
	DTO_INIT(PersonInfoJsonVO,JsonVO<PersonInfoDTO::Wrapper>)
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PERSONINFOVO_H_