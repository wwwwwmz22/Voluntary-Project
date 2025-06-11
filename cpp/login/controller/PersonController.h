#pragma once
/*

*/
#ifndef _PERSONCONTROLLER_H_
#define _PERSONCONTROLLER_H_

#include "oatpp-swagger/Types.hpp"
#include "../domain/vo/PersonInfoVO.h"
#include "../domain/query/PersonInfoQuery.h"
#include "../../lib-oatpp/include/domain/vo/BaseJsonVO.h"
using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(ApiController)
class PersonController:public oatpp::web::server::api::ApiController{
	//添加访问定义
	API_ACCESS_DECLARE(PersonController);
public:
	//定义查询用户信息接口端点描述
	ENDPOINT_INFO(queryUser){ 
		//定义标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("person.query"));
		//定义相应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(PersonInfoJsonVO);
		//定义其他参数
		API_DEF_ADD_QUERY_PARAMS(String, "school_id", ZH_WORDS_GETTER("person.info.stuid"), "2023000000", false);
		API_DEF_ADD_QUERY_PARAMS(String, "password", ZH_WORDS_GETTER("person.info.psw"), "", false);
	}

	//定义查询用户信息接口端点处理
	ENDPOINT(API_M_GET,"login/getUserInfo", queryUser,QUERIES(QueryParams,params)) {
		//解析查询参数
		auto query = PersonInfoQuery::createShared();
		query->school_id = params.get("school_id");
		query->pasword = params.get("password");
		//呼叫执行函数响应结果
		API_HANDLER_RESP_VO(executeQueryInfo(query));
	}


	//定义修改用户信息接口描述
	API_DEF_ENDPOINT_INFO(ZH_WORDS_GETTER("person.update"), modifyInfo, StringJsonVO::Wrapper);
	//定义修改用户信息接口处理
	API_HANDLER_ENDPOINT(API_M_PUT, "login/modifyuserinfo", modifyInfo, BODY_DTO(PersonBaseInfoDTO::Wrapper, dto), execModifyInfo(dto));

	//定义新增用户信息接口描述
	API_DEF_ENDPOINT_INFO(ZH_WORDS_GETTER("person.add"), addInfo, StringJsonVO::Wrapper);
	//定义新增用户信息接口处理
	API_HANDLER_ENDPOINT(API_M_POST, "login/adduserinfo", addInfo, BODY_DTO(PersonAllInfoDTO::Wrapper, dto), execAddUser(dto));

private:
	//查询用户信息
	PersonInfoJsonVO::Wrapper executeQueryInfo(const PersonInfoQuery::Wrapper& query);

	//修改用户信息
	StringJsonVO::Wrapper execModifyInfo(const PersonBaseInfoDTO::Wrapper& dto);

	//新增用户信息
	StringJsonVO::Wrapper execAddUser(const PersonAllInfoDTO::Wrapper& dto);
};
#include OATPP_CODEGEN_END(ApiController)
#endif // !_PERSONCONTROLLER_H_