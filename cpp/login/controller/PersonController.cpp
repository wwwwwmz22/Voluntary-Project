#include "PersonController.h"

#include "stdafx.h"
#include "oatpp/core/utils/ConversionUtils.hpp"
#include <iostream>
#include <sstream>
#include "../service/PersonInfoService.h"


PersonInfoJsonVO::Wrapper PersonController::executeQueryInfo(const PersonInfoQuery::Wrapper& query)
{
	//定义一个Service
	PersonInfoServer service;
	//查询数据
	auto result = service.getByIdAndPasword(query);
	//响应结果
	auto jvo = PersonInfoJsonVO::createShared();
	jvo->success(result);
	return jvo;
}

StringJsonVO::Wrapper PersonController::execModifyInfo(const PersonBaseInfoDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();
	//参数非空校验
	if (!dto->phone_number||!dto->pname||!dto->political_status||!dto->school_id||!dto->voluntary_id)
	{
		jvo->init(String(-1), RS_PARAMS_INVALID);
		return jvo;
	}

	PersonInfoServer service;
	if (service.updateData(dto)) {
		jvo->success(dto->school_id);
	}
	else {
		jvo->fail(dto->school_id);
	}
	return jvo;
}

StringJsonVO::Wrapper PersonController::execAddUser(const PersonAllInfoDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();
	//参数非空校验
	if (!dto->college||!dto->edu_background||!dto->gender||!dto->phone_number||!dto->pname||!dto->political_status||!dto->school_id||!dto->voluntary_id)
	{
		jvo->init(String(-1), RS_PARAMS_INVALID);
		return jvo;
	}
	//参数有效值校验
	/*if (dto->grade<0)
	{
		jvo->init(String(-1), RS_PARAMS_INVALID);
		return jvo;
	}*/
	PersonInfoServer service;
	if (service.saveData(dto)) {
		jvo->success(dto->school_id);
	}
	else {
		jvo->fail(dto->school_id);
	}
	return jvo;
}
