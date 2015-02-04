#ifndef FLAGS_H
#define FLAGS_H

template<typename Enum>
class Flags
{
public:
	inline Flags(Enum e) : _value(int(e)) {}
	inline Flags(int e) : _value(int(e)) {}

	inline operator int() const { return _value;  }

	inline Flags &operator&=(int mask) { _value &= mask; return *this; }
	inline Flags &operator|=(int mask) { _value |= mask; return *this; }
	inline Flags &operator^=(int mask) { _value ^= mask; return *this; }

	inline Flags &operator&=(Enum mask) { _value &= int(mask); return *this; }
	inline Flags &operator|=(Enum mask) { _value |= int(mask); return *this; }
	inline Flags &operator^=(Enum mask) { _value ^= int(mask); return *this; }

	inline Flags operator&(Enum mask) { return Flags(_value & mask); }
	inline Flags operator|(Enum mask) { return Flags(_value | mask); }
	inline Flags operator^(Enum mask) { return Flags(_value ^ mask); }
	inline Flags operator~() const { return Flags(~_value); }
	inline bool operator!() const { return !_value; }

private:
	int _value;
};

#define W_DECLAGE_FLAGS(FlagsName, Enum) \
typedef Flags<Enum> FlagsName;

#endif //FLAGS_H