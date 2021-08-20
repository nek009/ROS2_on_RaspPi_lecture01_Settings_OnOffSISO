[Topページへ](README_JP.md)

# 概要
基本的には公式ページ通りに行えばよい．

# インストール
以下の公式ページ通りにROS2を行えばよい．

* [公式のインストールガイド for foxy](https://docs.ros.org/en/foxy/Installation/Ubuntu-Install-Debians.html)
* [公式のインストールガイド for galactic](https://docs.ros.org/en/galactic/Installation/Ubuntu-Install-Debians.html)

## 特記
### ROS2 packagesについて
基本的に複数のディストロがインストールできるなら(例えばfoxyとgalactic)，全部入れるのを推奨する．
全部インストールしておけば，簡単に使用するディストロを切り替えることができる．<br>
またディストロ毎に以下のようなパッケージをインストールできる．
迷ったらdesktopを入れておけばよい．

* ros-\<distro\>-desktop
  * 推奨
* ros-\<distro\>-base
  * Bare Bones

### 上記以外でインストールしたもの

```shell
$ sudo sh -c 'echo "deb [arch=$(dpkg --print-architecture)] http://repo.ros2.org/ubuntu/main `lsb_release -cs` main" > /etc/apt/sources.list.d/ros2-latest.list'
$ curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
$ sudo apt update
$ sudo apt install python3-colcon-common-extensions
$ sudo apt install python3-pip
$ sudo apt install ~nros-<distro>-rqt*
```

python3-colcon-common-extensionsはcolconを使うのに必須．諸情報は[こちら](https://colcon.readthedocs.io/en/released/user/installation.html)．<br>
`~nros-<distro>-rqt*`は有用なパッケージだけど必須のものではない．

# Tips
## チュートリアルについて

インストール終わったらとりあえずチュートリアルをやることが重要．
基本的で大事なことが全部書かれている．．．足りないところもあるけど．
しかし，ここを読んでいる前提で説明するので，読むこと必須．

* [公式のチュートリアル for foxy](https://docs.ros.org/en/foxy/Tutorials.html)
