/* global apiRequest, getCurrentUser */

const currentUser = getCurrentUser();

window.onload = () => {
  if (!currentUser || !currentUser.school_id) {
    alert("无权限访问");
    return;
  }

  const dateInput = document.getElementById("qdate");
  const today = new Date();
  const yyyy = today.getFullYear();
  const mm = String(today.getMonth() + 1).padStart(2, '0');
  const dd = String(today.getDate()).padStart(2, '0');
  const todayStr = `${yyyy}-${mm}-${dd}`;
  dateInput.value = todayStr;

  loadCheckinInfo(); // 页面一加载就显示当天信息
};

// 查询签到信息
async function loadCheckinInfo() {
  const qdate = document.getElementById("qdate").value;
  if (!qdate) return alert("请选择日期！");

  let url;
  if (currentUser.identity === "admin") {
    // 管理员查询当天所有人
    url = `/duty/getOnDayDutyInfo?qdate=${encodeURIComponent(qdate)}`;
  } else {
    // 普通用户查询自己的信息
    url = `/duty/getOneDutyInfo?qdate=${encodeURIComponent(qdate)}&school_id=${encodeURIComponent(currentUser.school_id)}`;
  }

  const result = await apiRequest(url);
  const tbody = document.getElementById("checkin_table_body");
  tbody.innerHTML = "";

  const list = result.data?.list || [];
  if (list.length === 0) {
    tbody.innerHTML = `<tr><td colspan="7" style="text-align:center;">暂无值班记录</td></tr>`;
    return;
  }

  list.forEach(item => {
    const signInText = item.sign_in === 1 ? "已签到" : "未签到";
    const signOutText = item.sign_out === 1 ? "已签退" : "未签退";

    let disableSignIn = "", disableSignOut = "";
    if (currentUser.identity === "admin") {
      disableSignIn = "disabled";
      disableSignOut = "disabled";
    } else {
      disableSignIn = item.sign_in === 1 ? "disabled" : "";
      disableSignOut = item.sign_out === 1 || item.sign_in === 0 ? "disabled" : "";
    }

    const tr = document.createElement("tr");
    tr.innerHTML = `
      <td>${item.school_id}</td>
      <td>${item.qdate}</td>
      <td>${item.begin_time} - ${item.end_time}</td>
      <td>${signInText}</td>
      <td>${signOutText}</td>
      <td>
        <button onclick="updateCheckin('${item.qdate}','${item.begin_time}','${item.end_time}',1,'${item.school_id}')" ${disableSignIn}>签到</button>
        <button onclick="updateCheckin('${item.qdate}','${item.begin_time}','${item.end_time}',2,'${item.school_id}')" ${disableSignOut}>签退</button>
      </td>
    `;
    tbody.appendChild(tr);
  });
}
async function updateCheckin(qdate, begin_time, end_time, type, school_id) {
  if (currentUser.identity === "admin") return;

  // 获取当前时间
  const now = new Date();

  // 构造签到/签退时间的 Date 对象
  const [bHour, bMin] = begin_time.split(':').map(Number);
  const [eHour, eMin] = end_time.split(':').map(Number);
  const [y, m, d] = qdate.split('-').map(Number);

  const startDate = new Date(y, m - 1, d, bHour, bMin);
  const endDate = new Date(y, m - 1, d, eHour, eMin);

  // 定义签到/签退允许窗口
  const signInStart = new Date(startDate.getTime() - 10 * 60 * 1000);  // 开始前10分钟
  const signInEnd = new Date(startDate.getTime() + 10 * 60 * 1000);    // 开始后10分钟
  const signOutStart = new Date(endDate.getTime() - 10 * 60 * 1000);   // 结束前10分钟
  const signOutEnd = new Date(endDate.getTime() + 10 * 60 * 1000);     // 结束后10分钟

  if (type === 1 && (now < signInStart || now > signInEnd)) {
    alert("签到只能在开始前10分钟到开始后10分钟之间进行！");
    return;
  }

  if (type === 2 && (now < signOutStart || now > signOutEnd)) {
    alert("签退只能在结束前10分钟到结束后10分钟之间进行！");
    return;
  }

  // 获取当前签到签退状态
  const tbody = document.getElementById("checkin_table_body");
  const rows = tbody.getElementsByTagName("tr");
  let currentSignIn = 0, currentSignOut = 0;

  for (let row of rows) {
    const cells = row.getElementsByTagName("td");
    if (cells[0].innerText === school_id &&
      cells[1].innerText === qdate &&
      cells[2].innerText === `${begin_time} - ${end_time}`) {
      currentSignIn = cells[3].innerText === "已签到" ? 1 : 0;
      currentSignOut = cells[4].innerText === "已签退" ? 1 : 0;
      break;
    }
  }

  if (type === 2 && currentSignIn === 0) {
    alert("请先签到，再签退！");
    return;
  }

  const dto = { qdate, begin_time, end_time, school_id, sign_in: currentSignIn, sign_out: currentSignOut };
  if (type === 1) dto.sign_in = 1;
  if (type === 2) dto.sign_out = 1;

  const result = await apiRequest("/duty/updateInfo", {
    method: "PUT",
    headers: { "Content-Type": "application/json; charset=UTF-8" },
    body: JSON.stringify(dto)
  });

  if (result.code === 10000) {
    alert(`${type === 1 ? "签到" : "签退"}成功！`);
    loadCheckinInfo();
  } else {
    alert(`${type === 1 ? "签到" : "签退"}失败：${result.message}`);
  }
}
