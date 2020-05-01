const uint16_t CONTROLLER_IMG[] = {
  7,     // frame width
  7,     // frame height
  1,      // number of frames
  1,      // animation speed
  0xf818, // transparent color
  0,      // RGB565 color mode
  // frame 1/1
  0xf818, 0xf818, 0xFFD690, 0xFFD690, 0xFFD690, 0xf818, 0xf818, 
  0xf818, 0xf818, 0xFFD690, 0xFFD690, 0xFFD690, 0xf818, 0xf818, 
  0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 
  0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690,
  0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 
  0xf818, 0xf818, 0xFFD690, 0xFFD690, 0xFFD690, 0xf818, 0xf818, 
  0xf818, 0xf818, 0xFFD690, 0xFFD690, 0xFFD690, 0xf818, 0xf818
};

const uint16_t BUTTON_IMG[] = {
  7,     // frame width
  7,     // frame height
  1,      // number of frames
  1,      // animation speed
  0xf818, // transparent color
  0,      // RGB565 color mode
  // frame 1/1
  0xf818, 0xf818, 0xFFD690, 0xFFD690, 0xFFD690, 0xf818, 0xf818, 
  0xf818, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xf818, 
  0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 
  0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690,
  0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 
  0xf818, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xf818, 
  0xf818, 0xf818, 0xFFD690, 0xFFD690, 0xFFD690, 0xf818, 0xf818
};

const uint16_t BUTTON_FLAT_IMG[] = {
  7,     // frame width
  3,     // frame height
  1,      // number of frames
  1,      // animation speed
  0xf818, // transparent color
  0,      // RGB565 color mode
  // frame 1/1
  0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 
  0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690,
  0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690, 0xFFD690
};

void displayMenu() //Menu Screen
{
  gb.display.setCursor(0, 5);
  gb.display.setFontSize(2);
  gb.display.setColor(RED);
  gb.display.println("BATTLESHIP");
  gb.display.setCursor((gb.display.width()-33)/2, 18);
  gb.display.setFontSize(2);
  gb.display.setColor(BROWN);
  gb.display.println("META");
  gb.display.setCursor((gb.display.width()-36)/2, 36);
  gb.display.setFontSize(1);
  gb.display.setColor(WHITE);
  gb.display.println("1 Player");
  gb.display.setCursor((gb.display.width()-36)/2, 44);
  gb.display.println("2 Players");
  gb.display.setColor(GREEN);
  gb.display.fillCircle(selectorPosX, selectorPosY, 1);
}

void displayPauseMenu() //Menu Screen
{
  gb.display.setCursor((gb.display.width()-33)/2, 18);
  gb.display.setFontSize(2);
  gb.display.setColor(BROWN);
  gb.display.println("PAUSE");
  gb.display.setCursor((gb.display.width()-36)/2, 36);
  gb.display.setFontSize(1);
  gb.display.setColor(WHITE);
  gb.display.println("Resume game");
  gb.display.setCursor((gb.display.width()-36)/2, 44);
  gb.display.println("Main menu");
  gb.display.setColor(GREEN);
  gb.display.fillCircle(selectorPosX, selectorPosY, 1);
}

void displayPlaceShipsInfo(char player[])
{
  gb.display.setCursor(0, 5);
  gb.display.setFontSize(2);
  gb.display.setColor(RED);
  gb.display.printf(player);
  gb.display.setCursor(3, 18);
  gb.display.setFontSize(1);
  gb.display.setColor(BROWN);
  gb.display.println("Place ships:");
  gb.display.drawImage(3,28,CONTROLLER_IMG);
  gb.display.setColor(WHITE);
  gb.display.setCursor(gb.display.width()/2-25, 29);
  gb.display.println("move");
  drawButton(false,6, 39,"B");
  gb.display.setColor(WHITE);
  gb.display.setCursor(gb.display.width()/2-25, 37);
  gb.display.println("rotate");
  drawButton(false,6, 47,"A");
  gb.display.setColor(WHITE);
  gb.display.setCursor(gb.display.width()/2-25, 45);
  gb.display.println("place ship");
  drawButton(true,gb.display.width()-6, gb.display.height()-6, "A");
}

void displayPlacementBoard(int8_t arr[][10])
{
  for(int i=0;i<10;i++)
  {
    for(int j=0;j<10;j++)
    {
      if(arr[i][j]!=0)
      {
        gb.display.setColor(WHITE);
        gb.display.fillRect(1+6*i,1+6*j,5,5);  
      }
      else
      {
        gb.display.setColor(BLUE);
        gb.display.fillRect(1+6*i,1+6*j,5,5); 
      }
    }
  }
  gb.display.setColor(ORANGE);
  if(shipDirection==1)
  {
   gb.display.fillRect(shipPointX*6,shipPointY*6,6*toPlace+1,7); 
  }
  else
  {
   gb.display.fillRect(shipPointX*6,shipPointY*6,7,6*toPlace+1); 
  }
  gb.display.setCursor(gb.display.width()-16, 0);
  gb.display.setFontSize(1);
  gb.display.setColor(WHITE);
  gb.display.printf("B:%d",battleships4);
  gb.display.setCursor(gb.display.width()-16, 8);
  gb.display.printf("C:%d",cruisers3);
  gb.display.setCursor(gb.display.width()-16, 16);
  gb.display.printf("D:%d",destroyers2);
  gb.display.setCursor(gb.display.width()-16, 24);
  gb.display.printf("S:%d",submarines1);
}

void displayGameInfo()
{
  gb.display.setCursor(0, 5);
  gb.display.setFontSize(2);
  gb.display.setColor(RED);
  gb.display.printf("CONTROLS");
  gb.display.setCursor(3, 18);
  gb.display.setFontSize(1);
  gb.display.setColor(BROWN);
  gb.display.println("Game controls:");
  gb.display.drawImage(3,28,CONTROLLER_IMG);
  gb.display.setColor(WHITE);
  gb.display.setCursor(gb.display.width()/2-25, 29);
  gb.display.println("aim");
  drawButton(false,6, 39,"A");
  gb.display.setColor(WHITE);
  gb.display.setCursor(gb.display.width()/2-25, 37);
  gb.display.println("fire");
  drawButton(false,6, 47,"B");
  gb.display.setColor(WHITE);
  gb.display.setCursor(gb.display.width()/2-25, 45);
  gb.display.println("switch board");
  drawButton(true,gb.display.width()-6, gb.display.height()-6, "A");
  gb.display.drawImage(3,54,BUTTON_FLAT_IMG);
  gb.display.setColor(WHITE);
  gb.display.setCursor(gb.display.width()/2-25, 53);
  gb.display.println("game menu");
  drawButton(true,gb.display.width()-6, gb.display.height()-6, "A");
}

void displayPlayerFleet(int8_t arr[][10],int fireSeq)
{
  for(int i=0;i<10;i++)
  {
    for(int j=0;j<10;j++)
    {
      if(arr[i][j]>0)
      {
        gb.display.setColor(WHITE);
        gb.display.fillRect(1+6*i,1+6*j,5,5);  
      }
      else if(arr[i][j]<0 && arr[i][j]!=-9 && arr[i][j]!=-10)  //if hitted area and field is not missed and field is not sunk
      {
         if(fireSeq==1)
         {
           gb.display.setColor(ORANGE);
         }
         else
         {
           gb.display.setColor(YELLOW);
         }
         gb.display.fillRect(1+6*i,1+6*j,5,5);
      }
      else if(arr[i][j]==-10)
      {
        gb.display.setColor(GRAY);
        gb.display.fillRect(1+6*i,1+6*j,5,5);
        gb.display.setColor(BLACK);
        gb.display.drawLine(1+6*i, 1+6*j, 6*i+6, 6*j+6);
      }
      else if(arr[i][j]==-9)
      {
        gb.display.setColor(BLUE);
        gb.display.drawRect(1+6*i,1+6*j,5,5); 
        gb.display.setColor(BLACK);
        gb.display.fillRect(6*i+2,6*j+2,2,2);
      }
      else
      {
        gb.display.setColor(BLUE);
        gb.display.fillRect(1+6*i,1+6*j,5,5); 
      }
    }
  }
  gb.display.setColor(BROWN);
  gb.display.setCursor(gb.display.width()-16, 0);
  gb.display.printf("P");
  gb.display.setCursor(gb.display.width()-16, 7);
  gb.display.printf("L");
  gb.display.setCursor(gb.display.width()-16, 14);
  gb.display.printf("A");
  gb.display.setCursor(gb.display.width()-16, 21);
  gb.display.printf("Y");
  gb.display.setCursor(gb.display.width()-16, 28);
  gb.display.printf("E");
  gb.display.setCursor(gb.display.width()-16, 35);
  gb.display.printf("R");
  gb.display.setCursor(gb.display.width()-16, 42);
  if(playerTurn==1)
  {
    gb.display.printf("1"); 
  }
  else
  {
    gb.display.printf("2");
  }
  gb.display.setCursor(gb.display.width()-8, 0);
  gb.display.printf("F");
  gb.display.setCursor(gb.display.width()-8, 7);
  gb.display.printf("L");
  gb.display.setCursor(gb.display.width()-8, 14);
  gb.display.printf("E");
  gb.display.setCursor(gb.display.width()-8, 21);
  gb.display.printf("E");
  gb.display.setCursor(gb.display.width()-8, 28);
  gb.display.printf("T");
}

void displayAttackField(int8_t arr[][10],int player,int fireSeq,int battleship,int cruiser,int destroyer,int submarine)
{
  for(int i=0;i<10;i++)
  {
    for(int j=0;j<10;j++)
    {
      if(arr[i][j]<0 && arr[i][j]!=-9 && arr[i][j]!=-10)  //if hitted area and field is not missed and field is not sunk
      {
        if(checkHits(arr[i][j],player)==true)
        {
          arr[i][j]=-10;  //sunk
        }
        else
        {
          if(fireSeq==1)
          {
            gb.display.setColor(ORANGE);
          }
          else
          {
            gb.display.setColor(YELLOW);
          }
          gb.display.fillRect(1+6*i,1+6*j,5,5);
        }
      }
      else if(arr[i][j]==-10)
      {
        gb.display.setColor(GRAY);
        gb.display.fillRect(1+6*i,1+6*j,5,5);
        gb.display.setColor(BLACK);
        gb.display.drawLine(1+6*i, 1+6*j, 6*i+6, 6*j+6);
      }
      else if(arr[i][j]==-9)
      {
        gb.display.setColor(BLUE);
        gb.display.drawRect(1+6*i,1+6*j,5,5); 
        gb.display.setColor(BLACK);
        gb.display.fillRect(6*i+2,6*j+2,2,2);
      }
      else
      {
        gb.display.setColor(BLUE);
        gb.display.fillRect(1+6*i,1+6*j,5,5); 
      }
    }
  }
  if(fireSeq==1)
  {
    gb.display.setColor(RED);
  }
  else
  {
    gb.display.setColor(ORANGE);
  }
  gb.display.drawRect(targetPosX*6,targetPosY*6,7,7);
  gb.display.setColor(BROWN);
  gb.display.setCursor(gb.display.width()-16, 0);
  gb.display.printf("E");
  gb.display.setCursor(gb.display.width()-16, 7);
  gb.display.printf("N");
  gb.display.setCursor(gb.display.width()-16, 14);
  gb.display.printf("E");
  gb.display.setCursor(gb.display.width()-16, 21);
  gb.display.printf("M");
  gb.display.setCursor(gb.display.width()-16, 28);
  gb.display.printf("Y");
  gb.display.setCursor(gb.display.width()-8, 0);
  gb.display.printf("F");
  gb.display.setCursor(gb.display.width()-8, 7);
  gb.display.printf("L");
  gb.display.setCursor(gb.display.width()-8, 14);
  gb.display.printf("E");
  gb.display.setCursor(gb.display.width()-8, 21);
  gb.display.printf("E");
  gb.display.setCursor(gb.display.width()-8, 28);
  gb.display.printf("T");
  gb.display.setColor(WHITE);
  gb.display.setCursor(gb.display.width()-16, 35);
  gb.display.printf("B:%d",battleship);
  gb.display.setCursor(gb.display.width()-16, 42);
  gb.display.printf("C:%d",cruiser);
  gb.display.setCursor(gb.display.width()-16, 49);
  gb.display.printf("D:%d",destroyer);
  gb.display.setCursor(gb.display.width()-16, 56);
  gb.display.printf("S:%d",submarine);
}

void displayTurnInfo(int player)
{
  gb.display.setCursor(0, 5);
  gb.display.setFontSize(2);
  gb.display.setColor(RED);
  gb.display.printf("PLAYER %d",player);
  gb.display.setCursor(3, 18);
  gb.display.setFontSize(1);
  gb.display.setColor(BROWN);
  gb.display.println("Your turn.");
  if((gameMode==1&&playerTurn!=2)||(gameMode==2))
  {
    drawButton(true,gb.display.width()-6, gb.display.height()-6, "A");
  }
}

void displayInfoLockScreen()
{
  int HeightFix=0;
  if(targetPosY>4)
  {
    HeightFix=15;
  }
  if(hitSound!=true)
  {
    hitSound=true;
    if(missed)
    {
      gb.sound.playCancel(); 
    }
    else
    {
      gb.sound.playOK();
    }
  }
  gb.display.setColor(BEIGE);
  gb.display.fillRect(gb.display.width()/2-30, gb.display.height()/2+2-HeightFix,50,10);
  gb.display.setColor(BLACK);
  if(missed==true)
  {
    gb.display.setCursor(gb.display.width()/2-15, gb.display.height()/2+3-HeightFix);
    gb.display.printf("MISS!");  
  }
  else
  {
    gb.display.setCursor(gb.display.width()/2-25, gb.display.height()/2+3-HeightFix);
    gb.display.printf("DIRECT HIT!"); 
  }
}

void displayGameWinningScreen()  //End Game Result
{
  gb.display.setCursor(0, 5);
  gb.display.setFontSize(2);
  gb.display.setColor(RED);
  gb.display.printf("PLAYER %d",playerTurn);
  gb.display.setCursor(3, 22);
  gb.display.setColor(BROWN);
  gb.display.println("Wins!");
  drawButton(true,gb.display.width()-6, gb.display.height()-6, "A");
}

void buttonHint()
{
  drawButton(true,gb.display.width()-6, gb.display.height()-6, "A");
  //if(fireSeq==1)
  //{
  //  gb.display.setColor(RED);
  //}
  //else
  //{
  //  gb.display.setColor(ORANGE);
  //}
  //gb.display.fillCircle(gb.display.width()-6, gb.display.height()-6,4);
  //gb.display.setColor(BEIGE);
  //gb.display.fillCircle(gb.display.width()-6, gb.display.height()-6,3);
  //gb.display.setCursor(gb.display.width()-7, gb.display.height()-8);
  //gb.display.setColor(BLACK);
  //gb.display.setFontSize(1);
  //gb.display.printf("A");
}

void drawButton(bool hint,int posX, int posY, char tp[])
{
  if(hint==true)
  {
    if(fireSeq==1)
    {
      gb.display.setColor(RED);
    }
    else
    {
      gb.display.setColor(ORANGE);
    }
    gb.display.fillCircle(posX, posY,4); 
  }
  gb.display.drawImage(posX-3,posY-3,BUTTON_IMG);
  gb.display.setCursor(posX-1, posY-2);
  gb.display.setColor(BLACK);
  gb.display.setFontSize(1);
  gb.display.printf(tp);
}

