/* global apiRequest, getCurrentUser */

const MAX_COUNT = 3;
const timeSlots = [
    ["09:00", "11:00"],
    ["11:00", "13:00"],
    ["13:00", "15:00"],
    ["15:00", "17:00"],
    ["17:00", "19:00"],
    ["19:00", "21:00"],
    ["21:00", "22:00"]
];

// 缓存数据
let dutyMapCache = {};                 // key -> 已报名人数
let registeredSlotsCache = new Set();  // 当前用户已报名的时段
let currentQdate = null;

/** 判断时间段是否已经过去 */
function isPastSlot(slot, qdate) {
    const now = new Date();
    const slotStart = new Date(`${qdate}T${slot[0]}:00`);
    return now >= slotStart;
}

/** 渲染表格 */
function renderTable() {
    const tbody = document.getElementById("duty_table_body");
    if (!tbody) return;

    tbody.innerHTML = "";
    const qdate = currentQdate;

    timeSlots.forEach(slot => {
        const key = `${slot[0]}-${slot[1]}`;
        const count = dutyMapCache[key] || 0;

        let remaining = MAX_COUNT - count;
        if (remaining < 0) remaining = 0;

        const full = remaining <= 0;
        const isRegistered = registeredSlotsCache.has(key);
        const past = isPastSlot(slot, qdate);

        const remainingDisplay = past ? "已过" : String(remaining);

        // 按钮文本
        const btnText = past
            ? "已过"
            : isRegistered
                ? "已报名"
                : full ? "已满" : "报名";

        const btnDisabled = past || full || isRegistered;
        const cancelDisabled = past;

        // 按钮样式类（你CSS中需要定义以下类：btn-normal / btn-disabled / btn-registered）
        const btnClass = isRegistered
            ? "btn-registered"
            : btnDisabled ? "btn-disabled" : "btn-normal";

        // 剩余名额颜色（你CSS中已有 .past .registered .full .available）
        let remainingClass = "available";
        if (past) remainingClass = "past";
        else if (isRegistered) remainingClass = "registered";
        else if (full) remainingClass = "full";

        const tr = document.createElement("tr");
        tr.innerHTML = `
            <td class="${past ? "past" : ""}">${slot[0]} - ${slot[1]}</td>
            <td>${count}</td>
            <td class="${remainingClass}">${remainingDisplay}</td>
            <td>
                <button class="${btnClass}"
                    ${btnDisabled ? "disabled" : ""}
                    ${!btnDisabled ? `onclick="registerDuty('${qdate}','${slot[0]}','${slot[1]}')"` : ""}
                >${btnText}</button>

                <button class="cancel-btn"
                    ${cancelDisabled ? "disabled" : ""}
                    onclick="cancelDuty('${qdate}','${slot[0]}','${slot[1]}')"
                >取消报名</button>
            </td>
        `;
        tbody.appendChild(tr);
    });
}

/** 拉取数据并渲染 */
async function loadDutyInfo() {
    const qdate = document.getElementById("qdate").value;
    const user = getCurrentUser();
    if (!user || !qdate) return alert("请选择日期！");

    currentQdate = qdate;
    const tbody = document.getElementById("duty_table_body");
    tbody.innerHTML = `<tr><td colspan="4">加载中...</td></tr>`;

    try {
        // 所有人报名信息
        const resAll = await apiRequest(`/duty/getOnDayDutyInfo?qdate=${encodeURIComponent(qdate)}`);
        dutyMapCache = {};
        (resAll.data?.list || []).forEach(item => {
            const key = `${item.begin_time}-${item.end_time}`;
            dutyMapCache[key] = (dutyMapCache[key] || 0) + 1;
        });

        // 当前用户的报名信息
        const resUser = await apiRequest(`/duty/getOneDutyInfo?qdate=${encodeURIComponent(qdate)}&school_id=${encodeURIComponent(user.school_id)}`);
        registeredSlotsCache = new Set();
        (resUser.data?.list || []).forEach(item => {
            const key = `${item.begin_time}-${item.end_time}`;
            registeredSlotsCache.add(key);
        });

        renderTable();
    } catch (err) {
        console.error(err);
        tbody.innerHTML = `<tr><td colspan="4">加载失败，请重试</td></tr>`;
        alert("加载信息失败：" + (err.message || err));
    }
}

/** 报名 */
async function registerDuty(qdate, begin_time, end_time) {
    const user = getCurrentUser();
    if (!user) return alert("请先登录");

    // 检查用户得分是否达到90分
    const userScore = Number(user.score || 0);
    if (userScore < 90) {
        alert(`您的得分是 ${userScore} 分，未达到90分要求，请先去答题提高分数！`);
        return;
    }

    const key = `${begin_time}-${end_time}`;

    try {
        const dto = {
            dtolist: [
                { qdate, begin_time, end_time, school_id: user.school_id, sign_in: 0, sign_out: 0 }
            ]
        };

        const res = await apiRequest(`/duty/addInfo`, {
            method: "POST",
            body: JSON.stringify(dto)
        });

        if (res.code === 10000) {
            dutyMapCache[key] = (dutyMapCache[key] || 0) + 1;
            registeredSlotsCache.add(key);
            renderTable();
            alert("报名成功！");
        } else {
            alert("报名失败：" + res.message);
        }
    } catch (err) {
        alert("报名出错：" + err.message);
    }
}

/** 取消报名 */
async function cancelDuty(qdate, begin_time, end_time) {
    const user = getCurrentUser();
    if (!user) return alert("请先登录");

    if (!confirm("确定取消报名吗？")) return;

    const key = `${begin_time}-${end_time}`;

    try {
        const dto = { qdate, begin_time, end_time, school_id: user.school_id };
        const res = await apiRequest(`/duty/deleteInfo`, {
            method: "DELETE",
            body: JSON.stringify(dto)
        });

        if (res.code === 10000) {
            dutyMapCache[key] = Math.max(0, (dutyMapCache[key] || 0) - 1);
            registeredSlotsCache.delete(key);
            renderTable();
            alert("取消成功！");
        } else {
            alert("取消失败：" + res.message);
        }
    } catch (err) {
        alert("取消出错：" + err.message);
    }
}
