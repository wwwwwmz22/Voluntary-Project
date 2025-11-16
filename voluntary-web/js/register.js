/* global apiRequest */

// SHA256 加密
async function sha256(str) {
    const encoder = new TextEncoder();
    const data = encoder.encode(str);
    const hashBuffer = await crypto.subtle.digest("SHA-256", data);
    const hashArray = Array.from(new Uint8Array(hashBuffer));
    return hashArray.map(b => b.toString(16).padStart(2, "0")).join("");
}

function trimStr(v) { return (v || "").trim(); }
function validatePhone(phone) { return /^\d{11}$/.test(phone); }
function validateSchoolId(sid) { return /^\d{6,}$/.test(sid); }

async function register() {
    const pname = trimStr(document.getElementById("pname").value);
    const school_id = trimStr(document.getElementById("school_id").value);
    const password = document.getElementById("password").value;
    const confirm_password = document.getElementById("confirm_password").value;

    const college = trimStr(document.getElementById("college").value);
    const voluntary_id = trimStr(document.getElementById("voluntary_id").value);
    const political_status = document.getElementById("political_status").value;
    const phone_number = trimStr(document.getElementById("phone_number").value);
    const gender = document.getElementById("gender").value;
    const grade = parseInt(document.getElementById("grade").value, 10);
    const edu_background = document.getElementById("edu_background").value;

    // ======= 校验 =======
    if (!pname) return alert("请输入姓名");
    if (!school_id) return alert("请输入学号");
    if (!password) return alert("请输入密码");
    if (!confirm_password) return alert("请再次输入密码");
    if (password !== confirm_password) return alert("两次密码不一致");
    if (!validateSchoolId(school_id)) return alert("学号格式不正确（至少 6 位数字）");
    if (!validatePhone(phone_number)) return alert("手机号格式不正确，应为 11 位数字");

    // ======= 前端 SHA256 加密 =======
    const hashedPassword = await sha256(password);

    const payload = {
        school_id,
        pasword: hashedPassword,   // 传输加密后的密码
        pname,
        phone_number,
        voluntary_id,
        political_status,
        voluntary_time: 0,
        college,
        gender,
        grade,
        edu_background,
        identity: "user",
        score: 0
    };

    try {
        const result = await apiRequest(`/login/adduserinfo`, {
            method: "POST",
            headers: { "Content-Type": "application/json; charset=UTF-8" },
            body: JSON.stringify(payload)
        });

        if (result && result.code === 10000) {
            alert("注册成功！");
            window.location.href = "login.html";
        } else {
            alert("注册失败：" + (result?.message || "未知错误"));
        }
    } catch (err) {
        alert("连接服务器出错：" + err.message);
    }
}
