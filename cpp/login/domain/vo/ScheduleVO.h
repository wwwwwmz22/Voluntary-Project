#pragma once
/*

*/
#ifndef _SCHEDULEVO_H_
#define _SCHEDULEVO_H_


#include "../GlobalInclude.h"
#include "../dto/ScheduleDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)
class ScheduleJsonVO :public JsonVO<ScheduleListDTO::Wrapper> {
	DTO_INIT(ScheduleJsonVO, JsonVO<ScheduleListDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SCHEDULEVO_H_