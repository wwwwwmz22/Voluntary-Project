#pragma once
/*

*/
#ifndef _DUTYVO_H_
#define _DUTYVO_H_

#include "../GlobalInclude.h"
#include "../dto/DutyDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)
class DutyJsonVO:public JsonVO<DutyListDTO::Wrapper>{
	DTO_INIT(DutyJsonVO, JsonVO<DutyListDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_DUTYVO_H_