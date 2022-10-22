#include "Object.hpp"

class Loading {
	public:
	Loading() {
		_obj("assets/loagind.png", std::make_pair(0, 0), std::make_pair(41, 91));
	};
	private:
	Object _obj;
};