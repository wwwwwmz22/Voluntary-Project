// ===================== 抽 100 题 =====================
function getRandom100Questions() {
    const shuffled = QUESTIONS.sort(() => Math.random() - 0.5);
    return shuffled.slice(0, 100);
}

const examQuestions = getRandom100Questions();
localStorage.setItem("vol_exam", JSON.stringify(examQuestions));

// ===================== 渲染题目 =====================
const container = document.getElementById("questionContainer");

examQuestions.forEach((q, index) => {
    const div = document.createElement("div");
    div.className = "question";

    let optHtml = "";
    const opts = ["A", "B", "C", "D"];

    opts.forEach((opt, i) => {
        if (q.options[i]) {
            optHtml += `
                <label>
                    <input type="radio" name="q${index}" value="${opt}">
                    ${opt}. ${q.options[i]}
                </label>`;
        }
    });

    div.innerHTML = `
        <p><strong>第 ${index + 1} 题：</strong> ${q.question}</p>
        <div class="options">${optHtml}</div>
    `;

    container.appendChild(div);
});

// ===================== 计时（60分钟） =====================
let timeLeft = 60 * 60;
const timer = document.getElementById("timer");

const interval = setInterval(() => {
    timeLeft--;

    const min = Math.floor(timeLeft / 60);
    const sec = timeLeft % 60;

    timer.innerText = `考试时间：${min}:${sec.toString().padStart(2, "0")}`;

    if (timeLeft <= 0) {
        clearInterval(interval);
        submitExam();
    }
}, 1000);

// ===================== 交卷按钮 =====================
document.getElementById("submitBtn").onclick = submitExam;

// ===================== 提交试卷 =====================
async function submitExam() {
    clearInterval(interval);

    let score = 0;

    examQuestions.forEach((q, i) => {
        const selected = document.querySelector(`input[name="q${i}"]:checked`);
        const ans = selected ? selected.value : null;

        if (ans === q.answer) {
            score += q.score;
        }
    });

    // 保存成绩并跳转
    localStorage.setItem("vol_exam_score", score);

    window.location.href = "result.html";
}