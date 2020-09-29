#ifndef MAINAPP_H
#define MAINAPP_H

//--------------------------------------------------------------------------------

#include <string>
#include <sstream>
#include <ctime>
#include <cmath>
#include <vector>
#include "SDL_tools.h"
#include "GUI.h"
#include "GFX.h"
#include "GAM.h"
#include "APP.h"

//--------------------------------------------------------------------------------

#define MAX_FPS 20 // maksymalna liczba fps

#define TILE_WIDTH  68 // szerokosc pola
#define TILE_HEIGHT 34 // wysokosc pola

//--------------------------------------------------------------------------------

// typ wyliczeniowy rodzaju budowania
enum GAM_BuildType { BLD_NONE = -1, BLD_TRACKL = 0, BLD_TRACKR =  1, BLD_TRACKH = 2, BLD_TRACKV = 3, BLD_CLEAR = 4, BLD_GRASS = 5, BLD_ROCK = 6,
   BLD_WATER = 7, BLD_PATH = 8, BLD_ANY = 9, BLD_OBJECT = 10, BLD_STATION = 11, BLD_TRAIN = 12 };

//--------------------------------------------------------------------------------

// callback przycisków w oknie budowania
void BuildButtonClick(GUI_Button *target, void *param);

void PlaceMarkerButtonClick(GUI_Button *target, void *param);

void BuildPathButtonClick(GUI_Button *target, void *param);

void GenerateMapButtonClick(GUI_Button *target, void *param);

void PlaceStationButtonClick(GUI_Button *target, void *param);

void PlaceTrainMarkerButtonClick(GUI_Button *target, void *param);

void BuildTrainButtonClick(GUI_Button *target, void *param);

void MenuButtonClick(GUI_Button *target, void *param);

void OnWindowClose(GUI_Window *target, void *param);

//--------------------------------------------------------------------------------

class MainApp
{
public:

   bool quit; // flaga zakonczenia wykonywania programu

   GAM_BuildType buildType; // aktualny typ budowania
   GAM_SearchAlgorithm algorithm; // aktualny algorytm wyszukiwania sciezki
   int currSprite; // aktualne id sprite'a przy budowaniu

   GUI_WindowManager wndMng; // manager okien

   APP_AutoBuilderWindow *wndAuto;
   APP_GenerateWindow *wndGen;
   APP_BuildWindow *wndBuild;
   APP_InfoWindow *wndInfo;
   APP_StationWindow *wndStation;
   APP_TrainWindow *wndTrain;

   std::vector<GAM_MapTile*> currPath;
   bool clicked;
   bool isMapReady;

   GAM_Map *pMap;

   std::vector<GAM_Train*> trains;

   MainApp();
   ~MainApp();

   // uruchomienie aplikacji
   int Run();

   void ChangeBuildType(GAM_BuildType type);

   void CleanPath();
};

//--------------------------------------------------------------------------------

#endif