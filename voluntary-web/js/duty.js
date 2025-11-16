/* global apiRequest, getCurrentUser */

async function loadDutySchedule() {
  const qdate = document.getElementById("qdate").value;
  if (!qdate) return alert("请选择日期！");

  const user = getCurrentUser();
  const userName = user?.pname || "";

  const result = await apiRequest(`/duty/getSehedule?qdate=${encodeURIComponent(qdate)}`);
  const tbody = document.getElementById("schedule_table_body");
  tbody.innerHTML = "";

  // 只保留请求日期的数据
  const list = (result.data?.list || []).filter(item => item.qdate === qdate);

  if (list.length === 0) {
    tbody.innerHTML = `<tr><td colspan="3">该日期暂无值班安排</td></tr>`;
    return;
  }

  list.forEach(item => {
    const tr = document.createElement("tr");

    // 高亮当前用户名字
    let namesHtml = item.pname_list || "暂无人员";
    if (userName && item.pname_list?.includes(userName)) {
      const regex = new RegExp(`(${userName})`, "g");
      namesHtml = namesHtml.replace(regex, `<span class="highlight">$1</span>`);
    }

    tr.innerHTML = `
      <td>${item.qdate}</td>
      <td>${item.begin_time} - ${item.end_time}</td>
      <td>${namesHtml}</td>
    `;
    tbody.appendChild(tr);
  });
}