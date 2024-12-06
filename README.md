# ElaWidgetTools

## 简介

本项目是使用 QT-Widget 开发的 FluentUI 风格的组件库，同时提供不限于组件的常用集成功能；目前 Main 分支支持 QT5.12 以上所有版本 (
Linux 为 QT5.15 以上)，推荐版本为 QT 6.4.3 和 QT 6.6.2。

本项目基于 [Liniyous](https://github.com/Liniyous) 的 [https://github.com/Liniyous/ElaWidgetTools](https://github.com/Liniyous/ElaWidgetTools) 修改。

## 修改历史

修改的目标是降低编译要求，尽量减少不必要的依赖，以适应最低的要求编译它。

**修改内容**

- 编译要求从 C++ 17 改为 C++ 11 (所有 CMakeLists.txt)；

- 修改 `./src/private/ElaAppBarPrivate.cpp` 中需要 C++ 17 的代码；

- 修正 Qt5 环境下，Example 演示程序的资源文件不能正常编译的问题 (/example/CMakeLists.txt)；

- 屏蔽 ElaDxgi 和 T_ElaScreen, 编译开关放在 stdafx.h 中，可以自己打开 (所有相关的 .h、.cpp 文件)；

- 增加了遗漏的 `/install/lib/cmake/ElaWidgetToolsConfig.cmake` (CMake没有正常生成)；

- 修改 main.cpp 中的 QT_SCALE_FACTOR 值为 1.0，原来的值 1.5 太大了，启动 example 程序默认大小太大了。

**编译环境**

- 已在 Windows 10 + Qt 5.12.1 + MSVS 2015 64位 环境下编译通过。

- CMakeLists.txt 中编译选项为至少支持 C++ 11，低于 VS 2015 以下的版本能不能编译没试过，有兴趣的朋友可以自己尝试一下。

- 已尝试过 Qt 5.6.x 版本，CMake 可以 Configure，但编译的时候错误太多，很难修改，不现实。

## 修改细节

**关于 C++ 17 改为 C++ 11**

原代码中只有一处需要修改的，原作者属于是为了一碗醋，包了一顿饺子。

另外一个地方使用了 [[maybe_unuse]]，这个可能也属于 C++ 17，但无关痛痒，低版本只是报个 warning 而已。

`./src/private/ElaAppBarPrivate.cpp` 原代码：

```cpp
    case Qt::LeftEdge | Qt::TopEdge:
    case Qt::RightEdge | Qt::BottomEdge:
    {
        q->window()->setCursor(Qt::SizeFDiagCursor);
        break;
    }
    case Qt::RightEdge | Qt::TopEdge:
    case Qt::LeftEdge | Qt::BottomEdge:
    {
        q->window()->setCursor(Qt::SizeBDiagCursor);
        break;
    }
```

更改为（仅仅只是把 "|"" 改为 "+" ）：

```cpp
    case (Qt::LeftEdge + Qt::TopEdge):
    case (Qt::RightEdge + Qt::BottomEdge):
    {
        q->window()->setCursor(Qt::SizeFDiagCursor);
        break;
    }
    case (Qt::RightEdge + Qt::TopEdge):
    case (Qt::LeftEdge + Qt::BottomEdge):
    {
        q->window()->setCursor(Qt::SizeBDiagCursor);
        break;
    }
```

头文件我也用了 enum 和 const 常量的方法，直接改加号能用就用不上他们了。

**关于 ElaWidgetToolsConfig.cmake**

`ElaWidgetToolsConfig.cmake` 文件 CMake 没有正常生成，可以自己手动修改：

范例如下：

```cmake
set(ELAWIDGETTOOLS_INCLUDE_DIRS "C:/Project/Qt/ElaWidgetTools/src/include")
set(ELAWIDGETTOOLS_LIBRARIES "C:/Project/Qt/ElaWidgetTools/build/src/Release")
set(ELAWIDGETTOOLS_LIBRARY_DIRS "C:/Project/Qt/ElaWidgetTools/build/src/Release")
```

以上配置中，ElaWidgetTools 的根目录是：`C:/Project/Qt/ElaWidgetTools`，项目 Build 目录为 `./build`，请根据以上范例自行修改。

其实也可以改成自动配置的，我懒得改了。路径配置可能可以不对，但这个文件不存在，用 CMake configure 的时候会报错。

**关于 DXGI**

DXGI，是（DirectX Graphics Infrastructure），DirectX 的图像接口，ElaWidgetTools 示例代码中的 T_ElaScreen 使用了 DXGI 技术。

T_ElaScreen 代码在  `./example/ExamplePage/T_ElaScreen.h`，使用了 `ElaDxgi` 和 `ElaDxgiManager` ，`ElaDxgi` 引用的头文件 <dxgi1_6.h> 可能需要安装 DirectX 的 SDK 包才有，我懒得装，完全没必要。

T_ElaScreen 是用于录制桌面的，DXGI 用于捕捉桌面，据说效率更高，但是一个 UI 示例程序里本来就不应该有它，也是属于为了一碗醋，包了顿饺子。

如果想打开 `T_ElaScreen` 的支持，可以在 `./src/include/stdafx.h` 中打开，如下所示：

```cpp
#ifndef STDAFX_H
#define STDAFX_H

//
// Enable or disable ElaScreen component?
// Added by shines77, 2024-12-05
//
#define USE_ELA_SCREEN  0
```

把 `USE_ELA_SCREEN` 改为 1，即为打开 T_ElaScreen 的编译。

## 本仓库 Git

[https://github.com/shines77/ElaWidgetTools](https://github.com/shines77/ElaWidgetTools)

[https://gitee.com/shines77/ElaWidgetTools](https://gitee.com/shines77/ElaWidgetTools)

从以下开始是原项目的 `README.md` 内容。

## 原项目简介

本项目是基于QT-Widget开发的FluentUI风格的组件库，同时提供不限于组件的常用集成功能；目前Main分支支持QT5.12以上所有版本(
Linux为QT5.15以上)，推荐版本为QT6.4.3和QT6.6.2；

## 重要提示

该项目项目性质原因，暂不接受任何PR！！！使用问题或BUG请直接进群反馈，都会及时处理，感谢您的支持！ 企鹅群：850243692

## 支持平台

| [Windows][win-link] | [Ubuntu][ubuntu-link] |
|---------------------|-----------------------|
| ![win-badge]        | ![ubuntu-badge]       |

[win-link]: https://github.com/Liniyous/ElaWidgetTools/actions?query=workflow%3AWindows "WindowsAction"

[win-badge]: https://img.shields.io/badge/Windows-Passing-61C263

[ubuntu-link]: https://github.com/Liniyous/ElaWidgetTools/actions?query=workflow%3AUbuntu "UbuntuAction"

[ubuntu-badge]: https://img.shields.io/badge/Ubuntu-Passing-61C263

## 主界面预览

<div align=center>
  <img src="doc/preview/ElaWidgetTools_Light.png">
</div>
<div align=center>
  <img src="doc/preview/ElaWidgetTools_Dark.png">
</div>

## 支持的组件

| 目录                     | 说明           | 备注                         |
|------------------------|--------------|----------------------------|
| ElaApplication         | 程序初始化        |                            |
| ElaAppBar              | 窗口顶部标题栏      | 支持拖动窗口，最小化、最大化、关闭窗口、调整窗口尺寸 |
| ElaAcrylicUrlCard      | 带图片的交互式亚克力卡片 | 支持URL跳转                    |
| ElaBreadcrumbBar       | 面包屑组件        | 自动处理点击事件                   |
| ElaCheckBox            | 勾选框          |                            |
| ElaComboBox            | 下拉框          |                            |
| ElaColorDialog         | 颜色选择器        |                            |
| ElaCalendar            | 日历视图         |                            |
| ElaCalendarPicker      | 日期选择器        |                            |
| ElaMultiSelectComboBox | 多选下拉框        |                            |
| ElaContentDialog       | 带遮罩的对话框      |                            |
| ElaDockWidget          | 停靠窗口         |                            |
| ElaSpinBox             | 微调框          |                            |
| ElaDoubleSpinBox       | 微调框          | 浮点数                        |
| ElaDxgiManager         | DXGI采集器      | 支持自动选择采集设备 效率远高于原生采集       |
| ElaEventBus            | 事件总线         |                            |
| ElaFlowLayout          | 流式布局         | 支持动画                       |
| ElaIcon                | 图标           |                            |
| ElaIconButton          | 图标按钮         |                            |
| ElaImageCard           | 图片卡片         |                            |
| ElaInteractiveCard     | 带图片的交互式透明卡片  |                            |
| ElaKeyBinder           | 单按键绑定器       |                            |
| ElaLineEdit            | 输入框          |                            |
| ElaListView            | 列表视图         |                            |
| ElaLog                 | 消息日志         |                            |
| ElaMenu                | 菜单           |                            |
| ElaMenuBar             | 菜单栏          |                            |
| ElaMessageBar          | 弹出式信息栏       | 支持八方向，锚定位置                 |
| ElaMessageButton       | 弹出信息按钮       |                            |
| ElaPivot               | 轴转导航         |                            |
| ElaPlainTextEdit       | 文本编辑框        |                            |
| ElaPushButton          | 按钮           |                            |
| ElaPopularCard         | 热门卡片         |                            |
| ElaProgressBar         | 进度条          |                            |
| ElaPromotionCard       | 促销卡片         |                            |
| ElaPromotionView       | 促销卡片视窗       |                            |
| ElaSwitchButton        | 切换按钮         |                            |
| ElaSuggestBox          | 建议搜索框        |                            |
| ElaRadioButton         | 单选按钮         |                            |
| ElaNavigationRouter    | 路由跳转         |                            |
| ElaToggleSwitch        | 开关按钮         |                            |
| ElaTabBar              | 选项卡          | 谷歌浏览器风格                    |
| ElaTabWidget           | 选项卡页面        | 谷歌浏览器风格                    |
| ElaTableView           | 表格视图         |                            |
| ElaTreeView            | 树型视图         |                            |
| ElaToolButton          | 带下拉菜单的工具按钮   |                            |
| ElaToolBar             | 工具栏          |                            |
| ElaTheme               | 主题管理器        |                            |
| ElaReminderCard        | 带图片的提醒卡片     |                            |
| ElaScrollbar           | 滚动条          |                            |
| ElaScrollArea          | 滚动区域         | 可设置鼠标拖动                    |
| ElaScrollPage          | 滚动页面         | 自带堆栈页面和面包屑导航               |
| ElaScrollPageArea      | 滚动页面区域组件     |                            |
| ElaSlider              | 拖动条          |                            |
| ElaStatusBar           | 状态栏          |                            |
| ElaExponentialBlur     | 指数模糊         |                            |
| ElaText                | Text文本       |                            |
| ElaGraphicsScene       | 高级场景         | 大量实用API                    |
| ElaGraphicsView        | 高级视图         | 按键缩放、拖动                    |
| ElaGraphicsItem        | 高级图元         | 大量实用API                    |
| ElaWindow              | 带导航栏的无边框窗口   |                            |
| ElaWidget              | 无边框模态窗口      |                            |
