#pragma once
#include <memory>

class Object
{
public:
	//座標構造体
	struct Location
	{
		int x;
		int y;
	};

protected:
	//座標
	Location location;
	//大きさ
	int size;

	//画像ハンドル
	std::shared_ptr<int> image;

private:
	

public:
	virtual ~Object() {};
	virtual void Update() = 0;
	void Draw() const;

	Location GetLocation() { return location; }
	int GetSize() { return size; }
};

