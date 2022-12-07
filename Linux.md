# Linux使用笔记

## 安装libxcb
- 使用`apt-cache search libxcb`指令搜索相关库。
  - `libname`:用作软件依赖。
  - `libname-dev`:软件的依赖库，可用作开发组件。
  - `libname-dbg`:用于调试库。
- 使用`apt install libxcb`安装所需要的库。
## 配置`Wsl`使用`Windows`的字体包
  - `sudo ln -s /mnt/c/Windows/Fonts /usr/share/fonts/font`
  - `fc-cache -fv`