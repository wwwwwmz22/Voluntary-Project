/* global apiRequest */

// SHA256 加密
async function sha256(str) {
    const encoder = new TextEncoder();
    const data = encoder.encode(str);
    const hashBuffer = await crypto.subtle.digest("SHA-256", data);
    const hashArray = Array.from(new Uint8Array(hashBuffer));
    return hashArray.map(b => b.toString(16).padStart(2, "0")).join("");
}

function _trim(v) { return (v || "").toString().trim(); }

async function login() {
    const schoolId = _trim(document.getElementById("school_id_login").value);
    const password = document.getElementById("password_login").value;

    if (!schoolId) return alert("请输入学号");
    if (!password) return alert("请输入密码");

    // ======= 前端 SHA256 加密 =======
    const hashedPassword = await sha256(password);

    try {
        const res = await apiRequest(
            `/login/getUserInfo?school_id=${encodeURIComponent(schoolId)}&password=${encodeURIComponent(hashedPassword)}`
        );

        if (res.code === 10000 && res.data) {
            localStorage.setItem("userData", JSON.stringify(res.data));
            alert("登录成功！");
            window.location.href = "main.html";
        } else {
            alert("登录失败：" + (res.message || "用户名或密码错误"));
        }
    } catch (err) {
        alert("连接服务器出错：" + err.message);
    }
}

function logout() {
    localStorage.removeItem("userData");
    window.location.href = "login.html";
}
