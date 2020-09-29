#include "MainApp.h"

//--------------------------------------------------------------------------------

MainApp::MainApp()
{
   wndAuto = NULL;
   wndGen = NULL;
   wndBuild = NULL;
   wndInfo = NULL;
   wndStation = NULL;
   wndTrain = NULL;
   pMap = NULL;
}

//--------------------------------------------------------------------------------

MainApp::~MainApp()
{
   delete wndAuto;
   wndAuto = NULL;

   delete wndGen;
   wndGen = NULL;

   delete wndBuild;
   wndBuild = NULL;

   delete wndStation;
   wndStation = NULL;

   delete wndTrain;
   wndTrain = NULL;

   delete pMap;
   pMap = NULL;
}

//--------------------------------------------------------------------------------

int MainApp::Run()
{
   int currTick; // wartosc odliczania licznika fps

   int i, ww, hh;
   int width, height; // szerokosc i wysokosc obszaru roboczego
   int mouseX = 0, mouseY = 0, oldX = 0, oldY = 0; // pozycje myszy
   int oldI = 0, oldJ = 0; // znormalizowane pozycje myszy na mapie

   int cursor = -1; // ikona przy kursorze

   bool check = true;
   bool init = true; // flaga pierwszego przejscia petli programu
   quit = false;

   int MAP_SIZE = 200; // wielkosc mapy
   isMapReady = false;

   buildType = BLD_NONE; // aktualny typ budowania
   algorithm = FND_CHEAPEST; // aktualny algorytm wyszukiwania sciezki
   currSprite = SPR_ROADL; // aktualne id sprite'a przy budowaniu

   bool leftClicked = false; // lewy przycisk myszy wcisniety
   bool rightClicked = false; // ppm wcisniety

   bool leftPress = false;
   bool rightPress = false;
   bool upPress = false;
   bool downPress = false;

   SDL_Surface *screen = NULL; // powierzchnia ekranu
   SDL_Surface *theme = NULL; // powierzchnia motywu okienek
   SDL_Surface *sprites = NULL; // powierzchnia sprite'ow
   SDL_Surface *game = NULL; // powierzchnia pola gry

   SDL_Event event; // zdarzenie programu

   TTF_Font *font = NULL; // czcionka domyslna

   GFX_SpriteManager sprMng; // manager sprite'ow
   GFX_Tweener tweener; // tweener animacji

   std::stringstream str; // strumien lancuchow znakowych

   srand((int)time(NULL)); // inicjalizacja randomizera

   if(SDL_Init(SDL_INIT_EVERYTHING) == -1) // inicjalizacja SDL
      return 1;

   if(TTF_Init() == -1) // inicjalizacja TTF
      return 1;

   screen = SDL_SetVideoMode(0, 0, 32, SDL_HWSURFACE | SDL_FULLSCREEN); // utworzenie powierzchni ekranowej
   if(NULL == screen)
      return 1;
   width = screen->clip_rect.w; // pobranie rozmiarow powierzchni
   height = screen->clip_rect.h;

   SDL_WM_SetCaption("SDL window engine test", NULL); // ustawienie tytulu okna

   theme = LoadImage("theme.png"); // zaladowanie motywu okien
   if(NULL == theme)
      return 1;

   sprites = LoadImage("sprites.png"); // zaladowanie grafiki sprite'ow
   if(NULL == sprites)
      return 1;

   font = TTF_OpenFont("font.ttf", 10); // zaladowanie czcionki
   if(NULL == font)
      return 1;

   if(!sprMng.Load("sprites.txt")) // zaladowanie listy sprite'ow
      return 1;

   game = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32, 0, 0, 0, 0); // utworzenie powierzchni gry
   if(NULL == game)
      return 1;

   // utworzenie kursora z zegarkiem
   Uint8 mask[] = { 0x1F, 0x80, 0x3F, 0xC0, 0x3F, 0xC0, 0x3F, 0xC0, 0x7F, 0xE0, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xF0, 0xFF, 0xF0, 0x7F, 0xE0, 0x3F, 0xC0, 0x3F, 0xC0, 0x3F, 0xC0, 0x1F, 0x80 };
   Uint8 data[] = { 0x00, 0x00, 0x1F, 0x80, 0x1F, 0x80, 0x1F, 0x80, 0x20, 0x40, 0x44, 0x20, 0x44, 0x20, 0x44, 0x20, 0x47, 0x20, 0x40, 0x20, 0x40, 0x20, 0x20, 0x40, 0x1F, 0x80, 0x1F, 0x80, 0x1F, 0x80, 0x00, 0x00 };
   SDL_Cursor *defCur = SDL_GetCursor(); // pobranie domyslnego kursora
   SDL_Cursor *waitCur = SDL_CreateCursor(data, mask, 16, 16, 0, 0); // utworzenie zegarka

   wndMng.SetDefaults(theme, font, width, height); // ustawienie domyslnych wartosci managera okien

   SDL_Color color = {0x00, 0x00, 0x00}; // kolor czarny
   SDL_Color cGrey = ColorRGB(0xcf, 0xcf, 0xcf);

   wndInfo = new APP_InfoWindow(10, height-90, theme, font); // utworzenie okna informacji o polu
   wndInfo->visible = false;

   wndBuild = new APP_BuildWindow(width/2-145, 0, theme, font, &sprMng); // okno budowania
   //wndBuild->visible = false;
   wndBuild->AddButtonCallbacks(BuildButtonClick, this);

   APP_MenuWindow menu(-2, -15, theme, font, &sprMng);
   menu.AddMenuCallbacks(MenuButtonClick, this);

   wndGen = new APP_GenerateWindow(width/2-90, height/2-95, theme, font);
   wndGen->genBtn->AddCallback(GenerateMapButtonClick, this);
   wndMng.AddWindow(wndGen);

   wndAuto = new APP_AutoBuilderWindow(width/2-103, height/2-129, theme, font);
   wndAuto->visible = false;
   wndAuto->placeBtn->AddCallback(PlaceMarkerButtonClick, this);
   wndAuto->buildBtn->AddCallback(BuildPathButtonClick, this);

   wndStation = new APP_StationWindow(0, 0, theme, font, &sprMng);
   wndStation->visible = false;
   wndStation->placeBtn->AddCallback(PlaceStationButtonClick, this);

   wndTrain = new APP_TrainWindow(0, 0, theme, font);
   wndTrain->visible = false;
   wndTrain->placeBtn->AddCallback(PlaceTrainMarkerButtonClick, this);
   wndTrain->buildBtn->AddCallback(BuildTrainButtonClick, this);

   FPSmanager fps; // regulator fps
   SDL_initFramerate(&fps); // inicjalizacja fps

   while(!isMapReady && !quit)
   {
      while(SDL_PollEvent(&event)) // petla pobierajaca zdarzenia
      {
         wndMng.ProcessEvent(&event); // przetworzenie zdarzen przez managera

         switch(event.type) // sprawdzenie typu zdarzenia
         {
         case SDL_KEYDOWN: // wcisniety klawisz
            if(event.key.keysym.sym == SDLK_ESCAPE) // wcisniety escape, wyjscie z programu
               quit = true;
            break;      

         case SDL_QUIT: // wyjscie z programu
            quit = true;
            break;
         }
      }

      SDL_FillRect(screen, &(screen->clip_rect), SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)); // wypelnienie ekranu czarnym kolorem

      wndMng.RenderAll(screen); // renderowanie okien

      if(SDL_Flip(screen) == -1) // przewrocenie powierzchni ekranu
         return 1;

      SDL_framerateDelay(&fps); // ograniczenie fps
   }

   MAP_SIZE = wndGen->sizeNum->GetValue();

   int cx = (width-TILE_WIDTH)/2; // wyliczenie poczatkowego punktu mapy
   int cy = (height-(MAP_SIZE+1)*TILE_HEIGHT)/2;

   wndAuto->AddCloseCallback(OnWindowClose, this);
   wndBuild->AddCloseCallback(OnWindowClose, this);
   wndInfo->AddCloseCallback(OnWindowClose, this);
   wndStation->AddCloseCallback(OnWindowClose, this);
   wndTrain->AddCloseCallback(OnWindowClose, this);

   wndMng.AddWindow(&menu);
   wndMng.AddWindow(wndBuild);
   wndMng.AddWindow(wndInfo);
   wndMng.AddWindow(wndAuto);
   wndMng.AddWindow(wndStation);
   wndMng.AddWindow(wndTrain);

   pMap = new GAM_Map(MAP_SIZE, width, height, TILE_WIDTH, TILE_HEIGHT, &sprMng); // utworzenie mapy
   GAM_Map &map = *pMap;

   GenerateCities(map, MAP_SIZE, wndGen->cityNum->GetValue());
   autofill(map, MAP_SIZE, wndGen->waterNum->GetValue()*10, 10, 15, SPR_WATER, false, COST_WATER); // zapelnienie mapy losowym terenem
   autofill(map, MAP_SIZE, wndGen->rockNum->GetValue()*2, 5, 10, SPR_ROCK, false, COST_ROCK);
   autofill(map, MAP_SIZE, wndGen->treeNum->GetValue()*10, 10, 15, SPR_TREES1, true, COST_TREES, 4);

   GAM_AStar astar(&map); // obiekt wyszukujacy sciezki
   std::vector<GAM_MapTile*> path; // wektor na pola sciezki
   clicked = false; // wybrany pierwszy punkt sciezki
   int fx = 0, fy = 0; // wspolrzednie pierwszego punktu

   //GAM_Train train(SPR_LOCO1, 94, 94, 20, 4, pMap, TILE_HEIGHT, true); // pociag
   //map.AddRailArea(1, 92, 94, -18, 0);

   GUI_Notifier notifier(width, 60, &tweener, theme, font); // wyswietlacz powiadomien
   notifier.Notify("Welcome! Project v0.1"); // wyswietlenie powiadomienia z powitaniem

   int xx = 0, yy = 0, ox = 0, oy = 0;

   //SDL_ShowCursor(SDL_DISABLE);

   while(!quit) // petla glowna programu
   {
      currTick = SDL_GetTicks();

      //SDL_GetMouseState(&mouseX, &mouseY);

      xx = -((mouseX-TILE_WIDTH/2-cx)/2+cy-mouseY); // wyliczenie pozycji myszy w izometrii
      yy = ((mouseX-TILE_WIDTH/2-cx)/2-cy+mouseY);
      ox = xx/TILE_HEIGHT; // znormalizowanie pozycji
      oy = yy/TILE_HEIGHT;

      if(map.CheckBounds(ox, oy)) // kursor znajduje sie w granicach mapy
      {
         str.str(""); // wyczyszczenie strumienia
         str << "x: " << map[ox][oy].x << " y: " << map[ox][oy].y; // wpisanie tekstu do strumienia
         wndInfo->txt1->SetText(str.str()); // ustawienie tekstu w polu tekstowym
         str.str("");
         str << "cost: " << map[ox][oy].cost << "$";
         wndInfo->txt2->SetText(str.str());
      }
      else
      {
         wndInfo->txt1->SetText("No tile.");
         wndInfo->txt2->SetText("");
      }

      while(SDL_PollEvent(&event)) // petla pobierajaca zdarzenia
      {
         wndMng.ProcessEvent(&event); // przetworzenie zdarzen przez managera

         switch(event.type) // sprawdzenie typu zdarzenia
         {
         case SDL_KEYDOWN: // wcisniety klawisz
            if(event.key.keysym.sym == SDLK_ESCAPE) // wcisniety escape, wyjscie z programu
               quit = true;

            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
               quit = true;
               break;

            case SDLK_LEFT:
               leftPress = true;
               break;

            case SDLK_RIGHT:
               rightPress = true;
               break;

            case SDLK_UP:
               upPress = true;
               break;

            case SDLK_DOWN:
               downPress = true;
               break;
            }
            break;

         case SDL_KEYUP:
            switch(event.key.keysym.sym)
            {
            case SDLK_LEFT:
               leftPress = false;
               break;

            case SDLK_RIGHT:
               rightPress = false;
               break;

            case SDLK_UP:
               upPress = false;
               break;

            case SDLK_DOWN:
               downPress = false;
               break;
            }
            break;

         case SDL_MOUSEBUTTONDOWN: // wcisniety przycisk myszy
            if(event.button.button == SDL_BUTTON_RIGHT) // ppm
            {
               rightClicked = true;
               oldX = event.motion.x; // zapisanie wspolrzednych
               oldY = event.motion.y;
               //SDL_ShowCursor(SDL_DISABLE); // ukrycie kursora
            }

            // lpm, zadne okno nie jest aktywne, kursor w granicach mapy
            if((event.button.button == SDL_BUTTON_LEFT) && !wndMng.GetFocus() && map.CheckBounds(ox, oy))
            {
               leftClicked = true;
               oldI = ox; // zapisanie znormalizowanych wspolrzednych
               oldJ = oy;
            }
            break;

         case SDL_MOUSEBUTTONUP: // wycisniety przycisk myszy
            if(event.button.button == SDL_BUTTON_RIGHT) // ppm
            {
               rightClicked = false;
               //SDL_ShowCursor(SDL_ENABLE); // pokazanie kursora
            }

            if((event.button.button == SDL_BUTTON_LEFT) && leftClicked) // lpm
            {
               leftClicked = false;

               switch(buildType) // sprawdzenie typu budowania
               {
               case BLD_TRACKL:
                  map.AddRailArea(1, oldI, oldJ, oldI-ox, 0); // wstawienie obszaru z szynami
                  break;

               case BLD_TRACKR: 
                  map.AddRailArea(2, oldI, oldJ, 0, oldJ-oy);
                  break;

               case BLD_TRACKH:
                  map.AddRailArea((mouseY-cy > (ox+oy+1)*TILE_HEIGHT/2) ? 16 : 4, ox, oy, 0, 0);
                  //map(ox, oy).AddRail((mouseY-cy > (ox+oy+1)*TILE_HEIGHT/2) ? 16 : 4); // dodanie szyn do pojedynczego pola
                  break;

               case BLD_TRACKV:
                  map.AddRailArea((mouseX-cx > (oy-ox+1)*TILE_WIDTH/2) ? 8 : 32, ox, oy, 0, 0);
                  //map(ox, oy).AddRail((mouseX-cx > (oy-ox+1)*TILE_WIDTH/2) ? 8 : 32);
                  break;

               case BLD_GRASS:
                  map.AddLandArea(SPR_GRASS, oldI, oldJ, oldI-ox, oldJ-oy, COST_GRASS); // wstawienie pola z trawa
                  break;

               case BLD_ROCK:
                  map.AddLandArea(SPR_ROCK, oldI, oldJ, oldI-ox, oldJ-oy, COST_ROCK); // pole z kamieniami
                  break;

               case BLD_WATER:
                  map.AddLandArea(SPR_WATER, oldI, oldJ, oldI-ox, oldJ-oy, COST_WATER); // pole z woda
                  break;

               /*case BLD_ANY:
                  map.AddLandArea(currSprite, oldI, oldJ, oldI-ox, oldJ-oy, COST_LOCKED); // pole z dowolnym sprite
                  break;*/

               case BLD_CLEAR:
                  map.ClearArea(oldI, oldJ, oldI-ox, oldJ-oy); // wyczyszczenie obszaru
                  break;

               /*case BLD_OBJECT:
                  if(tBtn.IsChecked())
                     map.AddDynamicObject(new GAM_Object(currSprite, xx, yy, TILE_HEIGHT, false)); // dodanie obiektu dynamicznego do mapy
                  else
                     map.AddStaticObject(currSprite, ox, oy); // dodanie obiektu statycznego do mapy
                  break;*/

               case BLD_PATH:
                  if(!clicked) // wybor pierwszego pola sciezki
                  {
                     clicked = true; // ustawienie flagi
                     fx = ox; // zapisanie wspolrzednych
                     fy = oy;
                     for(i = 0; i < path.size(); i++) // wygaszenie pol poprzedniej sciezki
                        path[i]->highlight = -1;
                     map[ox][oy].highlight = SPR_POINT2; // podswietlenie pierwszego pola
                  }
                  else if((fx != ox) || (fy != oy)) // wybor koncowego pola sciezki
                  {
                     SDL_SetCursor(waitCur); // pokazanie zegarka zamiast kursora
                     path = astar.FindPath(fx, fy, ox, oy, (wndAuto->searchList->GetSelection() == 0) ? FND_CHEAPEST : FND_SHORTEST, !wndAuto->omitBtn->IsChecked()); // wyszukanie sciezki
                     SDL_SetCursor(defCur); // pokazanie kursora

                     if(path.size() == 0) // sciezka nie znaleziona
                     {
                        wndMng.ShowAlert("Pathfinder", "Path not found!"); // wyswietlenie alertu
                        notifier.Notify("Path not found!", true);
                     }
                     else // sciezka znaleziona
                     {
                        fx = ox;
                        fy = oy;

                        currPath.pop_back();
                        currPath.insert(currPath.end(), path.begin(), path.end());

                        for(i = 1; i < path.size(); i++)
                           path[i]->highlight = SPR_POINT1;

                           
                        map[ox][oy].highlight = SPR_POINT2;

                        int cost = 0;
                        for(i = 0; i < currPath.size(); i++)
                           cost += currPath[i]->cost;

                        str.str("");
                        str << currPath.size() << " km";
                        wndAuto->distanceInfo->SetText(str.str());

                        str.str("");
                        str << cost << " $";
                        wndAuto->costInfo->SetText(str.str());

                        //train.SetPath(currPath); // ustawienie sciezki pociagu
                     }            
                  }
                  break;

               case BLD_TRAIN:
                  if(!clicked) // wybor pierwszego pola sciezki
                  {
                     if((map[ox][oy].railType == 1) || (map[ox][oy].railType == 2))
                     {
                        clicked = true; // ustawienie flagi
                        fx = ox; // zapisanie wspolrzednych
                        fy = oy;
                        for(i = 0; i < path.size(); i++) // wygaszenie pol poprzedniej sciezki
                           path[i]->highlight = -1;
                        map[ox][oy].highlight = SPR_POINT2; // podswietlenie pierwszego pola
                     }
                     else
                        wndMng.ShowAlert("Error", "Train's path must start\non a straight rail track!");
                  }
                  else if((fx != ox) || (fy != oy)) // wybor koncowego pola sciezki
                  {
                     SDL_SetCursor(waitCur); // pokazanie zegarka zamiast kursora
                     path = astar.FindPath(fx, fy, ox, oy, FND_RAIL); // wyszukanie sciezki
                     SDL_SetCursor(defCur); // pokazanie kursora

                     if(path.size() == 0) // sciezka nie znaleziona
                     {
                        wndMng.ShowAlert("Pathfinder", "Path not found!"); // wyswietlenie alertu
                        notifier.Notify("Path not found!", true);
                     }
                     else // sciezka znaleziona
                     {
                        fx = ox;
                        fy = oy;

                        currPath.pop_back();
                        currPath.insert(currPath.end(), path.begin(), path.end());

                        for(i = 1; i < path.size(); i++)
                           path[i]->highlight = SPR_POINT1;


                        map[ox][oy].highlight = SPR_POINT2;

                        str.str("");
                        str << currPath.size() << " km";
                        wndTrain->distanceInfo->SetText(str.str());
                     }            
                  }
                  break;

               case BLD_STATION:
                  ww = wndStation->lengthNum->GetValue()-1;

                  check = true;
                  for(i = 0; i < ww+1; i++)
                  {
                     int xx = wndStation->orientationList->GetSelection() ? ox : ox+ww/2-i;
                     int yy = wndStation->orientationList->GetSelection() ? oy+ww/2-i : oy;
                     
                     if(!map.CheckBounds(xx, yy))
                        continue;

                     GAM_MapTile &t = map[xx][yy];
                     if((t.cost < 0) || t.hasStation || (t.railType != 0) || (t.landType != SPR_GRASS))
                     {
                        check = false;
                        break;
                     }
                  }

                  if(check)
                  {
                     ww = wndStation->orientationList->GetSelection() ? 0 : wndStation->lengthNum->GetValue()-1;
                     hh = wndStation->orientationList->GetSelection() ? wndStation->lengthNum->GetValue()-1 : 0;
                     map.AddRailArea(wndStation->orientationList->GetSelection()+1, ox + ww/2, oy + hh/2, ww, hh, true);
                  }
                  else
                     wndMng.ShowAlert("Error", "Cannot build a station here!");
                  break;
               }
            }
            break;

         case SDL_MOUSEMOTION: // poruszenie mysza
            mouseX = event.motion.x; // zapisanie wspolrzednych
            mouseY = event.motion.y;

            if(rightClicked) // ppm przytrzymany
            {
               cx += oldX-mouseX; // przesuniecie aktualnego punktu mapy
               cy += oldY-mouseY;
               map.MoveMap(oldX-mouseX, oldY-mouseY); // przesuniecie mapy
               SDL_WarpMouse(oldX, oldY); // powrot kursora na miejsce klikniecia
            }
            break;

         case SDL_QUIT: // wyjscie z programu
            quit = true;
            break;
         }
      }

      if(init) // pierwsze przejscie petli
      {
         init = false;
         tweener.Init(SDL_GetTicks()); // inicjalizacja tweenera
         notifier.Init(SDL_GetTicks()); // incjalizacja powiadomien
      }
      tweener.Step(SDL_GetTicks()); // wykonanie kroku tweenera

      //train.Update(); // aktualizacja pozycji pociagu
      for(i = 0; i < trains.size(); i++)
         if(NULL != trains[i])
            trains[i]->Update();

      SDL_FillRect(screen, &(screen->clip_rect), SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)); // wypelnienie ekranu czarnym kolorem

      SDL_FillRect(game, &(game->clip_rect), SDL_MapRGB(game->format, 0x00, 0x00, 0x00)); // wypelnienie powierzchni gry

      if(leftPress)
      {
         map.MoveMap(20, 0);
         cx += 20;
      }
      if(rightPress)
      {
         map.MoveMap(-20, 0);
         cx -= 20;
      }
      if(upPress)
      {
         map.MoveMap(0, 20);
         cy += 20;
      }
      if(downPress)
      {
         map.MoveMap(0, -20);
         cy -= 20;
      }

      if(buildType == BLD_STATION)
      {
         ww = wndStation->orientationList->GetSelection() ? 0 : wndStation->lengthNum->GetValue()-1;
         hh = wndStation->orientationList->GetSelection() ? wndStation->lengthNum->GetValue()-1 : 0;
         map.SetCursor(true, ox + ww/2, oy + hh/2, ww, hh);
      }
      else if(leftClicked) // lmp wcisniety
      {
         switch(buildType) // sprawdzenie typu budowy
         {
         case BLD_TRACKL:
            map.SetCursor(true, oldI, oldJ, oldI-ox, 0); // ustawienie pionowego obszaru zaznaczenia kursora
            break;

         case BLD_TRACKR:
            map.SetCursor(true, oldI, oldJ, 0, oldJ-oy); // poziomy obszar
            break;

         case BLD_WATER:
         case BLD_GRASS:
         case BLD_ROCK:
         case BLD_CLEAR:
         case BLD_ANY:
            map.SetCursor(true, oldI, oldJ, oldI-ox, oldJ-oy); // prostokatny obszar
            break;

         default:
            map.SetCursor(true, ox, oy); // pojedyncze pole
            break;
         }
      }
      else
         map.SetCursor(true, ox, oy);

      map.Render(game); // renderowanie mapy

      SDL_BlitSurface(game, NULL, screen, NULL); // przekopiowanie powierzchni gry na ekran

      notifier.Render(screen, SDL_GetTicks()); // renderowanie powiadomien

      wndMng.RenderAll(screen); // renderowanie okien

      switch(buildType) // sprawdzenie typu budowy
      {
      case BLD_TRACKL:
         cursor = ICO_TRACKL; // ustawienie ikony przy kursorze
         break;
      case BLD_TRACKR:
         cursor = ICO_TRACKR;
         break;
      case BLD_TRACKH:
         cursor = ICO_TRACKH;
         break;
      case BLD_TRACKV:
         cursor = ICO_TRACKV;
         break;
      case BLD_GRASS:
         cursor = ICO_GRASS;
         break;
      case BLD_ROCK:
         cursor = ICO_ROCK;
         break;
      case BLD_WATER:
         cursor = ICO_WATER;
         break;
      case BLD_CLEAR:
         cursor = ICO_BOMB;
         break;
      default:
         cursor = -1;
         break;
      }

      if(!rightClicked && (cursor > 0)) // ikona przy kursorze aktywna
         sprMng.DrawSprite(cursor, mouseX+15, mouseY+15, screen); // narysowanie ikony przy kursorze
      //sprMng.DrawSprite(ICO_CURSOR, mouseX, mouseY, screen);

      if(SDL_Flip(screen) == -1) // przewrocenie powierzchni ekranu
         return 1;

      SDL_framerateDelay(&fps); // ograniczenie fps
   }

   // zwolnienie powierzchni
   SDL_FreeSurface(game);
   SDL_FreeSurface(screen);
   SDL_FreeSurface(sprites);
   SDL_FreeSurface(theme);

   SDL_FreeCursor(waitCur); // zwolnienie kursora

   TTF_CloseFont(font); // zwolnienie czcionki

   TTF_Quit(); // zakonczenie modulow
   SDL_Quit();

   int siz = trains.size();
   for(i = 0; i < siz; i++)
   {
      delete trains[i];
      trains[i] = NULL;
   }

   //CleanUp();

   return 0;
}

//--------------------------------------------------------------------------------

void MainApp::ChangeBuildType(GAM_BuildType type)
{
   if((buildType == BLD_PATH) && (type != BLD_PATH))
   {
      wndAuto->placeBtn->SetText("Place marker");
      clicked = false;
      CleanPath();
   }

   if((buildType == BLD_TRAIN) && (type != BLD_TRAIN))
   {
      wndTrain->placeBtn->SetText("Place marker");
      clicked = false;
      CleanPath();
   }

   if((buildType == BLD_STATION) && (type != BLD_STATION))
   {
      wndStation->placeBtn->SetText("Place station");
   }

   buildType = type;
}

//--------------------------------------------------------------------------------

void MainApp::CleanPath()
{
   int siz = currPath.size();
   for(int i = 0; i < siz; i++)
      currPath[i]->highlight = -1;
   currPath.clear();
}

//--------------------------------------------------------------------------------

void PlaceMarkerButtonClick(GUI_Button *target, void *param)
{
   MainApp *app = (MainApp*)param;

   if(app->buildType != BLD_PATH)
   {
      app->ChangeBuildType(BLD_PATH);
      app->wndAuto->placeBtn->SetText("Cancel path");
      app->wndAuto->distanceInfo->SetText("0 km");
      app->wndAuto->costInfo->SetText("0 $");
      app->CleanPath();
   }
   else
   {
      app->ChangeBuildType(BLD_NONE);
      app->wndAuto->placeBtn->SetText("Place marker");
      app->clicked = false;
      app->CleanPath();
   }   
}

//--------------------------------------------------------------------------------

void BuildPathButtonClick(GUI_Button *target, void *param)
{
   MainApp *app = (MainApp*)param;
   GAM_Map *map = app->pMap;

   for(int i = 0; i < app->currPath.size(); i++) // przejscie przez wszystkie pola sciezki
   {
      if((i > 0) && (i < app->currPath.size()-1))
      {
         GAM_MapTile *curr = app->currPath[i], *prev = app->currPath[i-1], *next = app->currPath[i+1];

         if((curr->y == prev->y) && (curr->x < prev->x))
            if(next->y < curr->y)
               map->AddRailArea(32, curr->x, curr->y);
            else if(next->y > curr->y)
               map->AddRailArea(16, curr->x, curr->y);
            else
               map->AddRailArea(1, curr->x, curr->y);

            if((curr->y == prev->y) && (curr->x > prev->x))
               if(next->y < curr->y)
                  map->AddRailArea(4, curr->x, curr->y);
               else if(next->y > curr->y)
                  map->AddRailArea(8, curr->x, curr->y);
               else
                  map->AddRailArea(1, curr->x, curr->y);

               if((curr->x == prev->x) && (curr->y < prev->y))
                  if(next->x < curr->x)
                     map->AddRailArea(8, curr->x, curr->y);
                  else if(next->x > curr->x)
                     map->AddRailArea(16, curr->x, curr->y);
                  else
                     map->AddRailArea(2, curr->x, curr->y);

                  if((curr->x == prev->x) && (curr->y > prev->y))
                     if(next->x < curr->x)
                        map->AddRailArea(4, curr->x, curr->y);
                     else if(next->x > curr->x)
                        map->AddRailArea(32, curr->x, curr->y);
                     else
                        map->AddRailArea(2, curr->x, curr->y);
      }
      else if((i == 0) && (i < app->currPath.size()-1))
      {
         GAM_MapTile *curr = app->currPath[i], *next = app->currPath[i+1];

         if(next->x != curr->x)
            map->AddRailArea(1, curr->x, curr->y);
         else
            map->AddRailArea(2, curr->x, curr->y);
      }
      else if((i == app->currPath.size()-1) && (i > 0))
      {
         GAM_MapTile *curr = app->currPath[i], *prev = app->currPath[i-1];

         if(prev->x != curr->x)
            map->AddRailArea(1, curr->x, curr->y);
         else
            map->AddRailArea(2, curr->x, curr->y);
      }
   }

   app->ChangeBuildType(BLD_NONE);
   app->wndAuto->placeBtn->SetText("Place marker");
   app->clicked = false;
   app->CleanPath();
}

//--------------------------------------------------------------------------------

void GenerateMapButtonClick(GUI_Button *target, void *param)
{
   MainApp *app = (MainApp*)param;
   app->isMapReady = true;
   app->wndGen->visible = false;
}

//--------------------------------------------------------------------------------

void PlaceStationButtonClick(GUI_Button *target, void *param)
{
   MainApp *app = (MainApp*)param;

   if(app->buildType != BLD_STATION)
   {
      app->ChangeBuildType(BLD_STATION);
      app->wndStation->placeBtn->SetText("Cancel");
   }
   else
   {
      app->ChangeBuildType(BLD_NONE);
      app->wndStation->placeBtn->SetText("Place station");
   }
}

//--------------------------------------------------------------------------------

// callback przycisków w oknie budowania
void BuildButtonClick(GUI_Button *target, void *param)
{
   MainApp *app = (MainApp*)param;
   app->ChangeBuildType((GAM_BuildType)target->data);
}

//--------------------------------------------------------------------------------

void PlaceTrainMarkerButtonClick(GUI_Button *target, void *param)
{
   MainApp *app = (MainApp*)param;

   if(app->buildType != BLD_TRAIN)
   {
      app->ChangeBuildType(BLD_TRAIN);
      app->wndTrain->placeBtn->SetText("Cancel path");
      app->wndAuto->distanceInfo->SetText("0 km");
      app->CleanPath();
   }
   else
   {
      app->ChangeBuildType(BLD_NONE);
      app->wndTrain->placeBtn->SetText("Place marker");
      app->clicked = false;
      app->CleanPath();
   }
}

//--------------------------------------------------------------------------------

void BuildTrainButtonClick(GUI_Button *target, void *param)
{
   MainApp *app = (MainApp*)param;

   if(app->currPath.size() > 1)
   {
      GAM_MapTile *first = app->currPath[0], *last = app->currPath[app->currPath.size()-1];
      if((first->x != last->x) || (first->y != last->y))
      {
         app->wndMng.ShowAlert("Error", "Train's path must be\na closed loop!");
         return;
      }
      else
      {
         GAM_Train *train = new GAM_Train(SPR_LOCO1, first->x, first->y, app->wndTrain->lengthNum->GetValue(), 4, app->pMap, TILE_HEIGHT, true);
         train->SetPath(app->currPath);
         app->trains.push_back(train);
      }
   }

   app->ChangeBuildType(BLD_NONE);
   app->wndTrain->placeBtn->SetText("Place marker");
   app->clicked = false;
   app->CleanPath();
}

//--------------------------------------------------------------------------------

void MenuButtonClick(GUI_Button *target, void *param)
{
   MainApp *app = (MainApp*)param;
   app->ChangeBuildType(BLD_NONE);

   switch(target->data)
   {
   case MENU_BUILD:
      app->wndMng.FocusWindow(app->wndBuild, !app->wndBuild->visible);
      app->wndBuild->visible = true;
      break;

   case MENU_AUTO:
      app->wndMng.FocusWindow(app->wndAuto, !app->wndAuto->visible);
      app->wndAuto->visible = true;
      break;

   case MENU_STATION:
      app->wndMng.FocusWindow(app->wndStation, !app->wndStation->visible);
      app->wndStation->visible = true;
      break;

   case MENU_TRAIN:
      app->wndMng.FocusWindow(app->wndTrain, !app->wndTrain->visible);
      app->wndTrain->visible = true;
      break;

   case MENU_INFO:
      app->wndMng.FocusWindow(app->wndInfo, !app->wndInfo->visible);
      app->wndInfo->visible = true;
      break;

   case MENU_EXIT:
      app->quit = true;
      break;
   }
}

//--------------------------------------------------------------------------------

void OnWindowClose(GUI_Window *target, void *param)
{
   MainApp *app = (MainApp*)param;
   app->ChangeBuildType(BLD_NONE);
}