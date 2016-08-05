#pragma once

#include "drollerbase.h"

using std::iterator;


namespace utils
{
	struct DieValueIs;


	template<uint8_t SIDES>
	class DiceRoller: public IDiceRoller
	{
	public:
		typedef Die<SIDES> Die_t, *Die_i;
		typedef std::vector<Die_t> Dice_c, *Dice_ci;
		typedef Dice_c::iterator DIter_t;

	protected:
		Dice_c _dice;
		uint16_t _value;

		void sort()
		{ std::sort(_dice.begin(), _dice.end()); }

		void recalculateValue()
		{
			_value = 0;
			for (Die_t d: _dice)
				_value += (uint16_t)d.value();
		}

		DiceRoller(Dice_c dice): _dice(dice), _value(0)
		{
			sort();
			recalculateValue();
		}


	public:
		DiceRoller(uint8_t num): _value(0)
		{
			if (num < 1) return;

			_dice = Dice_c(num);

			roll();
		}

		~DiceRoller()
		{
			_dice.clear();
		}

		void roll()
		{
			_value = 0;

			for (Die_t &d : _dice)
				_value += d.getRoll();

			sort();

		}

		uint16_t getRoll()
		{
			roll();
			return _value;
		}

		void rerollValuesOf(uint8_t val)
		{
				
			DIter_t i = _dice.begin(), end = _dice.end(), old;
			while (true)
			{
				old = i;
				i = std::find_if(i, _dice.end(), DieValueIs(val));

				if (i == end) break;

				i->roll();
			}
			sort();
			recalculateValue();

		}

		void rerollLowest(uint8_t n)
		{
			n = clamp(n, 1, count()-1)-1;

			sort();
			for (uint8_t i = 0; i<n; i++)
				_dice[i].roll();

			sort();
			recalculateValue();
		}
		void rerollLowest()
		{ rerollLowest(1); }

		void rerollHighest(uint8_t n)
		{
			short len = count() - 1;
			n = clamp(n, 1, len)-1;
			

			sort();

			for (int i=len; i>=len-n; i--)
				_dice[i].roll();

			sort();
			recalculateValue();
		}
		void rerollHighest()
		{ rerollHighest(1); }

		Die_t& operator[] (int i)
		{
			i = clamp(i, count()*-1, count()-1);

			if (i < 0)
				i += count();

			return _dice[i];
		}

		
		DiceRoller dropLowest(uint8_t n)
		{
			n = clamp(n, 1, count());
			Dice_c tmp(_dice);

			tmp.erase(tmp.begin(), tmp.begin()+n-1);
			DiceRoller dtmp(tmp);
			return dtmp;
		}

		DiceRoller dropLowest()
		{ return dropLowest(1); }
		
		DiceRoller dropHighest(uint8_t n)
		{
			n = clamp(n, 1, count());
			Dice_c tmp(_dice);

			tmp.erase(tmp.end() - (n - 1), tmp.end());
			DiceRoller dtmp(tmp);
			return dtmp;
		}
		DiceRoller dropHighest()
		{ return dropHighest(1); }

		uint8_t count()
		{ return (uint8_t)_dice.size(); }

		void count(uint8_t n)
		{
			n = clamp(n, 1, 255);

			_dice.resize(n);
		}
		
		void increment()
		{ count(count() + 1); }
		void decrement()
		{ count(count() - 1); }

	};

	struct DieValueIs
	{
		uint8_t _find;
		DieValueIs(uint8_t n): _find(n) { }

		template<uint8_t N>
		bool operator() (const Die<N> &d)
		{
			return d.value() == _find;
		}
	};
}
