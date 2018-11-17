#pragma once

#include <memory>

class Color
{
public:
	enum
	{
		RED,
		GREEN,
		BLUE,
		ALPHA,
		WHITE,
		BLACK
	};

public:
	Color();
	Color(const float* const data) { memcpy(_dataColor, data, (sizeof(float) * 4)); }
	Color(const float r, const float g, const float b);
	Color(const float r, const float g, const float b, const float a);
	Color(const int templateColor);

	//inline Color& operator=(const int templateColor) { *this = Color(templateColor); }
	inline Color& operator=(const Color& color)		{ memcpy(_dataColor, color._dataColor, (sizeof(float) * 4));	return *this; }
	inline Color& operator=(const float* const data){ memcpy(_dataColor, data, (sizeof(float) * 4));			return *this; }
	inline bool operator==(const Color& color) {
		if (_dataColor[RED] == color._dataColor[RED] && _dataColor[GREEN] == color._dataColor[GREEN] && _dataColor[BLUE] == color._dataColor[BLUE] && _dataColor[ALPHA] == color._dataColor[ALPHA])  return true;
		return false;
	}

	inline float& operator[](const size_t index) { return _dataColor[index]; }
	
	inline void setColor(const Color& color)		{ memcpy(_dataColor, color._dataColor, (sizeof(float) * 4)); }
	inline void set(const float* const data){ memcpy(_dataColor, data, (sizeof(float) * 4)); }

	inline void setRed(float const r)	{ _dataColor[RED] = r;	}
	inline void setGreen(float const g)	{ _dataColor[GREEN] = g;	}
	inline void setBlue(float const b)	{ _dataColor[BLUE] = b;	}
	inline void setAlpha(float const a) { _dataColor[ALPHA] = a;	}

	inline float getRed()	const { return _dataColor[RED];	}
	inline float getGreen()	const { return _dataColor[GREEN];	}
	inline float getBlue()	const { return _dataColor[BLUE];	}
	inline float getAlpha()	const { return _dataColor[ALPHA];	}

	inline const float* const getColorPtr() const { return _dataColor; }

private:
	float _dataColor[4];

private:
	static float _dataColorStatic[4];
};
