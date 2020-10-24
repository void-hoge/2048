# 2048AI

[2048](https://play2048.co/)を自動でやります。  
builtinのビット演算関係の関数を使っているのでgccが要ります。  

## モンテカルロ法のクラス
monte_carloはモンテカルロ法による探索です。  
コンストラクタの引数は以下の通り
```C++
monte_carlo::monte_carlo(
	int search_count /*何回試行するか*/,
	int max_search_depth /*試行ごとにランダムな何手動かすか*/
)
```
葉ノードにおけるボードのスコアの和を評価値として使います。

## 全探索のクラス(wip)
full_searchは全探索です。今んとこ全探索になってません。  
空きマス全てに対して枝が分岐するから木のサイズがすごいことになる気がする。  
どうすればいいんだろう。
```C++
full_search::full_search(
	int max_search_depth /*何手まで読むか*/
)
```
