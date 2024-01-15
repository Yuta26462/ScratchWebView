#pragma once
#include <memory>

class Object
{
public:
	//���W�\����
	struct Location
	{
		int x;
		int y;
	};

protected:
	//���W
	Location location;
	//�傫��
	int size;

	//�摜�n���h��
	std::shared_ptr<int> image;

private:
	

public:
	virtual ~Object() {};
	virtual void Update() = 0;
	void Draw() const;

	Location GetLocation() { return location; }
	int GetSize() { return size; }
};

