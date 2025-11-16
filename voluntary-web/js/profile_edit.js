// 加载编辑页面的个人信息
function loadEditProfile() {
    const user = getCurrentUser();
    if (!user) return;

    // 填充表单中的数据，如果有用户输入则使用输入的值，否则使用缓存值
    document.getElementById("edit_pname").value = user.pname || '';
    document.getElementById("edit_school_id").value = user.school_id || ''; // 学号是不可修改的
    document.getElementById("edit_college").value = user.college || '';
    document.getElementById("edit_voluntary_id").value = user.voluntary_id || '';
    document.getElementById("edit_political_status").value = user.political_status || '';
    document.getElementById("edit_phone_number").value = user.phone_number || '';
    document.getElementById("edit_grade").value = user.grade || '';  // 如果为空则填入默认值
    document.getElementById("edit_education").value = user.education || '';  // 如果为空则填入默认值
}

// 页面加载完成后自动执行
document.addEventListener("DOMContentLoaded", loadEditProfile);
