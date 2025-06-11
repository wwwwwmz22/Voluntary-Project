#include "PersonController.h"

#include "stdafx.h"
#include "oatpp/core/utils/ConversionUtils.hpp"
#include <iostream>
#include <sstream>
#include "../service/PersonInfoService.h"


PersonInfoJsonVO::Wrapper PersonController::executeQueryInfo(const PersonInfoQuery::Wrapper& query)
{
	//����һ��Service
	PersonInfoServer service;
	//��ѯ����
	auto result = service.getByIdAndPasword(query);
	//��Ӧ���
	auto jvo = PersonInfoJsonVO::createShared();
	jvo->success(result);
	return jvo;
}

StringJsonVO::Wrapper PersonController::execModifyInfo(const PersonBaseInfoDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();
	//�����ǿ�У��
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
	//�����ǿ�У��
	if (!dto->college||!dto->edu_background||!dto->gender||!dto->phone_number||!dto->pname||!dto->political_status||!dto->school_id||!dto->voluntary_id)
	{
		jvo->init(String(-1), RS_PARAMS_INVALID);
		return jvo;
	}
	//������ЧֵУ��
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
