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

    // 根据题目类型确定输入框类型
    let inputType = "radio";
    if (q.type === "多选题") {
        inputType = "checkbox";
    } else if (q.type === "判断题") {
        inputType = "radio";
    }

    let optHtml = "";
    const opts = ["A", "B", "C", "D"];

    // 处理判断题的特殊选项
    if (q.type === "判断题") {
        optHtml = `
            <label>
                <input type="${inputType}" name="q${index}" value="A">
                A. 正确
            </label>
            <label>
                <input type="${inputType}" name="q${index}" value="B">
                B. 错误
            </label>`;
    } else {
        // 处理单选题和多选题
        opts.forEach((opt, i) => {
            if (q.options[i]) {
                optHtml += `
                    <label>
                        <input type="${inputType}" name="q${index}" value="${opt}">
                        ${opt}. ${q.options[i]}
                    </label>`;
            }
        });
    }

    div.innerHTML = `
        <p><strong>第 ${index + 1} 题（${q.type}）：</strong> ${q.question}</p>
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
        // 根据题目类型获取答案
        if (q.type === "多选题") {
            // 多选题：获取所有选中的选项
            const selected = document.querySelectorAll(`input[name="q${i}"]:checked`);
            const ans = Array.from(selected).map(el => el.value).sort().join('');

            // 多选题答案需要排序后比较
            if (ans === q.answer.split('').sort().join('')) {
                score += q.score;
            }
        } else {
            // 单选题和判断题：获取选中的选项
            const selected = document.querySelector(`input[name="q${i}"]:checked`);
            const ans = selected ? selected.value : null;

            if (ans === q.answer) {
                score += q.score;
            }
        }
    });

    // 保存成绩并跳转
    localStorage.setItem("vol_exam_score", score);

    window.location.href = "result.html";
}