// ================= 全局配置 =================

// 后端 API 地址（修改此处即可）
window.backendUrl = "http://172.24.169.216:8090";

// 统一请求函数
async function apiRequest(endpoint, options = {}) {
  try {
    const response = await fetch(`${backendUrl}${endpoint}`, options);
    const result = await response.json();
    return result;
  } catch (error) {
    alert("连接服务器出错：" + error.message);
    throw error;
  }
}

// 获取当前登录用户
function getCurrentUser() {
  const user = JSON.parse(localStorage.getItem("userData"));
  if (!user) {
    alert("请先登录！");
    window.location.href = "login.html";
    return null;
  }
  return user;
}

