#ifndef GOST_INCLUDE
#define GOST_INCLUDE


#include "types.h"

#define ENCRYPTION 0
#define DECRYPTION 1


//-----------VARIABLES------------
//S блоки ЦБ
/*
static const byte SBox[8][16] =
{
    {4u,10u,9u,2u,13u,8u,0u,14u,6u,11u,1u,12u,7u,15u,5u,3u},
    {14u,11u,4u,12u,6u,13u,15u,10u,2u,3u,8u,1u,0u,7u,5u,9u},
    {5u,8u,1u,13u,10u,3u,4u,2u,14u,15u,12u,7u,6u,0u,9u,11u},
    {7u,13u,10u,1u,0u,8u,9u,15u,14u,4u,6u,12u,11u,2u,5u,3u},
    {6u,12u,7u,1u,5u,15u,13u,8u,4u,10u,9u,14u,0u,3u,11u,2u},
    {4u,11u,10u,0u,7u,2u,1u,13u,3u,6u,8u,5u,9u,12u,15u,14u},
    {13u,11u,4u,1u,3u,15u,5u,9u,0u,10u,14u,7u,6u,8u,2u,12u},
    {1u,15u,13u,0u,5u,7u,10u,4u,9u,2u,3u,14u,6u,11u,8u,12u}
};
*/
//id-tc26-gost-28147-param-Z
static const byte SBox[8][16] =
 {{0xC,0x4,0x6,0x2,0xA,0x5,0xB,0x9,0xE,0x8,0xD,0x7,0x0,0x3,0xF,0x1},
 {0x6,0x8,0x2,0x3,0x9,0xA,0x5,0xC,0x1,0xE,0x4,0x7,0xB,0xD,0x0,0xF},
 {0xB,0x3,0x5,0x8,0x2,0xF,0xA,0xD,0xE,0x1,0x7,0x4,0xC,0x9,0x6,0x0},
 {0xC,0x8,0x2,0x1,0xD,0x4,0xF,0x6,0x7,0x0,0xA,0x5,0x3,0xE,0x9,0xB},
 {0x7,0xF,0x5,0xA,0x8,0x1,0x6,0xD,0x0,0x9,0x3,0xE,0xB,0x4,0x2,0xC},
 {0x5,0xD,0xF,0x6,0x9,0x2,0xC,0xA,0xB,0x7,0x8,0x1,0x4,0x3,0xE,0x0},
 {0x8,0xE,0x2,0x5,0x6,0x9,0x1,0xC,0xF,0x4,0xB,0x0,0xD,0xA,0x3,0x7},
 {0x1,0x7,0xE,0xD,0x0,0x5,0x8,0x3,0x4,0xF,0xA,0x6,0x9,0xC,0xB,0x2}};
//-------------END-------------------

//----------FUNCTIONS-------------------


//Функция из 256 бит ключа, разхбитых на 8 чисел по 32 бита, собирает массив их 32 ключей по 32 бита
// mode - режим работы (шифрование / дешифроавние) 
void MakeRoundsKeys(u32 * input_message, u32 * output_message, short int mode);

//Функция преобразовывает строку символов в сообщение, которое можно передать функции шифрования
void CharMessageToU32(char * input_message, u32 * output_message);

//Функция преобразовывает строку u32 в  текстовое сообщение 
void U32ToCharMessage(u32 * input_message, char * output_message);

//Режим простой замены
//тип данных u32, так как он = 32 битам.
//ключ передаем как массив раундовых 32 битных ключей в кол-ве 8 штук
//данные передаем как массив из двух элементов по 32 бита
void GOST_ECB (u32 * key, u32 * data);

// Режим гаммирования
// GOST_Gamma(ключи, синхропосылка 1, синхропосылка 1, Входные данные, Выходные данные, объем данных в байтах)
void GOST_Gamma (unsigned int * key, unsigned int S1, unsigned int S2, unsigned int * InData, unsigned int * OutData, short int size);

// Режим выработки имитовставки
// GOST_MAC(ключи, переменная для имитовставки, данные, объем данных в байтах)
void GOST_MAC (unsigned int * key, unsigned int * MAC, unsigned int * Data, short int size);

// Сравнение двух массивов
// Array_Comparing (массив Array_1, массив Array_2, размер массива)
int Array_Comparing (unsigned int * Array_1, unsigned int * Array_2, short int size);
//-------------END-------------------

#endif
