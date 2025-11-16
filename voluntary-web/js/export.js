/* global backendUrl */

// 页面加载时验证是否管理员
window.onload = function () {
  const user = JSON.parse(localStorage.getItem("userData") || "{}");

  if (!user || !user.identity) {
    showNoPermission();
    return;
  }

  if (user.identity !== "admin") {
    showNoPermission();
  } else {
    document.getElementById("adminContent").style.display = "block";
  }
};

function showNoPermission() {
  document.getElementById("noPermission").style.display = "block";
}


// ================= 导出义工时长表 =================
async function exportVolunteerHours() {
  const beginDate = document.getElementById("begin_date").value;
  const endDate = document.getElementById("end_date").value;
  const resultBox = document.getElementById("export_result");

  if (!beginDate || !endDate) {
    alert("请先选择开始和结束日期！");
    return;
  }

  const exportUrl = `${backendUrl}/duty/export?begin_date=${encodeURIComponent(beginDate)}&end_date=${encodeURIComponent(endDate)}`;

  try {
    const response = await fetch(exportUrl, { method: "POST" });

    if (!response.ok) {
      resultBox.innerHTML = `<p style="color:#e74c3c;">❌ 导出失败：服务器返回 ${response.status}</p>`;
      return;
    }

    // 处理文件流
    const blob = await response.blob();
    const url = window.URL.createObjectURL(blob);

    const a = document.createElement("a");
    a.href = url;
    a.download = `义工时表_${beginDate}_至_${endDate}.xlsx`;
    document.body.appendChild(a);
    a.click();
    a.remove();
    window.URL.revokeObjectURL(url);

    // 优化后的成功提示（绿色 + 自动消失）
    resultBox.innerHTML = `<p style="color:#2ecc71;">✔ 导出成功！文件已自动下载。</p>`;
    setTimeout(() => {
      resultBox.innerHTML = "";
    }, 3000);

  } catch (error) {
    resultBox.innerHTML = `<p style="color:#e74c3c;">⚠ 连接服务器失败：${error.message}</p>`;
  }
}
