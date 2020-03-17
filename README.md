# buaa-se2020-Team109


以下内容若有问题或分歧，请及时发issue或者微信群讨论。（初步暂定）


## 目录结构
documents/
src/
    Test/
    Module1/
        src/
        test/
    Module2/
    Module3/

涉及到具体语言的特性，目录结构可能有所更改。



## Branch规范
![image-20200317210317324](/home/qushuo/.config/Typora/typora-user-images/image-20200317210317324.png)
其中Test人员的行为未确定
* 在dev分支进行Test代码的编写，并测试
* 创建Test分支
文档更新
* 原则上文档更新也不允许pushmaster分支
* 或在dev分支上进行更新
* 或新建document分支

### master
理论上是稳定无bug的版本，不接受任何push，只有dev分支经过测试后merge。

### dev
各个developers完成当前阶段的开发后merge到dev，进行测试。

### 开发人员-开发模块
各个开发人员check出自己的分支，命名为**姓名-模块名**，在merge到dev之前请尽可能保证减少bug，也可自己独立测试。

### fix-bug名
若dev分支出现bug，则测试人员发issue，由具体出现bug模块负责人创建此分支，进行bug修复，修复后merge到dev分支。

### hotfix-bug名
若master出现bug（原则上不应该出现），共同商讨出现原因，创建此分支，进行bug修复后merge到master分支和dev分支


## Commit命名

### 开发类
格式：
Dev<module_name>: 内容

### 测试类
格式：
Test: 内容

### bug修复
bug修复请添加相应关键字来关闭提出bug的issue，具体请参考[github文档](https://help.github.com/en/enterprise/2.16/user/github/managing-your-work-on-github/closing-issues-using-keywords)

格式：
Fix<module_name>: 内容, fix #issue