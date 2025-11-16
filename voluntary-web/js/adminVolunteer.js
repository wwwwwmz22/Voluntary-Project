// ------------------ 权限验证 ------------------
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


// ------------------ 搜索志愿者 ------------------
async function searchVolunteer() {
    const key = document.getElementById("searchKey").value.trim();
    const tbody = document.getElementById("volunteerTable");

    if (key === "") {
        tbody.innerHTML = `<tr><td colspan="12" class="no-data">请输入搜索关键词</td></tr>`;
        return;
    }

    try {
        const res = await apiRequest(`/login/getUserInfo?key=${encodeURIComponent(key)}`);

        if (!res.data) {
            tbody.innerHTML = `<tr><td colspan="12" class="no-data">没有找到相关志愿者</td></tr>`;
            return;
        }

        // 处理单条用户数据或数组
        const list = Array.isArray(res.data) ? res.data : [res.data];

        tbody.innerHTML = list.map(v => `
      <tr>
        <td>${v.pname || ""}</td>
        <td>${v.school_id || ""}</td>
        <td>${v.phone_number || ""}</td>
        <td>${v.gender || ""}</td>
        <td>${v.college || ""}</td>
        <td>${v.grade || ""}</td>
        <td>${v.edu_background || ""}</td>
        <td>${v.political_status || ""}</td>
        <td>${v.voluntary_id || ""}</td>
        <td>${v.voluntary_time || 0}</td>
        <td>${v.score || 0}</td>
        <td>${v.identity || ""}</td>
      </tr>
    `).join("");

    } catch (err) {
        console.error("查询失败:", err);
        tbody.innerHTML = `<tr><td colspan="12" class="no-data">查询失败，请稍后重试</td></tr>`;
    }
}
function goBack() {
    window.location.href = "volunteer.html"; // 或者 history.back() 返回上一页
}