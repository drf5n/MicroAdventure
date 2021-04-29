// Try storing an adventure-like structure in PROGMEM 
// Based on https://forum.arduino.cc/t/storing-a-struct-array-in-progmem/512308


struct nodeStruct         // typedef to store the nodes
{
  uint16_t id;
  char label[200];
  uint16_t data;
  uint16_t east; 
  uint16_t west; 
  uint16_t north;
  uint16_t south; 
};


// Sample data from an old "Hunt the Wumpus" game and "Adventure"
// https://github.com/osgcc/colossal-cave-adventure/blob/master/advdat.77-03-31
// ... but simplify and map movement words 43:E, 44:W, 45:N, 46:S 
//
// FLASH storage of array of nodes
const nodeStruct nodes[] PROGMEM =  
{//node, desc,data,      forward, left, right, back (zero based) 
  { 0,  "Zero Placeholder",0xfeed, 0,0,0,0},
  { 1, "YOU ARE STANDING AT THE END OF A ROAD BEFORE A SMALL BRICK BUILDING.",
    0xface, 3,2,5,4}, 
  { 2, "YOU HAVE WALKED UP A HILL, STILL IN THE FOREST THE ROAD NOW SLOPES BACK DOWN",
    0xdead, 1,5,1,5},
  { 3, "YOU ARE INSIDE A BUILDING, A WELL HOUSE FOR A LARGE SPRING.", 0xbeef, 0,1,0,0},
  { 4, "YOU ARE IN A VALLEY IN THE FOREST BESIDE A STREAM TUMBLING ALONG A ROCKY BED.", 0xFC12, 5,5,1,7},
  { 5, "YOU ARE IN OPEN FOREST, WITH A DEEP VALLEY TO ONE SIDE.", 0xFC12, 4,4,0,4},
  { 6, "YOU ARE IN OPEN FOREST NEAR BOTH A VALLEY AND A ROAD.", 0xFC12, 4,4,1,5},
  { 7, "AT YOUR FEET ALL THE WATER OF THE STREAM SPLASHES INTO A\n"\
       "2 INCH SLIT IN THE ROCK. DOWNSTREAM THE STREAMBED IS BARE ROCK.", 0xFC12, 5,5,4,8},
  { 8, "YOU ARE IN A 20 FOOT DEPRESSION FLOORED WITH BARE DIRT.", 0xFC12, 9,5,7,5},
  { 9, "YOU ARE IN A SMALL CHAMBER BENEATH A 3X3 STEEL GRATE TO THE\n"\
       "SURFACE. A LOW CRAWL OVER COBBLES LEADS INWARD TO THE WEST.", 0xFC12, 8,10,0,0},
  { 10, "YOU ARE CRAWLING OVER COBBLES IN A LOW PASSAGE. THERE IS A\n"\
        "DIM LIGHT AT THE EAST END OF THE PASSAGE.", 0xFC12, 9,11,0,0},
  { 11, "YOU ARE IN A DEBRIS ROOM, FILLED WITH STUFF WASHED IN FROM\n"\
        "THE SURFACE.  YOU HEAR A WUMPUS.", 0xFC12, 10,10,10,12},
  { 12, "wumpus dodecahedron 0, ", 0x0000, 13,16,19,11}, // 1,4,7 (+12)
  { 13, "wumpus dodecahedron 1", 0x0000, 14,12,21,13}, // 2,0,9
  { 14, "wumpus dodecahedron 2", 0x0000, 15,13,23,14}, // 3,1,11
  { 15, "wumpus dodecahedron 3", 0x0000, 16,14,25,15}, //4,2,13
  { 16, "wumpus dodecahedron 4", 0x0000, 12,15,17,16}, //0,3,5
  { 17, "wumpus dodecahedron 5", 0x0000, 12,26,18,17}, // 0,14,6
  { 18, "wumpus dodecahedron 6", 0x0000, 19,17,28,18}, // 7,5,16
  { 19, "wumpus dodecahedron 7", 0x0000, 12,18,19,20}, // 0,6,8
  { 20, "wumpus dodecahedron 8", 0x0000, 21,19,29,20}, // 9,7,17
  { 21, "wumpus dodecahedron 9", 0x0000, 13,20,22,21}, // 1,8,10
  { 22, "wumpus dodecahedron 10", 0x0000, 23,21,30,22}, // 11,9,18
  { 23, "wumpus dodecahedron 11", 0x0000, 14,22,24,23}, // 2,10,12
  { 24, "wumpus dodecahedron 12", 0x0000, 25,23,31,24}, //13,11,19
  { 25, "wumpus dodecahedron 13", 0x0000, 15,24,26,25}, // 3,12,14,
  { 26, "wumpus dodecahedron 14", 0x0000, 17,25,27,26}, // 5,13,15
  { 27, "wumpus dodecahedron 15", 0x0000, 26,31,28,27}, // 14,19,16
  { 28, "wumpus dodecahedron 16", 0x0000, 18,27,29,28}, //6,15,17
  { 29, "wumpus dodecahedron 17", 0x0000, 20,28,30,29}, // 8,16,18
  { 30, "wumpus dodecahedron 18", 0x0000, 22,29,31,30}, // 10,17,19
  { 31, "wumpus dodecahedron 19", 0x0000, 24,30,27,31}, // 12,18,15
  };


nodeStruct node;  // RAM spage for the working node
int new_location,look ;
int location ;
int old_location ; 

int doGetNode(int i){  // copy a node from FLASH to working memory 
  if( (i > 0) && ((unsigned int) i < sizeof(nodes)/sizeof(node))){
     memcpy_P( &node, &nodes[i], sizeof( nodeStruct));
     return(true);
  }
  Serial.print("Problems copying node ");
  Serial.println(i);
  return(0);
}

int check_move(int plan, int location){
  if (plan <1 ){
    Serial.println("You can't go that direction");
    return(location);
  }
  return(plan);
  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial); // wait....
  location = 0;
  new_location = 1;
  look = 1;
  
}
void loop() {
  char ch;
  if(look or new_location != location){
    doGetNode(new_location);
    old_location = location;
    location = new_location ; 
    Serial.println( node.label);
    Serial.println("e,w,n,s? ");
    look = 0;
  }
  if (Serial.available()){
    ch = Serial.read();
    if(ch == '\n' or ch == '\r') { 
      Serial.println(ch);
      look = 1;
    }
    switch(ch) {
      case 'e':
        new_location = check_move(node.east,location);
        break;
      case 'w':
        new_location = check_move(node.west,location);
        break;
      case 'n':
        new_location = check_move(node.north,location);;
        break;
      case 's':
        new_location = check_move(node.south,location);
        break;
    }
    
  }
 // delay(500);

}
