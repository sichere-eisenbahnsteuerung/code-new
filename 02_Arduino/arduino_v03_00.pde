/*
 *    Der Code ermöglicht das Senden vom Microcontoller zum PC. Die entgegengesetzte Richtung ist nicht möglich.
 *    Copyright (C) 2011 Fabian Sobota
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file		arduino_v03_00.pde
 * @author	Fabian Sobota
 * 
 * @brief	Die Datei beinhaltet den Code für den Arduino
 *
 *				Der Code ermöglicht das Senden vom Microcontoller zum PC.
 *				Die entgegengesetzte Richtung ist nicht möglich.
 * @date		14.12.2010
 */


// include the SoftwareSerial library so you can use its functions:
#include <Wire.h>

#define ON 1
#define OFF 0
#define RX_PIN 2
#define TX_PIN 3
#define LED_PIN_I2C 13
#define LED_PIN_RS232 13
#define MAX_MELDUNGEN 30
#define START_BYTE 2
#define END_BYTE 3
#define CRC32POLY 0x04C11DB7 // CRC-32 Polynom 

// Puffer der Nachrichten 
	//Byte 0 = lenght,
	//Byte 1-lenght = Inhalt
byte message_i2c[MAX_MELDUNGEN][256];
byte message_rs232[MAX_MELDUNGEN][256];

// Anzahl der aktuell gepufferten Nachrichten
int puffered_msg_i2c;		//von i2c   nach rs232
int puffered_msg_rs232;		//von rs232 nach i2c

/**
 * @brief	Setup-Funktion - wird vom Arduino einmal zu Beginn aufgerufen.
 *
 *			Die Setup-Funktion initialisiert alle vom Arduino benötigten 
 *			Variablen/Pins/Software-Komponenten 
 *
 * @return void
 */
void setup()
{
   // Initialisiere Variablen
   puffered_msg_i2c=0;
   puffered_msg_rs232=0;
 
   // Definiere den jeweiligen Pin-Modus
   pinMode(RX_PIN, INPUT);
   pinMode(TX_PIN, OUTPUT);
	pinMode(LED_PIN_RS232, OUTPUT);
	// Definiere I2C Pin nur, wenn sich dieser vom rs232 unterscheidet
	if (LED_PIN_RS232!=LED_PIN_I2C)	
		pinMode(LED_PIN_I2C, OUTPUT);
   
   // Setze die Datenrate des SoftwareSerial-Port
   Serial.begin(9600);
   // Verbinde zum I^2C-Bus mit Adresse #4
   Wire.begin(4);
	// Fange Events ab
   Wire.onReceive(receiveEvent_i2c);
}

/**
 * @brief	loop-Funktion - wird vom Arduino nach der Setup-Funktion in einer Endlosschleife aufgerufen
 *
 *			Die loop-Funktion empfängt ggf. Daten des PC's und überprüft anschließend den Puffer vom i2c-Bus.
 *
 * @return void
 */
void loop()
{
	receive_rs232();
	//Überprüfe Puffer
	check_puffer();
}

/**
 * @brief	Ruft die Überprüfung des i2c-Puffers auf.
 *
 *
 * @return void
 */
void check_puffer()
{
	//Überprüfe den i2c->RS232 Puffer
	check_i2c_puffer();
	
	//Überprüfung des RS232->i2c Puffer deaktiviert
	//check_rs232_puffer();
}

/**
 * @brief	Überprüft den i2c-Puffer
 *
 *				Überprüft den i2c-Puffer, setzt den Nachrichten-Stand zurück
 *				und Löscht ggf. das Lämpchen für den Pufferüberlauf
 * @return void
 */
void check_i2c_puffer()
{
	//Puffer von i2c nach RS232
	if(puffered_msg_i2c > 0) 
	{
   	send_all_messages();
   	puffered_msg_i2c = 0;
		set_led(LED_PIN_I2C,OFF);
  	}
}


/*
 * @brief	Überprüft den RS232-Puffer
 *
 *				Überprüft den RS232-Puffer, setzt den Nachrichten-Stand zurück
 *				und Löscht ggf. das Lämpchen für den Pufferüberlauf
 * @return void
 */
/*
void check_rs232_puffer()
{
	//Puffer von RS232 nach i2c
	if(puffered_msg_rs232 > 0) 
	{
   	for(int i=0; i<puffered_msg_rs232;++i)
			for(int n=0; n<7;++n)
			{
				Wire.send(message_rs232[i+1][n+1]);
			}   
		puffered_msg_rs232 = 0;
		set_led(LED_PIN_RS232,OFF);
  	}
}
*/

/*
 * @brief	Setzt die Pin-Nummer pinNum auf den Status state
 *
 * @param	pinNum	Bestimmt die Pin-Nummer
 * @param	state		Bestimmt den zusetzenden Status
 * @return void
 */
void set_led(int pinNum, int state)
{
  digitalWrite(pinNum, state);
}

/*
 * @brief	Empfängt Daten von der RS232-Schnittstelle
 *
 *				Empfängt Daten von der RS232-Schnittstelle, sofern Daten anliegen.
 *				Ist der Puffer voll, so wird die Lampe LED_PIN_RS232 auf ON geschaltet.
 *				Es wird das Start- und Endbyte, sowie die Checksumme überprüft.
 * @return void
 */
void receive_rs232()
{
	bool overflow = false;
	//Überprüfe ob Daten anliegen
	while(Serial.available()&&!overflow)
	{
		if(puffered_msg_rs232==MAX_MELDUNGEN)
		{
			overflow = true;
			set_led(LED_PIN_RS232,ON);
			continue;
		}
		//Suche das Startbyte
		if(Serial.read()==START_BYTE)
		{
			//Empfange die Länge
			byte length = Serial.read();
			message_rs232[puffered_msg_rs232][0] = length;
			for(int i=1; i<=length;++i)
			{
				//Empfange die Daten
				message_rs232[puffered_msg_rs232][i] = Serial.read();
			}

			//Überprüfe die Checksumme
			byte checksum = Serial.read();
			if(!check_checksum(puffered_msg_rs232,checksum))
				continue;

			//überprüfe das Endbyte
			if(Serial.read()==END_BYTE)
				++puffered_msg_rs232;
		}
	}
}

/*
 * @brief	Überprüft die Checksumme
 *
 * @param	index		Beinhaltet die Indexnummer der zu Überprüfenen Nachricht.
 * @param	checksum Beinhaltet die zu Überprüfenden Checksumme
 * @return 	bool - Gibt an ob die Überprüfung erfolgreich(true) oder nicht erfolgreich(false) war.
 */
bool check_checksum(int index, byte checksum) 
{	
	//Zusammensetzung der Checksumme: CRC
	uint32_t crc32 = 0; // Schieberegister 
	for (int i = 0; i < message_i2c[index][0]+1; ++i)
   {
		if (((crc32 & 0x80000000) ? 1 : 0) != message_i2c[index][i])
   		crc32 = (crc32 << 1) ^ CRC32POLY;
      else
         crc32 <<= 1;	
	}

	if (((crc32 & 0x80000000) ? 1 : 0) != checksum)
   		crc32 = (crc32 << 1) ^ CRC32POLY;
      else
         crc32 <<= 1;	

	if(crc32==0)
		return true;
	return false;
}

/*
 * @brief	RecieveEvent der I2C-Schnittstelle
 *
 * @param	number_bytes	Anzahl der Emfangenen Bits.
 * @return 	void
 */
void receiveEvent_i2c(int number_bytes)
{
	int number_messages = number_bytes/7;
  	for(int i=0;i<number_messages;++i)
	{
		if(puffered_msg_i2c<MAX_MELDUNGEN)
		{
			message_i2c[i][0] = 7;
   		for(int j=0;j<7;++j) 
			{
      		message_i2c[i][j+1] = Wire.receive();
			}
			++puffered_msg_i2c;
		}
  		else
  		{
  	 		// Puffer ist voll, setze LED_PIN auf ON
  	   	set_led(LED_PIN_I2C,ON);
			// breche Schleife ab
			i = number_messages;
  		}
	}
}

/*
 * @brief	Sendet alle Nachrichten über die RS232-Schnittstelle.
 *
 *			Sendet alle Nachrichten über die RS232-Schnittstelle.
 *			Dabei wird vorweg das Startbyte und hinterher, die Checksumme und das Endbyte.
 *			Die Länge wird vor der eigentlichen Nachricht (Byte 0) mitgesendet.
 * @return 	void
 */
void send_all_messages()
{
	for(int n=0; n < puffered_msg_i2c; ++n)
	{
		Serial.print(START_BYTE,HEX);
		for(int i = 0; i <= message_i2c[n][0]+1 ;++i)
		{
			Serial.print(message_i2c[n][i],HEX);
		}
		Serial.print(create_checksum(n),HEX);
		Serial.print(END_BYTE,HEX);	
	}
}

/*
 * @brief	Erstellt die Checksumme
 *
 *			Die Checksumme wird nach dem CRC-Verfahren erstellt. Das CRC-Polynome 
 *			ist als Konstante unter dem Namen CRC32POLY definiert
 * @return 	byte - Checksumme der Nachricht
 */
byte create_checksum(int index)
{
	//Zusammensetzung der Checksumme: CRC
	uint32_t crc32 = 0; // Schieberegister 

   for (int i = 0; i < message_i2c[index][0]+1; ++i)
   {
		if (((crc32 & 0x80000000) ? 1 : 0) != message_i2c[index][i])
   		crc32 = (crc32 << 1) ^ CRC32POLY;
      else
         crc32 <<= 1;	
	}
	return crc32;
}

