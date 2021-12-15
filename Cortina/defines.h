#pragma once

#define SERIAL_BAUDRATE 9600

#define TEMPO_LOOP_MILLIS 100 //em milis
#define TEMPO_ENTRE_PRINT 2000 //em milis
#define FAIXA_SEGURANCA_VALOR_ANALOGIC_VERIFICACAO 8

//---

//NANO
#define SEN_IR A4
#define SEN_CORTINA_POTENCIOMETRO_ABAS A5
#define SEN_CORTINA_POTENCIOMETRO_ABAS_CONFIG_MIN A7
#define SEN_CORTINA_POTENCIOMETRO_ABAS_CONFIG_MAX A6
#define SEN_CORTINA_INICIO 10
#define SEN_CORTINA_MEIO 9
#define SEN_CORTINA_FIM 8
#define SEN_BLACKOUT_INICIO 7
#define SEN_BLACKOUT_MEIO 6
#define SEN_BLACKOUT_FIM 5
#define ACAO_CORTINA_ABA1 11
#define ACAO_CORTINA_ABA2 12
#define ACAO_CORTINA_COMPRIMENTO 4
#define ACAO_CORTINA_BLACKOUT 3

//---


//
//// linha 1
#define CR_ABRE_TUDO 69//0xFFA25D
#define CR_LUZ_DIARIA 70//0xFF629D
#define CR_FECHA_TUDO 71//0xFFE21D
//
//// linha 2
//#define CR_CORTINA_MAIS 68//0xFF22DD
#define CR_ABAS_000g 64//0xFF02FD
//#define CR_BLACKOUT_MAIS 67//0xFFC23D
//
//// linha 3
//#define CR_CORTINA_MENOS 7//0xFFE01F
#define CR_ABAS_045g 21//0xFFA857
//#define CR_BLACKOUT_MENOS 9//0xFF906F
//
//// linha 4
#define CR_CORTINA_ABRIR 22//0xFF6897
#define CR_ABAS_090g 25//0xFF9867
#define CR_BLACKOUT_ABRIR 13//0xFFB04F
//
//// linha 5
#define CR_CORTINA_MEIO 12//0xFF30CF
#define CR_ABAS_135g 24//0xFF18E7
#define CR_BLACKOUT_MEIO 94//0xFF7A85
//
//// linha 6
#define CR_CORTINA_FECHAR 8//0xFF10EF
#define CR_ABAS_180g 28//0xFF38C7
#define CR_BLACKOUT_FECHAR 90//0xFF5AA5
//
//// linha 7
//#define CR_PANIC1 66//0xFF42BD
//#define CR_LOG 82//0xFF4AB5
//#define CR_PANIC3 74//0xFF52AD