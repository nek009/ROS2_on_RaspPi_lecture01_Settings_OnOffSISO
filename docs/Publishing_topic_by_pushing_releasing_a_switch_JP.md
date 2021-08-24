[Topページへ](README_JP.md)

# 概要
ROS2 nodeの作成を行う．
作成するnodeはスイッチを押したり離したり(GPIO26の状態が変更)すると関連する情報をpublishするものである．
まずpublishするメッセージの型を考え，メッセージに関連したパッケージを作成する．
その後，メッセージを利用したnodeの作成を行う．

# 使用メッセージ
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
  * gpio_messages/msg/GpioState.msg

内容は以下の通り．

```text
uint16 gpio
bool level
```

### package.xmlとCMakeLists.txtの編集
以下は関連する部分のみ抜粋．

**package.xml**
```xml
<package format="3">
  <build_depend>rosidl_default_generators</build_depend>
  <exec_depend>rosidl_default_runtime</exec_depend>
  <member_of_group>rosidl_interface_packages</member_of_group>
```

**CMakeLists.txt**
```text
find_package(rosidl_default_generators REQUIRED)

set(msg_files
  "msg/GpioState.msg"
)
rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
)
ament_export_dependencies(rosidl_default_runtime)
```

## ビルド & 確認

```shell
$ colcon_cd
$ colcon build --symlink-install --packages-up-to gpio_messages
$ . install/local_setup.bash
$ ros2 interface list # confirm that difined message is shown
$ ros2 interface show gpio_messages/msg/GpioState
```
