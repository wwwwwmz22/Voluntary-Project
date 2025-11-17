/* global apiRequest, getCurrentUser */

document.addEventListener("DOMContentLoaded", () => {

    const score = Number(localStorage.getItem("vol_exam_score")) || 0;

    document.getElementById("scoreBox").innerHTML =
        `你本次考试得分：<strong>${score} 分</strong>`;

    let user = getCurrentUser();
    if (!user) {
        alert("用户未登录！");
        return;
    }

    async function checkAndUpdateScore() {
        const oldScore = Number(user.score || 0);

        console.log("旧成绩:", oldScore, "本次成绩:", score);

        if (score <= oldScore) {
            console.log("成绩未提升，不更新");
            return;
        }

        // 确保 school_id 是字符串类型，score 是数字类型
        const payload = {
            school_id: String(user.school_id),
            score: Number(score)
        };

        console.log("发送的数据:", payload);

        try {
            // 直接使用 fetch 而不是 apiRequest 来更好地控制请求
            const response = await fetch(`${backendUrl}/login/modifyuserscore`, {
                method: "PUT",
                headers: {
                    "Content-Type": "application/json"
                },
                body: JSON.stringify(payload)
            });

            console.log("响应状态:", response.status);
            console.log("响应是否成功:", response.ok);

            // 检查响应是否成功
            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }

            const result = await response.json();
            console.log("接口返回:", result);

            if (result && result.code === 10000) {
                console.log("成绩更新成功！");
                user.score = score;
                localStorage.setItem("userData", JSON.stringify(user));
                alert("成绩更新成功！");
            } else {
                console.error("成绩更新失败：", result ? result.message : "未知错误");
                alert("成绩更新失败：" + (result ? result.message : "未知错误"));
            }

        } catch (err) {
            console.error("更新成绩出错：", err);
            alert("更新成绩出错：" + err.message);
        }
    }

    checkAndUpdateScore();

    document.getElementById("backBtn").onclick = () => {
        window.location.href = "main.html";
    };

    localStorage.removeItem("vol_exam");
});
