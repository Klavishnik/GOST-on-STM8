
#include "GOST.H"

// Режим простой замены
// GOST_ECB(ключи, режим(0 - зашифрование, 1 - расшифрование), Данные)
void GOST_ECB (u32 * key, u32 * data)
{
  u32 temp;
  
  //32 раунда шифрования 
  for (int round = 0; round < 32; round++)
  {
    temp = 0;
    //(N1 + key_roud) mod 2^32
    //Сложение блока N1 с раундовым ключом по mod 2^32
    
    temp = (data[0] + key[round]);
      
    //Разбиение блока на 8 4-разрядных векторов
    byte Vector[8];
    for (int n = 0; n < 8; n++)
    {
      Vector[n] = (temp >> n * 4) & 0x0F;
      //Подстановка в S-блоке
      Vector[n] = SBox[n][Vector[n]];
    }
    temp = 0;
    
    //Объединение выходных векторов в блок размером 32 бита
    for (int n = 0; n < 8; n++)
    { 
      temp = temp  << 4| (Vector[n]);
    }

    //Циклический сдвиг в сторону старших разрядов на 11 бит
    temp = (temp << 11) | (temp >> 21);
    //Побитовое сложение по mod2 результата с N2
    temp = temp ^ data[1];
    //Для раундов 1 - 31 шифрования
    if (round == 31)
    {
        data[1] = temp;
    }
    else
    {
      data[1] = data[0];
      data[0] = temp;
    }
    //Для последнего раунда шифрования
   
  }
}

//Функция преобразовывает строку символов в сообщение, которое можно передать функции шифрования
void CharMessageToU32(char * input_message, u32 * output_message)
{
  //Длина строки 64 / 8 = 8 байт (символов) 
  for(int i = 0; i < 2; i++)
  {
    output_message[i] = (u32)input_message[0 + i*4] << 8;
    output_message[i] = ((output_message[i])|((u32)input_message[1 + i*4])) << 8;
    output_message[i] = ((output_message[i])|((u32)input_message[2 + i*4])) << 8;
    output_message[i] = ((output_message[i])|((u32)input_message[3 + i*4]));
  }
}

void U32ToCharMessage(u32 * input_message, char * output_message)
{
  for(int i = 0; i < 2; i++)
  {
    output_message[0 + i * 4] = (char)(( input_message[i] >> 24));
    output_message[1 + i * 4] = (char)(( input_message[i] & 0x00FF0000) >> 16);
    output_message[2 + i * 4] = (char)(( input_message[i] & 0x0000FF00) >> 8);
    output_message[3 + i * 4] = (char)(( input_message[i] & 0x000000FF));
  }
  output_message[8] = '\0';
}


void MakeRoundsKeys(u32 * input_message, u32 * output_message, short int mode)
{
  for(int i = 0; i < 32; i++)
  {
    if(mode == ENCRYPTION)
    {
        if(i < 24)
            output_message[i] = input_message[i % 8];
        
        else
            output_message[i] = input_message[7 - (i % 8)];
     }
   
    
    else if(mode == DECRYPTION)
    {
       if (i < 8)
          output_message[i] = input_message[i % 8];
      
       if (i >= 8)
          output_message[i] = input_message[7 - (i % 8)];
    }
  }
}

