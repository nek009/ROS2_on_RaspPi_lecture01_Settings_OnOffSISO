[Topページへ](README_JP.md)

# 概要
ROS2 nodeの作成を行う．
作成するnodeはスイッチを押したり離したり(GPIO26の状態が変更)すると関連する情報をpublishするものである．
まずpublishするメッセージの型を考え，メッセージに関連したパッケージを作成する．
その後，メッセージを利用したnodeの作成を行う．

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

# Publisherノード
上記のメッセージを使用してpublisherノードを作成する．

* トピック名
  * gpio_state

## ROS2プログラミング
### ROS2 packageの準備

```shell
$ colcon_cd
$ ros2 pkg create gpio_state_recognition_nodes --build-type ament_cmake --dependencies rclcpp gpio_messages
```

### プログラミング

* 対象ファイル
  * gpio_state_recognition_nodes/src/[pub_gpio_state_node.hpp](../src/gpio_state_recognition_nodes/src/pub_gpio_state_node.hpp)
  * gpio_state_recognition_nodes/src/[pub_gpio_state_node.cpp](../src/gpio_state_recognition_nodes/src/pub_gpio_state_node.cpp)

### package.xmlとCMakeLists.txtの編集

* 対象ファイル
  * gpio_state_recognition_nodes/[package.xml](../src/gpio_state_recognition_nodes/package.xml)
  * gpio_state_recognition_nodes/[CMakeLists.txt](../src/gpio_state_recognition_nodes/CMakeLists.txt)
    * [# For target以下24-49行目](../src/gpio_state_recognition_nodes/CMakeLists.txt#L23-L48)を追加

## ビルドと確認
### ビルド

```shell
$ colcon_cd
$ colcon build --symlink-install --packages-up-to gpio_state_recognition_nodes
$ . install/local_setup.bash
```

### 確認
ターミナルを二つ(term1とterm2とする)起動する．
term1でノードを実行する．

```shell
$ . install/local_setup.bash
$ ros2 run gpio_state_recognition_nodes pub_gpio_state_target
```

term2でノードがメッセージを発信しているか，ROS2コマンドで確認する．

```shell
$ . install/local_setup.bash
$ ros2 topic echo /pub_gpio_state
```

# コンポーネントとしてのPublisherノード
上記のノードは実行可能なtarget形式である．
すぐに使えて便利だが，拡張性やロバスト性を考えるとコンポーネントの方がよい．
コンポーネントにすると，上記と同じようにtarget形式にもできる．
その際，複数のノードを組み合わせて一つのtarget形式にできる．
この時，ノード間通信はzero-copy(めっちゃはやい，通信ではなく値をそのまま渡せる感じ)となる．
そのうえtarget形式にしなくても，`ros2 component standalone`や`ros2 run rclcpp_components component_container`と`ros2 component load`の組み合わせてでそのまま実行できる．<br>
ここでは，上記のパッケージで，作成したノードをベースにコンポーネントを作成する．

* トピック名
  * gpio_state

## ROS2プログラミング
### visibility.hの準備
visibility.hはスクラッチから作成するのは大変．
なので[公式のgithub上のvisibility.h](https://github.com/ros2/examples/blob/master/rclcpp/composition/minimal_composition/include/minimal_composition/visibility.h)からDLしカスタマイズして使用する．<br>
カスタマイズする点は，文字列`MINIMAL_COMPOSITION`である．
これを自分用の文字列`ROS2RASP_LECTURE_PUBGPIOSTATECOMPONENTNODE`にする．
ちなみに`namespace`と`class name`を`_`でつなげて作っている．

```shell
$ cd gpio_state_recognition_nodes/include/gpio_state_recognition_nodes
$ curl https://raw.githubusercontent.com/ros2/examples/master/rclcpp/composition/minimal_composition/include/minimal_composition/visibility.h > visibility.h
$ sed -i s/MINIMAL_COMPOSITION/ROS2RASP_LECTURE_PUBGPIOSTATECOMPONENTNODE/g visibility.h
```

### プログラミング

* 対象ファイル
  * gpio_state_recognition_nodes/include/gpio_state_recognition_nodes/[pub_gpio_state_component_node.hpp](../src/gpio_state_recognition_nodes/include/gpio_state_recognition_nodes/pub_gpio_state_component_node.hpp)
  * gpio_state_recognition_nodes/src/[pub_gpio_state__component_node.cpp](../src/gpio_state_recognition_nodes/src/pub_gpio_state_component_node.cpp)

### package.xmlとCMakeLists.txtの編集

* 対象ファイル
  * gpio_state_recognition_nodes/[package.xml](../src/gpio_state_recognition_nodes/package.xml)
    * \<depend\>rclcpp_components\</depend\>を追加
  * gpio_state_recognition_nodes/[CMakeLists.txt](../src/gpio_state_recognition_nodes/CMakeLists.txt)
    * find_package(rclcpp_components REQUIRED)を追加
    * [# For component以下50-100行目](../src/gpio_state_recognition_nodes/CMakeLists.txt#L50-L100)

## ビルドと確認
### ビルド

```shell
$ colcon_cd
$ colcon build --symlink-install --packages-up-to gpio_state_recognition_nodes
$ . install/local_setup.bash
```

### 確認
ターミナルを二つ(term1とterm2とする)起動する．
term1でノードを実行する．

```shell
$ . install/local_setup.bash
$ ros2 component standalone gpio_state_recognition_nodes ros2rasp_lecture::PubGpioStateComponentNode
```

term2でノードがメッセージを発信しているか，ROS2コマンドで確認する．

```shell
$ . install/local_setup.bash
$ ros2 topic echo /pub_gpio_state
```

## targetでのコンポーネントの使用
以下でtarget内でコンポーネントを使用する方法を示す(正確には共有ライブラリだけど)．

### target用のパッケージの準備

```shell
$ colcon_cd
$ ros2 pkg create gpio_state_recognition_target  --build-type ament_cmake --dependencies rclcpp gpio_state_recognition_nodes
```

### プログラミング

* target file
  * gpio_state_recognition_target/src/[pub_gpio_state_recognition_target.cpp](../src/gpio_state_recognition_target/src/gpio_state_recognition_target.cpp)

### package.xmlやCMakeLists.txtの編集

* target file
  * gpio_state_recognition_target/[CMakeLists.txt](../src/gpio_state_recognition_nodes/CMakeLists.txt)

### ビルド

```shell
$ colcon_cd
$ colcon build --symlink-install --packages-up-to gpio_state_recognition_target
$ . install/local_setup.bash
```

### 確認
ターミナルを二つ(term1とterm2とする)起動する．
term1でノードを実行する．

```shell
$ . install/local_setup.bash
$ ros2 run gpio_state_recognition_target pub_gpio_state_recognition_target
```

term2でノードがメッセージを発信しているか，ROS2コマンドで確認する．

```shell
$ . install/local_setup.bash
$ ros2 topic echo /pub_gpio_state
```