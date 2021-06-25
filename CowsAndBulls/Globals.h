#pragma once

#ifndef GLOBALS_H_
#define GLOBALS_H_

#define ATTEMPTS 30

//#define W_HEIGHT 3000
//#define W_WIDTH 1500
//#define W_SCALE 1

//#define W_HEIGHT 1000
//#define W_WIDTH 500
//#define W_SCALE 0.333333333

/*
Да, несомненно глобальные переменные - это зло,
но до последнего момента здесь были define, а
потом задушила совесть, и сделал автоматический
просчет размеров и коэффициента
*/
namespace Globals {
	int __W_HEIGHT__;
	int __W_WIDTH__;
	float __W_SCALE__;
}


#endif