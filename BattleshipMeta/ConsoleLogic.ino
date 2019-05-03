

//--------------------------------------Create random board-----------------------
void shipPlacementAi()
{
    int shipsCount=10;
    while(shipsCount>0)
    {
        if(battleships4!=0)
        {
            PlaceShipOnMatrix(4,4);
            battleships4--;
            shipsCount--;
        }
        if(cruisers3!=0)
        {
            if(cruisers3==1)
            {
                PlaceShipOnMatrix(3,3);
            }
            else
            {
                PlaceShipOnMatrix(3,7);
            }
            cruisers3--;
            shipsCount--;
        }
        if(destroyers2!=0)
        {
            if(destroyers2==2)
            {
                PlaceShipOnMatrix(2,2);
            }
            else if(destroyers2==1)
            {
                PlaceShipOnMatrix(2,5);
            }
            else
            {
                PlaceShipOnMatrix(2,6);
            }
            destroyers2--;
            shipsCount--;
        }
        if(submarines1!=0)
        {
            PlaceShipOnMatrix(1,1);
            submarines1--;
            shipsCount--;
        }
    }
}

void PlaceShipOnMatrix(int size,int id)
{
    bool placed=false;
    while(!placed)
    {
        int x=random(0,10);//(rand()%10);
        int y=random(0,10);//(rand()%10);
        int direction=random(0,2);//rand()%2;
        if(PlayerMatrix2[x][y]!=0)
            continue;

        if(direction==1)
        {
            if(x+size<=9)
            {
                bool canBePlaced=true;
                for(int i=x;i<x+size;i++)
                {
                    if(PlayerMatrix2[i][y]!=0)
                    {
                        canBePlaced=false;
                        break;
                    }
                }
                if(canBePlaced==true)
                {
                    for(int i=x;i<x+size;i++)
                    {
                        PlayerMatrix2[i][y]=id;
                    }
                    break;
                }
            }
            else if(x-size>=0)
            {
                bool canBePlaced=true;
                for(int i=x-size;i<x;i++)
                {
                    if(PlayerMatrix2[i][y]!=0)
                    {
                        canBePlaced=false;
                        break;
                    }
                }
                if(canBePlaced==true)
                {
                    for(int i=x-size;i<x;i++)
                    {
                        PlayerMatrix2[i][y]=id;
                    }
                    break;
                }
            }
        }
        else
        {
            if(y+size<=9)
            {
                bool canBePlaced=true;
                for(int i=y;i<y+size;i++)
                {
                    if(PlayerMatrix2[x][i]!=0)
                    {
                        canBePlaced=false;
                        break;
                    }
                }
                if(canBePlaced==true)
                {
                    for(int i=y;i<y+size;i++)
                    {
                        PlayerMatrix2[x][i]=id;
                    }
                    break;
                }
            }
            else if(y-size>=0)
            {
                bool canBePlaced=true;
                for(int i=y-size;i<y;i++)
                {
                    if(PlayerMatrix2[x][i]!=0)
                    {
                        canBePlaced=false;
                        break;
                    }
                }
                if(canBePlaced==true)
                {
                    for(int i=y-size;i<y;i++)
                    {
                        PlayerMatrix2[x][i]=id;
                    }
                    break;
                }
            }
        }
    }
}

//--------------------------------------Attack enemy ship-----------------------
int findEmptySlot()
{
    int Result=0;
    for(int i=0;i<10;i++)
    {
        if(EnemyHitsCache[i].activeFight==false)
        {
            Result=i;
            break;
        }
    }
    return Result;
}

void setBattleSlot(int shipId,int x,int y)
{
    int slotIndex=findEmptySlot();
    switch(shipId)
    {
        case 2:
            EnemyHitsCache[slotIndex].activeFight=true;
            EnemyHitsCache[slotIndex].enemySize=2;
            EnemyHitsCache[slotIndex].shipId=shipId;
            EnemyHitsCache[slotIndex].posX=x;
            EnemyHitsCache[slotIndex].posY=y;
            EnemyHitsCache[slotIndex].damage=1;
            break;
        case 3:
            EnemyHitsCache[slotIndex].activeFight=true;
            EnemyHitsCache[slotIndex].enemySize=3;
            EnemyHitsCache[slotIndex].shipId=shipId;
            EnemyHitsCache[slotIndex].posX=x;
            EnemyHitsCache[slotIndex].posY=y;
            EnemyHitsCache[slotIndex].damage=1;
            break;
        case 4:
            EnemyHitsCache[slotIndex].activeFight=true;
            EnemyHitsCache[slotIndex].enemySize=4;
            EnemyHitsCache[slotIndex].shipId=shipId;
            EnemyHitsCache[slotIndex].posX=x;
            EnemyHitsCache[slotIndex].posY=y;
            EnemyHitsCache[slotIndex].damage=1;
            break;
        case 5:
            EnemyHitsCache[slotIndex].activeFight=true;
            EnemyHitsCache[slotIndex].enemySize=2;
            EnemyHitsCache[slotIndex].shipId=shipId;
            EnemyHitsCache[slotIndex].posX=x;
            EnemyHitsCache[slotIndex].posY=y;
            EnemyHitsCache[slotIndex].damage=1;
            break;
        case 6:
            EnemyHitsCache[slotIndex].activeFight=true;
            EnemyHitsCache[slotIndex].enemySize=2;
            EnemyHitsCache[slotIndex].shipId=shipId;
            EnemyHitsCache[slotIndex].posX=x;
            EnemyHitsCache[slotIndex].posY=y;
            EnemyHitsCache[slotIndex].damage=1;
            break;
        case 7:
            EnemyHitsCache[slotIndex].activeFight=true;
            EnemyHitsCache[slotIndex].enemySize=3;
            EnemyHitsCache[slotIndex].shipId=shipId;
            EnemyHitsCache[slotIndex].posX=x;
            EnemyHitsCache[slotIndex].posY=y;
            EnemyHitsCache[slotIndex].damage=1;
            break;
    }
}

bool huntingMode(int currentFight)
{
    bool HuntingResult=true;
    int direction=EnemyHitsCache[currentFight].direction;
    int posX=EnemyHitsCache[currentFight].posX;
    int posY=EnemyHitsCache[currentFight].posY;
    bool fieldDetermined=false;
    while(!fieldDetermined)
    {
        if(direction==1)    //north
        {
            if(EnemyHitsCache[currentFight].posX>0) //check if north field exists
            {
                if(PlayerMatrix1[posX-1][posY]==0) // if field is empty (missed)
                {
                   PlayerMatrix1[posX-1][posY]=-9;
                   if(EnemyHitsCache[currentFight].damage>1) // if ship is vertical line set south (3)
                    {
                        EnemyHitsCache[currentFight].posX+=(EnemyHitsCache[currentFight].damage-1); //modify posX to set field to the south
                        EnemyHitsCache[currentFight].direction=3;
                    }
                    else // if AI does not know ship shape
                    {
                        EnemyHitsCache[currentFight].direction=2;
                    }
                    targetPosX=posX-1;
                    targetPosY=posY;
                    HuntingResult=false;
                    break;
                }
                else if(PlayerMatrix1[posX-1][posY]<0) //if field was already shot
                {
                    if(EnemyHitsCache[currentFight].damage>1) // if ship is vertical line set south (3)
                    {
                        EnemyHitsCache[currentFight].posX+=(EnemyHitsCache[currentFight].damage-1); //modify posX to set field to the south
                        EnemyHitsCache[currentFight].direction=3;
                        posX+=(EnemyHitsCache[currentFight].damage-1);
                        direction=3;
                        continue;
                    }
                    else // if AI does not know ship shape
                    {
                        EnemyHitsCache[currentFight].direction=2;
                        direction=2;
                        continue;
                    }
                }
                else if(PlayerMatrix1[posX-1][posY]>0) // if field is ship space
                {
                  gb.lights.fill(RED);
                  if(PlayerMatrix1[posX-1][posY]==EnemyHitsCache[currentFight].shipId) //if AI hit hunted ship
                  {
                      PlayerMatrix1[posX-1][posY]=PlayerMatrix1[posX-1][posY]-2*PlayerMatrix1[posX-1][posY];

                      EnemyHitsCache[currentFight].posX--;
                      EnemyHitsCache[currentFight].damage++;
                      targetPosX=posX-1;
                      targetPosY=posY;
                      break;
                  }
                  else    //if AI hit new ship
                  {
                      if(PlayerMatrix1[posX-1][posY]==1) //destroy 1 field ship
                      {
                          PlayerMatrix1[posX-1][posY]=-1;
                          P1submarine--;
                      }
                      else //Add new slot
                      {
                          setBattleSlot(PlayerMatrix1[posX-1][posY],posX-1,posY);
                          PlayerMatrix1[posX-1][posY]=PlayerMatrix1[posX-1][posY]-2*PlayerMatrix1[posX-1][posY];
                      }
                      if(EnemyHitsCache[currentFight].damage>1) // if ship is vertical line set south (3)
                      {
                          EnemyHitsCache[currentFight].posX+=(EnemyHitsCache[currentFight].damage-1); //modify posX to set field to the south
                          EnemyHitsCache[currentFight].direction=3;
                      }
                      else // if AI does not know ship shape
                      {
                          EnemyHitsCache[currentFight].direction=2;
                      }
                      targetPosX=posX-1;
                      targetPosY=posY;
                      break;
                  }
                }
            }
            else //north field does not exist
            {
                if(EnemyHitsCache[currentFight].damage>1)
                {
                    EnemyHitsCache[currentFight].posX+=(EnemyHitsCache[currentFight].damage-1); //modify posX to set field to the south
                    EnemyHitsCache[currentFight].direction=3;
                    posX+=(EnemyHitsCache[currentFight].damage-1);
                    direction=3;
                    continue;
                }
                else
                {
                    EnemyHitsCache[currentFight].direction=2;
                    direction=2;
                    continue;
                }
            }
        }
        else if(direction==3) //south
        {
             if(EnemyHitsCache[currentFight].posX<9) //check if south field exists
            {
                if(PlayerMatrix1[posX+1][posY]==0) // if field is empty (missed)
                {
                   PlayerMatrix1[posX+1][posY]=-9;
                   if(EnemyHitsCache[currentFight].damage>1) // if ship is vertical line set north (1)
                    {
                        EnemyHitsCache[currentFight].posX-=(EnemyHitsCache[currentFight].damage-1); //modify posX to set field to the north
                        EnemyHitsCache[currentFight].direction=1;
                    }
                    else // if AI does not know ship shape
                    {
                        EnemyHitsCache[currentFight].direction=4;
                    }
                    targetPosX=posX+1;
                    targetPosY=posY;
                    HuntingResult=false;
                    break;
                }
                else if(PlayerMatrix1[posX+1][posY]<0) //if field was already shot
                {
                    if(EnemyHitsCache[currentFight].damage>1) // if ship is vertical line set north (1)
                    {
                        EnemyHitsCache[currentFight].posX-=(EnemyHitsCache[currentFight].damage-1); //modify posX to set field to the north
                        EnemyHitsCache[currentFight].direction=1;
                        posX-=(EnemyHitsCache[currentFight].damage-1);
                        direction=1;
                        continue;
                    }
                    else // if AI does not know ship shape
                    {
                        EnemyHitsCache[currentFight].direction=4;
                        direction=4;
                        continue;
                    }
                }
                else if(PlayerMatrix1[posX+1][posY]>0) // if field is ship space
                {
                  gb.lights.fill(RED);
                  if(PlayerMatrix1[posX+1][posY]==EnemyHitsCache[currentFight].shipId) //if AI hit hunted ship
                  {
                      PlayerMatrix1[posX+1][posY]=PlayerMatrix1[posX+1][posY]-2*PlayerMatrix1[posX+1][posY];

                      EnemyHitsCache[currentFight].posX++;
                      EnemyHitsCache[currentFight].damage++;
                      targetPosX=posX+1;
                      targetPosY=posY;
                      break;
                  }
                  else    //if AI hit new ship
                  {
                      if(PlayerMatrix1[posX+1][posY]==1) //destroy 1 field ship
                      {
                          PlayerMatrix1[posX+1][posY]=-1;
                          P1submarine--;
                      }
                      else //Add new slot
                      {
                          setBattleSlot(PlayerMatrix1[posX+1][posY],posX+1,posY);
                          PlayerMatrix1[posX+1][posY]=PlayerMatrix1[posX+1][posY]-2*PlayerMatrix1[posX+1][posY];
                      }
                      PlayerMatrix1[posX+1][posY]=-9;
                      if(EnemyHitsCache[currentFight].damage>1) // if ship is vertical line set north (1)
                      {
                          EnemyHitsCache[currentFight].posX-=(EnemyHitsCache[currentFight].damage-1); //modify posX to set field to the north
                          EnemyHitsCache[currentFight].direction=1;
                      }
                      else // if AI does not know ship shape
                      {
                          EnemyHitsCache[currentFight].direction=4;
                      }
                      targetPosX=posX+1;
                      targetPosY=posY;
                      break;
                  }
                }
            }
            else //north field does not exist
            {
                if(EnemyHitsCache[currentFight].damage>1)
                {
                    EnemyHitsCache[currentFight].posX-=(EnemyHitsCache[currentFight].damage-1); //modify posX to set field to the north
                    EnemyHitsCache[currentFight].direction=1;
                    posX-=(EnemyHitsCache[currentFight].damage-1);
                    direction=1;
                    continue;
                }
                else
                {
                    EnemyHitsCache[currentFight].direction=4;
                    direction=4;
                    continue;
                }
            }
        }
        else if(direction==2) //west
        {
            if(EnemyHitsCache[currentFight].posY>0) //check if north field exists
            {
                if(PlayerMatrix1[posX][posY-1]==0) // if field is empty (missed)
                {
                   PlayerMatrix1[posX][posY-1]=-9;
                   if(EnemyHitsCache[currentFight].damage>1) // if ship is horizontal line set east (4)
                    {
                        EnemyHitsCache[currentFight].posY+=(EnemyHitsCache[currentFight].damage-1); //modify posX to set field to the east
                        EnemyHitsCache[currentFight].direction=4;
                    }
                    else // if AI does not know ship shape
                    {
                        EnemyHitsCache[currentFight].direction=3;
                    }
                    targetPosX=posX;
                    targetPosY=posY-1;
                    HuntingResult=false;
                    break;
                }
                else if(PlayerMatrix1[posX][posY-1]<0) //if field was already shot
                {
                    if(EnemyHitsCache[currentFight].damage>1) // if ship is horizontal line set east (4)
                    {
                        EnemyHitsCache[currentFight].posY+=(EnemyHitsCache[currentFight].damage-1); //modify posY to set field to the east
                        EnemyHitsCache[currentFight].direction=4;
                        posY+=(EnemyHitsCache[currentFight].damage-1);
                        direction=4;
                        continue;
                    }
                    else // if AI does not know ship shape
                    {
                        EnemyHitsCache[currentFight].direction=3;
                        direction=3;
                        continue;
                    }
                }
                else if(PlayerMatrix1[posX][posY-1]>0) // if field is ship space
                {
                  gb.lights.fill(RED);
                  if(PlayerMatrix1[posX][posY-1]==EnemyHitsCache[currentFight].shipId) //if AI hit hunted ship
                  {
                      PlayerMatrix1[posX][posY-1]=PlayerMatrix1[posX][posY-1]-2*PlayerMatrix1[posX][posY-1];

                      EnemyHitsCache[currentFight].posY--;
                      EnemyHitsCache[currentFight].damage++;
                      targetPosX=posX;
                      targetPosY=posY-1;
                      break;
                  }
                  else    //if AI hit new ship
                  {
                      if(PlayerMatrix1[posX][posY-1]==1) //destroy 1 field ship
                      {
                          PlayerMatrix1[posX][posY-1]=-1;
                          P1submarine--;
                      }
                      else //Add new slot
                      {
                          setBattleSlot(PlayerMatrix1[posX][posY-1],posX,posY-1);
                          PlayerMatrix1[posX][posY-1]=PlayerMatrix1[posX][posY-1]-2*PlayerMatrix1[posX][posY-1];
                      }
                      if(EnemyHitsCache[currentFight].damage>1) // if ship is horizontal line set east (4)
                      {
                          EnemyHitsCache[currentFight].posY+=(EnemyHitsCache[currentFight].damage-1); //modify posX to set field to the east
                          EnemyHitsCache[currentFight].direction=4;
                      }
                      else // if AI does not know ship shape
                      {
                          EnemyHitsCache[currentFight].direction=3;
                      }
                      targetPosX=posX;
                      targetPosY=posY-1;
                      break;
                  }
                }
            }
            else //west field does not exist
            {
                if(EnemyHitsCache[currentFight].damage>1)
                {
                    EnemyHitsCache[currentFight].posY+=(EnemyHitsCache[currentFight].damage-1); //modify posY to set field to the east
                    EnemyHitsCache[currentFight].direction=4;
                    posY+=(EnemyHitsCache[currentFight].damage-1);
                    direction=4;
                    continue;
                }
                else
                {
                    EnemyHitsCache[currentFight].direction=3;
                    direction=3;
                    continue;
                }
            }
        }
        else //east
        {
            if(EnemyHitsCache[currentFight].posY<9) //check if east field exists
            {
                if(PlayerMatrix1[posX][posY+1]==0) // if field is empty (missed)
                {
                   PlayerMatrix1[posX][posY+1]=-9;
                   if(EnemyHitsCache[currentFight].damage>1) // if ship is horizontal line set west (2)
                    {
                        EnemyHitsCache[currentFight].posY-=(EnemyHitsCache[currentFight].damage-1); //modify posY to set field to the east
                        EnemyHitsCache[currentFight].direction=2;
                    }
                    else // if AI does not know ship shape
                    {
                        EnemyHitsCache[currentFight].direction=1;
                    }
                    targetPosX=posX;
                    targetPosY=posY+1;
                    HuntingResult=false;
                    break;
                }
                else if(PlayerMatrix1[posX][posY+1]<0) //if field was already shot
                {
                    if(EnemyHitsCache[currentFight].damage>1) // if ship is horizontal line set west (2)
                    {
                        EnemyHitsCache[currentFight].posY-=(EnemyHitsCache[currentFight].damage-1); //modify posY to set field to the west
                        EnemyHitsCache[currentFight].direction=2;
                        posY-=(EnemyHitsCache[currentFight].damage-1);
                        direction=2;
                        continue;
                    }
                    else // if AI does not know ship shape
                    {
                        EnemyHitsCache[currentFight].direction=1;
                        direction=1;
                        continue;
                    }
                }
                else if(PlayerMatrix1[posX][posY+1]>0) // if field is ship space
                {
                  gb.lights.fill(RED);
                  if(PlayerMatrix1[posX][posY+1]==EnemyHitsCache[currentFight].shipId) //if AI hit hunted ship
                  {
                      PlayerMatrix1[posX][posY+1]=PlayerMatrix1[posX][posY+1]-2*PlayerMatrix1[posX][posY+1];

                      EnemyHitsCache[currentFight].posY++;
                      EnemyHitsCache[currentFight].damage++;
                      targetPosX=posX;
                      targetPosY=posY+1;
                      break;
                  }
                  else    //if AI hit new ship
                  {
                      if(PlayerMatrix1[posX][posY+1]==1) //destroy 1 field ship
                      {
                          PlayerMatrix1[posX][posY+1]=-1;
                          P1submarine--;
                      }
                      else //Add new slot
                      {
                          setBattleSlot(PlayerMatrix1[posX][posY+1],posX,posY+1);
                          PlayerMatrix1[posX][posY+1]=PlayerMatrix1[posX][posY+1]-2*PlayerMatrix1[posX][posY+1];
                      }
                      if(EnemyHitsCache[currentFight].damage>1) // if ship is horizontal line set west (2)
                      {
                          EnemyHitsCache[currentFight].posY-=(EnemyHitsCache[currentFight].damage-1); //modify posY to set field to the east
                          EnemyHitsCache[currentFight].direction=2;
                      }
                      else // if AI does not know ship shape
                      {
                          EnemyHitsCache[currentFight].direction=1;
                      }
                      targetPosX=posX;
                      targetPosY=posY+1;
                      break;
                  }
                }
            }
            else //west field does not exist
            {
                if(EnemyHitsCache[currentFight].damage>1)
                {
                    EnemyHitsCache[currentFight].posY-=(EnemyHitsCache[currentFight].damage-1); //modify posY to set field to the west
                    EnemyHitsCache[currentFight].direction=2;
                    posY-=(EnemyHitsCache[currentFight].damage-1);
                    direction=2;
                    continue;
                }
                else
                {
                    EnemyHitsCache[currentFight].direction=1;
                    direction=1;
                    continue;
                }
            }
        }
    }
    if(EnemyHitsCache[currentFight].enemySize==EnemyHitsCache[currentFight].damage) //if enemy ship is sinked
    {
       EnemyHitsCache[currentFight].activeFight=false;
       switch(EnemyHitsCache[currentFight].shipId)
       {
        case 2:
            P1destroyer--;
            player1ShipsHP.destroyer2=0;
            break;
        case 3:
            P1cruiser--;
            player1ShipsHP.cruiser3=0;
            break;
        case 4:
            P1battleship--;
            player1ShipsHP.battleship4=0;
            break;
        case 5:
            P1destroyer--;
            player1ShipsHP.destroyer5=0;
            break;
        case 6:
            P1destroyer--;
            player1ShipsHP.destroyer6=0;
            break;
        case 7:
            P1cruiser--;
            player1ShipsHP.cruiser7=0;
            break;
       }
    }

    return HuntingResult;
}

bool enemyFiring()
{
    bool EnemyTurn=true;
    bool Miss=false;
    while(EnemyTurn==true)
    {
        if(P1destroyer==0 && P1cruiser==0 && P1battleship==0 && P1submarine==0)
            break;
        int fightMode=1; //1 - Seeking, 2 - Hunting
        int currentFight=0;
        for(int i=0;i<10;i++)
        {
            if(EnemyHitsCache[i].activeFight==true)
            {
                fightMode=2;
                currentFight=i;
                break;
            }
        }
        if(fightMode==1)
        {
            int x=random(0,10);//(rand()%10);
            int y=random(0,10);//(rand()%10);
            if(PlayerMatrix1[x][y]==0)
            {
              targetPosX=x;
              targetPosY=y;
              PlayerMatrix1[x][y]=-9;
              Miss=true;
              infoLock=true;
              break;
            }
            else if(PlayerMatrix1[x][y]>0)
            {
                targetPosX=x;
                targetPosY=y;
                gb.lights.fill(RED);
                if(PlayerMatrix1[x][y]==1)
                {
                    PlayerMatrix1[x][y]=-1;
                    P1submarine--;
                    infoLock=true;
                    break;
                }
                else if(PlayerMatrix1[x][y]==2)
                {
                    setBattleSlot(2,x,y);
                    PlayerMatrix1[x][y]=-2;
                    infoLock=true;
                    break;
                }
                else if(PlayerMatrix1[x][y]==3)
                {
                    setBattleSlot(3,x,y);
                    PlayerMatrix1[x][y]=-3;
                    infoLock=true;
                    break;
                }
                else if(PlayerMatrix1[x][y]==4)
                {
                    setBattleSlot(4,x,y);
                    PlayerMatrix1[x][y]=-4;
                    infoLock=true;
                    break;
                }
                else if(PlayerMatrix1[x][y]==5)
                {
                    setBattleSlot(5,x,y);
                    PlayerMatrix1[x][y]=-5;
                    infoLock=true;
                    break;
                }
                else if(PlayerMatrix1[x][y]==6)
                {
                    setBattleSlot(6,x,y);
                    PlayerMatrix1[x][y]=-6;
                    infoLock=true;
                    break;
                }
                else if(PlayerMatrix1[x][y]==7)
                {
                    setBattleSlot(7,x,y);
                    PlayerMatrix1[x][y]=-7;
                    infoLock=true;
                    break;
                }
            }
        }
        else
        {
            bool huntingResult=huntingMode(currentFight);
            if(huntingResult==false)
            {
                Miss=true;
            }
            infoLock=true;
            break;
        }
    }

    return Miss;
}
