The MIT License (MIT)

Copyright (c) 2015 S74nk0 - Stanko Krstić

#pragma once

#include "ui/CocosGUI.h"

class HelperFunctions
{
public:
	static void setIntToLabel(cocos2d::ui::TextBMFont *label, int value, const char * format = "%d") {
		char buf[12];
		sprintf(buf, format, value);
		label->setString(buf);
	}
};

//namespace HF = HelperFunctions;
using HF = HelperFunctions;