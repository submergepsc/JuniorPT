# JuniorPT

## Overview
JuniorPT 收录了阶段性课堂/实验练习的 PPT 题目（已转换为 Markdown）以及对应的 C++ 参考实现。代码按照训练批次划分在 `pt1`–`pt7` 目录中，便于独立练习、调试与后续扩展。

## 快速开始
1. 克隆仓库：`git clone git@github.com:submergepsc/JuniorPT.git`
2. 进入目录：`cd JuniorPT`
3. 运行批量编译脚本验证环境
4. 按需进入各 `ptN` 目录阅读 Markdown、编辑或运行题目源码

## 目录结构
- `ptN/`：第 N 次课堂练习
  - `New 第 N 次课堂练习.pptx`：原始课件
  - `New 第 N 次课堂练习.md`：幻灯片文字版题目说明
  - `*.cpp`：按课件指定文件名实现的 C++ 题解
- `a.py`：预留脚本入口，可放置 PPT 转 Markdown 等自动化工具
- `LICENSE`：授权条款（默认 MIT）

> 建议保持 PPT、Markdown 与题解文件名一致，以便后续维护。

## 题目索引
### pt1 基础循环与数组
- `Pi.cpp`：莱布尼茨级数求 PI
- `ShapeEx.cpp`：打印菱形图案
- `CountChar.cpp`：统计字符串字符频率
- `CountDigit.cpp`：统计整数各数字出现次数
- `Huiwen.cpp`：判断回文数
- `candy.cpp`：分发糖果（贪心法）

### pt2 分解、加密与排序
- `Tgs.cpp`：枚举 1-10000 同构数
- `DecomposeTest.cpp`：质因数分解
- `CodeEncry.cpp`：四位数加密
- `ws.cpp`：1000 内完数
- `dclass.cpp`：100 学生随机分班
- `ColorSort.cpp`：红绿蓝排序（荷兰旗）

### pt3 经典谜题与数论
- `peach.cpp`：猴子吃桃
- `carno.cpp`：车牌推理
- `pp.cpp`：乒乓球队配对
- `tranOcttoDec.cpp`：八进制转十进制
- `nkcs.cpp`：尼科彻斯定律
- `HIndex.cpp`：H 指数

### pt4 数据结构与数组进阶
- `ListInert2.cpp`：有序数组插入
- `killPrisoner.cpp`：奇偶出列约瑟夫
- `wordMax.cpp`：最长单词
- `wordCount.cpp`：词频统计
- `magic.cpp`：奇数阶幻方
- `GasCircle.cpp`：加油站环路

### pt5 字符串、双指针与贪心
- `InsertStr.cpp`：主串插入子串
- `pailie.cpp`：循环排列矩阵
- `mostWater.cpp`：盛水容器
- `brackets.cpp`：括号匹配
- `monkey.cpp`：约瑟夫数组解
- `monkeyLink.cpp`：约瑟夫链表解
- `IPO.cpp`：IPO 资本最大化

### pt6 链表专题
- `createList.cpp`：链表拼接
- `monkeyLink.cpp`：链表约瑟夫
- `moveList.cpp`：移除右侧更大节点
- `reverseLink.cpp`：带头结点逆置
- `danceMatch.cpp`：舞伴配对模拟

### pt7 综合模拟
- `getNumber.cpp`：提取数字序列
- `BridgeCard.cpp`：桥牌发牌
- `undercover.cpp`：谁是卧底推断
- `marry.cpp`：五服内婚姻合法性

## 编译与运行
批量编译（Linux / macOS / WSL）：

```bash
shopt -s globstar nullglob
for file in pt*/**/*.cpp; do
  echo "building $file"
  g++ -std=c++17 "$file" -o /tmp/juniorpt.out || exit 1
done
```

单个题目调试：

```bash
g++ -std=c++17 pt3/peach.cpp -o peach && ./peach
```

若在 Windows + MinGW 环境，可将 `g++` 替换为对应编译器命令。

## 辅助脚本建议
- PPT 转 Markdown：可使用 Python `zipfile + xml.etree.ElementTree` 解析 `ppt/slides/slide*.xml` 中的 `a:t` 文本，将输出写入 `New 第 N 次课堂练习.md`。
- 批量构建脚本：建议新建 `scripts/build_all.sh` 或 `scripts/build_all.ps1` 封装上述命令，方便持续集成。
- 样例管理：若题目含复杂输入，可在 Markdown 中追加示例段落，或在源码顶部记录注释示例。

## 增量维护指引
1. 新增练习：将 PPT 放入对应 `ptN` 目录，并同步生成 Markdown。
2. 添加题解：按课件指定文件名创建 `.cpp`，保持输入输出格式简洁明了。
3. 更新文档：每次新增题目后同步更新「题目索引」或相关章节。
4. 公共代码：如需复用工具函数，可创建 `lib/` 或 `include/`，并在 README 中记录引用方式。
5. 版本控制：尽量保持各 `ptN` 相互独立，减少跨目录依赖，便于课堂按批次交付。

## 常见问题
- 仓库位于其他 Git 项目内部时，执行 `git add .` 会提示嵌套仓库；请在 `JuniorPT` 内单独提交，或改用 submodule 管理。
- 中文路径或终端编码导致的编译警告，可将仓库放在 ASCII 路径下，或按需添加 `-fexec-charset=UTF-8` 等参数。
- 若 PPT 更新内容较多，可重新运行转换脚本覆盖 Markdown，并在提交信息中注明更新来源。
