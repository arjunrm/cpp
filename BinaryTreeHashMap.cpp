#include <iostream>

template <typename T>
class BinaryTree
{
public:
	T _val;
	BinaryTree* _left;
	BinaryTree* _right;

	BinaryTree(T val) : _val(val), _left(nullptr), _right(nullptr) {}

	void add(T val)
	{
		if (val < _val)
		{
			if (_left)
				_left->add(val);
			else
				_left = new BinaryTree(val);
		}
		else
		{
			if (_right)
				_right->add(val);
			else
				_right = new BinaryTree(val);
		}
	}

	bool remove(T val)
	{
		if (val < _val)
		{
			if (_left)
				_left->remove(val);
			else
				return false;
		}
		else if (val > _val)
		{
			if (_right)
				_right->remove(val);
			else
				return false;
		}
		else
		{

		}
	}

	bool find(T val)
	{
		if (val < _val)
		{
			if (_left)
				_left->find(val);
			else
				return false;
		}
		else if (val > _val)
		{
			if (_right)
				_right->find(val);
			else
				return false;
		}
		else
			return true;
	}
};

int main()
{

}