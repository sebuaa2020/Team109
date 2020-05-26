# buaa-se2020-Team109

### 项目结构
```yaml
Team109:
  - assets # 项目资源
  - docs # 项目文档
  - ros_ws: # ros workspace
    - src:
      - third lib # 第三方库，对于不需要修改的第三方库建议使用 git submodule 管理 
      - my_pkg # 项目源代码包
  - scripts: # 执行各个功能的脚本
    - obj_detect.sh # 物体检测脚本
  - main.cpp # 主要为了在clion等IDE中编写代码需要的target，目前为输出项目版本
  - CMakeLists.txt # IDE需要的顶层cmake配置，可以根据自己环境修改include_directories来实现智能提示
  - setup.sh # 项目初始化脚本，安装ros以及需要的各种库
```

请参考[wiki](https://github.com/sebuaa2020/Team109/wiki/sebuaa2020-Team109)