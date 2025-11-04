#pragma once
/*

*/
#ifndef _DUTYDTO_H_
#define _DUTYDTO_H_

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)
class DutyBaseDTO : public oatpp::DTO {
	DTO_INIT(DutyBaseDTO, DTO);
	//查询时间
	API_DTO_FIELD_DEFAULT(String, qdate, ZH_WORDS_GETTER("duty.info.date"));
	//开始时间
	API_DTO_FIELD_DEFAULT(String, begin_time, ZH_WORDS_GETTER("duty.info.begin_time"));
	//结束时间
	API_DTO_FIELD_DEFAULT(String, end_time, ZH_WORDS_GETTER("duty.info.end_time"));
};

class DutyCountDTO :public DutyBaseDTO {
	DTO_INIT(DutyCountDTO, DutyBaseDTO);
	//学号
	API_DTO_FIELD_DEFAULT(String, school_id, ZH_WORDS_GETTER("duty.info.school_id"));
	//签到
	API_DTO_FIELD_DEFAULT(Int64, sign_in, ZH_WORDS_GETTER("duty.info.sign_in"));
	//签退
	API_DTO_FIELD_DEFAULT(Int64, sign_out, ZH_WORDS_GETTER("duty.info.sign_out"));
};

class DutyListDTO :public oatpp::DTO {
	DTO_INIT(DutyListDTO, DTO);
	API_DTO_FIELD_DEFAULT(List<DutyCountDTO::Wrapper>, list, ZH_WORDS_GETTER("duty.info.cnt"));
};

class DeleteDutyDTO : public DutyBaseDTO {
	DTO_INIT(DeleteDutyDTO, DutyBaseDTO);
	//学号
	API_DTO_FIELD_DEFAULT(String, school_id, ZH_WORDS_GETTER("duty.info.school_id"));
};


class DutyDTO:public DeleteDutyDTO {
	DTO_INIT(DutyDTO, DeleteDutyDTO);
	//签到
	API_DTO_FIELD_DEFAULT(Int64, sign_in, ZH_WORDS_GETTER("duty.info.sign_in"));
	//签退
	API_DTO_FIELD_DEFAULT(Int64, sign_out, ZH_WORDS_GETTER("duty.info.sign_out"));
};

//批量添加报名信息
class AddDutyDTO :public oatpp::DTO {
	DTO_INIT(AddDutyDTO, DTO);
	DTO_FIELD(List<DutyDTO::Wrapper>, dtolist);
	DTO_FIELD_INFO(dtolist) {
		info->description = ZH_WORDS_GETTER("duty.info.info");
	}
};

//报名返回参数信息
class DutyInsertResultDTO : public oatpp::DTO {
	DTO_INIT(DutyInsertResultDTO, DTO)

	DTO_FIELD(Boolean, success);  // 是否成功
	DTO_FIELD(String, message);   // 提示信息
};

//导出详细数据
class DutyExportDTO :public oatpp::DTO {
	DTO_INIT(DutyExportDTO, DTO);
	//义工号
	DTO_FIELD(String, voluntary_id);
	DTO_FIELD_INFO(voluntary_id) {
		info->description = ZH_WORDS_GETTER("duty.excel.voluntary_id");
	}
	//姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("duty.excel.name");
	}
	//服务日期
	DTO_FIELD(String, date);
	DTO_FIELD_INFO(date) {
		info->description = ZH_WORDS_GETTER("duty.excel.date");
	}
	//签到时间
	DTO_FIELD(String, begin_time);
	DTO_FIELD_INFO(begin_time) {
		info->description = ZH_WORDS_GETTER("duty.excel.begin_time");
	}
	//签退时间
	DTO_FIELD(String, end_time);
	DTO_FIELD_INFO(end_time) {
		info->description = ZH_WORDS_GETTER("duty.excel.end_time");
	}
	//服务时长
	DTO_FIELD(Float64, total_time);
	DTO_FIELD_INFO(total_time) {
		info->description = ZH_WORDS_GETTER("duty.excel.total_time");
	}

};

class DutyExportListDTO :public oatpp::DTO {
	DTO_INIT(DutyExportListDTO, DTO);
	API_DTO_FIELD_DEFAULT(List<DutyExportDTO::Wrapper>, list, ZH_WORDS_GETTER("duty.excel.list"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_DUTYDTO_H_