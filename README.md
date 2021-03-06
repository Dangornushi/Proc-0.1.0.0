# Proto言語について

この言語は、高い拡張性とわかりやすい文法を意識して設計されました。

- わかりやすい文法
- 動的型付け
- VMの動作方式

## わかりやすい文法

例えば、関数を定義するときは
C言語の場合：

```main.c
int main() {
```

ですがProto言語の場合：

```main.pr
fn main(0) {
```

となります。これが何を意味しているかというと、

- 関数定義に型をつけることは不必要
- 引数は明示的に記す必要がある

ということです。
これは、コードの量を削減できる、またわかりやすいというメリットがあります。
波括弧こそ書かなければなりませんが、これは構文をわかりやすくするためのものであり、それを除けばわかりやすくかつ書くことがでます。プログラミング初心者に優しい設計です。

### 関数定義

```
fn  main(0) {
    //何かしらの処理
    end
}
```
全ての処理はmain関数が記述されていないと始まらず、今のバージョンでは関数の外や別ファイルにに変数の定義はできません。

## if文

```
// x = int

if x > 12 {
    //何かしらの処理
}
```
比較演算子には「>, < ==」が使用可能。

## while文

```
// x = int / 直接の整数でも問題ない

while x {
    //何かしらの処理
}
```

## 足し引き掛け割る

関数定義の際にすることが可能（足し、引き、掛け、割る）

```
//足し

int x = 10 + 2

//引き

int y = 14 - 2

//掛け

int z = 3 * 4

//割る

int s = 24 / 2

```

## 関数呼び出し

```
~~~
int x = 10
int y = 2
sub(x, y)
~~~

~~~
fn sub( x,y ) {
    msg x
    msg y
    end
}

```

引数のコンマとデータの区切りに空白を入れることはできない。

## 終わりに

この言語はまだ開発途中です。もしバグなどありましたらぜひプルリクなどでお知らせください。
また、コンタクトを取りたい方は　https://twitter.com/dangomu39300363　までお越しください。s
