#include<Gamebuino-Meta.h>

struct ShipsHP
{
  int8_t battleship4=4;
  int8_t cruiser3=3;
  int8_t cruiser7=3;
  int8_t destroyer2=2;
  int8_t destroyer5=2;
  int8_t destroyer6=2;
};

//Menu Screen Parameters
bool menuScreen=true;
int8_t gameMode=1;

//Placement screens
bool placementInfoScreen=false;
bool placementScreen=false;
bool player1Placement=false;
bool player2Placement=false;
int8_t toPlace=0;

int8_t battleships4=1;
int8_t cruisers3=2;
int8_t destroyers2=3;
int8_t submarines1=4;
int8_t shipPointX=4;
int8_t shipPointY=4;
int8_t shipDirection=1; //1-horizontal, 2 - vertical

//Game Info Parameters
bool gameInfoScreen=false;

//Game Parameters
bool gameScreen=false;
int8_t gameBoard=1;
int8_t playerBoard=1; //1 - aiming matrix, 2 - player matrix
int8_t playerTurn=1; //1 - 1 player, 2 - 2 player/console
int8_t fireSeq=1;  //flickering elements

bool infoLock=false;  //display attack message and block GUI
bool hitSound=false;
bool missed=false; //end current player turn

//Winning Screen Parameters
bool winningScreen=false;

//Pause Screen Parameters
bool pause=false;
int8_t pauseMode=1;

//Menu Selector Parameters
int8_t selectorPosX=17;
int8_t selectorPosY=38;
int8_t selectorWidth=3;
int8_t selectorHeight=1;

//Player1 Parameters
int8_t PlayerMatrix1[10][10]=
{{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0}};

ShipsHP player1ShipsHP; 

int8_t P1battleship=1;
int8_t P1cruiser=2;
int8_t P1destroyer=3;
int8_t P1submarine=4;

//Player2 Parameters
int8_t PlayerMatrix2[10][10]=
{{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0}};

int8_t P2battleship=1;
int8_t P2cruiser=2;
int8_t P2destroyer=3;
int8_t P2submarine=4;

ShipsHP player2ShipsHP;

//Aimer Parameters
int8_t targetPosX=0;
int8_t targetPosY=0;
int8_t row=0;
int8_t column=0;

//AI Parameters
struct enemyInfo
{
    bool activeFight;
    int8_t shipId;
    int8_t posX;
    int8_t posY;
    int8_t direction;
    int8_t enemySize;
    int8_t damage;
};

bool consoleThinking=false;
bool turnInfoScreen=false;
bool choiceSound=false;
uint8_t track=-1;

enemyInfo EnemyHitsCache[]={{false,0,0,0,1,0,0},{false,0,0,0,1,0,0},{false,0,0,0,1,0,0},{false,0,0,0,1,0,0},{false,0,0,0,1,0,0},{false,0,0,0,1,0,0},{false,0,0,0,1,0,0},{false,0,0,0,1,0,0},{false,0,0,0,1,0,0},{false,0,0,0,1,0,0}};

//AI Automation

int frames=0;
bool aiAction=false;

//-----------------
void setup() {
  gb.begin();
}

void loop() {
  while(!gb.update())
  gb.display.clear();
  
  gb.lights.clear();
  
  if(menuScreen==true) //Menu screen
  {
    menuFunction();
  }
  else  //Game screen
  {
    if(gameMode==1) //Player vs AI
    {
      if(placementInfoScreen==true)
      {
         placeShipsInfo("Player 1");  //Placement info screen
      }
      else if(placementScreen==true)
      {
         player1Placement=shipPlacement(PlayerMatrix1); //Placement screen P1
         if(player1Placement==true)
         {
            battleships4=1;
            cruisers3=2;
            destroyers2=3;
            submarines1=4;
            shipPointX=4;
            shipPointY=4;
            shipPlacementAi(); //AI is creating board
            gameInfoScreen=true;
            turnInfoScreen=true;
         }
      }
    }
    else //Player vs Player
    {
      if(player1Placement!=true)
      {
        if(placementInfoScreen==true)
        {
          placeShipsInfo("Player 1");
        }
        else if(placementScreen==true)
        {
          player1Placement=shipPlacement(PlayerMatrix1);
          if(player1Placement==true)
          {
            toPlace=0;
            battleships4=1;
            cruisers3=2;
            destroyers2=3;
            submarines1=4;
            shipPointX=4;
            shipPointY=4;
            shipDirection=1;
            placementInfoScreen=true;
            placementScreen=true;
          }
        }
      }
      else
      {
        if(placementInfoScreen==true)
        {
          placeShipsInfo("Player 2");
        }
        else if(placementScreen==true)
        {
          player2Placement=shipPlacement(PlayerMatrix2);
          if(player2Placement==true)
          {
            gameInfoScreen=true;
            turnInfoScreen=true;
          }
        }
      }
    }
      if(gameInfoScreen==true) //Game controls screen
      {
        gameInfo();
      }
      else if(gameScreen==true)
      {
        if(gameMode==1)//countdown for AI next action
        {
          timeCalculations();
        }
        game();
      }
      else if(winningScreen==true)
      {
        gameWinningScreen();
      }
      else if(pause==true)
      {
        pauseMenuFunction();
      }
  }
  if(fireSeq==1)//animation color change
  {
    fireSeq=2;
  }
  else
  {
    fireSeq=1;
  }
  //gb.display.setCursor(0, 5);
  //gb.display.setFontSize(1);
  //gb.display.setColor(WHITE);
  //gb.display.println(gb.getCpuLoad());
}

void menuFunction() {
  displayMenu();
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
  else if(gb.buttons.pressed(BUTTON_A))
  {
    menuScreen=false;
    placementInfoScreen=true;
    clearGameData();
  }
}

void pauseMenuFunction(){
  displayPauseMenu();
  if(gb.buttons.pressed(BUTTON_UP)||gb.buttons.pressed(BUTTON_DOWN)) {
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
  else if(gb.buttons.pressed(BUTTON_A)) {
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
  else if(gb.buttons.pressed(BUTTON_MENU)) {
    gameScreen=true;
    pause=false;
  }
}

void placeShipsInfo(char player[]) {
  displayPlaceShipsInfo(player);
  if(gb.buttons.pressed(BUTTON_A)) {
    placementInfoScreen=false;
    placementScreen=true;
  }
}

void gameInfo() {
  displayGameInfo();
  if(gb.buttons.pressed(BUTTON_A)) {
    gameInfoScreen=false;
    gameScreen=true;
  }
}

void gameWinningScreen() {
  displayGameWinningScreen();
  if(gb.buttons.pressed(BUTTON_A))
  {
    winningScreen=false;
    menuScreen=true;
  }
}

void timeCalculations() {
  if(aiAction==false)
  {
    if(frames==25)// every second tick update game mechanics
    {
      frames=0;
      aiAction=true;
    }
    else
    {
      frames++;
    } 
  }
}

void clearGameData()
{
  //Reset Boards
  for(int i=0;i<10;i++)
  {
    for(int j=0;j<10;j++)
    {
      PlayerMatrix1[i][j]=0;
      PlayerMatrix2[i][j]=0;
    }
  }

  //Reset AI struct array
  for(int8_t i=0;i<10;i++)
  {
      EnemyHitsCache[i].activeFight=false;
      EnemyHitsCache[i].direction=1;
      EnemyHitsCache[i].damage=0;
      EnemyHitsCache[i].enemySize=0;
      EnemyHitsCache[i].posX=0;
      EnemyHitsCache[i].posY=0;
      EnemyHitsCache[i].shipId=0;
  }

  //Reset player ships count
  P1battleship=1;
  P1cruiser=2;
  P1destroyer=3;
  P1submarine=4;

  P2battleship=1;
  P2cruiser=2;
  P2destroyer=3;
  P2submarine=4;

  playerBoard=1;
  playerTurn=1;
  //Reset structs
  player1ShipsHP.battleship4=4;
  player1ShipsHP.cruiser3=3;
  player1ShipsHP.cruiser7=3;
  player1ShipsHP.destroyer2=2;
  player1ShipsHP.destroyer5=2;
  player1ShipsHP.destroyer6=2;

  player2ShipsHP.battleship4=4;
  player2ShipsHP.cruiser3=3;
  player2ShipsHP.cruiser7=3;
  player2ShipsHP.destroyer2=2;
  player2ShipsHP.destroyer5=2;
  player2ShipsHP.destroyer6=2;

  //Reset placement parameters
  player1Placement=false;
  player2Placement=false;
  toPlace=0;
  battleships4=1;
  cruisers3=2;
  destroyers2=3;
  submarines1=4;
  shipPointX=4;
  shipPointY=4;
  shipDirection=1;

  //reset aimer
  targetPosX=0;
  targetPosY=0;
  row=0;
  column=0;
  pauseMode=1;
  selectorPosY=38;
  aiAction=false;
  frames=0;
}

bool shipPlacement(int8_t arr[][10])
{
  if(battleships4>0){
    toPlace=4;
  }
  else if(cruisers3>0){
    toPlace=3;
  }
  else if(destroyers2>0){
    toPlace=2;
  }
  else if(submarines1>0){
    toPlace=1;
  }
  else{
    placementScreen=false;
    return true;
  }

  if(gb.buttons.pressed(BUTTON_LEFT))
  {
    if(shipPointX>0)
    {
      shipPointX--; 
    }
  }
  else if(gb.buttons.pressed(BUTTON_RIGHT))
  {
    if(shipDirection==2)
    {
      if(shipPointX<9)
      {
        shipPointX++;
      }
    }
    else
    {
      if(shipPointX+toPlace<10)
      {
        shipPointX++; 
      }
    }
  }
  else if(gb.buttons.pressed(BUTTON_UP))
  {
    if(shipPointY>0)
    {
      shipPointY--; 
    }
  }
  else if(gb.buttons.pressed(BUTTON_DOWN))
  {
    if(shipDirection==1)
    {
      if(shipPointY<9)
      {
        shipPointY++;
      }
    }
    else
    {
      if(shipPointY+toPlace<10)
      {
        shipPointY++; 
      }
    }
  }
  else if(gb.buttons.pressed(BUTTON_B))  //rotate ship
  {
    gb.sound.playTick();
    if(shipDirection==1)
    {
      if(shipPointY+toPlace<=10)
      {
        shipDirection=2; 
      }
    }
    else
    {
      if(shipPointX+toPlace<=10)
      {
        shipDirection=1; 
      }
    }
  }
  if(gb.buttons.pressed(BUTTON_A))  //place ship
  {
    bool canBePlaced=true;
    if(shipDirection==1)    //check if there are any occupied places
    {
      for(int i=shipPointX;i<shipPointX+toPlace;i++)
      {
        if(arr[i][shipPointY]!=0)
        {
          gb.sound.playCancel();
          canBePlaced=false;
        }
      }
      if(canBePlaced==true)
      {
        gb.sound.playOK();
        for(int i=shipPointX;i<shipPointX+toPlace;i++)
        {
          if(toPlace==2)
          {
            if(destroyers2==3)
            {
             arr[i][shipPointY]=2; 
            }
            else if(destroyers2==2)
            {
              arr[i][shipPointY]=5;
            }
            else
            {
              arr[i][shipPointY]=6; 
            }
          }
          else if(toPlace==3)
          {
            if(cruisers3==2)
            {
              arr[i][shipPointY]=3;
            }
            else
            {
              arr[i][shipPointY]=7; 
            }
          }
          else
          {
            arr[i][shipPointY]=toPlace; 
          }
        }
      }
    }
    else
    {
      for(int i=shipPointY;i<shipPointY+toPlace;i++)
      {
        if(arr[shipPointX][i]!=0)
        {
          gb.sound.playCancel();
          canBePlaced=false;
        }
      }
      if(canBePlaced==true)
      {
        gb.sound.playOK();
        for(int i=shipPointY;i<shipPointY+toPlace;i++)
        {
          if(toPlace==2)
          {
            if(destroyers2==3)
            {
             arr[shipPointX][i]=2; 
            }
            else if(destroyers2==2)
            {
              arr[shipPointX][i]=5;
            }
            else
            {
              arr[shipPointX][i]=6; 
            }
          }
          else if(toPlace==3)
          {
            if(cruisers3==2)
            {
              arr[shipPointX][i]=3;
            }
            else
            {
              arr[shipPointX][i]=7; 
            }
          }
          else
          {
            arr[shipPointX][i]=toPlace; 
          }
        }
      }
    }
    if(canBePlaced==true)
    {
      shipPointX=4;
      shipPointY=4;
      if(toPlace==4)
      {
        battleships4--;
      }
      else if(toPlace==3)
      {
        cruisers3--;
      }
      else if(toPlace==2)
      {
        destroyers2--;
      }
      else if(toPlace==1)
      {
        submarines1--;
      } 
    }
  }
  displayPlacementBoard(arr);

  return false;
}

void infoScreen(int player)
{
  displayTurnInfo(player);
  if((gameMode==1&&playerTurn!=2)||(gameMode==2))
  {
    if(gb.buttons.pressed(BUTTON_A))
    {
      turnInfoScreen=false;
    } 
  }
  else
  {
    if(aiAction==true)
    {
      turnInfoScreen=false;
      aiAction=false;
    }
  }
}

void game()
{
  bool onePress=false; //Only one key A pressed at frame
  if(turnInfoScreen==true)
  {
    infoScreen(playerTurn);
    return;
  }
    if(playerBoard==1)//draw aiming screen
    {
      //---------------------------------------------------
      if((gameMode==1&&playerTurn!=2)||(gameMode==2))
      {
          if(gb.buttons.pressed(BUTTON_DOWN)&&infoLock==false){
            if(row!=9)
            {
              targetPosY+=1;
              row++;
            }
          }
          else if(gb.buttons.pressed(BUTTON_UP)&&infoLock==false){
            if(row!=0)
            {
              targetPosY-=1;
              row--;
            }
          }
          else if(gb.buttons.pressed(BUTTON_LEFT)&&infoLock==false){
            if(column!=0)
            {
              targetPosX-=1;
              column--;
            }
          }
          else if(gb.buttons.pressed(BUTTON_RIGHT)&&infoLock==false){
            if(column!=9)
            {
              targetPosX+=1;
              column++;
            }
          }
          else if(gb.buttons.pressed(BUTTON_A)&&infoLock==false){
            if(playerTurn==1)
            {
              missed=attackShip(PlayerMatrix2); 
            }
            else
            {
              missed=attackShip(PlayerMatrix1);
            }
            onePress=true;
          }
      }
      //---------------------------------------------------

     if(playerTurn==1)
     {
        displayAttackField(PlayerMatrix2,2,fireSeq,P2battleship,P2cruiser,P2destroyer,P2submarine);
     }
     else
     {
        if(gameMode==1)
        {
          if(consoleThinking==false)
          {
            missed=enemyFiring();
            onePress=true;
            consoleThinking=true; 
          }
        }
        displayAttackField(PlayerMatrix1,1,fireSeq,P1battleship,P1cruiser,P1destroyer,P1submarine);
     }
   }
   else //display player fleet screen
   {
    if(playerTurn==1)
    {
      displayPlayerFleet(PlayerMatrix1,fireSeq);
    }
    else
    {
      displayPlayerFleet(PlayerMatrix2,fireSeq); 
    }
   }
   if(gb.buttons.pressed(BUTTON_B)&&infoLock==false)
   {
     if(playerBoard==1)
     {
        playerBoard=2;
     }
     else
     {
        playerBoard=1;
     }
   }
   else if(gb.buttons.pressed(BUTTON_MENU)&&infoLock==false)
   {
      selectorPosX=17;
      selectorPosY=38;
      pauseMode=1;
      gameScreen=false;
      pause=true;
   } 
  
  if(infoLock==true)
  {
    displayInfoLockScreen();
    if((gameMode==1&&playerTurn!=2)||(gameMode==2)) //players control
    {
      if(gb.buttons.pressed(BUTTON_A)&&onePress==false){
        infoLock=false; //unblock
        hitSound=false;

        if(missed) 
        {
          if(playerTurn==1)
          {
            playerTurn=2;
          }
          else
          {
            playerTurn=1;
          }
          targetPosX=0;
          targetPosY=0;
          row=0;
          column=0;
          aiAction=false;
          missed=false;
          turnInfoScreen=true;
        }
        if(checkWinningConditions()==true)
        {
          gameScreen=false;
          winningScreen=true;
        }
      }
    }
    else //AI control
    {
      if(aiAction==true)  
      {
        infoLock=false; //unblock
        hitSound=false;
        if(missed==true)
        {
          playerTurn=1;
          if(consoleThinking==true) {
            consoleThinking=false;
          }
          targetPosX=0;
          targetPosY=0;
          row=0;
          column=0;
          missed=false;
          turnInfoScreen=true;
        }
        else
        {
          if(consoleThinking==true) {
            consoleThinking=false;
          }
          aiAction=false;        
        }
        if(checkWinningConditions()==true)
        {
          gameScreen=false;
          winningScreen=true;
        }
      }
    }
  }
}

bool attackShip(int8_t arr[][10])
{
  bool Missed=false;
    if(arr[targetPosX][targetPosY]<0)
    {
      infoLock=false; //prevent showing info on already shooted field
      return false;
    }     
    else if(arr[targetPosX][targetPosY]==0)//missed
    {
      arr[targetPosX][targetPosY]=-9;
      infoLock=true;
      return true;
    }
    else
    {
      gb.lights.fill(RED);
      infoLock=true;
      int value=arr[targetPosX][targetPosY];
      switch(value)
      {
        case 1:
        {
          if(playerTurn==1)
          {
            P2submarine--; 
          }
          else
          {
            P1submarine--;
          }
          break;
        }
        case 2:
        {
          if(playerTurn==1)
          {
            player2ShipsHP.destroyer2-=1;
            if(player2ShipsHP.destroyer2==0)
            {
              P2destroyer--;
            } 
          }
          else
          {
            player1ShipsHP.destroyer2-=1;
            if(player1ShipsHP.destroyer2==0)
            {
              P1destroyer--;
            } 
          }
          break;
        }
        case 3:
        {
          if(playerTurn==1)
          {
            player2ShipsHP.cruiser3-=1;
            if(player2ShipsHP.cruiser3==0)
            {
              P2cruiser--;
            }  
          }
          else
          {
            player1ShipsHP.cruiser3-=1;
            if(player1ShipsHP.cruiser3==0)
            {
              P1cruiser--;
            }
          }
          break; 
        }
        case 4:
        {
          if(playerTurn==1)
          {
            player2ShipsHP.battleship4-=1;
            if(player2ShipsHP.battleship4==0)
            {
              P2battleship--;
            }  
          }
          else
          {
            player1ShipsHP.battleship4-=1;
            if(player1ShipsHP.battleship4==0)
            {
              P1battleship--;
            } 
          }
          break; 
        }
        case 5:
        {
          if(playerTurn==1)
          {
            player2ShipsHP.destroyer5-=1; 
            if(player2ShipsHP.destroyer5==0)
            {
              P2destroyer--;
            }
          }
          else
          {
            player1ShipsHP.destroyer5-=1; 
            if(player1ShipsHP.destroyer5==0)
            {
              P1destroyer--;
            }
          }
          break;
        }
        case 6:
        {
          if(playerTurn==1)
          {
            player2ShipsHP.destroyer6-=1;
            if(player2ShipsHP.destroyer6==0)
            {
              P2destroyer--;
            }
          }
          else
          {
            player1ShipsHP.destroyer6-=1;
            if(player1ShipsHP.destroyer6==0)
            {
              P1destroyer--;
            }
          }
          break;
        }
        case 7:
        {
          if(playerTurn==1)
          {
            player2ShipsHP.cruiser7-=1;
            if(player2ShipsHP.cruiser7==0)
            {
              P2cruiser--;
            } 
          }
          else
          {
            player1ShipsHP.cruiser7-=1;
            if(player1ShipsHP.cruiser7==0)
            {
              P1cruiser--;
            } 
          }
          break;
        }
      }
      arr[targetPosX][targetPosY]-=(2*value);
      Missed=false;
    }
  return Missed;
}

bool checkHits(int hitValue, int player)
{
  bool result=false;
  switch(hitValue)
  {
    case -1:
    {
      result=true;
      break;
    }
    case -2:
    {
      if(player==1)
      {
        if(player1ShipsHP.destroyer2==0)
        {
          result=true;
        } 
      }
      else
      {
        if(player2ShipsHP.destroyer2==0)
        {
          result=true;
        } 
      }
      break;
    }
    case -3:
    {
      if(player==1)
      {
        if(player1ShipsHP.cruiser3==0)
        { 
          result=true;
        } 
      }
      else
      {
        if(player2ShipsHP.cruiser3==0)
        { 
          result=true;
        } 
      }
      break;
    }
    case -4:
    {
      if(player==1)
      {
        if(player1ShipsHP.battleship4==0)
        {
          result=true;
        } 
      }
      else
      {
        if(player2ShipsHP.battleship4==0)
        {
          result=true;
        } 
      }
      break;
    }
    case -5:
    {
      if(player==1)
      {
        if(player1ShipsHP.destroyer5==0)
        {
          result=true;
        } 
      }
      else
      {
        if(player2ShipsHP.destroyer5==0)
        {
          result=true;
        }
      }
      break;
    }
    case -6:
    {
      if(player==1)
      {
        if(player1ShipsHP.destroyer6==0)
        {
          result=true;
        }
      }
      else
      {
        if(player2ShipsHP.destroyer6==0)
        {
          result=true;
        }
      }
      break;
    }
    case -7:
    {
      if(player==1)
      {
        if(player1ShipsHP.cruiser7==0)
        {
          result=true;
        } 
      }
      else
      {
        if(player2ShipsHP.cruiser7==0)
        {
          result=true;
        } 
      }
      break;
    }
  }
  return result;
}

bool checkWinningConditions()
{
  if(P1battleship==0 && P1cruiser==0 && P1destroyer==0 && P1submarine==0)
  {
    return true;
  }
  else if(P2battleship==0 && P2cruiser==0 && P2destroyer==0 && P2submarine==0)
  {
    return true;
  }
  else
  {
    return false;
  }
}
