# 工作交接
## Jenkins
### 存在的问题 
- **Unittest-depth-magic**
  - 手动点击立即构建会触发所有分支依次进行构建的bug \
    *设定为master分支后，手动点击立即构建--等待构建成功后，将指定分支修改为\*/\*的形式可以解决*
  - 不能按照预定的分支触发，之前测试正常
- **Unittest-light-magic**
  - 单元测试存在问题，无法通过 
- **Unittest-palman-magic**
  - 测试分支还未合入master，代码在[dekang/palman](http://192.168.104.2/gitlab/inception/depth-magic/-/tree/dekang/palman)的分支上 
- **perf_910_runner_3288_android**
  - Jenkins服务器无法远程连接到安卓开发板
- **depth-magic的Unittest中CMakeLists.txt对不同算法的链接库的判断**
- **使用```make coverage```指令，进行内存泄漏检查**
  - 目前的Jenkins还未安装valgrind-3.19工具（提了Jenkins镜像的修改后Dockerfile的merge request）
  - 即使安装了valgrind-3.19工具，也需要适配到deptrum为6eac422b或之后版本才能正常进行内存泄漏检查
### Jenkins上的进展
- **palman测试样例搭建**
  - 基本已经完成，测试代码写在depth-magic的[dekang/palman](http://192.168.104.2/gitlab/inception/depth-magic/-/tree/dekang/palman)分支
- **orthodox测试搭建：1.ci测试；2.jenkins测试**
  - gitlab-ci上加入了```make memcheck```与```make coverage```指令的定义，ci上会进行内存泄漏检查与代码覆盖率检查，可以下载覆盖率网页报告
  - Jenkins同样加入了覆盖率检查与内存泄漏检查的任务
  - palman产线生产前，在本地写过一些批量测试的脚本，未在Jenkins上搭建任务。
- **depth-magic测试搭建：1.ci测试；2.jenkins测试**
  - Jenkins上的depth-magic，light-magic等都存在测试不过的问题
  - ci目前未做相关工作
### 代码覆盖率检查
- **在Jenkins上进行代码覆盖率检查**
  - 在编译时打开```ENABLE_CODE_COVERAGE```选项
  - 进入build目录执行```make coverage```指令
- **```make coverage```指令**
  - 在orthodox中会执行cover_report.sh脚本，生成可执行程序的代码覆盖率网页报告
  - orthodox与depth-magic中的```make coverage```指令的都在test的CMakeLists.txt中定义
## 代码
- **orthdox中的script/cover_report.sh**
  ```
  #!/bin/bash
  VAR=$@                                                                   接收传入参数
  cd ${1}/../                                                              切换至build目录
  ./bin/${VAR#* }                                                          运行可执行程序
  if [ -d "${2%_*}-coverage_report" ];then
    rm -rf ${2%_*}-coverage_report
  fi
  mkdir ${2%_*}-coverage_report                                            创建目录，例如palman-coverage——report
  gcovr   --xml-pretty \                                                   输出 Cobertura XML 格式
          --output ${2%_*}-coverage_report/${2%_*}-coverage.xml \
          --print-summary \                                                输出总的统计数据，即覆盖率百分比
          --html-details ${2%_*}-coverage_report/${2%_*}-coverage.html \   输出 HTML 格式的统计数据，以代码文件为单位，加入-details生成的网页报告可以查看每行的执行次数
          --gcov-executable ${1}/../bin/llvm-gcov \                        使用的工具，在build/bin/下会生成，不能使用相对路径！
          --exclude-unreachable-branches \
          --exclude-function-lines \
          --root ../ \                                                     工作目录
          ${1}/samples/CMakeFiles/${2%.*}.dir                              搜索该目录下的 gcda 和 gcno 文件
  pycobertura show \                                                       pycobertura 用于将 XML 输出转化为逐行注释的覆盖信息，以 HTML 格式展示。
          --format html \
          --output ${2%_*}-coverage_report/${2%_*}-pycobertura.html \
          --source ../ \
          ${2%_*}-coverage_report/${2%_*}-coverage.xml
  ```
- **depth-magic中[dekang/palman](http://192.168.104.2/gitlab/inception/depth-magic/-/tree/dekang/palman)分支，未合入**
  - 加入了cover_report.sh脚本，相比于orthodox中有改动
  - 加入palman100_runner的单元测试，gdfmm的函数测试
  - 在Unittest/CMakeLists.txt中定义```make coverage```指令
  - 对samples下的runner进行内存泄漏检查，定义在Unittest/CMakeLists.txt中
- **depth-magic中[dekang/jenkinsfile](http://192.168.104.2/gitlab/inception/depth-magic/-/tree/dekang/jenkinsfile)分支，未合入** 
  -  添加了Jenkinsfile文件，后期Jenkins搭建有需要可以参考，可以实现类似gitlab-ci的效果。
       - **优点：** 
       1. Deptrum版本更换时，替换构建脚本的deptrum版本号可以一起替换Jenkinsfile里的版本号
       2. 可以根据Jenkinsfile定义的阶段，显示构建以及测试过程中每个阶段的用时
       3. 可以避免在Jenkins网页端手动点击构建出现无限构建的现象
       4. Jenkins上网页的任务搭建比较轻松
       - **缺点：**
       1. 每一次Jenkinsfile的改动都需要提交merge request
       2. 只有分支里有Jenkinsfile文件的才可以正常构建
- **docker-image-builder中的[dekang/Dockerfile](http://192.168.104.2/gitlab/predator/docker-image-builder/-/tree/dekang/Dockerfile)**
  - 修改了debian11-jenkins/Dockerfile文件
    ```
    FROM jenkins/jenkins
    MAINTAINER deptrum

    WORKDIR /home/

    USER root

    RUN sed -i 's@http://\(deb\|security\).debian.org@https://mirrors.aliyun.com@g' /etc/apt/sources.list\
      && apt-get update -y && apt-get install build-essential -y \
      && apt-get install cmake -y \      在本地电脑测试编译出镜像中不含cmake工具，所以加入这条命令安装cmake
      && mkdir /root/.ssh \
      && chmod a+w /root/.bashrc /etc/hosts \
      && echo 'echo "192.168.104.2   heptagon">>/etc/hosts'>>/root/.bashrc \
      && echo 'StrictHostKeyChecking no'>>/etc/ssh/ssh_config \
      && apt-get install pip -y \        安装pip工具
      && pip install -i https://pypi.tuna.tsinghua.edu.cn/simple gcovr \         安装gcovr工具
      && pip install -i https://pypi.tuna.tsinghua.edu.cn/simple pycobertura     安装pycobertura工具

    COPY ./ssh/id_rsa ./ssh/known_hosts /root/.ssh/
    COPY ./valgrind/valgrind-3.19.0.tar.bz2 /home/    将valgrind-3.19压缩包拷贝到容器内

    RUN chmod 600 /root/.ssh/* \
      &&cd /home && tar -jxvf valgrind-3.19.0.tar.bz2 && rm valgrind-3.19.0.tar.bz2 \  解压压缩包后，删除压缩包
      &&cd /home/valgrind-3.19.0 && ./configure && make && make install && rm -r ../valgrind-3.19.0   执行安装命令，安装完成删除解压得到的文件

    ENV PATH /var/jenkins_home/projects/cmake-3.17.2-Linux-x86_64/bin:$PATH  配置容器的环境变量
    ENV THIRD_PARTY_ROOT /var/jenkins_home/projects/third_party  配置容器的环境变量
    ```
- **validation的cpack与orthodox的cpack打包相关**
  - 相关代码写在src/pipeline/CMakeLists.txt之中
  - symbol文件的打包，需要编译时开启```ENABLE_DUMP_SYMS```选项，在项目外侧的CMakeLists.txt中加入```find_package(BreakPad REQUIRED)```代码，编译动态库。
- **gitlab-ci**
  - orthodox中gitlab-ci上执行```make memcheck```指令不能正常完成，显示对应容器中没有valgrind工具。
  - gitlab-ci进行代码覆盖率检测，和build阶段使用的镜像并非同一个。目前需要在gitlab-ci的coverage阶段进行编译，根据其结果进行覆盖率检测。\
    *使用build阶段产生的文件，无法正常进行代码覆盖率检查。（不清楚原因）*