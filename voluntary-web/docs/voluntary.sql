/*
 Navicat Premium Data Transfer

 Source Server         : 127.0.0.1
 Source Server Type    : MySQL
 Source Server Version : 80020
 Source Host           : 127.0.0.1:3306
 Source Schema         : voluntary

 Target Server Type    : MySQL
 Target Server Version : 80020
 File Encoding         : 65001

 Date: 16/11/2025 15:40:24
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for duty_recording
-- ----------------------------
DROP TABLE IF EXISTS `duty_recording`;
CREATE TABLE `duty_recording`  (
  `id` int NOT NULL AUTO_INCREMENT COMMENT 'id',
  `school_id` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '学号',
  `qdate` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '日期',
  `begin_time` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '开始',
  `end_time` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '结束',
  `sign_in` int NULL DEFAULT NULL COMMENT '签到',
  `sign_out` int NULL DEFAULT NULL COMMENT '签退',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 41 CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '值班记录' ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for feedback_recording
-- ----------------------------
DROP TABLE IF EXISTS `feedback_recording`;
CREATE TABLE `feedback_recording`  (
  `id` int NOT NULL AUTO_INCREMENT COMMENT 'id',
  `school_id` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '学号',
  `pname` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '姓名',
  `qdate` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '日期',
  `isclean` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '卫生情况',
  `isnoise` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '喧哗情况',
  `isfood` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '吃东西情况',
  `isseat` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '占座情况',
  `isother` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '其他情况',
  `begin_time` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `end_time` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 6 CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '反馈记录' ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for vp_login
-- ----------------------------
DROP TABLE IF EXISTS `vp_login`;
CREATE TABLE `vp_login`  (
  `id` int NOT NULL AUTO_INCREMENT COMMENT 'id',
  `pname` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '姓名',
  `school_id` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '学号',
  `pasword` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '密码',
  `college` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '学院',
  `voluntary_id` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '义工号',
  `political_status` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '政治面貌',
  `phone_number` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '手机号',
  `voluntary_time` int NULL DEFAULT NULL COMMENT '志愿时长',
  `gender` varchar(4) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '性别',
  `grade` int NULL DEFAULT NULL COMMENT '年级',
  `identity` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '身份（志愿者、管理员）',
  `edu_background` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '学历',
  `score` int NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 10 CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '注册信息' ROW_FORMAT = DYNAMIC;

SET FOREIGN_KEY_CHECKS = 1;
