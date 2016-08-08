#pragma once

#include "../../globals.h"

using std::string;
using std::endl;

using utils::xList;
using utils::rgbCode_t;
using utils::oss;
using utils::E;
using utils::cnd_str;
using utils::dict;

namespace nevermore
{	
	enum class Gender : uint8_t
	{
		Unknown = 0,
		Male = 1,
		Female = 2
	};

	enum class EDTypesID : uint8_t
	{
		Attribute, InfoBlock
	};

	template<class _Col>
	struct IterTypes
	{
		ctypedef _Col::iterator iter;
		ctypedef _Col::const_iterator cn_iter;
		ctypedef _Col::reverse_iterator rev_iter;
		ctypedef _Col::const_reverse_iterator cn_rev_iter;

		template<class T>
		struct is_iter : std::false_type { };
		template<>
		struct is_iter<iter> : std::true_type {};
		template<>
		struct is_iter<cn_iter> : std::true_type {};
		template<>
		struct is_iter<rev_iter> : std::true_type {};
		template<>
		struct is_iter<cn_rev_iter> : std::true_type {};

		template<class T, typename RT = void>
		using cen_iter_t = std::enable_if_t<is_iter<T>::value, RT>;


	};

	typedef struct ColorType
	{
		rgbCode_t data;

		ColorType(uint32_t value): data(value)
		{ }
		ColorType(uint8_t r, uint8_t g, uint8_t b)
			: ColorType(RGB_MAKE(r,g,b))
		{ }
		ColorType(uint8_t (&rgb)[3]): ColorType(rgb[0], rgb[1], rgb[2])
		{ }
		ColorType(): ColorType(0)
		{ }

		inline uint8_t red()
		{ return RGB_GETR(data); }
		inline uint8_t green()
		{ return RGB_GETG(data); }
		inline uint8_t blue()
		{ return RGB_GETB(data); }
		
		void setR(uint8_t r)
		{ data = RGB_SETR(data, r); }
		void setG(uint8_t g)
		{ data = RGB_SETG(data, g); }
		void setB(uint8_t b)
		{ data = RGB_SETB(data, b); }
		
		inline cstr hex()
		{
			char buf[6];
			int n = sprintf(buf, "%06X", (uint32_t)data);
			return buf;
		}

		inline bool operator== (const uint32_t &test)
		{ return (data.value == test); }
		inline bool operator== (const rgbCode_t &test)
		{ return (data == test); }
		inline bool operator== (const ColorType &rhs)
		{ return (*this == rhs.data); }

	} color_t;

	class ColorStore
	{
	public:
		typedef dict<color_t> store_t;
		typedef IterTypes<store_t> its;

		ctypedef store_t::value_type pos_t;


		typedef struct cmp_val
		{
			cmp_val(color_t c): _c(c) { }
			cmp_val(uint32_t v): _c(v) { }
			cmp_val(uint8_t r, uint8_t g, uint8_t b)
				: _c(r,g,b)
			{ }
			cmp_val(uint8_t(&rgb)[3]): cmp_val(rgb[0], rgb[1], rgb[2])
			{ }

			bool operator() (pos_t p)
			{ return (p.second == _c ); }
		private:
			color_t _c;
		} cmp_val;

	private: 
		store_t _data;

		void filter()
		{ utils::rm_duplicates(_data); }

	public:
		template<typename _Iter>
		ColorStore(_Iter first, _Iter last): _data(first, last)
		{ filter(); }
		ColorStore(store_t src): _data(src)
		{ filter(); }
		ColorStore(string key, color_t value)
		{
			_data[key] = value;
		}
		ColorStore()
		{ }

		inline store_t& data()
		{
			filter();
			return _data;
		}
		operator store_t&()
		{ return data(); }

		operator store_t() const
		{ return _data; }

		color_t& find(string key)
		{
			its::iter it = data().find(key);
			assert(it != _data.end());

			return it->second;
		}

		template<typename... Ts>
		string find_key(Ts... value)
		{
			filter();
			its::iter it = std::find_if(_data.begin(), _data.end(), cmp_val(value...));
			assert(it != _data.end());

			return it->first;
		}

		color_t& operator[] (string key)
		{ return _data[key]; }

		template<typename... Ts>
		string operator() (Ts... args)
		{ return find_key(args); }

	};


	

	typedef struct DescriptionName
	{
		typedef xList<string>::iterator m_iter;
		typedef xList<string>::const_iterator m_cn_iter;

		string name;
		xList<string> prefixes, suffixes;

		template<class _Iter1, class _Iter2>
		DescriptionName(string name, _Iter1 pBeg, _Iter1 pEnd, _Iter2 sBeg, _Iter2 sEnd)
			: name(name), prefixes(pBeg, pEnd), suffixes(sBeg, sEnd)
		{}

		template<size_t N1, size_t N2>
		DescriptionName(string name, string(&pref)[N1], string(&suff)[N2])
			: DescriptionName(name, pref, pref + N1, suff, suff + N2)
		{}

		DescriptionName(string name, xList<string> pref, xList<string> suff)
			: DescriptionName(name, pref.begin(), pref.end(), suff.begin(), suff.end())
		{}

		DescriptionName(string name): name(name)
		{}

		DescriptionName(): DescriptionName("")
		{}

		inline operator string() const
		{
			if (prefixes.size() > 0)
				for (int i = 0; i < prefixes.size(); i++)
					oss << prefixes[i] << cnd_str(i == (prefixes.size()-1), ", ", " ");

			oss << name;

			if (suffixes.size() > 0)
				for (int i = 0; i < suffixes.size(); i++)
					oss << cnd_str(i == 0," of ", ", of ") << suffixes[i];

			return oss.str();
		}

	} desc_name_t;

	typedef struct USLength
	{
		static const uint8_t INCHES_IN_FOOT = 12;
		static const uint8_t PRECISION = 3;
		uint16_t raw_inches;

		USLength(uint16_t inches): raw_inches(inches)
		{ }
		USLength(): USLength(0)
		{ }

		USLength& operator= (uint16_t inches)
		{
			raw_inches = inches;
			return *this;
		}

		operator string() const
		{
			uint16_t feet = raw_inches / INCHES_IN_FOOT;
			uint16_t inches = raw_inches % INCHES_IN_FOOT;
			
			oss << feet << "'" << std::setfill('0') << std::setw(2) << inches;
			return oss.str();
		}

		operator double() const
		{
			double tmp = ((double)raw_inches) / INCHES_IN_FOOT;
			return (round(tmp * B10(PRECISION)) / (double)B10(PRECISION));
		}
	} us_len_t;


	typedef struct USWeight
	{
		static const uint8_t OUNCES_IN_POUND = 16;
		static const uint8_t PRECISION = 3;

		uint16_t raw_ounces;

		USWeight(uint16_t ounces): raw_ounces(ounces)
		{ }

		USWeight(): USWeight(0)
		{ }

		USWeight& operator= (uint16_t ounces)
		{
			raw_ounces = ounces;
			return *this;
		}

		operator string() const
		{
			uint16_t pounds = raw_ounces / OUNCES_IN_POUND;
			uint16_t ounces = raw_ounces % OUNCES_IN_POUND;

			oss << pounds << "lbs. " << ounces << "oz";
			return oss.str();
		}

		operator double() const
		{
			double tmp = ((double)raw_ounces)/OUNCES_IN_POUND;
			return (round(tmp * B10(PRECISION)) / (double)B10(PRECISION));
		}

	} us_wt_t;


	template<size_t N>
	struct cbuf_ext { char data[N]; };

	typedef struct NMColor
	{
		enum class Presets : uint32_t
		{
			CT_White = 0xffffff,
			CT_Black = 0x000000,
			CT_Gray = 0x808080,
			CT_Red = 0xff0000,
			CT_Green = 0x00ff00,
			CT_Blue = 0x0000ff
		};

		cstr name;
		color_t color;

		NMColor(cstr nm, uint32_t cval): name(nm), color(cval)
		{	}
		NMColor(cstr nm, Presets cval): NMColor(nm, (uint32_t)cval)
		{ }
		NMColor(cstr nm): name(nm)
		{ }
		NMColor(): NMColor("")
		{ }

	} NMColor;

	typedef struct ActorDescriptionInfo
	{
		Gender   gender;
		us_len_t height;
		us_wt_t  weight;
		uint16_t age;



	} actor_dinfo_t;

}
