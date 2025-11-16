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

        const payload = {
            school_id: String(user.school_id),
            score: Number(score)
        };

        try {
            const result = await apiRequest(`/login/modifyuserscore`, {
                method: "PUT",
                headers: { "Content-Type": "application/json" }, // ← 必须加
                body: JSON.stringify(payload)
            });

            console.log("接口返回:", result);

            if (result.code === 10000) {
                console.log("成绩更新成功！");

                user.score = score;
                localStorage.setItem("userData", JSON.stringify(user));

            } else {
                console.error("成绩更新失败：", result.message);
            }

        } catch (err) {
            console.error("更新成绩出错：", err);
        }
    }

    checkAndUpdateScore();

    document.getElementById("backBtn").onclick = () => {
        window.location.href = "main.html";
    };

    localStorage.removeItem("vol_exam");
});
