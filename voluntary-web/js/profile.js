// 从 localStorage 获取当前用户
function getCurrentUser() {
    const data = localStorage.getItem("userData");
    return data ? JSON.parse(data) : null;
}

// 加载个人信息
async function loadProfile() {
    const user = getCurrentUser();
    if (!user) return;

    try {
        // 从服务器获取最新用户信息
        const response = await apiRequest(`/login/getUserInfo?school_id=${user.school_id}&password=${user.pasword}`);
        if (response && response.code === 10000) {
            const latestUser = response.data;
            // 更新本地缓存
            localStorage.setItem("userData", JSON.stringify(latestUser));

            // 显示最新信息
            document.getElementById("profile_name").innerText = latestUser.pname;
            document.getElementById("profile_schoolid").innerText = latestUser.school_id;
            document.getElementById("profile_college").innerText = latestUser.college || "未填写";
            document.getElementById("profile_vid").innerText = latestUser.voluntary_id || "未分配";
            document.getElementById("profile_political").innerText = latestUser.political_status || "无";
            document.getElementById("profile_phone").innerText = latestUser.phone_number || "";
            document.getElementById("profile_gender").innerText = latestUser.gender || "未填写";
            document.getElementById("profile_grade").innerText = latestUser.grade || "未填写";
            document.getElementById("profile_edu").innerText = latestUser.edu_background || "未填写";
            document.getElementById("profile_dorm").innerText = latestUser.dorm || "未填写";
            document.getElementById("profile_roomid").innerText = latestUser.roomid || "未填写";
            document.getElementById("profile_score").innerText = latestUser.score || 0;
        } else {
            // 如果获取失败，使用本地缓存的数据
            document.getElementById("profile_name").innerText = user.pname;
            document.getElementById("profile_schoolid").innerText = user.school_id;
            document.getElementById("profile_college").innerText = user.college || "未填写";
            document.getElementById("profile_vid").innerText = user.voluntary_id || "未分配";
            document.getElementById("profile_political").innerText = user.political_status || "无";
            document.getElementById("profile_phone").innerText = user.phone_number || "";
            document.getElementById("profile_gender").innerText = user.gender || "未填写";
            document.getElementById("profile_grade").innerText = user.grade || "未填写";
            document.getElementById("profile_edu").innerText = user.edu_background || "未填写";
            document.getElementById("profile_dorm").innerText = user.dorm || "未填写";
            document.getElementById("profile_roomid").innerText = user.roomid || "未填写";
            document.getElementById("profile_score").innerText = user.score || 0;
        }
    } catch (error) {
        console.error("获取用户信息失败:", error);
        // 如果出现错误，使用本地缓存的数据
        document.getElementById("profile_name").innerText = user.pname;
        document.getElementById("profile_schoolid").innerText = user.school_id;
        document.getElementById("profile_college").innerText = user.college || "未填写";
        document.getElementById("profile_vid").innerText = user.voluntary_id || "未分配";
        document.getElementById("profile_political").innerText = user.political_status || "无";
        document.getElementById("profile_phone").innerText = user.phone_number || "";
        document.getElementById("profile_gender").innerText = user.gender || "未填写";
        document.getElementById("profile_grade").innerText = user.grade || "未填写";
        document.getElementById("profile_edu").innerText = user.edu_background || "未填写";
        document.getElementById("profile_dorm").innerText = user.dorm || "未填写";
        document.getElementById("profile_roomid").innerText = user.roomid || "未填写";
        document.getElementById("profile_score").innerText = user.score || 0;
    }
}

// 登出
function logout() {
    // === 彻底清除所有本地登录信息 ===
    // 清除localStorage中的用户数据
    localStorage.removeItem("userData");
    localStorage.removeItem("token");
    localStorage.removeItem("userInfo");
    localStorage.removeItem("user");
    localStorage.removeItem("access_token");

    // 清除sessionStorage
    sessionStorage.clear();

    // 清除可能存在的全局变量
    if (window.currentUser) window.currentUser = null;
    if (window.userData) window.userData = null;

    window.location.href = "login.html";
}
