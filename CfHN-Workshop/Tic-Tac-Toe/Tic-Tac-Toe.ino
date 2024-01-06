int Spielfeld[9];
int Spieler;
int Gewinner;

// Alle Pins, die mit den LEDs verbunden sind, auf Ausgang setzen
void Init( void )
{
  for (int i = 2; i < 15; i++)
  {
    pinMode(i, OUTPUT);
  }
}

// Um alle LEDs aus zu schalten, müssen die damit verbundenen Pins auf LOW gesetzt werden.
void AllesAus( void )
{
  for (int i = 2; i < 15; i++)
  {
    // Der Pin 11 muss abeer auf HIGH gesetzt werden, weil er nicht mit einem Transistor verbunden ist
    if( i != 11)
    {
      digitalWrite(i, HIGH);
    }
    else
    {
      digitalWrite(i, LOW);
    }
  }
}

//  Zu Beginn eines Spiels werden alle Variablen auf ihren Standardwert gesetzt
void InitVariablen( void )
{
  // Alle Elemente des Arrays Spielfeld werden mit 0 belegt
  for (int i = 0; i < 9; i++)
  {
    Spielfeld[i] = 0;
  }
  
  // Spieler 1 darf mit dem Spiel beginnen
  Spieler = 1;

  // Noch hat niemand gewonnen. Deshalb wird diese Variable mit 0 belegt
  Gewinner = 0;
}

// Diese Funktion liefert zurück, welche Taste atuell gedrückt wird.
// Alle Tasten bilden einen Spannungsteiler, mit dem das Verhältnis der Widerstände zueinander über einen AD-Wandler ausgelesen wird.
// Falls keine Tate gedrückt wird, zieht der Pulldown-Widerstand die Spannung auf 0V
int TasteGedrueckt( void )
{
  // 10 bedeutet, dass keine Taste gedrückt wird
  int Taste = 10;

  int ADC_Wert = analogRead( A7 );

  // Im Folgenen werden die Werte des AD-Wandlers verglichen. daraus wird dann ermittelt, welche taste gedrückt wird
  
  if ( (ADC_Wert > 360) && (ADC_Wert < 370) )
  {
    Taste = 0;
  }
  if ( (ADC_Wert > 560) && (ADC_Wert < 570) )
  {
    Taste = 1;
  }
  if ( (ADC_Wert > 635) && (ADC_Wert < 645) )
  {
    Taste = 2;
  }
  if ( (ADC_Wert > 390) && (ADC_Wert < 400) )
  {
    Taste = 3;
  }
  if ( (ADC_Wert > 500) && (ADC_Wert < 515) )
  {
    Taste = 4;
  }
  if ( (ADC_Wert > 725) && (ADC_Wert < 735) )
  {
    Taste = 5;
  }
  if ( (ADC_Wert > 415) && (ADC_Wert < 430) )
  {
    Taste = 6;
  }
  if ( (ADC_Wert > 460) && (ADC_Wert < 470) )
  {
    Taste = 7;
  }
  if ( (ADC_Wert > 845) && (ADC_Wert < 860) )
  {
    Taste = 8;
  }

  //Serial.println( Taste );

  // Der ermittelte wert für die Taste wird anschließend zurückgegeben
  return Taste;
}

// Diese Funktion kümmert sich um die Ausgabe der Status-LED
void AusgabeStatusLED( void )
{
  // Je nachdem, welcher Spieler gerade dran ist, leuchtet die LED in einer bestimmten Farbe
  switch (Spieler)
  {
    case 0: // Allle Farben aus
        digitalWrite(5, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
        break;
    case 1: // Rot
        digitalWrite(5, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(8, LOW);
        break;
    case 2: // Gruen
        digitalWrite(5, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
        break;
    case 3: // Blau
        digitalWrite(5, LOW);
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
        break;
  }

  // Setze die gemeinsame Kathode auf HIGH und schalte die LED somit an
  digitalWrite(11, HIGH);

  // Warte eine Millisekunde
  delay(1);

  // Schalte die LED aus
  digitalWrite(11, LOW);

  AllesAus();
}

// Diese Funktion gibt den Inhalt des Arrays Spielfeld auf der LED Matrix aus.
void AusgabeLEDs()
{
  // Das wird für alle 3 Zeilen widerholt
  for(int i = 0; i < 3; i++)
  {
    // Prüfe die LEDs 0, 3 und 6
    switch ( Spielfeld[ 3*i ] )
    {
      case 0: // alle Farben aus
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);
        break;
      case 1: // Rot
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);
        break;
      case 2: // Gruen
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        break;
      case 3: // Blau
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        break;
    }

    // Pruefe die LEDs 1, 4 und 7
    switch ( Spielfeld[ 3*i + 1 ] )
    {
      case 0: // Allle Farben aus
        digitalWrite(5, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
        break;
    case 1: // Rot
        digitalWrite(5, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(8, LOW);
        break;
    case 2: // Gruen
        digitalWrite(5, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
        break;
    case 3: // Blau
       digitalWrite(5, LOW);
       digitalWrite(7, HIGH);
       digitalWrite(8, HIGH);
       break;
    }

    // Pruefe die LEDs 2, 5 und 8
    switch ( Spielfeld[ 3*i + 2 ] )
    {
      case 0: // alle Farben aus
        digitalWrite(12, HIGH);
        digitalWrite(13, HIGH);
        digitalWrite(14, HIGH);
        break;
      case 1: // Rot
        digitalWrite(12, LOW);
        digitalWrite(13, HIGH);
        digitalWrite(14, HIGH);
        break;
      case 2: // Gruen
        digitalWrite(12, HIGH);
        digitalWrite(13, HIGH);
        digitalWrite(14, LOW);
        break;
      case 3: // Blau
        digitalWrite(12, HIGH);
        digitalWrite(13, LOW);
        digitalWrite(14, HIGH);
        break;
    }

    // Schalte die dazugehörigr gemeinsame Kathode an.
    // Die Zustände an den Kathoden werden durch den Transistor invertiert
    switch(i)
    {
      case 0: digitalWrite(10, LOW); break;
      case 1: digitalWrite(9, LOW); break;
      case 2: digitalWrite(6, LOW); break;
    }

    // warte eine Millisekunde
    delay(1);

    // Schalte die LED Matrix wieder aus
    AllesAus();
  }
}

// Nach jedem Spielzug muss geprüft werden ob es einen Gewinner gibt
// Dazu werden einfach die Werte in dem Array Spielfeld zeilenweise uns spaltenweise multipliziert
void PruefeGewinner( void )
{
  int Produkt = 1;

  // Pruefe zuerst, ob es ein Unentschieden gibt
  for(int i = 0; i < 9; i++)
  {
    Produkt *= Spielfeld[i];
  }
  if(Produkt != 0)
  {
    Gewinner = -1;
  }

  // Pruefe alle 3 Zeilen und Spalten
  for(int i = 0; i < 3; i++)
  {
    Produkt = Spielfeld[0+i]*Spielfeld[3+i]*Spielfeld[6+i];
    if(Produkt == 1)
    {
      Gewinner = 1;
    }
    if(Produkt == 8)
    {
      Gewinner = 2;
    }

    Produkt = Spielfeld[0+i*3]*Spielfeld[1+3*i]*Spielfeld[2+3*i];
    if(Produkt == 1)
    {
      Gewinner = 1;
    }
    if(Produkt == 8)
    {
      Gewinner = 2;
    }
  }

  // Pruefe die 2 Diagonalen
  Produkt = Spielfeld[0] * Spielfeld[4] * Spielfeld[8];
  if(Produkt == 1)
  {
    Gewinner = 1;
  }
  if(Produkt == 8)
  {
    Gewinner = 2;
  }

  Produkt = Spielfeld[2] * Spielfeld[4] * Spielfeld[6];
  if(Produkt == 1)
  {
    Gewinner = 1;
  }
  if(Produkt == 8)
  {
    Gewinner = 2;
  }
}

// Falls das Spiel gewonnen wurde, zeige eine dazugehörige Animation
void SpielGewonnen( void )
{
  bool neuesSpiel = false;

  // Zuerst bleibt die Anzeig für 2 Sekunden auf dem aktuellen Spielstand
  unsigned long Counter = millis();
  while((millis() - 2000) < Counter)
  {
    AusgabeLEDs();
  }

  // Danach wird noch zwischengespeichert, welcher Spieler als nächstes an der Reihe wäre
  // Das ist notwendig, weil später dieser Wert verloren geht
  int naechsterSpieler = Gewinner + 1;
  if (naechsterSpieler > 2)
  {
    naechsterSpieler = 1;
  }

  // Solange keine Taste gedrückt wird, wird nun diese Animation angezeigt
  do
  {
    // Teil 1
    for(int i = 0; i < 9; i++)
    {
      Spielfeld[i] = Gewinner;
    }
    Spielfeld[4] = 0;

    Counter = millis();
    while((millis() - 1000) < Counter)
    {
      AusgabeLEDs();

      if(TasteGedrueckt() != 10)
      {
        neuesSpiel = true;
      }
    }

    // Teil 2
    for(int i = 0; i < 9; i++)
    {
      Spielfeld[i] = 0;
    }
    Spielfeld[4] = Gewinner;

    Counter = millis();
    while((millis() - 1000) < Counter)
    {
      AusgabeLEDs();

      if(TasteGedrueckt() != 10)
      {
        neuesSpiel = true;
      }
    }
  }while(!neuesSpiel);

  // eine Taste wurde gedrückt. Das Spiel kann weitergehen
  InitVariablen();
  Spieler = naechsterSpieler;
}

// Falls das Spiel mit unentschieden endet, zeige eine dazugehörige Animation
void SpielUnentschieden( void )
{
  bool neuesSpiel = false;

  // Zuerst bleibt die Anzeig für 2 Sekunden auf dem aktuellen Spielstand
  unsigned long Counter = millis();
  while((millis() - 2000) < Counter)
  {
    AusgabeLEDs();
  }

  // Danach wird noch zwischengespeichert, welcher Spieler als nächstes an der Reihe wäre
  // Das ist notwendig, weil später dieser Wert verloren geht
  int naechsterSpieler = Spieler;

  // Solange keine Taste gedrückt wird, wird nun diese Animation angezeigt
  do
  { 
    // Teil 1
    Spielfeld[0]=1;
    Spielfeld[2]=1;
    Spielfeld[6]=1;
    Spielfeld[8]=1;
    Spielfeld[4]=0;
    Spielfeld[1]=2;
    Spielfeld[3]=2;
    Spielfeld[5]=2;
    Spielfeld[7]=2;

    Counter = millis();
    while((millis() - 1000) < Counter)
    {
      AusgabeLEDs();

      if(TasteGedrueckt() != 10)
      {
        neuesSpiel = true;
      }
    }

    // Teil 2
    Spielfeld[0]=2;
    Spielfeld[2]=2;
    Spielfeld[6]=2;
    Spielfeld[8]=2;
    Spielfeld[4]=0;
    Spielfeld[1]=1;
    Spielfeld[3]=1;
    Spielfeld[5]=1;
    Spielfeld[7]=1;

    Counter = millis();
    while((millis() - 1000) < Counter)
    {
      AusgabeLEDs();

      if(TasteGedrueckt() != 10)
      {
        neuesSpiel = true;
      }
    }
  }while(!neuesSpiel);
  
  InitVariablen();
  Spieler = naechsterSpieler;
}

// Die Setup-Funktion wird beim ersten Start aufgerufen
void setup() {
  Init();
  AllesAus();
  InitVariablen();

  //Serial.begin(9600);
}

// Die Loop Funktion wird endlos durchlaufen
void loop() {

  // ermittle, ob eine Tastee geddrückt wurde
  int Taste = TasteGedrueckt();

  // Falls eine Taste gedrückt wurde und dieses Feld noch unbelegt ist, markiere es mit dem aktuellen Spieler
  if ((Taste != 10) && (Spielfeld[ Taste ] == 0))
  {
    Spielfeld[ Taste ] = Spieler;
    Spieler++;
  }

  // Nach jedem Spielzug ist der neue Spieler an der Reihe. Dafür wird der Spieler zuerst inkrementiert und danach ein Übrelauf geprüft
  if (Spieler > 2)
  {
    Spieler = 1;
  }

  // An der Status-LED wird gezeigt, welcher Spieler gerade an der Reihe ist
  AusgabeStatusLED();

  // Der aktuelle Spielstand wird auf der LED Matrix ausgegeben
  AusgabeLEDs();

  // Es wird geprüft, ob es schon einen Gewinner gibt
  PruefeGewinner();

  //Serial.println(Gewinner);

  // Falle es einen Gewinner gibt, wird die dazugehörige Animation aktiviert
  if(Gewinner > 0)
  {
    SpielGewonnen();
  }
  // Falls das Spiel unentscheiden steht, wird die dazugrhörige Animation aktiviert
  if(Gewinner == -1)
  {
    SpielUnentschieden();
  }
  
  /*
  for(int i = 0; i < 9; i++)
  {
    Serial.print(Spielfeld[i]);
    Serial.print("; ");
  }
  Serial.print("   ");
  Serial.print(analogRead(A7));
  Serial.print("   ");
  Serial.print(Taste);
  Serial.print("   ");
  Serial.print(Spieler);
  Serial.println(" ");
  */
}
