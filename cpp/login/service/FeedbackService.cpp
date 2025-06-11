#include "FeedbackService.h"
#include "../dao/FeedbackDAO.h"
#include "../domain/do/FeedbackDO.h"



FeedbackListDTO::Wrapper FeedbackService::listAll(const FeedbackQuery::Wrapper& query)
{
	auto result = FeedbackListDTO::createShared();
	result->list = oatpp::List<FeedbackDTO::Wrapper>::createShared();

	FeedbackDAO dao;
	std::list<FeedbackDO> res = dao.selectWithPage(query);

	for (FeedbackDO sub: res)
	{
		auto dto = FeedbackDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, school_id, SchoolId, qdate, Qdate, pname, pName, isclean,isClean,isnoise,isNoise,isfood,isFood,isseat,isSeat,isother,isOther);
		result->list->push_back(dto);
	}
	return result;
}

bool FeedbackService::saveData(const FeedbackDTO::Wrapper& dto)
{
	FeedbackDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, SchoolId, school_id, Qdate, qdate, pName, pname, isClean,isclean,   isNoise,isnoise,  isFood,isfood, isSeat,isseat,  isOther ,isother);
	FeedbackDAO dao;
	return dao.insert(data) == 1;
}
