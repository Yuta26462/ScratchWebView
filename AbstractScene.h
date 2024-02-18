#pragma once

class AbstractScene
{
protected:

public:

	virtual ~AbstractScene() {};

	//描画以外の更新を実行
	virtual AbstractScene* Update() = 0;

	//描画に関することを実装
	virtual void Draw() const = 0;

	/// <summary>
	/// 文字の描画するX座標が中心になるX座標を取得する。
	///	文字列を改行("\n)で分割し、各行の空白を削除した後、最も長い行を基準に中央揃えのX座標を計算する
	/// </summary>
	/// <param name="string">描画する文字列</param>
	/// <param name="font_handle">描画に使用するフォントハンドル(未入力又は0の場合はデフォルトフォントハンドルを使用</param>
	/// <param name="margin">中央のX座標に間隔を空ける値</param>
	int GetDrawCenterX(const char* string, int font_handle = 0, int margin = 0) const;
};