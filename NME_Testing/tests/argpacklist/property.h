#pragma once

#include "../../globals.h"

using std::string;
using std::pair;
using std::shared_ptr;

template<typename T, class Allc = std::allocator<T>>
using xList = std::vector<T, Allc>;

template<typename V>
using nameVal = pair<string, V>;

#define PrVAL(x) std::make_pair(std::string(#x), &x)



class Property
{
protected:
	string name;
	void *data;

public:
	Property(const string &nm, void *val): name(nm), data(val)
	{}
	Property(): Property("", nullptr) {}
	virtual ~Property() { delete data; }

	virtual inline void* Data() const = 0;
	virtual void Data(void*) = 0;

	virtual inline operator void*() const = 0;
	virtual Property& operator= (nameVal<void*>) = 0;
};

template<typename T>
class TypedProperty : public virtual Property
{
protected:
	void *data;
public:
	typedef Property base;
	typedef T val_t;

	TypedProperty(const string &nm, val_t *val): base(nm, val)
	{}
	TypedProperty(): base()
	{}
	~TypedProperty() {}

	inline val_t* Data() const
	{
		val_t *tmp = static_cast<val_t*>(data);
		return tmp;
	}
	void Data(val_t *val)
	{
		data = val;
	}

	inline operator val_t*() const
	{
		val_t *tmp = static_cast<val_t*>(data);
		return tmp;
	}

	TypedProperty& operator= (nameVal<void*> value)
	{
		name = value.first;
		data = value.second;
	}
};

typedef xList<shared_ptr<Property>> plist_t;
