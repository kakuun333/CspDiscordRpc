#pragma once
#ifndef MACRO_UTIL_H
#define MACRO_UTIL_H



/*
* 獲取變數名稱
* 例：GetVariableName(MyVar)
* @param Variable 變數
*/ 
#define GetVariableName(Variable) (#Variable)

#endif // MACRO_UTIL_H