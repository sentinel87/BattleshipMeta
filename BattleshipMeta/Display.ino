
void menuFunction() //Menu Screen
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

  if(gb.buttons.pressed(BUTTON_UP)||gb.buttons.pressed(BUTTON_DOWN)){
      if(gameMode==1)
      {
        gameMode=2;
        selectorPosY=46;
      }
      else
      {
        gameMode=1;
        selectorPosY=38;
      }
      gb.sound.playTick();
    }

  gb.display.setColor(GREEN);
  gb.display.fillCircle(selectorPosX, selectorPosY, 1);

  if(gb.buttons.pressed(BUTTON_A))
  {
    menuScreen=false;
    placementInfoScreen=true;
    clearGameData();
  }
}

void pauseMenuFunction() //Menu Screen
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

  if(gb.buttons.pressed(BUTTON_UP)||gb.buttons.pressed(BUTTON_DOWN)){
      if(pauseMode==1)
      {
        pauseMode=2;
        selectorPosY=46;
      }
      else
      {
        pauseMode=1;
        selectorPosY=38;
      }
      gb.sound.playTick();
    }

  gb.display.setColor(GREEN);
  gb.display.fillCircle(selectorPosX, selectorPosY, 1);

  if(gb.buttons.pressed(BUTTON_A))
  {
    if(pauseMode==1)
    {
      gameScreen=true;
      pause=false;
    }
    else
    {
      pause=false;
      menuScreen=true;
      selectorPosY=38;
      gameMode=1;
    }
  }
  else if(gb.buttons.pressed(BUTTON_MENU))
  {
    gameScreen=true;
    pause=false;
  }
}

void placeShipsInfo(char player[])
{
  gb.display.setCursor(0, 5);
  gb.display.setFontSize(2);
  gb.display.setColor(RED);
  gb.display.printf(player);
  gb.display.setCursor(3, 18);
  gb.display.setFontSize(1);
  gb.display.setColor(BROWN);
  gb.display.println("Place ships:");
  gb.display.setCursor(gb.display.width()/2-15, 8);
  gb.display.setColor(WHITE);
  gb.display.setCursor(gb.display.width()/2-38, 32);
  gb.display.println("+ - move");
  gb.display.setCursor(gb.display.width()/2-38, 40);
  gb.display.println("B - rotate");
  gb.display.setCursor(gb.display.width()/2-38, 48);
  gb.display.println("A - place");
  buttonHint();

  if(gb.buttons.pressed(BUTTON_A))
  {
    placementInfoScreen=false;
    placementScreen=true;
  }
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

void gameInfo()
{
  gb.display.setCursor(0, 5);
  gb.display.setFontSize(2);
  gb.display.setColor(RED);
  gb.display.printf("CONTROLS");
  gb.display.setCursor(3, 18);
  gb.display.setFontSize(1);
  gb.display.setColor(BROWN);
  gb.display.println("Game controls:");
  gb.display.setColor(WHITE);
  gb.display.setCursor(gb.display.width()/2-38, 26);
  gb.display.println("+ - aim");
  gb.display.setCursor(gb.display.width()/2-38, 34);
  gb.display.println("A - fire");
  gb.display.setCursor(gb.display.width()/2-38, 42);
  gb.display.println("B - switch board");
  gb.display.setCursor(gb.display.width()/2-38, 50);
  gb.display.println("Sel - game menu");
  buttonHint();

  if(gb.buttons.pressed(BUTTON_A))
  {
    gameInfoScreen=false;
    gameScreen=true;
  }
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
  buttonHint();
  if(gb.buttons.pressed(BUTTON_A))
  {
    turnInfoScreen=false;
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

void gameWinningScreen()  //End Game Result
{
  gb.display.setCursor(0, 5);
  gb.display.setFontSize(2);
  gb.display.setColor(RED);
  gb.display.printf("PLAYER %d",playerTurn);
  gb.display.setCursor(3, 22);
  gb.display.setColor(BROWN);
  gb.display.println("Wins!");
  buttonHint();
  if(gb.buttons.pressed(BUTTON_A))
  {
    winningScreen=false;
    menuScreen=true;
  }
}

void buttonHint()
{
  if(fireSeq==1)
  {
    gb.display.setColor(RED);
  }
  else
  {
    gb.display.setColor(ORANGE);
  }
  gb.display.fillCircle(gb.display.width()-6, gb.display.height()-6,4);
  gb.display.setColor(BEIGE);
  gb.display.fillCircle(gb.display.width()-6, gb.display.height()-6,3);
  gb.display.setCursor(gb.display.width()-7, gb.display.height()-8);
  gb.display.setColor(BLACK);
  gb.display.printf("A");
}

