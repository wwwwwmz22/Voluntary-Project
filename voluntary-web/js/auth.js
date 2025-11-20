/* global apiRequest */

/**
 * 手动实现的 SHA-1 哈希函数 (简化版)
 * @param {string} message - 需要进行哈希的输入字符串
 * @returns {string} - 计算出的 SHA-1 哈希值 (40 位十六进制字符串)
 */
function manualSha1(message) {
    // 步骤 1: 预处理 - 将输入字符串转换为 UTF-8 编码的字节数组
    const encoder = new TextEncoder();
    let data = encoder.encode(message);
    const originalLength = data.length * 8; // 原始消息长度 (以比特为单位)

    // 步骤 2: 填充消息
    // a. 追加一个 '1' 比特
    data = [...data, 0x80]; // 0x80 是二进制的 10000000

    // b. 追加 '0' 比特，直到消息长度 ≡ 448 mod 512
    while ((data.length * 8) % 512 !== 448) {
        data.push(0x00);
    }

    // c. 追加原始消息长度 (64 比特的大端整数)
    for (let i = 7; i >= 0; i--) {
        data.push((originalLength >>> (i * 8)) & 0xff);
    }

    // 步骤 3: 初始化哈希值 (A, B, C, D, E)
    let A = 0x67452301;
    let B = 0xefcdab89;
    let C = 0x98badcfe;
    let D = 0x10325476;
    let E = 0xc3d2e1f0;

    // 步骤 4: 处理消息块 (每个块 512 比特 = 64 字节)
    for (let i = 0; i < data.length; i += 64) {
        const chunk = data.slice(i, i + 64);

        // 扩展消息块: 将 64 字节的块扩展为 80 个 32 位字
        const W = new Array(80);
        for (let t = 0; t < 16; t++) {
            W[t] = (chunk[t * 4] << 24) |
                (chunk[t * 4 + 1] << 16) |
                (chunk[t * 4 + 2] << 8) |
                chunk[t * 4 + 3];
        }
        for (let t = 16; t < 80; t++) {
            W[t] = manualSha1RotateLeft(W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16], 1);
        }

        // 初始化工作变量
        let tempA = A;
        let tempB = B;
        let tempC = C;
        let tempD = D;
        let tempE = E;

        // 主循环
        for (let t = 0; t < 80; t++) {
            let f, K;
            if (t < 20) {
                f = (tempB & tempC) | ((~tempB) & tempD);
                K = 0x5a827999;
            } else if (t < 40) {
                f = tempB ^ tempC ^ tempD;
                K = 0x6ed9eba1;
            } else if (t < 60) {
                f = (tempB & tempC) | (tempB & tempD) | (tempC & tempD);
                K = 0x8f1bbcdc;
            } else {
                f = tempB ^ tempC ^ tempD;
                K = 0xca62c1d6;
            }

            const temp = (manualSha1RotateLeft(tempA, 5) + f + tempE + K + W[t]) & 0xffffffff;
            tempE = tempD;
            tempD = tempC;
            tempC = manualSha1RotateLeft(tempB, 30);
            tempB = tempA;
            tempA = temp;
        }

        // 更新哈希值
        A = (A + tempA) & 0xffffffff;
        B = (B + tempB) & 0xffffffff;
        C = (C + tempC) & 0xffffffff;
        D = (D + tempD) & 0xffffffff;
        E = (E + tempE) & 0xffffffff;
    }

    // 步骤 5: 拼接最终哈希值
    const format = (n) => {
        // 将 32 位整数转换为 8 位十六进制字符串，不足位数补零
        return n.toString(16).padStart(8, '0');
    };

    return (format(A) + format(B) + format(C) + format(D) + format(E));
}

/**
 * SHA-1 辅助函数：循环左移
 * @param {number} n - 要移位的 32 位整数
 * @param {number} bits - 移位的位数
 * @returns {number} - 移位后的结果
 */
function manualSha1RotateLeft(n, bits) {
    return ((n << bits) | (n >>> (32 - bits))) & 0xffffffff;
}

function _trim(v) { return (v || "").toString().trim(); }

async function login() {
    const schoolId = _trim(document.getElementById("school_id_login").value);
    const password = document.getElementById("password_login").value;

    if (!schoolId) return alert("请输入学号");
    if (!password) return alert("请输入密码");

    // ======= 前端 SHA256 加密 =======
    const hashedPassword = manualSha1(password);
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
