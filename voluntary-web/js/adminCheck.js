/* global getCurrentUser */

// 判断是否为管理员
function isAdmin() {
    const user = getCurrentUser();
    return user && user.identity === "管理员";
}

// 只允许管理员访问某页面
function requireAdmin() {
    if (!isAdmin()) {
        alert("您没有权限访问此页面！");
        window.location.href = "main.html"; // 也可以跳回 volunteer.html
    }
}

// 在页面显示时根据身份隐藏某个区块（如新增日志区）
// sectionId: 需要隐藏的 DOM id
function hideIfNotAdmin(sectionId) {
    const element = document.getElementById(sectionId);
    if (!element) return;

    if (!isAdmin()) {
        element.style.display = "none";
    }
}

// 仅管理员可见的 UI 模块
function showAdminOnly(sectionId) {
    const element = document.getElementById(sectionId);
    if (!element) return;

    if (isAdmin()) {
        element.style.display = "block";
    } else {
        element.style.display = "none";
    }
}

