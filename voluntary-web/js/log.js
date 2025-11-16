/* global apiRequest, dutyList */

// 当前用户信息
const currentUser = JSON.parse(localStorage.getItem("userData") || "{}");

// 页面初始化
window.onload = async () => {
  if (!currentUser || !currentUser.identity) {
    alert("无权限访问！");
    document.getElementById("view_section")?.classList.add("hidden");
    document.getElementById("add_section")?.classList.add("hidden");
    return;
  }

  const today = getTodayDate();
  document.getElementById("qdate")?.setAttribute("value", today);

  if (currentUser.identity === "admin") {
    // 管理员：显示日志表格，隐藏新增模块
    document.getElementById("add_section")?.classList.add("hidden");
    document.getElementById("view_section")?.classList.remove("hidden");
    await loadFeedback(today);
  } else {
    // 普通用户：显示新增模块，隐藏表格
    document.getElementById("view_section")?.classList.add("hidden");
    document.getElementById("add_section")?.classList.remove("hidden");
    await fillUserInfo(today);
  }

  // 绑定文本框显示控制
  ["clean", "noise", "food", "seat"].forEach(key => {
    const sel = document.getElementById(`add_is${key}`);
    const input = document.getElementById(`add_${key}_content`);
    if (!sel || !input) return;
    sel.addEventListener("change", e => {
      input.classList.toggle("hidden", e.target.value === "否");
    });
  });

  // 绑定新增按钮
  const btn = document.getElementById("btn_add_feedback");
  if (btn) btn.addEventListener("click", addFeedback);
};

// 获取今天日期字符串 yyyy-mm-dd
function getTodayDate() {
  const today = new Date();
  const yyyy = today.getFullYear();
  const mm = String(today.getMonth() + 1).padStart(2, "0");
  const dd = String(today.getDate()).padStart(2, "0");
  return `${yyyy}-${mm}-${dd}`;
}

// 管理员加载违规日志（显示时间段）
async function loadFeedback(qdate) {
  if (!qdate) return;
  const tbody = document.getElementById("feedback_table_body");
  if (!tbody) return;

  try {
    const result = await apiRequest(`/feedback/getFeedbackInfo?qdate=${encodeURIComponent(qdate)}`);
    tbody.innerHTML = "";

    const list = result.data?.list || [];
    if (list.length === 0) {
      tbody.innerHTML = `<tr><td colspan="9" style="text-align:center;">该日期暂无违规记录</td></tr>`;
      return;
    }

    list.forEach(item => {
      const tr = document.createElement("tr");
      tr.innerHTML = `
        <td>${item.qdate}</td>
        <td>${item.pname}</td>
        <td>${item.school_id}</td>
        <td>${item.begin_time} ~ ${item.end_time}</td>
        <td>${item.isclean}</td>
        <td>${item.isnoise}</td>
        <td>${item.isfood}</td>
        <td>${item.isseat}</td>
        <td>${item.isother || "无"}</td>
      `;
      tbody.appendChild(tr);
    });
  } catch (err) {
    alert("加载日志失败：" + err.message);
  }
}

// 检查是否在允许的时间段内
function isValidTimeSlot(begin_time, end_time) {
  // 时间段列表
  const timeSlots = [
    ["09:00", "11:00"],
    ["11:00", "13:00"],
    ["13:00", "15:00"],
    ["15:00", "17:00"],
    ["17:00", "19:00"],
    ["19:00", "21:00"],
    ["21:00", "22:00"]
  ];

  // 检查提交的时间段是否在允许的时间段列表中
  for (const [start, end] of timeSlots) {
    if (begin_time === start && end_time === end) {
      return true;
    }
  }

  return false;
}

// 普通用户自动填充新增表单
async function fillUserInfo(today) {
  const user = currentUser;
  if (!user) return;

  document.getElementById("add_qdate")?.setAttribute("value", today);
  document.getElementById("add_pname")?.setAttribute("value", user.pname || "");
  document.getElementById("add_school_id")?.setAttribute("value", user.school_id || "");

  let begin_time = "未知";
  let end_time = "未知";

  // 时间段列表
  const timeSlots = [
    ["09:00", "11:00"],
    ["11:00", "13:00"],
    ["13:00", "15:00"],
    ["15:00", "17:00"],
    ["17:00", "19:00"],
    ["19:00", "21:00"],
    ["21:00", "22:00"]
  ];

  const now = new Date();
  const nowMinutes = now.getHours() * 60 + now.getMinutes();

  for (const [start, end] of timeSlots) {
    const [sh, sm] = start.split(":").map(Number);
    const [eh, em] = end.split(":").map(Number);
    const startMinutes = sh * 60 + sm;
    const endMinutes = eh * 60 + em;
    if (nowMinutes >= startMinutes && nowMinutes <= endMinutes) {
      begin_time = start;
      end_time = end;
      break;
    }
  }

  document.getElementById("add_begin_time")?.setAttribute("value", begin_time);
  document.getElementById("add_end_time")?.setAttribute("value", end_time);
}

// 提交新增记录
async function addFeedback() {
  const qdate = document.getElementById("add_qdate")?.value;
  const pname = document.getElementById("add_pname")?.value;
  const school_id = document.getElementById("add_school_id")?.value;
  const begin_time = document.getElementById("add_begin_time")?.value;
  const end_time = document.getElementById("add_end_time")?.value;

  // 检查是否在允许的时间段内
  if (!isValidTimeSlot(begin_time, end_time)) {
    alert("只能在规定的值班时间段内提交违规日志！");
    return;
  }

  if (!qdate || !pname || !school_id) {
    alert("缺少必要信息！");
    return;
  }

  const data = {
    qdate,
    pname,
    school_id,
    begin_time,
    end_time,
    isclean: document.getElementById("add_isclean")?.value === "是" ? document.getElementById("add_clean_content")?.value : "否",
    isnoise: document.getElementById("add_isnoise")?.value === "是" ? document.getElementById("add_noise_content")?.value : "否",
    isfood: document.getElementById("add_isfood")?.value === "是" ? document.getElementById("add_food_content")?.value : "否",
    isseat: document.getElementById("add_isseat")?.value === "是" ? document.getElementById("add_seat_content")?.value : "否",
    isother: document.getElementById("add_isother")?.value || ""
  };

  try {
    const result = await apiRequest("/feedback/addFeedbackInfo", {
      method: "POST",
      headers: { "Content-Type": "application/json; charset=UTF-8" },
      body: JSON.stringify(data)
    });

    if (result.code === 10000) {
      alert("记录提交成功！");
      // 重置表单
      ["clean", "noise", "food", "seat"].forEach(k => {
        const sel = document.getElementById(`add_is${k}`);
        const input = document.getElementById(`add_${k}_content`);
        if (sel) sel.value = "否";
        if (input) {
          input.value = "";
          input.classList.add("hidden");
        }
      });
      document.getElementById("add_isother")?.setAttribute("value", "");
    } else {
      alert("提交失败：" + result.message);
    }
  } catch (err) {
    alert("提交失败：" + err.message);
  }
}
