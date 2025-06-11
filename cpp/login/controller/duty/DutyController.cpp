#include "DutyController.h"
#include "../../service/DutyService.h"



DutyJsonVO::Wrapper DutyController::executeQueryInfo(const DutyQuery::Wrapper& query)
{
	DutyService server;
	auto result = server.getInfo(query);
	auto jvo = DutyJsonVO::createShared();
	jvo->success(result);
	return jvo;
}

Uint64JsonVO::Wrapper DutyController::execAdd(const AddDutyDTO::Wrapper& dtolist)
{
	auto jvo = Uint64JsonVO::createShared();
	if (!dtolist) {
		jvo->init(UInt64(-1), RS_PARAMS_INVALID);
		return jvo;
	}

	DutyService server;
	//执行数据添加
	bool res = server.saveData(dtolist->dtolist);
	if (res)
	{
		jvo->init(UInt64(1), RS_SUCCESS);
	}
	else {
		jvo->init(UInt64(-1), RS_PARAMS_INVALID);
	}
	return jvo;
}

Uint64JsonVO::Wrapper DutyController::execUpdate(const DutyDTO::Wrapper& dto)
{
	auto jvo = Uint64JsonVO::createShared();
	if (!dto->begin_time || !dto->end_time || !dto->qdate || !dto->school_id) {
		jvo->init(UInt64(-1), RS_PARAMS_INVALID);
		return jvo;
	}
	DutyService server;
	if (server.updateData(dto))
	{
		jvo->success(UInt64(1));
	}
	else {
		jvo->fail(UInt64(-1));
	}
	return jvo;
}

Uint64JsonVO::Wrapper DutyController::execRemove(const DeleteDutyDTO::Wrapper& dto)
{
	auto jvo = Uint64JsonVO::createShared();
	if (!dto->begin_time || !dto->end_time || !dto->qdate || !dto->school_id) {
		jvo->init(UInt64(-1), RS_PARAMS_INVALID);
		return jvo;
	}
	DutyService server;
	if (server.deleteData(dto))
	{
		jvo->success(UInt64(1));
	}
	else {
		jvo->fail(UInt64(-1));
	}
	return jvo;
}

ScheduleJsonVO::Wrapper DutyController::executeQuerySchedule(const DutyQuery::Wrapper& query)
{
	DutyService server;
	auto result = server.getSchedule(query);
	auto jvo = ScheduleJsonVO::createShared();
	jvo->success(result);
	return jvo;
}
