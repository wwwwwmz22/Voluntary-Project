/* global apiRequest, getCurrentUser, sha256 */

// 加载编辑页面的个人信息
function loadEditProfile() {
    const user = getCurrentUser();
    if (!user) return;

    console.log("当前用户信息：", user);
    // 填充表单中的数据，如果有用户输入则使用输入的值，否则使用缓存值
    document.getElementById("edit_pname").value = user.pname || '';
    document.getElementById("edit_school_id").value = user.school_id || ''; // 学号是不可修改的
    document.getElementById("edit_college").value = user.college || '';
    document.getElementById("edit_voluntary_id").value = user.voluntary_id || '';
    document.getElementById("edit_political_status").value = user.political_status || '';
    document.getElementById("edit_phone_number").value = user.phone_number || '';
    document.getElementById("edit_grade").value = user.grade || '';  // 如果为空则填入默认值
    document.getElementById("edit_education").value = user.edu_background || '';  // 如果为空则填入默认值
    document.getElementById("edit_dorm").value = user.dorm || '';  // 宿舍楼栋
    document.getElementById("edit_roomid").value = user.roomid || '';  // 房间号
}

// 保存修改后的个人信息
async function saveProfile() {
    const user = getCurrentUser();
    if (!user) return alert("请先登录！");

    // 获取表单中的数据
    const pname = document.getElementById("edit_pname").value.trim();
    const school_id = user.school_id; // 学号不可修改
    const college = document.getElementById("edit_college").value.trim();
    const voluntary_id = document.getElementById("edit_voluntary_id").value.trim();
    const political_status = document.getElementById("edit_political_status").value.trim();
    const phone_number = document.getElementById("edit_phone_number").value.trim();
    const grade = document.getElementById("edit_grade").value.trim();
    const edu_background = document.getElementById("edit_education").value.trim();
    const dorm = document.getElementById("edit_dorm").value.trim();
    const roomid = document.getElementById("edit_roomid").value.trim();

    // 对于未填写的字段，使用缓存中的值
    const payload = {
        school_id: school_id,
        pname: pname || user.pname || "",
        college: college || user.college || "",
        voluntary_id: voluntary_id || user.voluntary_id || "",
        political_status: political_status || user.political_status || "",
        phone_number: phone_number || user.phone_number || "",
        grade: grade ? parseInt(grade) : (user.grade || 0),
        edu_background: edu_background || user.edu_background || "",
        dorm: dorm || user.dorm || "",
        roomid: roomid || user.roomid || ""
    };


    console.log("发送的数据：", payload);

    try {
        const res = await apiRequest(`/login/modifyuserinfo`, {
            method: "PUT",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify(payload)
        });

        if (res.code === 10000) {
            // 更新本地缓存的用户信息
            const updatedUser = { ...user, ...payload };
            localStorage.setItem("userData", JSON.stringify(updatedUser));

            alert("信息更新成功！");
            window.location.href = "profile.html";
        } else {
            alert("信息更新失败：" + (res.message || "未知错误"));
        }
    } catch (err) {
        console.error("更新信息出错：", err);
        alert("更新信息出错：" + err.message);
    }
}

// 页面加载完成后自动执行
document.addEventListener("DOMContentLoaded", loadEditProfile);
