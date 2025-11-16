// 从 localStorage 获取当前用户
function getCurrentUser() {
    const data = localStorage.getItem("userData");
    return data ? JSON.parse(data) : null;
}

// 加载个人信息
function loadProfile() {
    const user = getCurrentUser();
    if (!user) return;

    document.getElementById("profile_name").innerText = user.pname;
    document.getElementById("profile_schoolid").innerText = user.school_id;
    document.getElementById("profile_college").innerText = user.college || "未填写";
    document.getElementById("profile_vid").innerText = user.voluntary_id || "未分配";
    document.getElementById("profile_political").innerText = user.political_status || "无";
    document.getElementById("profile_phone").innerText = user.phone_number || "";
    document.getElementById("profile_gender").innerText = user.gender || "未填写";
    document.getElementById("profile_grade").innerText = user.grade || "未填写";
    document.getElementById("profile_edu").innerText = user.edu_background || "未填写";
    document.getElementById("profile_score").innerText = user.score || 0;
}

// 登出
function logout() {
    localStorage.removeItem("userData");
    window.location.href = "login.html";
}
