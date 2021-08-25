[Topページへ](../README_JP.md)

# 概要
スイッチの状態に関するメッセージをpublishするROS2 publisherノードの作成を行う．
トピックメッセージは[ここ](Creation_of_a_topic_message_for_a_state_of_a_switch_JP.md)で作成したものを用いる．

# Publisherノード
上記のメッセージを使用してpublisherノードを作成する．

* トピック名
  * pub_gpio_state

## ROS2プログラミング
### ROS2 packageの準備

```shell
$ colcon_cd
$ ros2 pkg create gpio_state_recognition_node --build-type ament_cmake --dependencies rclcpp gpio_msgs
```

### プログラミング

* 対象ファイル
  * gpio_state_recognition_node/src/[pub_gpio_state_node.hpp](../src/gpio_state_recognition_node/src/pub_gpio_state_node.hpp)
  * gpio_state_recognition_node/src/[pub_gpio_state_node.cpp](../src/gpio_state_recognition_node/src/pub_gpio_state_node.cpp)
  * gpio_state_recognition_node/src/[pub_gpio_state_main.cpp](../src/gpio_state_recognition_node/src/pub_gpio_state_main.cpp)

### package.xmlとCMakeLists.txtの編集

* 対象ファイル
  * gpio_state_recognition_node/[CMakeLists.txt](../src/gpio_state_recognition_node/CMakeLists.txt)
    * [# For target以下24-49行目](../src/gpio_state_recognition_node/CMakeLists.txt#L24-L49)を追加

## ビルドと確認
### ビルド

```shell
$ colcon_cd
$ colcon build --symlink-install --packages-up-to gpio_state_recognition_node
$ . install/local_setup.bash
```

### 確認
ターミナルを二つ(term1とterm2とする)起動する．
term1でノードを実行する．

```shell
$ . install/local_setup.bash
$ ros2 run gpio_state_recognition_node pub_gpio_state_target
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
  * pub_gpio_state

## ROS2プログラミング
### visibility.hの準備
visibility.hはスクラッチから作成するのは大変．
なので[公式のgithub上のvisibility.h](https://github.com/ros2/examples/blob/master/rclcpp/composition/minimal_composition/include/minimal_composition/visibility.h)からDLしカスタマイズして使用する．<br>
カスタマイズする点は，文字列`MINIMAL_COMPOSITION`である．
これを自分用の文字列`GPIO_STATE_RECOGNITION_NODE`にする．
ちなみに`package name`から名前付けしている．

```shell
$ cd gpio_state_recognition_node/include/gpio_state_recognition_node
$ curl https://raw.githubusercontent.com/ros2/examples/master/rclcpp/composition/minimal_composition/include/minimal_composition/visibility.h > visibility.h
$ sed -i s/MINIMAL_COMPOSITION/GPIO_STATE_RECOGNITION_NODE/g visibility.h
```

### プログラミング

* 対象ファイル
  * gpio_state_recognition_node/include/gpio_state_recognition_node/[pub_gpio_state_component_node.hpp](../src/gpio_state_recognition_node/include/gpio_state_recognition_node/pub_gpio_state_component_node.hpp)
  * gpio_state_recognition_node/src/[pub_gpio_state__component_node.cpp](../src/gpio_state_recognition_node/src/pub_gpio_state_component_node.cpp)

### package.xmlとCMakeLists.txtの編集

* 対象ファイル
  * gpio_state_recognition_node/[package.xml](../src/gpio_state_recognition_node/package.xml)
    * \<depend\>rclcpp_components\</depend\>を追加
  * gpio_state_recognition_node/[CMakeLists.txt](../src/gpio_state_recognition_node/CMakeLists.txt)
    * find_package(rclcpp_components REQUIRED)を追加
    * [# For component以下50-100行目](../src/gpio_state_recognition_node/CMakeLists.txt#L50-L100)

## ビルドと確認
### ビルド

```shell
$ colcon_cd
$ colcon build --symlink-install --packages-up-to gpio_state_recognition_node
$ . install/local_setup.bash
```

### 確認
ターミナルを二つ(term1とterm2とする)起動する．
term1でノードを実行する．

```shell
$ . install/local_setup.bash
$ ros2 component standalone gpio_state_recognition_node ros2rasp_lecture::PubGpioStateComponentNode
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
$ ros2 pkg create gpio_state_recognition_target  --build-type ament_cmake --dependencies rclcpp gpio_state_recognition_node
```

### プログラミング

* target file
  * gpio_state_recognition_target/src/[pub_gpio_state_recognition_target.cpp](../src/gpio_state_recognition_target/src/pub_gpio_state_recognition_target.cpp)

### package.xmlやCMakeLists.txtの編集

* target file
  * gpio_state_recognition_target/[CMakeLists.txt](../src/gpio_state_recognition_target/CMakeLists.txt)

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
