#pragma once
/*

*/
#ifndef _DUTYRESULTDO_H_
#define _DUTYRESULTDO_H_

class DutyResultDO {
	CC_SYNTHESIZE(int, cnt, Cnt);
	CC_SYNTHESIZE(string, qdate, Qdate);
	CC_SYNTHESIZE(string, begin_time, BeginTime);
	CC_SYNTHESIZE(string, end_time, EndTime);
public:
	DutyResultDO() {
		cnt = 0;
		qdate = "";
		begin_time = "";
		end_time = "";
	}

};
// ��DutyResultDO����ָ���趨һ����������ʹ��
typedef std::shared_ptr<DutyResultDO> PtrDutyResultDO;
#endif // !_DUTYRESULTDO_H_