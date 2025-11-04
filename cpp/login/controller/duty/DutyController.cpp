#include "DutyController.h"
#include "../../service/DutyService.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"

DutyJsonVO::Wrapper DutyController::executeQueryInfo(const DutyQuery::Wrapper& query)
{
	DutyService server;
	auto result = server.getOneInfo(query);
	auto jvo = DutyJsonVO::createShared();
	jvo->success(result);
	return jvo;
}

StringJsonVO::Wrapper DutyController::execAdd(const AddDutyDTO::Wrapper& dtolist)
{
	auto jvo = StringJsonVO::createShared();

	// 参数检查
	if (!dtolist || !dtolist->dtolist) {
		jvo->setStatus(RS_FAIL);
		jvo->data = u8"参数为空";
		return jvo;
	}

	DutyService service;
	DutyInsertResultDTO::Wrapper res = service.saveData(dtolist->dtolist);

	// 判断结果
	if (res && res->success) {
		jvo->setStatus(RS_SUCCESS);
		jvo->data = res->message;
	}
	else {
		jvo->setStatus(RS_FAIL);
		jvo->data = res->message;
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

#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>

// 用于URL编码的函数
std::string urlEncode(const std::string& value) {
	std::ostringstream escaped;
	escaped << std::hex << std::setfill('0');
	for (const char& c : value) {
		if (isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '_' || c == '.' || c == '~') {
			escaped << c;
		}
		else {
			escaped << '%' << std::uppercase << std::setw(2) << int(static_cast<unsigned char>(c));
		}
	}
	return escaped.str();
}

std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse>DutyController::execExportPeople(const DutyExportQuery::Wrapper& query)
{
	DutyService service;
	auto res = service.exportDuty(query);
	oatpp::List<DutyExportDTO::Wrapper> result = res->list;

	// 将数据写入到Excel中
	auto buff = ExcelComponent().writeVectorToBuff("Sheet1",
		[result](ExcelComponent* ex) {
			// 写入第一行标题
			// 合并单元格 C3 和 C4
			ex->mergeCells(1, 1, 1, 9);
			ex->addHeader(1, { u8"深圳志愿者（义工）服务时间统计表（用于组织管理员导入系统）" });
			ex->setAlignmentCenter(1, 1);
			
			// 写入第二行表头
			ex->addHeader(2,{
				u8"序号",
				u8"义工号",
				u8"姓名",
				u8"服务开展日期(yyyy/MM/dd)",
				u8"签到时间(HH:mm)",
				u8"签退时间(HH:mm)",
				u8"服务时长（单位:小时）",
				u8"录入人",
				u8"证明人"
				});

			// 写入数据
			int row = 3;  // 从第三行开始写入数据
			int col = 1;
			int index = 1;
			for (auto item : *(result.get())) {
				col = 1;
				ex->setCellValue(row, col++, std::to_string(index++));
				ex->setCellValue(row, col++, item->voluntary_id ? (item->voluntary_id) : "");
				ex->setCellValue(row, col++, item->name ? (item->name) : "");
				std::string date = item->date ? item->date->c_str() : "";
				std::replace(date.begin(), date.end(), '-', '/');
				ex->setCellValue(row, col++, date);
				ex->setCellValue(row, col++, item->begin_time ? (item->begin_time) : "");
				ex->setCellValue(row, col++, item->end_time ? (item->end_time) : "");
				std::ostringstream oss;
				oss << std::fixed << std::setprecision(2) << item->total_time;
				ex->setCellValue(row, col++, oss.str());
				ex->setCellValue(row, col++, "");
				ex->setCellValue(row, col++, u8"李林吉");
				ex->setRowProperties(row++);
			}
		});

	// 组装下发数据
	const char* charData = reinterpret_cast<const char*>(buff.data());
	auto fstring = String(charData, buff.size());

	// 创建响应头
	auto response = createResponse(Status::CODE_200, fstring);

	// 设置响应头信息
	response->putHeader(Header::CONTENT_TYPE, "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");

	// 对文件名进行 URL 编码
	std::string filename = u8"时光社区值班义工时统计表.xlsx";
	std::string encoded_filename = urlEncode(filename);

	// 使用 filename* 语法来支持 UTF-8 编码
	response->putHeader("Content-Disposition", "attachment; filename*=UTF-8''" + encoded_filename);

	return response;
}
