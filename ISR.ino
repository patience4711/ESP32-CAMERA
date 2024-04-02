// *******************************************************************************************
//                  interrupt service routine
// *******************************************************************************************
// deze routine wordt aangeroepen als de knop is ingedrukt
// het eerste deel is een debouncer en zort er tevens voor dat
// het programma niet bij een storing op het net denkt dat er een knop is ingedrukt.
// vervolgens wordt er gekeken of de knop kort / lang / langst was ingedrukt. Na kort
// wordt de blauwe led aangezet en de wdt uitgeschakeld omdat ie anders in reset gaat 
// We kunnen geen delay() gebruiken want dan volgt wdt reset
ICACHE_RAM_ATTR void isr() {
  detachInterrupt(0); // voorkomt interrupt tijdens interrupt
  DebugPrint("interrupt detected");
  unsigned long starttijd = millis(); // sla de tijd op in currentMillis
  unsigned long eindtijd = millis();
    while (eindtijd - starttijd  <= 100) { //2000 millis = 2 sec
    eindtijd = millis();
    yield();
    }
int val = digitalRead(0);
 if (val == 0) { // dwz de knop is weer losgelaten
   //DebugPrintln("knop was te kort ingedrukt dus een toevallige storing");
    attachInterrupt(digitalPinToInterrupt(0), isr, FALLING);
    return; // doe niks want knop is hoog dus het is een toevalligheid geweest
 }
attachInterrupt(digitalPinToInterrupt(0), isr, FALLING);
actionFlag = 9; //button pressed
yield();
return; 
// // nu wachten we weer maar nu langer 
// DebugPrintln("knop is nog ingedrukt dus geen toevallige storing");
// //statusvraag();
// // nu gaan we nog even wachten
//      //esp_task_wdt_reset(); //anders gaat ie in reset
//      while (eindtijd - starttijd  <= 2000) { //2000 millis = 2 sec
//      yield();
//      eindtijd = millis();
//      }
//  val = digitalRead(0);
// // we gaan weer de knop testen
// if (val == 0) { // als de knop nog is ingedrukt
//           // nu wachten we nog een keer, nog langer 
//           //DebugPrintln("knop is nog steeds ingedrukt");
//               //esp_task_wdt_reset(); //anders gaat ie in reset
//               while (eindtijd - starttijd  <= 6000) { //2000 millis = 2 sec
//               eindtijd = millis();
//                yield();
//               }
//               //esp_task_wdt_reset(); //anders gaat ie in reset
//               digitalWrite(led_onb, LED_AAN);
//               //DebugPrintln("knop is ingedrukt led aanzetten");
//               //vervolgens nu gaan we nog even wachten
//               while (eindtijd - starttijd  <= 9000) { //2000 millis = 2 se
//                yield();
//               eindtijd = millis();
//               }
//              // we gaan weer de knop testen, 
//                esp_task_wdt_reset();
//              digitalWrite(led_onb, LED_UIT);
//              val = digitalRead(0);
//              if (val == 0) { // nog steeds ingedrukt
//                    // DebugPrintln("knop is nog ingedrukt dus accesspoint openen");
//                     // we moeten nu wachten tot de knop is losglaten anders start ie op in programmeermodus
//                     while (val == 0) {
//                     val = digitalRead(0);
//                     yield();
//                     // blijf in deze lus totdat de knop is losgelaten
//                     }
//                     signalFlag = 11;
//                     return;
//                          
//                 } else {
//                  DebugPrintln("knop is eindelijk los dus resetten");
//                  ESP.restart(); // opnieuw opstarten
//            }
//     } 
// // de knop is losgelaten na de 2e evaluatie
// else { //
//  //DebugPrintln("knop is ingedrukt geweest maar nu niet meer");
// // de knop is nog ingedrukt dus nu moeten we schakelen
// // als de led uit is dan moet ie aan en omgekeerd
//    value = value+1; //value = 1 of groter
// 
//      if (value > 1) { //value was 1 dus aan
//      value=0; // met de knop schakelen we programma 1 in
//     //event =0;
//   //  DebugPrintln("we moeten uitschakelen");
//     //timers_disarm();
//     //if( event == 3 || event == 4 || event == 5 || event == 6 ) {
//       // mustSwitch[event-3] = false;
//      //}
//     //event=11; // = "er is uitgeschakeld met de drukknop<br>";
//     //inschakeltijdstip = 8; // uitschakelen wordt in de loop verwerkt
// 
//    }
//  else { //value = 1
//    //DebugPrintln("we moeten inschakelen");
//    //event=1; // = "er is ingeschakeld met de drukknop<br>";
//    //inschakeltijdstip = 1; //wordt in de loop verwerkt
//   }
//     attachInterrupt(digitalPinToInterrupt(0), isr, FALLING);  
// }
}
