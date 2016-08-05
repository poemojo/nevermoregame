#include <boost/bimap.hpp>
#include "globals.h"

#include "tests/store/util.h"

using std::cout;
using std::endl;
using std::string;
using std::pair;
using std::map;
using std::set;

typedef char *cstr;

#if 0
template<typename T>
using is_void = std::is_same<T, void>;

template<typename T>
void s_memcpy(void *&dest, const T *src)
{
	memcpy(dest, src, sizeof(T));
}

template<typename T>
void deleter(T *p) { delete p; }

template<typename _RT, typename... Params>
class Callback
{
public:
	typedef _RT return_t;

	virtual return_t invoke(Params...) = 0;
};

template<typename _RT, typename... Params>
class FunctionCallback : public virtual Callback<_RT, Params...>
{

public:
	typedef Callback<_RT, Params...> base;
	typedef typename base::return_t return_t;

	CALLBACK(return_t, Function)(Params...);

protected: Function_cb _function;
public:
	FunctionCallback(Function_cb func): _function(func)
	{}

	return_t invoke(Params... ps)
	{ return (*_function)(ps...); }
};

template<typename _RT, typename _ClTy, typename... Params>
class MethodCallback : public virtual Callback<_RT, Params...>
{
public:
	typedef Callback<_RT, Params...> base;
	typedef typename base::return_t return_t;
	typedef _ClTy Caller_t;

	MCALLBACK(_RT, _ClTy, Method)(Params...);
protected:
	void *_obj;
	Method_cb _method;

public:
	MethodCallback(Caller_t *obj, Method_cb method): _obj(obj), _method(method)
	{	}

	return_t invoke(Params... ps)
	{
		Caller_t *o = static_cast<Caller_t*>(_obj);
		return (o->*_method)(ps...);
	}
};

template<typename _RT, typename... Params>
class Delegate
{
public:
	typedef _RT return_t;
	typedef Callback<_RT, Params...> BCB_t;
	CALLBACK(_RT, Function)(Params...);

	typedef FunctionCallback<_RT, Params...> FCB_t;
	template<class Caller>
	using MCB_t = MethodCallback<_RT, Caller, Params...>;

	template<class Caller>
	using Method_cb = typename MCB_t<Caller>::Method_cb;

private: BCB_t *_callback;
public:
	Delegate(Function_cb func): _callback(new FCB_t(func))
	{ }

	template<class Caller>
	Delegate(Caller *obj, Method_cb<Caller> method)
		: _callback(new MCB_t<Caller>(obj, method))
	{ }

	~Delegate(void)
	{ }


	return_t operator()(Params... ps)
	{ return _callback->invoke(ps...); }
};



template<typename _RT, typename... Args>
inline static Delegate<_RT, Args...> makeDelegate(CBPARAM(_RT, func, Args...))
{
	Delegate<_RT, Args...> d(func);
	return d;
}

template<class Caller, typename _RT, typename... Args>
inline static Delegate<_RT, Args...> makeDelegate(Caller *obj, MCBPARAM(_RT, Caller, method, Args...))
{
	Delegate<_RT, Args...> d(obj, method);
	return d;
}

class A
{
protected: int x;
public:
	A(int n): x(n) { }
	A(const A& rhs)
	{
		x = rhs.x;
	}
	A(): A(0) { }

	inline int X() { return x; }
	void X(int n) { x = n; }

	int incr() { return ++x; }
	inline int sum(int b) { return x+b; }
};


void printStuff(string str, int one, int two)
{
	cout << str << " " << one << " " << two << endl;
}
#endif





int main()
{
	std::vector<int> v({10,10,11,4,10,6,11});
	map<string, int> m;
	
	m["hi"] = 1;
	m["foo"] = 1;
	m["bar"] = 2;
	m["baz"] = 3;

	rm_duplicates(v);
	rm_duplicates(m);

	printf("map<string, int>\n");
	for (auto e : m)
		printf("Key: %s\nValue:%d\n\n", e.first.c_str(), e.second);

	cout << endl << endl;

	for (int e : v)
		cout << e << endl;

	cout << endl << "Press Any Key to Quit...";


	getchar();
}
