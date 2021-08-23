[Topページへ](README_JP.md)

# 概要
ここではpigpiodを使ってハードウェアにアクセスする仕方を簡単に紹介する．
対象言語はc++である．<br>
まず，このリポジトリで使用する回路を下図に示す．
図では二つのRaspberry Piを使用しているが，一つしかない場合はpi2を無視してもらって大丈夫．
ブレッドボード上の回路などを変更する必要はない．

![target circuit](docs/figs/led_switch.png)

# 回路の作成
図のとおり，回路を作成する．

# プログラムの作成
プログラムを作成するための諸情報は公式の[pigpiod C Interface](http://abyz.me.uk/rpi/pigpio/pdif2.html)を参照のこと．
特に，`ESSENTIAL`と`BASIC`は重要となる．<br>
プログラムの流れは以下のようになる．

1. pigpiodを使用するための初期化
  * pigpio_start( )
1. 使用するGPIOのモード設定
  * set_mode( )
1. GPIOの利用
  * gpio_read( ), gpio_write( )
1. pigpiodの終了処理
  * pigpio_stop( )

pigpioデーモンはネットワークを通して複数のRasperry Piを扱うことができる．
そのため，どのRaspberry Piへの指令なのか区別する必要があり，pigpio_start関数の返り値でそれを行っている．

## 簡単な使用方法

* ソースファイル
  * [src/pigpio_library_test/src/on_off_siso.cpp](../src/pigpio_library_test/src/on_off_siso.cpp)

### ビルドと実行
ソースファイルをDLするか自分でつくって準備し，以下ようにビルド・実行する．

```shell
$ g++ -Wall -pthread -o on_off_siso on_off_siso.cpp -lpigpiod_if2
$ ./on_off_siso
```

実行後，スイッチを押すとledが消灯し，スイッチを離すとledが点灯する．

### 説明

<details><summary>pigpiodを使用するための初期化</summary><div>

[on_off_siso.cppの7行目から11行目](../src/pigpio_library_test/src/on_off_siso.cpp#L7-L10)で初期化を行っており，引数で使用するRasperry Piを指定している．
一つ目の引数が`NULL`の場合は接続先がlocalhostとなり，二つ目の引数が`NULL`の場合接続ポートが8888となる．
プログラムを実行しているRaspberry Piを使用する(ネット経由で他のRaspberry Piを使用しない)のであれば，`NULL`でよい．
</div></details>
<details><summary>使用するGPIOのモード設定</summary><div>

[on_off_siso.cppの13行目から16行目](../src/pigpio_library_test/src/on_off_siso.cpp#L13-L16)でGPIOの使用モードを指定している．<br>
GPIO21にはledがつながっており，`出力`として使用する．
そこで[14行目](../src/pigpio_library_test/src/on_off_siso.cpp#L14)にてGPIO21を出力(OUTPUT)として設定している．<br>
またGPIO26にはスイッチがつながっており，`入力`として使用する．
同じように[16行目](../src/pigpio_library_test/src/on_off_siso.cpp#L16)にてGPIO26を入力(INPUT)として設定している．
</div></details>
<details><summary>GPIOの利用</summary><div>

[on_off_siso.cppの18行目から22行目](../src/pigpio_library_test/src/on_off_siso.cpp#L18-L22)でスイッチの状態によってledの点灯/消灯を制御している．<br>
[19行目](../src/pigpio_library_test/src/on_off_siso.cpp#L19)ではGPIO26の状態を読んで，変数`input`に保存している．
ここでGPIO26のプルダウン抵抗によって，スイッチが押されるとGPIO26はHIGHになり`input`に`1`が保存される．
またスイッチが離されるとGPIO26はLOWになり，`input`には`0`が保存される．<br>
[20行目](../src/pigpio_library_test/src/on_off_siso.cpp#L20)では`input`の値がGPIO21に出力される．
ここでGPIO21が`0`の時ledが点灯し`1`の時ledは消灯する回路となっている(シンクロジック)．
そのため，スイッチを押すと`input`が`1`になりGPIO21が`1`を出力し，ledが消灯する．<br>
また[21行目](../src/pigpio_library_test/src/on_off_siso.cpp#L21)にて1秒間スリープし，ledの状態を保っている．
</div></details>
<details><summary>pigpiodの終了処理</summary><div>

[24行目](../src/pigpio_library_test/src/on_off_siso.cpp#L24)にてpigpiodの終了処理をしている．
</div></details>

## callback関数を使用した方法

* ソースファイル
  * [src/pigpio_library_test/src/on_off_siso_with_callback.cpp](../src/pigpio_library_test/src/on_off_siso_with_callback.cpp)

### ビルドと実行
ソースファイルをDLするか自分でつくって準備し，以下ようにビルド・実行する．

```shell
$ g++ -Wall -pthread -o on_off_siso_with_callback on_off_siso_with_callback.cpp -lpigpiod_if2
$ ./on_off_siso_with_callback
```

実行後，スイッチを押すとledが消灯し，スイッチを離すとledが点灯する．

### 説明
