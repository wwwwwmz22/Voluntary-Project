#pragma once
/*

*/
#ifndef _DUTYCONTROLLER_H_
#define _DUTYCONTROLLER_H_
#include "oatpp-swagger/Types.hpp"
#include "../../../lib-oatpp/include/ApiHelper.h"
#include "../../domain/vo/DutyVO.h"
#include "../../domain/query/DutyQuery.h"
#include "../../domain/dto/DutyDTO.h"
#include "../../../lib-oatpp/include/domain/vo/BaseJsonVO.h"
#include "../../domain/vo/ScheduleVO.h"

using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(ApiController)
class DutyController :public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(DutyController);
public:
	//定义查询报名信息接口端点描述
	ENDPOINT_INFO(queryDuty) {
		//定义标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("duty.query"));
		//定义相应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(DutyJsonVO);
		//定义其他参数
		API_DEF_ADD_QUERY_PARAMS(String, "qdate", ZH_WORDS_GETTER("duty.info.date"), "2025-05-15", false);
	}

	//定义查询报名信息接口端点处理
	ENDPOINT(API_M_GET, "duty/getDutyInfo", queryDuty, QUERIES(QueryParams, qdate)) {
		//解析查询参数
		API_HANDLER_QUERY_PARAM(querydate, DutyQuery, qdate);
		//呼叫执行函数响应结果
		API_HANDLER_RESP_VO(executeQueryInfo(querydate));
	}

	//定义新增报名信息接口描述
	API_DEF_ENDPOINT_INFO(ZH_WORDS_GETTER("duty.add"), addInfo, Uint64JsonVO::Wrapper);
	//定义新增报名信息接口处理
	API_HANDLER_ENDPOINT(API_M_POST, "duty/addInfo", addInfo, BODY_DTO(AddDutyDTO::Wrapper, dtolist), execAdd(dtolist));


	//定义修改报名信息接口描述
	API_DEF_ENDPOINT_INFO(ZH_WORDS_GETTER("duty.update"), updateInfo, Uint64JsonVO::Wrapper);
	//定义修改报名信息接口处理
	API_HANDLER_ENDPOINT(API_M_PUT, "duty/updateInfo", updateInfo, BODY_DTO(DutyDTO::Wrapper, dto), execUpdate(dto));

	//定义删除报名信息接口描述
	API_DEF_ENDPOINT_INFO(ZH_WORDS_GETTER("duty.delete"), removeInfo, Uint64JsonVO::Wrapper);
	//定义删除报名信息接口处理
	API_HANDLER_ENDPOINT(API_M_DEL, "duty/deleteInfo", removeInfo, BODY_DTO(DeleteDutyDTO::Wrapper, dto), execRemove(dto));

	//查询值班表
	ENDPOINT_INFO(querySchedule) {
		//定义标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("duty.queryschedule"));
		//定义相应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(ScheduleJsonVO);
		//定义其他参数
		API_DEF_ADD_QUERY_PARAMS(String, "qdate", ZH_WORDS_GETTER("duty.info.date"), "2025-05-15", false);
	}

	//定义查询报名信息接口端点处理
	ENDPOINT(API_M_GET, "duty/getSehedule", querySchedule, QUERIES(QueryParams, qdate)) {
		//解析查询参数
		API_HANDLER_QUERY_PARAM(queryschedule, DutyQuery, qdate);
		//呼叫执行函数响应结果
		API_HANDLER_RESP_VO(executeQuerySchedule(queryschedule));
	}

private:
	//查询报名信息
	DutyJsonVO::Wrapper executeQueryInfo(const DutyQuery::Wrapper& query);
	//新增报名信息
	Uint64JsonVO::Wrapper execAdd(const AddDutyDTO::Wrapper& dtolist);
	//修改信息
	Uint64JsonVO::Wrapper execUpdate(const DutyDTO::Wrapper& dto);
	//取消报名信息
	Uint64JsonVO::Wrapper execRemove(const DeleteDutyDTO::Wrapper& dto);
	//查询值班表
	ScheduleJsonVO::Wrapper executeQuerySchedule(const DutyQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)
#endif // !_DUTYCONTROLLER_H_