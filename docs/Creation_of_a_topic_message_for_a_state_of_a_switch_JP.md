[Topページへ](../README_JP.md)

# 概要

ROS2のpublisherノードはトピックメッセージを発信する．
ここでは，スイッチの状態に関するトピックメッセージの作成を行う．
ちなみにスイッチはGPIO26に接続されているため，厳密にはGPIO26の状態に関するトピックメッセージとなる．

# メッセージ
## 型の定義
今回はGPIO26がスイッチにつながっているが，必ずしもいつもそう接続されているとは限らない．
そこで，メッセージとしては「監視対象のGPIO番号」と「その状態」を考える．

* unsigned GPIO number
  * 監視対象のGPIO番号
* bool level
  * GPIOの状態(HIGH(true)またはLOW(false))

## ROS2プログラミング
### メッセージ用のパッケージ準備

```shell
$ colcon_cd
$ ros2 pkg create gpio_messages --build-type ament_cmake
$ mkdir gpio_messages/msg
```

### メッセージファイルの作成
以下のファイルを作成する．

* 対象ファイル
  * gpio_messages/msg/[GpioState.msg](../src/gpio_messages/msg/GpioState.msg)

### package.xmlとCMakeLists.txtの編集
* 対象ファイル
  * gpio_messages/[package.xml](../src/gpio_messages/package.xml)
  * gpio_messages/[CMakeLists.txt](../src/gpio_messages/CMakeLists.txt)

## ビルド & 確認

```shell
$ colcon_cd
$ colcon build --symlink-install --packages-up-to gpio_messages
$ . install/local_setup.bash
$ ros2 interface list # confirm that difined message is shown
$ ros2 interface show gpio_messages/msg/GpioState
```
