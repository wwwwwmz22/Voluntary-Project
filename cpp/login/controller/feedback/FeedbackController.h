#pragma once
/*

*/
#ifndef _FEEDBACKCONTROLLER_H_
#define _FEEDBACKCONTROLLER_H_
#include "oatpp-swagger/Types.hpp"
#include "../../../lib-oatpp/include/ApiHelper.h"
#include "../../domain/dto/FeedbackDTO.h"
#include "../../domain/query/FeedbackQuery.h"
#include "../../../lib-oatpp/include/domain/vo/BaseJsonVO.h"
#include "../../domain/vo/FeedbackVO.h"
using namespace oatpp;
#include OATPP_CODEGEN_BEGIN(ApiController)

class FeedbackController :public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(FeedbackController);
public:
	//查询违规情况
	ENDPOINT_INFO(queryFeedback) {
		//定义标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("feedback.query"));
		//定义相应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(FeedbackJsonVO);
		//定义其他参数
		API_DEF_ADD_QUERY_PARAMS(String, "qdate", ZH_WORDS_GETTER("duty.info.date"), "2025-05-15", false);
	}
	//定义查询违规情况接口端点处理
	ENDPOINT(API_M_GET, "feedback/getFeedbackInfo", queryFeedback, QUERIES(QueryParams, qdate)) {
		//解析查询参数
		API_HANDLER_QUERY_PARAM(querydate, FeedbackQuery, qdate);
		//呼叫执行函数响应结果
		API_HANDLER_RESP_VO(executeQueryInfo(querydate));
	}

	//定义新增报名信息接口描述
	API_DEF_ENDPOINT_INFO(ZH_WORDS_GETTER("feedback.add"), addInfo, Uint64JsonVO::Wrapper);
	//定义新增报名信息接口处理
	API_HANDLER_ENDPOINT(API_M_POST, "feedback/addFeedbackInfo", addInfo, BODY_DTO(FeedbackDTO::Wrapper, dto), execAdd(dto));

private:
	//查询报名信息
	FeedbackJsonVO::Wrapper executeQueryInfo(const FeedbackQuery::Wrapper& query);
	//新增报名信息
	Uint64JsonVO::Wrapper execAdd(const FeedbackDTO::Wrapper& dto);
};

#include OATPP_CODEGEN_END(ApiController)
#endif // !_FEEDBACKCONTROLLER_H_