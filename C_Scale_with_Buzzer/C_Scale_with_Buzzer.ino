int speakerPin = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(speakerPin, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  play('c', 2);
  play('d', 2);
  play('e', 2);
  play('f', 2);
  play('g', 2);
  play('a', 2);
  play('b', 2);
  play('C', 2);
//  play('D', 2);
//  play('E', 2);
//  play('F', 2);
//  play('G', 2);
//  play('A', 2);
//  play('B', 2);

  //play(' ', 3);

  //play('C', 2);
  play('b', 2);
  play('a', 2);
  play('g', 2);
  play('f', 2);
  play('e', 2);
  play('d', 2);
  play('c', 2);

  
  while(true){}   // get stuck in this loop forever 
                  // so that the song only plays once
}

void play(char note, int beats) {
  int numNotes = 14; // number of notes in our note and
                     // frequencey array (there are 15
                     // values but arrays start at 0)

  // Note: these notes are C major 
  // (there are no sharps or flats)

  // this array is used to look up the notes
  char notes[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 
  'C', 'D', 'E', 'F', 'G', 'A', 'B', ' '};

  // this array matches frequencies with each letter 
  // (e.g. the 4th note is 'f', the 4th frequency is 175)
  int frequencies[] = {131, 147, 165, 175, 196, 220, 
  247, 262, 294, 330, 349, 392, 440, 494, 0};

  int currentFrequency = 0; /**
                             *the frequency that we 
                             *find when we look up a 
                             *frequency in the arrays
                              */
  int beatLength = 150; //the length of one beat (changing this will speed up or slow down the tempo of the song)


  for (int i = 0; i < numNotes; i++) {
    if (notes[i] == note) {
      currentFrequency = frequencies[i];// Yes! Set the current frequency to match that note
      break;
    }
  }
  //play the frequency that matched our letter 
  // for the number of beats passed to the play function
  tone(speakerPin, currentFrequency, beats * beatLength);
  delay(beats * beatLength);  //wait for the length of the tone so that it has time to play
  delay(50); //a little delay between the notes makes the song sound more natural

}


/* CHART OF FREQUENCIES FOR NOTES IN C MAJOR
Note      Frequency (Hz)
c        131
d        147
e        165
f        175
g        196
a        220
b        247
C        262
D        294
E        330
F        349
G        392
A        440
B        494
C++      523 Hz
*/
