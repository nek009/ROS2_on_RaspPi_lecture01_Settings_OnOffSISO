[Topページへ](README_JP.md)

# 概要
ここでは特にROS2用の設定について述べる．
例にてROS2用トップディレクトリ(colcon_cdで管理するディレクトリ)は`~/ros2_install`としている(ROS2のtutorialに合わせた)．
ディレクトリ自体は自分の好みに合わせて変えてよい．

# .bashrcの設定
\<disto\>の部分はROS2のディストリビューションの名前となる．
例えば，`foxy`や`galactic`などとなる．

## 簡単な設定方法
以下のコマンドを実行して設定．


```shell
$ echo "source /usr/share/colcon_cd/function/colcon_cd.sh" >> ~/.bashrc
$ echo "export _colcon_cd_root=~/ros2_install" >> ~/.bashrc
$ echo "source /opt/ros/<distro>/setup.bash" >> ~/.bashrc
```

## ちょっと凝った設定方法
.bachrcを以下のように編集して設定．
編集にはvimやnanoなどのエディタを使用のこと．
以下は関係する部分だけ抜粋したものとなる．

```bashrc

if [ -f /usr/share/colcon_cd/function/colcon_cd.sh ]; then
    source /usr/share/colcon_cd/function/colcon_cd.sh
    export _colcon_cd_root=~/ros2_install
fi

# 使用しない方をコメントアウト
DISTRO="foxy"
# DISTRO="galactic"
if [ -f /opt/ros/$DISTRO/setup.bash ]; then
    echo "ROS2 $DISTRO is activated."
    source /opt/ros/$DISTRO/setup.bash
fi

```
