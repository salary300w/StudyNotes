#gcovr用法简介：
```bash
gcovr --xml-pretty                      \
      --output coverage.xml             \
      --print-summary                   \
      --html coverage.html              \
      --gcov-executable 'llvm-cov gcov' \
      --root ${SOURCE_DIR}              \
      ${BUILD_DIR}
```
其中一些选项的具体含义如下：

* `--xml-pretty` : 输出 Cobertura XML 格式

* `--print-summary` : 输出总的统计数据，即覆盖率百分比

* `--html` : 输出 HTML 格式的统计数据，以代码文件为单位

* `--gcov-executable` :  若代码是 clang 编译的，需要调用 `llvm-cov` 来处理

* `--root` : 以 `${SOURCE_DIR}` 为源码文件根目录，例如 `deptrum`

* `${BUILD_DIR}` : 搜索该目录下的 `gcda` 和 `gcno` 文件。
* 完整的 gcovr 命令行介绍可参见[官网](https://gcovr.com/en/stable/manpage.html)，推荐使用 gcovr 5.0 或以上版本。