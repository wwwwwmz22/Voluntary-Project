#include "FeedbackController.h"
#include "../../service/FeedbackService.h"



FeedbackJsonVO::Wrapper FeedbackController::executeQueryInfo(const FeedbackQuery::Wrapper& query)
{
	FeedbackService service;
	auto result = service.listAll(query);
	auto jvo = FeedbackJsonVO::createShared();
	jvo->success(result);
	return jvo;
}

Uint64JsonVO::Wrapper FeedbackController::execAdd(const FeedbackDTO::Wrapper& dto)
{
	auto jvo = Uint64JsonVO::createShared();
	if (!dto) {
		jvo->init(UInt64(-1), RS_PARAMS_INVALID);
		return jvo;
	}

	FeedbackService server;
	//执行数据添加
	bool res = server.saveData(dto);
	if (res)
	{
		jvo->init(UInt64(1), RS_SUCCESS);
	}
	else {
		jvo->init(UInt64(-1), RS_PARAMS_INVALID);
	}
	return jvo;
}
